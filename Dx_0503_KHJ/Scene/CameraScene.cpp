#include "framework.h"
#include "CameraScene.h"

CameraScene::CameraScene()
{
	_background = make_shared<Quad>(L"Resource/LostArk.png");
	//_background->GetTransform()->GetScale() *= 5.0f;

	_zelda = make_shared<Zelda>();

	_zeldaFollow = make_shared<Transform>();
	Vector2 temp = this->LoadPos();
	_zelda->SetPosition(temp.x, temp.y);
	_zeldaFollow->GetPos() = _zelda->GetTransForm()->GetPos();


	Camera::GetInstance()->SetTarget(_zeldaFollow);

	Vector2 LeftBottom = { -_background->GetHalfSize().x, -_background->GetHalfSize().y };
	Vector2 RightTop = { _background->GetHalfSize().x, _background->GetHalfSize().y };
	Camera::GetInstance()->SetLeftBottom(LeftBottom);
	Camera::GetInstance()->SetRightTop(RightTop);

	_button = make_shared<Button>();
	_button->SetScale(Vector2(0.1f, 0.1f));
	_button->SetPosition(Vector2{ 100, WIN_HEIGHT - 100 });
	_button->SetText("Save");
	_button->SetEvent(std::bind(&CameraScene::SavePos, this));
	_button->SetEventParam(std::bind(&CameraScene::Test, this, placeholders::_1), 5);

	// Render Target
	_rtv = make_shared<RenderTarget>(WIN_WIDTH, WIN_HEIGHT);
	_targetTexture = make_shared<Quad>(L"RTV", _background->GetHalfSize());
	shared_ptr<Texture> texture = Texture::Add(L"test", _rtv->GetSRV());
	_targetTexture->SetTexture(texture);
	_targetTexture->GetTransform()->GetPos() = { 0,0 };
	_targetTexture->GetTransform()->GetScale() *= 0.1f;

	_miniPlayer = make_shared<Quad>(L"Resource/cs.png");
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

	// Render Target
	_targetTexture->Update();
	_targetTexture->GetTransform()->GetPos() = Camera::GetInstance()->GetTransform()->GetPos()
		+ Vector2(WIN_WIDTH - _targetTexture->GetHalfSize().x - 300, WIN_HEIGHT - _targetTexture->GetHalfSize().y - 300);
	Vector2 ratio;
	{
		//ratio.x = 
	}

	Vector2 mP = Camera::GetInstance()->GetMouseWorldPos();
	if (_button->GetRectCollider()->IsCollision(mP))
	{
		_button->GetRectCollider()->SetRed();
	}
	else
	{
		_button->GetRectCollider()->SetGreen();
	}

	_miniPlayer->Update();
}

void CameraScene::Render()
{
	_background->Render();
	_zelda->Render();

	// Render Target
	_targetTexture->Render();
}

void CameraScene::PreRender()
{
	// Render Target
	_rtv->Set();
	_miniPlayer->Render();	
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
