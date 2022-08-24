#include "framework.h"
#include "MPlayer.h"

MPlayer::MPlayer()
{
	_sprite = make_shared<Sprite>(MAPLE_MOVE,Vector2(4,5));
	_col = make_shared<RectCollider>(_sprite->GetHalfFrameSize());
	_col->SetParent(_sprite->GetTransform());
	_ropeCol = make_shared<RectCollider>(_sprite->GetHalfFrameSize() * 0.7f);
	_ropeCol->SetParent(_sprite->GetTransform());
	
	CreateData();
}

MPlayer::~MPlayer()
{
}

void MPlayer::Update()
{
	/*Operation();
	Jumpimg();*/

	_sprite->Update();


	for (auto& action : _actions)
	{
		action->Update();
		if (!action->IsPlay())
			continue;
		_sprite->SetClipToActionBuffer(action->GetCurClip());
	}
	_col->Update();
	_ropeCol->Update();
}

void MPlayer::Render()
{
	_sprite->Render();
}

void MPlayer::PostRender()
{
	ImGui::Text("PlayerX : %.1f, PlayerY : %.1f", _playerPos.x, _playerPos.y);
}

void MPlayer::DebugRender()
{
	_col->Render();
	_ropeCol->Render();
	ImGui::Text("AniState : %c", _aniState);
}

void MPlayer::SetPosition(float x, float y)
{
	_sprite->GetTransform()->GetPos() = { x,y };
	_playerPos = { x,y };
}

void MPlayer::SetAnimation(State aniState)
{
	if (_actions[aniState]->IsPlay() && _actions[aniState]->GetAniType() == Action::LOOP)
		return;

	for (auto& action : _actions)
	{
		if (action->IsPlay() && _aniState == aniState)
			continue;

		action->Reset();
	}

	_actions[aniState]->Play();
	_aniState = aniState;
}

void MPlayer::CreateData()
{
	float maple_player1_depth = 276.0f;

	_actions.reserve(7);
	vector<Action::Clip> clips;
	float w = 224.0f / 4.0f;
	float h = maple_player1_depth / 5.0f;

	float y = 0;
	{
		clips.emplace_back(0, y, w, h, Texture::Add(MAPLE_MOVE));
	}
		_actions.push_back(make_shared<Action>(clips, "L_IDLE"));
		clips.clear();
	{
		clips.emplace_back(0 + w, y, w, h, Texture::Add(MAPLE_MOVE));
	}
	_actions.push_back(make_shared<Action>(clips, "R_IDLE"));
	clips.clear();

	y = maple_player1_depth * (1.0f / 5.0f);
	{
		clips.emplace_back(0, y, w, h, Texture::Add(MAPLE_MOVE));
		clips.emplace_back(0 + w, y, w, h, Texture::Add(MAPLE_MOVE));
		clips.emplace_back(0 + w * 2, y, w, h, Texture::Add(MAPLE_MOVE));
	}
	shared_ptr<Action> leftRun = make_shared<Action>(clips, "L_RUN", Action::LOOP);
	_actions.push_back(leftRun);
	clips.clear();

	y = maple_player1_depth * (2.0f / 5.0f);
	{
		clips.emplace_back(0, y, w, h, Texture::Add(MAPLE_MOVE));
		clips.emplace_back(0 + w, y, w, h, Texture::Add(MAPLE_MOVE));
		clips.emplace_back(0 + w * 2, y, w, h, Texture::Add(MAPLE_MOVE));
	}
	shared_ptr<Action> rightRun = make_shared<Action>(clips, "R_RUN", Action::LOOP);
	_actions.push_back(rightRun);
	clips.clear();

	y = maple_player1_depth * (3.0f / 5.0f);
	{
		clips.emplace_back(0, y, w, h, Texture::Add(MAPLE_MOVE));
	}
	_actions.push_back(make_shared<Action>(clips, "L_JUMP"));
	clips.clear();

	{
		clips.emplace_back(0 + w, y, w, h, Texture::Add(MAPLE_MOVE));
	}
	_actions.push_back(make_shared<Action>(clips, "R_JUMP"));
	clips.clear();

	y = maple_player1_depth * (4.0f / 5.0f);

	{
		clips.emplace_back(0, y, w, h, Texture::Add(MAPLE_MOVE));
	}
	_actions.push_back(make_shared<Action>(clips, "CLIMBING_IDLE"));
	clips.clear();

	{
		clips.emplace_back(0, y, w, h, Texture::Add(MAPLE_MOVE));
		clips.emplace_back(0 + w, y, w, h, Texture::Add(MAPLE_MOVE));
	}
	shared_ptr<Action> climbing = make_shared<Action>(clips, "CLIMBING", Action::LOOP);
	_actions.push_back(climbing);
	clips.clear();

	for (auto& action : _actions)
		action->Pause();

	_actions[State::L_IDLE]->Play();
}

