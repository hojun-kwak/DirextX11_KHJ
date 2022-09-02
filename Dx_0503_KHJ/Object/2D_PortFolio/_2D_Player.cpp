#include "framework.h"
#include "_2D_Player.h"

_2D_Player::_2D_Player()
{
	_MoveS = make_shared<Sprite>(MAPLE_MOVE, Vector2(4, 5));
	_MoveC = make_shared<RectCollider>(_MoveS->GetHalfFrameSize());
	_MoveC->SetParent(_MoveS->GetTransform());

	_ropeCol = make_shared<RectCollider>(Vector2(_MoveS->GetHalfFrameSize().x - 10.0f, _MoveS->GetHalfFrameSize().y + 10.0f));
	_ropeCol->SetParent(_MoveS->GetTransform());
	_ropeCol->SetBlue();

	_AttackS = make_shared<Sprite>(MAPLE_ATACK, Vector2(3,2));
	_AttackC = make_shared<RectCollider>(_AttackS->GetHalfFrameSize());
	_AttackC->SetParent(_AttackS->GetTransform());

	_tiles = _2D_ObjPManager::GetInstance()->GetTiles();
	_ropes = _2D_ObjPManager::GetInstance()->GetRopes();
	_mons  = _2D_ObjPManager::GetInstance()->GetMons();

	_playerPos = { _tiles[0][0]->GetPos().x, _tiles[0][0]->GetPos().y + _tiles[0][0]->GetQuad()->GetHalfSize().y * 2.0f };

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
	
	KnockBack();
	DebugSetColor();

	for (auto& sprite : _sprites)
		sprite.second->Update();

	for (auto& col : _cols)
		col.second->Update();

	_ropeCol->Update();

	for (auto& action : _actions)
	{
		action->Update();
		if (!action->IsPlay())
			continue;
		for (auto& sprites : _sprites)
			sprites.second->SetClipToActionBuffer(action->GetCurClip());
	}

	
}

void _2D_Player::Render()
{
	for (auto& sprite : _sprites)
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

	for (auto& cols : _cols)
	{
		for (auto& rope : _ropes)
		{
			if (cols.second->IsCollision(rope->GetCol(), false))
			{
				cols.second->SetRed();
				rope->GetCol()->SetRed();
			}
			else
			{
				cols.second->SetGreen();
				rope->GetCol()->SetGreen();
			}
		}


		for (auto& mons : _mons)
		{
			if (cols.first == "AttackC")
			{
				if (cols.second->IsCollision(mons->GetCol(), false))
				{
					cols.second->SetRed();
					mons->GetCol()->SetRed();
				}
				else
				{
					cols.second->SetGreen();
					mons->GetCol()->SetGreen();
				}
			}
		}
	}
}

void _2D_Player::SetPosition(float x, float y)
{
	for(auto& sprite : _sprites)
		sprite.second->GetTransform()->GetPos() = { x,y };

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

		if (_situ == _2D_Player::Situation::ATTACK)
		{
			_isAttack = false;
			action->Stop();
		}

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
	shared_ptr<Action> Lattack = make_shared<Action>(clips, "L_ATTACK", Action::LOOP);
	Lattack->SetEndEvent(std::bind(&_2D_Player::AttackEnd,this));
	_actions.push_back(Lattack);
	clips.clear();

	y = maple_attack_depth * (1.0f / 2.0f);
	{
		clips.emplace_back(0, y, w, h, Texture::Add(MAPLE_ATACK));
		clips.emplace_back(0 + w, y, w, h, Texture::Add(MAPLE_ATACK));
		clips.emplace_back(0 + w * 2, y, w, h, Texture::Add(MAPLE_ATACK));
	}
	shared_ptr<Action> Rattack = make_shared<Action>(clips, "R_ATTACK", Action::LOOP);
	Rattack->SetEndEvent(std::bind(&_2D_Player::AttackEnd, this));
	_actions.push_back(Rattack);
	clips.clear();

}

