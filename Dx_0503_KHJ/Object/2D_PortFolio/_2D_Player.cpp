#include "framework.h"
#include "_2D_Player.h"

_2D_Player::_2D_Player()
{
	_MoveS = make_shared<Sprite>(MAPLE_MOVE, Vector2(4, 5));
	_MoveC = make_shared<RectCollider>(_MoveS->GetHalfFrameSize());
	_MoveC->SetParent(_MoveS->GetTransform());

	_ropeCol = make_shared<RectCollider>(Vector2(_MoveS->GetHalfFrameSize().x - 10.0f, _MoveS->GetHalfFrameSize().y + 7.0f));
	_ropeCol->SetParent(_MoveS->GetTransform());
	_ropeCol->SetBlue();

	_AttackS = make_shared<Sprite>(MAPLE_ATACK, Vector2(3,2));
	_AttackC = make_shared<RectCollider>(_AttackS->GetHalfFrameSize());
	_AttackC->SetParent(_AttackS->GetTransform());

	CreateData();
}

_2D_Player::~_2D_Player()
{
}

void _2D_Player::Update()
{
	this->SetPosition(_playerPos.x, _playerPos.y);

	Operation();
	Jumpimg();
	Attacking();
	DebugSetColor();

	for (auto& sprite : _sprites)
	{
		if (_aniState == L_ATTACK || _aniState == R_ATTACK)
		{
			if (sprite.first == "AttackS")
				sprite.second->Update();
		}
		else
		{
			if (sprite.first == "MoveS")
				sprite.second->Update();
		}
	}

	for (auto& col : _cols)
	{
		if (_aniState == L_ATTACK || _aniState == R_ATTACK)
		{
			if (col.first == "AttackC")
				col.second->Update();
		}
		else
		{
			if (col.first == "MoveC")
				col.second->Update();
		}
	}

	for (auto& action : _actions)
	{
		action->Update();
		if (!action->IsPlay())
			continue;
		/*_sprite->SetClipToActionBuffer(action->GetCurClip());
		_AttackS->SetClipToActionBuffer(action->GetCurClip());*/
		for (auto& sprites : _sprites)
			sprites.second->SetClipToActionBuffer(action->GetCurClip());

	}
	_ropeCol->Update();

}

void _2D_Player::Render()
{
	/*_sprite->Render();
	_AttackS->Render();*/
	for (auto sprite : _sprites)
	{
		if (_aniState == L_ATTACK || _aniState == R_ATTACK)
		{
			if (sprite.first == "AttackS")
				sprite.second->Render();
		}
		else
		{
			if (sprite.first == "MoveS")
				sprite.second->Render();
		}
	}
}

void _2D_Player::PostRender()
{
	ImGui::Text("PlayerX : %.1f, PlayerY : %.1f", _playerPos.x, _playerPos.y);
}

void _2D_Player::DebugRender()
{
	for (auto col : _cols)
		if (_aniState == L_ATTACK || _aniState == R_ATTACK)
		{
			if (col.first == "AttackC")
				col.second->Render();
		}
		else
		{
			if (col.first == "MoveC")
				col.second->Render();
		}

	_ropeCol->Render();
}

void _2D_Player::DebugSetColor()
{
	for (auto& floorTiles : _tiles)
	{
		for (auto& tile : floorTiles)
		{
			for (auto& col : _cols)
			{
				if (col.second->IsCollision(tile->GetColl(), false))
				{
					if (_aniState == L_ATTACK || _aniState == R_ATTACK)
					{
						if (col.first == "AttackC")
						{
							col.second->SetRed();
							tile->GetColl()->SetRed();
							
						}
					}
					else
					{
						if (col.first == "MoveC")
						{
							col.second->SetRed();
							tile->GetColl()->SetRed();
						}
					}
				}
				else
				{
					if (_aniState == L_ATTACK || _aniState == R_ATTACK)
					{
						if (col.first == "AttackC")
						{
							col.second->SetGreen();
							tile->GetColl()->SetGreen();
						}
					}
					else
					{
						if (col.first == "MoveC")
						{
							col.second->SetGreen();
							tile->GetColl()->SetGreen();
						}
					}
					
				}
			}
		}
	}

	for (auto& rope : _ropes)
	{
		if (_ropeCol->IsCollision(rope->GetCol(), false))
		{
			_ropeCol->SetRed();
			rope->GetCol()->SetRed();
		}
		else
		{
			_ropeCol->SetGreen();
			rope->GetCol()->SetGreen();
		}
	}
}

