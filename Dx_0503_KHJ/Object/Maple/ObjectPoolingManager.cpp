#include "framework.h"
#include "ObjectPoolingManager.h"

ObjectPoolingManager* ObjectPoolingManager::_instance = nullptr;

ObjectPoolingManager::ObjectPoolingManager()
{
	_tiles = make_shared<Tiles>();
}

ObjectPoolingManager::~ObjectPoolingManager()
{
}

void ObjectPoolingManager::Update()
{
	_tiles->Update();
}

void ObjectPoolingManager::Render()
{
	_tiles->Render();
}

void ObjectPoolingManager::PostRender()
{
}

void ObjectPoolingManager::DebugRender()
{
	_tiles->DebugRender();
}
