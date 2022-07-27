#include "framework.h"
#include "MapleScene.h"

MapleScene::MapleScene()
{
	_background = make_shared<Quad>(L"Resource/Maple/background2.png");

	_mainTiles = make_shared<Tiles>();
	_mainTiles->SetPosition(_background->GetTransform()->GetPos());

	_player = make_shared<MPlayer>();

	_playerFollow = make_shared<Transform>();
	_playerFollow->GetPos() = _player->GetTransForm()->GetPos();

	_monsters = make_shared<Monsters>();

	Camera::GetInstance()->SetTarget(_player->GetTransForm());
	Vector2 LeftBottom = { -_background->GetHalfSize().x, -_background->GetHalfSize().y };
	Vector2 RightTop = { _background->GetHalfSize().x, _background->GetHalfSize().y };
	Camera::GetInstance()->SetLeftBottom(LeftBottom);
	Camera::GetInstance()->SetRightTop(RightTop);

	_cursor = make_shared<Cursors>();
}

MapleScene::~MapleScene()
{
}

void MapleScene::Update()
{
	_background->Update();
	_mainTiles->Update();

	_player->Update();
	_monsters->Update();

	_cursor->Update();
	_cursor->SetPosition(MOUSE_WOLRD_POS);

	float distance = _player->GetTransForm()->GetPos().Distance(_playerFollow->GetPos());
	if (distance >= 30.0f)
	{
		_playerFollow->GetPos() = LERP(_playerFollow->GetPos(), _player->GetTransForm()->GetPos(), 0.001f);
	}
}

void MapleScene::Render()
{
	_background->Render();
	_mainTiles->Render();
	_player->Render();
	_monsters->Render();

	_cursor->Render();
}

void MapleScene::PostRender()
{
	if (KEY_DOWN(VK_F1))
	{
		if (_OnOff == false)
			_OnOff = true;
		else
			_OnOff = false;
	}
	if (_OnOff == true)
	{
		_mainTiles->PostRender();
		_player->PostRender();
		_cursor->PostRender();
		_monsters->PostRender();
	}
}