void _2D_Player::SetPosition(float x, float y)
{
	for(auto& sprite : _sprites)
		sprite.second->GetTransform()->GetPos() = { x,y };
	//_sprite->GetTransform()->GetPos() = { x,y };
	_playerPos = { x,y };
}

void _2D_Player::SetAnimation(State aniState)
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

void _2D_Player::CreateData()
{
	_sprites.insert(make_pair("MoveS", _MoveS));
	_cols.insert(make_pair("MoveC", _MoveC));
	_sprites.insert(make_pair("AttackS", _AttackS));
	_cols.insert(make_pair("AttackC", _AttackC));

	_actions.reserve(10);
	
	CreateMoveData();
	CreateAttackData();

	for (auto& action : _actions)
		action->Pause();

	_actions[State::L_IDLE]->Play();
	//_actions[State::L_ATTACK]->Play();
}

void _2D_Player::CreateMoveData()
{
	float maple_move_depth = 276.0f;
	float w = 224.0f / 4.0f;
	float h = maple_move_depth / 5.0f;

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

	y = maple_move_depth * (1.0f / 5.0f);
	{
		clips.emplace_back(0, y, w, h, Texture::Add(MAPLE_MOVE));
		clips.emplace_back(0 + w, y, w, h, Texture::Add(MAPLE_MOVE));
		clips.emplace_back(0 + w * 2, y, w, h, Texture::Add(MAPLE_MOVE));
	}
	shared_ptr<Action> leftRun = make_shared<Action>(clips, "L_RUN", Action::LOOP);
	_actions.push_back(leftRun);
	clips.clear();

	y = maple_move_depth * (2.0f / 5.0f);
	{
		clips.emplace_back(0, y, w, h, Texture::Add(MAPLE_MOVE));
		clips.emplace_back(0 + w, y, w, h, Texture::Add(MAPLE_MOVE));
		clips.emplace_back(0 + w * 2, y, w, h, Texture::Add(MAPLE_MOVE));
	}
	shared_ptr<Action> rightRun = make_shared<Action>(clips, "R_RUN", Action::LOOP);
	_actions.push_back(rightRun);
	clips.clear();

	y = maple_move_depth * (3.0f / 5.0f);
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

	y = maple_move_depth * (4.0f / 5.0f);

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

}

void _2D_Player::CreateAttackData()
{
	// 180 * 120
	float maple_attack_depth = 120.0f;
	float w = 180.0f / 3.0f;
	float h = maple_attack_depth / 2.0f;

	float y = 0;
	{
		clips.emplace_back(0, y, w, h, Texture::Add(MAPLE_ATACK));
		clips.emplace_back(0 + w, y, w, h, Texture::Add(MAPLE_ATACK));
		clips.emplace_back(0 + w * 2, y, w, h, Texture::Add(MAPLE_ATACK));
	}
	shared_ptr<Action> Lattack = make_shared<Action>(clips, "L_ATTACK", Action::LOOP, 1.0f);
	Lattack->SetEndEvent();
	_actions.push_back(Lattack);
	clips.clear();

	y = maple_attack_depth * (1.0f / 2.0f);
	{
		clips.emplace_back(0, y, w, h, Texture::Add(MAPLE_ATACK));
		clips.emplace_back(0 + w, y, w, h, Texture::Add(MAPLE_ATACK));
		clips.emplace_back(0 + w * 2, y, w, h, Texture::Add(MAPLE_ATACK));
	}
	shared_ptr<Action> Rattack = make_shared<Action>(clips, "R_ATTACK", Action::LOOP, 1.0f);
	_actions.push_back(Rattack);
	clips.clear();

}

