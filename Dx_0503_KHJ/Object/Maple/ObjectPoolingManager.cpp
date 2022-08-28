#include "framework.h"
#include "ObjectPoolingManager.h"

ObjectPoolingManager* ObjectPoolingManager::_instance = nullptr;

ObjectPoolingManager::ObjectPoolingManager()
{
	/*CreateTiles();
	CreateRopes();*/
}

ObjectPoolingManager::~ObjectPoolingManager()
{
}

void ObjectPoolingManager::Update()
{
	for (auto& floorTiles : _tiles)
		for (auto& tiles : floorTiles)
			tiles->Update();

	for (auto& rope : _ropes)
		rope->Update();
}

void ObjectPoolingManager::Render()
{
	for (auto& floorTiles : _tiles)
		for (auto& tiles : floorTiles)
			tiles->Render();

	for (auto& rope : _ropes)
		rope->Render();
}

void ObjectPoolingManager::PostRender()
{
}

void ObjectPoolingManager::DebugRender()
{
	for (auto& floorTiles : _tiles)
		for (auto& tiles : floorTiles)
			tiles->DebugRender();

	for (auto& rope : _ropes)
		rope->DebugRender();
}

void ObjectPoolingManager::CreateTiles()
{
	float y = 0;
	// 1Ãþ
	{
		_1floorTiles.reserve(_tileCount);
		y = -360.0f;
		for (int i = 0; i < _tileCount; i++)
		{
			shared_ptr<Tiles> temp1 = make_shared<Tiles>();
			switch (i)
			{
			case 0:
				temp1->SetPosition(Vector2(-640.0f + temp1->GetQuad()->GetHalfSize().x + 10.0f, y));
				temp1->SetIsActive(true);
				break;
			case 1:
				temp1->SetPosition(Vector2(-640.0f + (temp1->GetQuad()->GetHalfSize().x * 3.0f), y));
				temp1->SetIsActive(true);
				break;
			case 2:
				temp1->SetPosition(Vector2(-640.0f + (temp1->GetQuad()->GetHalfSize().x * 5.0f) - 10.0f, y));
				temp1->SetIsActive(true);
				break;
			case 3:
				temp1->SetPosition(Vector2(-640.0f + (temp1->GetQuad()->GetHalfSize().x * 7.0f) - 20.0f, y));
				temp1->SetIsActive(true);
				break;
			case 4:
				temp1->SetPosition(Vector2(-640.0f + (temp1->GetQuad()->GetHalfSize().x * 9.0f) - 30.0f, y));
				temp1->SetIsActive(true);
				break;
			case 5:
				temp1->SetPosition(Vector2(-640.0f + (temp1->GetQuad()->GetHalfSize().x * 11.0f) - 40.0f, y));
				temp1->SetIsActive(true);
				break;
			case 6:
				temp1->SetPosition(Vector2(-640.0f + (temp1->GetQuad()->GetHalfSize().x * 13.0f) - 200.0f, y));
				temp1->SetIsActive(true);
				break;
			default:
				break;
			}
			_1floorTiles.emplace_back(temp1);
		}
	}

	// 2Ãþ
	{
		_2floorTiles.reserve(_tileCount);
		y = -150.0f;
		for (int i = 0; i < _tileCount; i++)
		{
			shared_ptr<Tiles> temp2 = make_shared<Tiles>();
			switch (i)
			{
			case 0:
				temp2->SetPosition(Vector2(-640.0f + temp2->GetQuad()->GetHalfSize().x + 10.0f, y));
				temp2->SetIsActive(true);
				break;
			case 1:
				temp2->SetPosition(Vector2(-640.0f + (temp2->GetQuad()->GetHalfSize().x * 3.0f), y));
				temp2->SetIsActive(true);
				break;
			case 2:
				temp2->SetPosition(Vector2(-640.0f + (temp2->GetQuad()->GetHalfSize().x * 5.0f) - 10.0f, y));
				temp2->SetIsActive(true);
				break;
			case 3:
				temp2->SetPosition(Vector2(-640.0f + (temp2->GetQuad()->GetHalfSize().x * 7.0f) - 20.0f, y));
				temp2->SetIsActive(true);
				break;
			case 4:
				temp2->SetPosition(Vector2(-640.0f + (temp2->GetQuad()->GetHalfSize().x * 9.0f) - 30.0f, y));
				temp2->SetIsActive(true);
				break;
			case 5:
				temp2->SetPosition(Vector2(-640.0f + (temp2->GetQuad()->GetHalfSize().x * 11.0f) - 40.0f, y));
				temp2->SetIsActive(true);
				break;
			case 6:
				temp2->SetPosition(Vector2(-640.0f + (temp2->GetQuad()->GetHalfSize().x * 13.0f) - 200.0f, y));
				temp2->SetIsActive(true);
				break;
			default:
				break;
			}
			_2floorTiles.emplace_back(temp2);
		}
	}

	// 3Ãþ
	{
		_3floorTiles.reserve(_tileCount);
		y = 60.0f;
		for (int i = 0; i < _tileCount; i++)
		{
			shared_ptr<Tiles> temp3 = make_shared<Tiles>();
			switch (i)
			{
			case 0:
				temp3->SetPosition(Vector2(-640.0f + temp3->GetQuad()->GetHalfSize().x + 10.0f, y));
				temp3->SetIsActive(true);
				break;
			case 1:
				temp3->SetPosition(Vector2(-640.0f + (temp3->GetQuad()->GetHalfSize().x * 3.0f), y));
				temp3->SetIsActive(true);
				break;
			case 2:
				temp3->SetPosition(Vector2(-640.0f + (temp3->GetQuad()->GetHalfSize().x * 5.0f) - 10.0f, y));
				temp3->SetIsActive(true);
				break;
			case 3:
				temp3->SetPosition(Vector2(-640.0f + (temp3->GetQuad()->GetHalfSize().x * 7.0f) - 20.0f, y));
				temp3->SetIsActive(true);
				break;
			case 4:
				temp3->SetPosition(Vector2(-640.0f + (temp3->GetQuad()->GetHalfSize().x * 9.0f) - 30.0f, y));
				temp3->SetIsActive(true);
				break;
			case 5:
				temp3->SetPosition(Vector2(-640.0f + (temp3->GetQuad()->GetHalfSize().x * 11.0f) - 40.0f, y));
				temp3->SetIsActive(true);
				break;
			case 6:
				temp3->SetPosition(Vector2(-640.0f + (temp3->GetQuad()->GetHalfSize().x * 13.0f) - 200.0f, y));
				temp3->SetIsActive(true);
				break;
			default:
				break;
			}
			_3floorTiles.emplace_back(temp3);
		}
	}

	_tiles.emplace_back(_1floorTiles);
	_tiles.emplace_back(_2floorTiles);
	_tiles.emplace_back(_3floorTiles);
}

void ObjectPoolingManager::CreateRopes()
{
	{
		_ropes.reserve(_ropeCount);
		for (int i = 0; i < _ropeCount; i++)
		{
			shared_ptr<Rope> temp = make_shared<Rope>();
			temp->GetTransform()->GetScale() *= 0.3f;
			float ropeYSize = temp->GetQuad()->GetHalfSize().y;
			switch (i % 2)
			{
			case 0:
				switch (i)
				{
				case 0:
					temp->SetPosition(Vector2(-440.0f, (-150.0f - ropeYSize)));
					break;
				case 2:
					temp->SetPosition(Vector2(-440.0f, (60.0f - ropeYSize)));
					break;
				default:
					break;
				}
				break;
			case 1:
				switch (i)
				{
				case 1:
					temp->SetPosition(Vector2(440.0f, (-150.0f - ropeYSize)));
					break;
				case 3:
					temp->SetPosition(Vector2(440.0f, (60.0f - ropeYSize)));
					break;
				default:
					break;
				}
				break;
			default:
				break;
			}
			_ropes.emplace_back(temp);
		}
	}
}
