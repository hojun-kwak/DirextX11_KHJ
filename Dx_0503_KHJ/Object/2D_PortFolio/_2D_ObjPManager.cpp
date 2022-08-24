#include "framework.h"
#include "_2D_ObjPManager.h"

_2D_ObjPManager* _2D_ObjPManager::_instance = nullptr;

_2D_ObjPManager::_2D_ObjPManager()
{
	CreateTiles();
}

_2D_ObjPManager::~_2D_ObjPManager()
{
}

void _2D_ObjPManager::Update()
{
	for (auto& m : _tile)
		m->Update();
}

void _2D_ObjPManager::Render()
{
	for (auto& m : _tile)
		m->Render();
}

void _2D_ObjPManager::PostRender()
{
}

void _2D_ObjPManager::DebugRender()
{
	for (auto& m : _tile)
		m->DebugRender();
}

void _2D_ObjPManager::CreateTiles()
{
	for (int j = 0; j < _tileCount; j++)
	{
		shared_ptr<_2D_Tile> temp = make_shared<_2D_Tile>();
		float x = -640.0f;
		float y = -360.0f;
		switch (j)
		{
			case 0:
				temp->SetPosition(x,y);
				break;
			default:
				break;
			}
	}
}
