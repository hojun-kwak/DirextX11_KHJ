#include "framework.h"
#include "ObjectPoolingManager.h"

ObjectPoolingManager* ObjectPoolingManager::_instance = nullptr;

ObjectPoolingManager::ObjectPoolingManager()
{
	_tiles.reserve(_tileCount);
	for (int i = 0; i < _tileCount; i++)
	{
		shared_ptr<Tiles> temp = make_shared<Tiles>();
		temp->SetPosition(Vector2(0, i * 100.0f));
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
