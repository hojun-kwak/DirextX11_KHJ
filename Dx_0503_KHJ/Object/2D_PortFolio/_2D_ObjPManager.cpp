#include "framework.h"
#include "_2D_ObjPManager.h"

_2D_ObjPManager* _2D_ObjPManager::_instance = nullptr;

_2D_ObjPManager::_2D_ObjPManager()
{
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

	_mons->Update();
}

void _2D_ObjPManager::Render()
{
	for (auto& floorTiles : _tiles)
		for (auto& tiles : floorTiles)
			tiles->Render();

	for (auto& ropes : _ropes)
		ropes->Render();

	_mons->Render();
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

	_mons->DebugRender();
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
	_mons = make_shared<_2D_Monster>();
	_mons->SetPosition(0,0);
	_mons->_isActive = true;
	_mons->SetTile(_tiles);
}
