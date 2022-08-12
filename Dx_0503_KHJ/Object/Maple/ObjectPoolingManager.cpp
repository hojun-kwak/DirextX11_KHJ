#include "framework.h"
#include "ObjectPoolingManager.h"

ObjectPoolingManager* ObjectPoolingManager::_instance = nullptr;

ObjectPoolingManager::ObjectPoolingManager()
{
	// 이createTiles를 여러번 생성하는것은 가능할까?
	CreateTiles();

	for (int i = 0; i < _floor; i++)
	{
		vector<shared_ptr<Tiles>> temp = make_shared<Tiles>();
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

void ObjectPoolingManager::CreateTiles()
{
	_tiles.reserve(_tileCount);
	for (int i = 0; i < _tileCount; i++)
	{
		shared_ptr<Tiles> temp = make_shared<Tiles>();
		switch (i)
		{
		case 0:
			temp->SetPosition(Vector2(-640.0f + temp->GetQuad()->GetHalfSize().x + 10.0f, -360.0f));
			temp->_isActive = true;
			break;
		case 1:
			temp->SetPosition(Vector2(-640.0f + (temp->GetQuad()->GetHalfSize().x * 3.0f), -360.0f));
			temp->_isActive = true;
			break;
		case 2:
			temp->SetPosition(Vector2(-640.0f + (temp->GetQuad()->GetHalfSize().x * 5.0f) - 10.0f, -360.0f));
			temp->_isActive = true;
			break;
		case 3:
			temp->SetPosition(Vector2(-640.0f + (temp->GetQuad()->GetHalfSize().x * 7.0f) - 20.0f, -360.0f));
			temp->_isActive = true;
			break;
		case 4:
			temp->SetPosition(Vector2(-640.0f + (temp->GetQuad()->GetHalfSize().x * 9.0f) - 30.0f, -360.0f));
			temp->_isActive = true;
			break;
		case 5:
			temp->SetPosition(Vector2(-640.0f + (temp->GetQuad()->GetHalfSize().x * 11.0f) - 40.0f, -360.0f));
			temp->_isActive = true;
			break;
		case 6:
			temp->SetPosition(Vector2(-640.0f + (temp->GetQuad()->GetHalfSize().x * 13.0f) - 200.0f, -360.0f));
			temp->_isActive = true;
			break;
		default:
			break;
		}

		_tiles.emplace_back(temp);
	}
}
