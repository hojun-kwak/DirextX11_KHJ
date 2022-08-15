#include "framework.h"
#include "ObjectPoolingManager.h"

ObjectPoolingManager* ObjectPoolingManager::_instance = nullptr;

ObjectPoolingManager::ObjectPoolingManager()
{
	// 이createTiles를 여러번 생성하는것은 가능할까?
	CreateTiles();

	CreateData();
	_test.emplace_back(_1floorTiles);
	_test.emplace_back(_2floorTiles);
	_test.emplace_back(_3floorTiles);
}

ObjectPoolingManager::~ObjectPoolingManager()
{
}

void ObjectPoolingManager::Update()
{
	for (auto& tile : _tiles)
		tile->Update();

	/*for (auto& tile1 : _1floorTiles)
		tile1->Update();

	for (auto& tile2 : _2floorTiles)
		tile2->Update();

	for (auto& tile3 : _3floorTiles)
		tile3->Update();

	for (int i = 0; i < _test.size(); i++)
	{
		_test[0][i]->Update();
	}*/
}

void ObjectPoolingManager::Render()
{
	for (auto& tile : _tiles)
		tile->Render();

	/*for (auto& tile1 : _1floorTiles)
		tile1->Render();

	for (auto& tile2 : _2floorTiles)
		tile2->Render();

	for (auto& tile3 : _3floorTiles)
		tile3->Render();*/
}

void ObjectPoolingManager::PostRender()
{
}

void ObjectPoolingManager::DebugRender()
{
	for (auto& tile : _tiles)
		tile->DebugRender();

	/*for (auto& tile1 : _1floorTiles)
		tile1->DebugRender();

	for (auto& tile2 : _2floorTiles)
		tile2->DebugRender();

	for (auto& tile3 : _3floorTiles)
		tile3->DebugRender();*/
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
			temp->SetPosition(Vector2(-640.0f + (temp->GetQuad()->GetHalfSize().x * 6.0f), -360.0f));
			temp->_isActive = true;
			break;
		case 3:
			temp->SetPosition(Vector2(-640.0f + (temp->GetQuad()->GetHalfSize().x * 6.5f), -360.0f));
			temp->_isActive = true;
			break;
		case 4:
			temp->SetPosition(Vector2(-640.0f + (temp->GetQuad()->GetHalfSize().x * 8.5f), -360.0f));
			temp->_isActive = true;
			break;
		case 5:
			temp->SetPosition(Vector2(-640.0f + (temp->GetQuad()->GetHalfSize().x * 10.5f), -360.0f));
			temp->_isActive = true;
			break;
		case 6:
			temp->SetPosition(Vector2(-640.0f + (temp->GetQuad()->GetHalfSize().x * 12.5f), -360.0f));
			temp->_isActive = true;
			break;
		default:
			break;
		}

		_tiles.emplace_back(temp);
	}
}

