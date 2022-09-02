#include "framework.h"
#include "_2D_ObjPManager.h"

_2D_ObjPManager* _2D_ObjPManager::_instance = nullptr;

_2D_ObjPManager::_2D_ObjPManager()
{
	//srand(static_cast<float>(time(nullptr)));
	CreateTiles();
	CreateRopes();
	CreateMonster();
}

_2D_ObjPManager::~_2D_ObjPManager()
{
}

void _2D_ObjPManager::Update()
{
	for (auto& floorTiles : _tiles)
		for (auto& tiles : floorTiles)
			tiles->Update();

	for (auto& ropes : _ropes)
		ropes->Update();

	for (auto& mons : _mons)
		mons->Update();
}

void _2D_ObjPManager::Render()
{
	for (auto& floorTiles : _tiles)
		for (auto& tiles : floorTiles)
			tiles->Render();

	for (auto& ropes : _ropes)
		ropes->Render();

	for (auto& mons : _mons)
		mons->Render();
}

void _2D_ObjPManager::PostRender()
{
}

void _2D_ObjPManager::DebugRender()
{
	for (auto& floorTiles : _tiles)
		for (auto& tiles : floorTiles)
			tiles->DebugRender();

	for (auto& ropes : _ropes)
		ropes->DebugRender();

	for (auto& mons : _mons)
		mons->DebugRender();
}

void _2D_ObjPManager::CreateTiles()
{
	for (int i = 0; i < _tileFloor.size(); i++)
	{
		vector<shared_ptr<_2D_Tile>> _tile;
		for (int j = 0; j < _tileCount; j++)
		{
			shared_ptr<_2D_Tile> temp = make_shared<_2D_Tile>();
			float x = -630.0f + temp->GetQuad()->GetHalfSize().x;
			float y = -360.0f;
			if (j > 0)
			{
				x += temp->GetQuad()->GetHalfSize().x * (j * 2.0f);
			}
			temp->SetPosition(x, _tileFloor[i]);
			temp->_isActive = true;
			_tile.emplace_back(temp);
		}
		_tiles.emplace_back(_tile);
	}
	
}

void _2D_ObjPManager::CreateRopes()
{
	for (int i = 0; i < _ropeCount; i++)
	{
		shared_ptr<_2D_Rope> temp = make_shared<_2D_Rope>();
		float y = -temp->GetQuad()->GetHalfSize().y + _tiles[0][0]->GetQuad()->GetHalfSize().y - 10.0f;
		switch (i)
		{
		case 0:
			temp->SetPosition(Vector2(_tiles[1][0]->GetPos().x , _tileFloor[1] + y));
			temp->_isActive = true;
			break;
		case 1:
			temp->SetPosition(Vector2(_tiles[1][5]->GetPos().x, _tileFloor[1] +  y));
			temp->_isActive = true;
			break;
		case 2:
			temp->SetPosition(Vector2(_tiles[2][0]->GetPos().x, _tileFloor[2] + y));
			temp->_isActive = true;
			break;
		case 3:
			temp->SetPosition(Vector2(_tiles[2][5]->GetPos().x, _tileFloor[2] + y));
			temp->_isActive = true;
			break;
		default:
			break;
		}
		_ropes.emplace_back(temp);
	}
}

void _2D_ObjPManager::CreateMonster()
{
	for (int i = 0, j = 0; i < _monsCount; i++, j++)
	{
		shared_ptr<_2D_Monster> temp = make_shared<_2D_Monster>();
		if (i % 3 ==0)
			j = 0;

		if (i < 3)
		{
			temp->SetPosition(_tiles[1][j+1]->GetPos().x, _tileFloor[1] + _tiles[0][0]->GetQuad()->GetHalfSize().y * 1.5f);
			temp->_isActive = true;
			temp->SetTile(_tiles[1]);
		}
		else
		{
			temp->SetPosition(_tiles[2][j+1]->GetPos().x, _tileFloor[2] + _tiles[0][0]->GetQuad()->GetHalfSize().y * 1.5f);
			temp->_isActive = true;
			temp->SetTile(_tiles[2]);
		}

		if (i % 2 == 0)
			temp->SetDir(_2D_Monster::Direction::RIGHT);
		else
			temp->SetDir(_2D_Monster::Direction::LEFT);

		_mons.emplace_back(temp);
	}
}
