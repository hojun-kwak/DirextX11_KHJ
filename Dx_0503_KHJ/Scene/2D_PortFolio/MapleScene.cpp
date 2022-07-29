#include "framework.h"
#include "MapleScene.h"

MapleScene::MapleScene()
{
	_background = make_shared<Quad>(L"Resource/Maple/background2.png");

	_mainTiles = make_shared<Tiles>();
	_mainTiles->SetPosition(Vector2{ 0,0 });

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
	_cursor->SetPosition(CENTER);
}

MapleScene::~MapleScene()
{
}

void MapleScene::Update()
{
	_background->Update();
	_mainTiles->Update();

	//_player->SetPositioning(_mainTiles);
	if (_player->GetCol()->IsCollision(_mainTiles->GetColl(),false))
	{
		_player->GetCol()->SetRed();
	}
	else
		_player->GetCol()->SetGreen();

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
	_player->PostRender();
}

void MapleScene::DebugRender()
{
	_mainTiles->DebugRender();
	_player->DebugRender();
	_cursor->DebugRender();
	_monsters->DebugRender();
	
}
