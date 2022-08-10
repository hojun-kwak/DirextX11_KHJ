#include "framework.h"
#include "ObjectPoolingManager.h"

ObjectPoolingManager* ObjectPoolingManager::_instance = nullptr;

ObjectPoolingManager::ObjectPoolingManager()
{
	_tiles.reserve(_tileCount);
	for (int i = 0; i < _tileCount; i++)
	{
		shared_ptr<Tiles> temp = make_shared<Tiles>();
		
		switch (i)
		{
		case 0:
			for (int j = 0; j < 2; j++)
			{
				// 이거 숫자 수정
				//temp->SetPosition(Vector2(i * -(temp->GetQuad()->GetHalfSize().x * 2.0f), -360));
				temp->SetPosition(Vector2(0,0));
			}
			break;
		default:
			temp->SetPosition(Vector2(0,0));
			break;
		}
		
		_tiles.emplace_back(temp);
	}
}

ObjectPoolingManager::~ObjectPoolingManager()
{
}

void ObjectPoolingManager::Update()
{
	for (auto& tile : _tiles)
		tile->Update();
}

void ObjectPoolingManager::Render()
{
	for (auto& tile : _tiles)
		tile->Render();
}

void ObjectPoolingManager::PostRender()
{
}

void ObjectPoolingManager::DebugRender()
{
	for (auto& tile : _tiles)
		tile->DebugRender();
}
