#include "framework.h"
#include "MapleScene.h"

MapleScene::MapleScene()
{
	_background = make_shared<Quad>(L"Resource/Maple/background2.png");

	_player = make_shared<MPlayer>();
	/*vector<vector<shared_ptr<Tiles>>> tiles = ObjectPoolingManager::GetInstance()->GetTiles();
	vector<shared_ptr<Rope>> ropes = ObjectPoolingManager::GetInstance()->GetRopes();
	_player->SetTile(tiles);
	_player->SetRope(ropes);
	_player->SetPosition(tiles[0][0]->GetPos().x , tiles[0][0]->GetPos().y + tiles[0][0]->GetQuad()->GetHalfSize().y * 2.0f);*/

	_player->SetPosition(CENTER.x, CENTER.y);

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

	/*_tile = make_shared<Tiles>();
	_tile->SetPosition(CENTER);*/
}

MapleScene::~MapleScene()
{
}

void MapleScene::Update()
{
	_background->Update();
	ObjectPoolingManager::GetInstance()->Update();
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
	ObjectPoolingManager::GetInstance()->Render();
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
	ObjectPoolingManager::GetInstance()->DebugRender();
	_player->DebugRender();
	_cursor->DebugRender();
	_monsters->DebugRender();
}