void _2D_Player::Operation()
{
	// 좌우 이동
	for (auto& floorTiles : _tiles)
	{
		for (auto& tile : floorTiles)
		{
			for (auto& col : _cols)
			{
				if (col.second->IsCollision(tile->GetColl(), false))
				{
					if (KEY_PRESS(VK_LEFT))
					{
						_playerPos.x -= 150.0f * DELTA_TIME;
						_situ = _2D_Player::Situation::MOVE;
						this->SetAnimation(_2D_Player::State::L_RUN);
						return;
					}
					if (KEY_PRESS(VK_RIGHT))
					{
						_playerPos.x += 150.0f * DELTA_TIME;
						_situ = _2D_Player::Situation::MOVE;
						this->SetAnimation(_2D_Player::State::R_RUN);
						return;
					}
				}
			}
		}
	}

	// 위아래
	for (auto& rope : _ropes)
	{
		for (auto& col : _cols)
		{
			if (KEY_PRESS(VK_UP))
			{
				if (_ropeCol->IsCollision(rope->GetCol(), false) && col.second->IsCollision(rope->GetCol(), false))
				{
					_playerPos.x = rope->GetRopePos().x;
					_playerPos.y += 150.0f * DELTA_TIME;
					_situ = _2D_Player::Situation::CLIMB;
					this->SetAnimation(_2D_Player::State::CLIMBING);

					if (col.second->Top() >= rope->GetCol()->Top())
					{
						for (auto& floorTiles : _tiles)
							for (auto& tile : floorTiles)
							{
								if (rope->GetCol()->IsCollision(tile->GetColl(), false))
								{
									//_playerPos.y = tile->GetColl()->Top() + tile->GetQuad()->GetHalfSize().y;
									_playerPos.y = tile->GetPos().y + 4.0f + tile->GetQuad()->GetHalfSize().y * 2.0f;
									this->SetAnimation(_2D_Player::State::L_RUN);
									return;
								}
							}
					}
					return;
				}
			}
			if (KEY_PRESS(VK_DOWN))
			{
				if (_ropeCol->IsCollision(rope->GetCol(), false))
				{
					_playerPos.x = rope->GetRopePos().x;
					_playerPos.y -= 150.0f * DELTA_TIME;
					_situ = _2D_Player::Situation::CLIMB;
					this->SetAnimation(_2D_Player::State::CLIMBING);
					if (col.second->Top() < rope->GetCol()->Bottom())
					{
						for (auto& floorTiles : _tiles)
							for (auto& tile : floorTiles)
							{
								if (col.second->IsCollision(tile->GetColl(), false))
								{
									_playerPos.y = tile->GetPos().y + 4.0f + tile->GetQuad()->GetHalfSize().y * 2.0f;
									this->SetAnimation(_2D_Player::State::L_RUN);
									return;
								}
							}
					}
					return;
				}
			}
		}
	}
	
	// 점프
	if (_isJumping == false)
	{
		if (KEY_PRESS(VK_SPACE))
		{
			_isJumping = true;
			_situ = _2D_Player::Situation::JUMP;
			return;
		}
	}

	// 공격
	// 한번 눌렀을 때 실행되게 해보자
	if (_isAttack == false)
	{
		if (KEY_PRESS(VK_CONTROL))
		{
			_isAttack = true;
			_situ = _2D_Player::Situation::ATTACK;
			return;
		}
	}


	{
		if (KEY_UP(VK_LEFT))
		{
			this->SetAnimation(_2D_Player::State::L_IDLE);
			_situ = _2D_Player::NONE;
		}
		if (KEY_UP(VK_RIGHT))
		{
			this->SetAnimation(_2D_Player::State::R_IDLE);
			_situ = _2D_Player::NONE;
		}
		if (KEY_UP(VK_UP))
		{
			this->SetAnimation(_2D_Player::State::CLIMBING_IDLE);
			_situ = _2D_Player::NONE;
		}
		if (KEY_UP(VK_DOWN))
		{
			this->SetAnimation(_2D_Player::State::CLIMBING_IDLE);
			_situ = _2D_Player::NONE;
		}
		if (KEY_UP(VK_CONTROL))
		{
			this->SetAnimation(_2D_Player::State::L_IDLE);
			_situ = _2D_Player::NONE;
		}
	}
}

void _2D_Player::Jumpimg()
{
	if (_isJumping == false)
		return;

	Vector2 temp;
	_jumpPower -= (float)pow(_gravity, 2) * DELTA_TIME;

	temp.y = _jumpPower;
	_playerPos += temp * DELTA_TIME;
	this->SetAnimation(_2D_Player::State::L_JUMP);

	for (auto& floorTiles : _tiles)
		for (auto& tile : floorTiles)
		{
			for(auto& sprite : _sprites)

				for (auto& col : _cols)
				{
					if (col.second->IsCollision(tile->GetColl(), false))
					{
						if (_playerPos.y <= tile->GetColl()->Top() + sprite.second->GetHalfFrameSize().y - 5.0f)
						{
							this->SetAnimation(_2D_Player::State::L_IDLE);
							_jumpPower = 150.0f;
							_isJumping = false;
						}
					}
				}	
		}
}

void _2D_Player::Attacking()
{
	if (_isAttack == false)
		return;

	// 어떤 조건절이 들어갔을때 어떠한 상황을 만들게 할것인가?
	if (_situ == _2D_Player::Situation::ATTACK)
	{
		this->SetAnimation(_2D_Player::State::R_ATTACK);
		_situ = _2D_Player::Situation::NONE;
		return;
	}
	if (_situ == _2D_Player::Situation::NONE)
	{
		this->SetAnimation(_2D_Player::State::L_IDLE);
		_isAttack = false;
		return;
	}

}