void ObjectPoolingManager::CreateData()
{

	// 1층
	{
		_1floorTiles.reserve(_tileCount);
		for (int i = 0; i < _tileCount; i++)
		{
			shared_ptr<Tiles> temp1 = make_shared<Tiles>();
			switch (i)
			{
			case 0:
				temp1->SetPosition(Vector2(-640.0f + temp1->GetQuad()->GetHalfSize().x + 10.0f, -360.0f));
				temp1->_isActive = true;
				break;
			case 1:
				temp1->SetPosition(Vector2(-640.0f + (temp1->GetQuad()->GetHalfSize().x * 3.0f), -360.0f));
				temp1->_isActive = true;
				break;
			case 2:
				temp1->SetPosition(Vector2(-640.0f + (temp1->GetQuad()->GetHalfSize().x * 5.0f) - 10.0f, -360.0f));
				temp1->_isActive = true;
				break;
			case 3:
				temp1->SetPosition(Vector2(-640.0f + (temp1->GetQuad()->GetHalfSize().x * 7.0f) - 20.0f, -360.0f));
				temp1->_isActive = true;
				break;
			case 4:
				temp1->SetPosition(Vector2(-640.0f + (temp1->GetQuad()->GetHalfSize().x * 9.0f) - 30.0f, -360.0f));
				temp1->_isActive = true;
				break;
			case 5:
				temp1->SetPosition(Vector2(-640.0f + (temp1->GetQuad()->GetHalfSize().x * 11.0f) - 40.0f, -360.0f));
				temp1->_isActive = true;
				break;
			case 6:
				temp1->SetPosition(Vector2(-640.0f + (temp1->GetQuad()->GetHalfSize().x * 13.0f) - 200.0f, -360.0f));
				temp1->_isActive = true;
				break;
			default:
				break;
			}
			_1floorTiles.emplace_back(temp1);
		}
	}

	// 2층
	{
		_2floorTiles.reserve(_tileCount);
		for (int i = 0; i < _tileCount; i++)
		{
			shared_ptr<Tiles> temp2 = make_shared<Tiles>();
			switch (i)
			{
			case 0:
				temp2->SetPosition(Vector2(-640.0f + temp2->GetQuad()->GetHalfSize().x + 10.0f, 0.0f));
				temp2->_isActive = true;
				break;
			case 1:
				temp2->SetPosition(Vector2(-640.0f + (temp2->GetQuad()->GetHalfSize().x * 3.0f), 0.0f));
				temp2->_isActive = true;
				break;
			case 2:
				temp2->SetPosition(Vector2(-640.0f + (temp2->GetQuad()->GetHalfSize().x * 5.0f) - 10.0f, 0.0f));
				temp2->_isActive = true;
				break;
			case 3:
				temp2->SetPosition(Vector2(-640.0f + (temp2->GetQuad()->GetHalfSize().x * 7.0f) - 20.0f, 0.0f));
				temp2->_isActive = true;
				break;
			case 4:
				temp2->SetPosition(Vector2(-640.0f + (temp2->GetQuad()->GetHalfSize().x * 9.0f) - 30.0f, 0.0f));
				temp2->_isActive = true;
				break;
			case 5:
				temp2->SetPosition(Vector2(-640.0f + (temp2->GetQuad()->GetHalfSize().x * 11.0f) - 40.0f, 0.0f));
				temp2->_isActive = true;
				break;
			case 6:
				temp2->SetPosition(Vector2(-640.0f + (temp2->GetQuad()->GetHalfSize().x * 13.0f) - 200.0f, 0.0f));
				temp2->_isActive = true;
				break;
			default:
				break;
			}
			_2floorTiles.emplace_back(temp2);
		}
	}

	// 3층
	{
		_3floorTiles.reserve(_tileCount);
		for (int i = 0; i < _tileCount; i++)
		{
			shared_ptr<Tiles> temp3 = make_shared<Tiles>();
			switch (i)
			{
			case 0:
				temp3->SetPosition(Vector2(-640.0f + temp3->GetQuad()->GetHalfSize().x + 10.0f, 180.0f));
				temp3->_isActive = true;
				break;
			case 1:
				temp3->SetPosition(Vector2(-640.0f + (temp3->GetQuad()->GetHalfSize().x * 3.0f), 180.0f));
				temp3->_isActive = true;
				break;
			case 2:
				temp3->SetPosition(Vector2(-640.0f + (temp3->GetQuad()->GetHalfSize().x * 5.0f) - 10.0f, 180.0f));
				temp3->_isActive = true;
				break;
			case 3:
				temp3->SetPosition(Vector2(-640.0f + (temp3->GetQuad()->GetHalfSize().x * 7.0f) - 20.0f, -180.0f));
				temp3->_isActive = true;
				break;
			case 4:
				temp3->SetPosition(Vector2(-640.0f + (temp3->GetQuad()->GetHalfSize().x * 9.0f) - 30.0f, -180.0f));
				temp3->_isActive = true;
				break;
			case 5:
				temp3->SetPosition(Vector2(-640.0f + (temp3->GetQuad()->GetHalfSize().x * 11.0f) - 40.0f, -180.0f));
				temp3->_isActive = true;
				break;
			case 6:
				temp3->SetPosition(Vector2(-640.0f + (temp3->GetQuad()->GetHalfSize().x * 13.0f) - 200.0f, -180.0f));
				temp3->_isActive = true;
				break;
			default:
				break;
			}
			_3floorTiles.emplace_back(temp3);
		}
	}
}
