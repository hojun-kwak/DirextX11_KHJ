#include "framework.h"
#include "CameraScene.h"

CameraScene::CameraScene()
{
	_background = make_shared<Quad>(L"Resource/LostArk.png");
	//_background->GetTransform()->GetScale() *= 5.0f;

	_zelda = make_shared<Zelda>();

	Vector2 temp = LoadPos();
	_zelda->SetPosition(temp.x, temp.y);

	_zeldaFollow = make_shared<Transform>();
	_zeldaFollow->GetPos() = _zelda->GetTransForm()->GetPos();

	Camera::GetInstance()->SetTarget(_zelda->GetTransForm());

	Vector2 LeftBottom = { -_background->GetHalfSize().x, -_background->GetHalfSize().y };
	Vector2 RightTop = { _background->GetHalfSize().x, _background->GetHalfSize().y };
	Camera::GetInstance()->SetLeftBottom(LeftBottom);
	Camera::GetInstance()->SetRightTop(RightTop);

}

CameraScene::~CameraScene()
{
}

void CameraScene::Update()
{
	_background->Update();
	_zelda->Update();
}

void CameraScene::Render()
{
	_background->Render();
	_zelda->Render();
}

void CameraScene::PostRender()
{
	_zelda->PostRender();
	if (ImGui::Button("Save",{ 50, 50 }))
		SavePos();
}

void CameraScene::SavePos()
{
	BinaryWriter writer(L"Save/Zelda");
	vector<float> dataes;

	dataes.push_back(_zelda->GetTransForm()->GetPos().x);
	dataes.push_back(_zelda->GetTransForm()->GetPos().y);

	writer.Uint(dataes.size());
	writer.Byte(dataes.data(), sizeof(float) * dataes.size());
	
}

Vector2 CameraScene::LoadPos()
{

	BinaryReader reader(L"Save/Zelda");

	UINT size = reader.Uint();
	vector<float> dataes;
	dataes.resize(size);

	void* ptr = (void*)dataes.data();
	reader.Byte(&ptr, sizeof(float) * dataes.size());

	Vector2 tempPos;

	if (dataes.size() == 0)
	{
		tempPos = { 0.0f,0.0f };
		return tempPos;
	}

	tempPos.x = dataes[0];
	tempPos.y = dataes[1];

	return tempPos;
}