void _2D_Player::Operation()
{
	// 좌우 이동
	if (_isJumping == false)
	{
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
							if (tile->GetColl()->Left() < col.second->Left())
							{
								_playerPos.x -= 150.0f * DELTA_TIME;
								_situ = _2D_Player::Situation::MOVE;
								this->SetAnimation(_2D_Player::State::L_RUN);
								return;
							}
						}
						if (KEY_PRESS(VK_RIGHT))
						{
							if (tile->GetColl()->Right() > col.second->Right())
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
		}
	}

	// 위아래
	for (auto& rope : _ropes)
	{
		for (auto& col : _cols)
		{
			if (KEY_PRESS(VK_UP))
			{
				if (_ropeCol->IsCollision(rope->GetCol(), false))
				{
					_playerPos.x = rope->GetRopePos().x;
					_playerPos.y += 150.0f * DELTA_TIME;
					this->SetAnimation(_2D_Player::State::CLIMBING);
					_situ = _2D_Player::Situation::CLIMB;

					for (auto& floorTiles : _tiles)
						for (auto& tile : floorTiles)
						{
							if (col.second->IsCollision(tile->GetColl(), false))
							{
								if(_playerPos.y >= rope->GetCol()->Top())
								{
									_playerPos.x = tile->GetPos().x;
									_playerPos.y = tile->GetPos().y + tile->GetQuad()->GetHalfSize().y * 2.0f;
									this->SetAnimation(_2D_Player::State::L_IDLE);
									_situ = _2D_Player::Situation::NONE;
									return;
								}
							}
						}
				}
				return;
			}
			if (KEY_PRESS(VK_DOWN))
			{
				if (_ropeCol->IsCollision(rope->GetCol(), false))
				{
					_playerPos.x = rope->GetRopePos().x;
					_playerPos.y -= 150.0f * DELTA_TIME;
					this->SetAnimation(_2D_Player::State::CLIMBING);
					_situ = _2D_Player::Situation::CLIMB;
					if (col.second->Bottom() < rope->GetCol()->Bottom())
					{
						for (auto& floorTiles : _tiles)
							for (auto& tile : floorTiles)
							{
								if (col.second->IsCollision(tile->GetColl(), false))
								{
									_playerPos.x = tile->GetPos().x;
									_playerPos.y = tile->GetPos().y  + tile->GetQuad()->GetHalfSize().y * 2.0f;
									this->SetAnimation(_2D_Player::State::L_IDLE);
									_situ = _2D_Player::Situation::NONE;
									return;
								}
							}
					}
				}
				return;
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
			SOUND->Play("Jump", 0.1f);
			/*if (KEY_PRESS(VK_UP))
			{
				for (auto& rope : _ropes)
				{
					if (_ropeCol->IsCollision(rope->GetCol(),false))
					{
						_playerPos.x = rope->GetRopePos().x;
						_playerPos.y -= 150.0f * DELTA_TIME;
						this->SetAnimation(_2D_Player::State::CLIMBING);
						_situ = _2D_Player::Situation::CLIMB;
					}
				}
			}*/
			return;
		}
	}

	// 공격
	if (_situ == _2D_Player::Situation::NONE)
	{
		if (KEY_PRESS(VK_CONTROL))
		{
			_isAttack = true;
			_situ = _2D_Player::Situation::ATTACK;
			Attacking();
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
		if (KEY_UP(VK_UP) || KEY_UP(VK_DOWN))
		{
			if (_situ == _2D_Player::Situation::CLIMB)
			{
				this->SetAnimation(_2D_Player::State::CLIMBING_IDLE);
			}
			if (_situ == _2D_Player::Situation::NONE)
			{
				this->SetAnimation(_2D_Player::State::L_IDLE);
				_situ = _2D_Player::NONE;
			}
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
						if (_playerPos.y <= tile->GetPos().y + tile->GetQuad()->GetHalfSize().y * 2.0f)
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
	
	if (_aniState == _2D_Player::State::L_IDLE)
	{
		this->SetAnimation(_2D_Player::State::R_ATTACK);
	}
	if (_aniState == _2D_Player::State::R_IDLE)
	{
		this->SetAnimation(_2D_Player::State::L_ATTACK);
	}
	_isAttack = false;
	// 공격 모션이면서 
	for (auto& mons : _mons)
	{
		if (_AttackC->IsCollision(mons->GetCol(), false))
		{
			mons->_isActive = false;
			mons->Attacked();
			
			return;
		}
	}

	return;
	
}

void _2D_Player::KnockBack()
{
	/*for(auto& tiles : _tiles)
		for (auto& mons : _mons)
			if (_ropeCol->IsCollision(mons->GetCol(),false))
			{
				float temp = 50.0f;
				_playerPos.x += temp * DELTA_TIME;
			}*/
}
