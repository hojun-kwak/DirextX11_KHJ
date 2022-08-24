#include "framework.h"
#include "_2D_Scene.h"

_2D_Scene::_2D_Scene()
{
	_background = make_shared<Quad>(L"Resource/Maple/background2.png");
	_player = make_shared<_2D_Player>();
	_playerFollow = make_shared<Transform>();
	_playerFollow->GetPos() = _player->GetTransForm()->GetPos();

	CameraSetting();

	SOUND->Add("BGM_1", "Resource/Sound/BGM.wav");
	//SOUND->Play("BGM_1", 0.1f);
}

_2D_Scene::~_2D_Scene()
{
}

void _2D_Scene::Update()
{
	_background->Update();
	_player->Update();
	_2D_ObjPManager::GetInstance()->Update();
	float distance = _player->GetTransForm()->GetPos().Distance(_playerFollow->GetPos());
	if (distance >= 30.0f)
	{
		_playerFollow->GetPos() = LERP(_playerFollow->GetPos(), _player->GetTransForm()->GetPos(), 0.001f);
	}
}

void _2D_Scene::Render()
{
	_background->Render();
	_player->Render();
	_2D_ObjPManager::GetInstance()->Render();
}

void _2D_Scene::PostRender()
{
	_player->PostRender();
}

void _2D_Scene::DebugRender()
{
	_player->DebugRender();
	_2D_ObjPManager::GetInstance()->DebugRender();
}

void _2D_Scene::CameraSetting()
{
	Camera::GetInstance()->SetTarget(_player->GetTransForm());
	Vector2 LeftBottom = { -_background->GetHalfSize().x, -_background->GetHalfSize().y };
	Vector2 RightTop = { _background->GetHalfSize().x, _background->GetHalfSize().y };
	Camera::GetInstance()->SetLeftBottom(LeftBottom);
	Camera::GetInstance()->SetRightTop(RightTop);
}
