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

	_button = make_shared<Button>();
	_button->SetScale(Vector2(0.1f, 0.1f));
	_button->SetPosition(Vector2{ 100, WIN_HEIGHT - 100 });
	//_button->SetText("Button");
	_button->SetText("Save");
	_button->SetEvent(std::bind(&CameraScene::SavePos, this));
	_button->SetEventParam(std::bind(&CameraScene::Test, this, placeholders::_1), 5);
}

CameraScene::~CameraScene()
{
}

void CameraScene::Update()
{
	_background->Update();
	_zelda->Update();

	float distance = _zelda->GetTransForm()->GetPos().Distance(_zeldaFollow->GetPos());
	if (distance >= 30.0f)
	{
		_zeldaFollow->GetPos() = LERP(_zeldaFollow->GetPos(), _zelda->GetTransForm()->GetPos(), 0.001f);
	}

	_button->Update();

	Vector2 mP = Camera::GetInstance()->GetMouseWorldPos();
	if (_button->GetRectCollider()->IsCollision(mP))
	{
		_button->GetRectCollider()->SetRed();
	}
	else
	{
		_button->GetRectCollider()->SetGreen();
	}
}

void CameraScene::Render()
{
	_background->Render();
	_zelda->Render();
}

void CameraScene::PostRender()
{
	_zelda->PostRender();
	/*if (ImGui::Button("Save",{ 50, 50 }))
		SavePos();*/
		/*if (_button->GetRectCollider()->IsCollision(MOUSE_WOLRD_POS))
		{
			SavePos();
		}*/

	_button->PostRender();
}

void CameraScene::SavePos()
{
	BinaryWriter writer(L"Save/Zelda");
	vector<float> dataes;

	dataes.push_back(_zelda->GetTransForm()->GetPos().x);
	dataes.push_back(_zelda->GetTransForm()->GetPos().y);

	writer.Uint(dataes.size());
	writer.Uint(dataes.size() * sizeof(float));
	writer.Byte(dataes.data(), sizeof(float) * dataes.size());

}

void CameraScene::Test(int test)
{
	int a = test;
}

Vector2 CameraScene::LoadPos()
{

	BinaryReader reader(L"Save/Zelda");

	UINT size = reader.Uint();
	UINT byteSize = reader.Uint();
	vector<float> dataes;
	dataes.resize(size);

	void* ptr = (void*)dataes.data();
	//reader.Byte(&ptr, sizeof(float) * dataes.size());
	reader.Byte(&ptr, byteSize);

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