//void MPlayer::Operation()
//{
//	this->SetPosition(_playerPos.x, _playerPos.y);
//	
//	{
//		for(auto& floorTiles : _tiles)
//			for (auto& tile : floorTiles)
//			{
//				if (_col->IsCollision(tile->GetColl(), false))
//				{
//					_col->SetRed();
//					tile->GetColl()->SetRed();
//					if (KEY_PRESS(VK_LEFT))
//					{
//						_playerPos.x -= 150.0f * DELTA_TIME;
//						this->SetAnimation(MPlayer::State::L_RUN);
//						return;
//					}
//					if (KEY_PRESS(VK_RIGHT))
//					{
//						_playerPos.x += 150.0f * DELTA_TIME;
//						this->SetAnimation(MPlayer::State::R_RUN);
//						return;
//					}
//				}
//				else
//				{
//					_col->SetGreen();
//					tile->GetColl()->SetGreen();
//				}
//		}
//
//		// ��ٸ��� �浹�ø� �߻��ϰ� �ҿ���
//		for (auto& rope : _ropes)
//		{
//			if (_ropeCol->IsCollision(rope->GetColl(), false))
//			{
//				_col->SetRed();
//				_ropeCol->SetRed();
//				rope->GetColl()->SetRed();
//				if (KEY_PRESS(VK_DOWN))
//				{
//					_playerPos.x = rope->GetRopePos().x;
//					_playerPos.y -= 150.0f * DELTA_TIME;
//					this->SetAnimation(MPlayer::State::CLIMBING);
//					// ���� ������ top�� �����ŭ �ö�Դٸ�? �켱 ������
//					if (_playerPos.y < rope->GetColl()->Bottom())
//					//if (_playerPos.y < -301.5f)
//					{
//						_playerPos.x = rope->GetRopePos().x;
//						_playerPos.y -= 10.0f;
//						for(auto& FloorTiles : _tiles)
//							for (auto& tile : FloorTiles)
//							{
//								if (_col->IsCollision(tile->GetColl(), false))
//								{
//									_playerPos.y = tile->GetColl()->Top() + tile->GetQuad()->GetHalfSize().y;
//									this->SetAnimation(MPlayer::State::L_IDLE);
//								}
//							}
//						return;
//					}
//					return;
//				}
//				if (KEY_PRESS(VK_UP))
//				{
//					_playerPos.x = rope->GetRopePos().x;
//					_playerPos.y += 150.0f * DELTA_TIME;
//					this->SetAnimation(MPlayer::State::CLIMBING);
//					if (_playerPos.y >= rope->GetColl()->Top())
//					{
//						for(auto& floorTiles : _tiles)
//							for (auto& tile : floorTiles)
//							{
//								if (_col->IsCollision(tile->GetColl(), false))
//								{
//									_playerPos.x = rope->GetRopePos().x;
//									_playerPos.y = tile->GetColl()->Top() + tile->GetQuad()->GetHalfSize().y;
//									this->SetAnimation(MPlayer::State::L_IDLE);
//									return;
//								}
//							}
//					}
//					return;
//				}
//			}
//			else
//			{
//				_col->SetGreen();
//				_ropeCol->SetGreen();
//				rope->GetColl()->SetGreen();
//			}
//		}
//		
//
//		if (_isJumping == false)
//		{
//			if (KEY_PRESS(VK_SPACE))
//			{
//				_isJumping = true;
//				return;
//			}
//		}
//	}
//	{
//		if (KEY_UP(VK_LEFT))
//			this->SetAnimation(MPlayer::State::L_IDLE);
//		if (KEY_UP(VK_RIGHT))
//			this->SetAnimation(MPlayer::State::R_IDLE);
//		if (KEY_UP(VK_UP))
//			this->SetAnimation(MPlayer::State::CLIMBING_IDLE);
//		if(KEY_UP(VK_DOWN))
//			this->SetAnimation(MPlayer::State::CLIMBING_IDLE);
//	}
//}

//void MPlayer::Jumpimg()
//{
//	if (_isJumping == false)
//		return;
//
//	Vector2 temp;
//	_jumpPower -= (float)pow(_gravity, 2) * DELTA_TIME;
//
//	temp.y = _jumpPower;
//	_playerPos += temp * DELTA_TIME;
//	this->SetAnimation(MPlayer::State::L_JUMP);
//	
//	for (auto& floorTiles : _tiles)
//		for (auto& tile : floorTiles)
//		{
//			if (_col->IsCollision(tile->GetColl(), false))
//			{
//				if (_playerPos.y <= tile->GetColl()->Top() + _sprite->GetHalfFrameSize().y - 5.0f)
//				{
//					this->SetAnimation(MPlayer::State::L_IDLE);
//					_jumpPower = 150.0f;
//					_isJumping = false;
//				}
//			}
//		}
//	
//}