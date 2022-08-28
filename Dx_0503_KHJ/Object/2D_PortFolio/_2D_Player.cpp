#include "framework.h"
#include "_2D_Player.h"

_2D_Player::_2D_Player()
{
	_sprite = make_shared<Sprite>(MAPLE_MOVE, Vector2(4,5));
	_col = make_shared<RectCollider>(_sprite->GetHalfFrameSize());
	_col->SetParent(_sprite->GetTransform());
	_ropeCol = make_shared<RectCollider>(Vector2(_sprite->GetHalfFrameSize().x - 10.0f, _sprite->GetHalfFrameSize().y + 7.0f));
	_ropeCol->SetParent(_sprite->GetTransform());
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
	DebugSetColor();

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

void _2D_Player::Render()
{
	_sprite->Render();
	
}

void _2D_Player::PostRender()
{
	ImGui::Text("PlayerX : %.1f, PlayerY : %.1f", _playerPos.x, _playerPos.y);
}

void _2D_Player::DebugRender()
{
	_col->Render();
	_ropeCol->Render();
}

void _2D_Player::DebugSetColor()
{
	for (auto& floorTiles : _tiles)
	{
		for (auto& tile : floorTiles)
		{
			if (_col->IsCollision(tile->GetColl(), false))
			{
				_col->SetRed();
				tile->GetColl()->SetRed();
			}
			else
			{
				_col->SetGreen();
				tile->GetColl()->SetGreen();
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
	_sprite->GetTransform()->GetPos() = { x,y };
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

void _2D_Player::Operation()
{
	for (auto& floorTiles : _tiles)
	{
		for (auto& tile : floorTiles)
		{
			if (_col->IsCollision(tile->GetColl(), false))
			{
				if (KEY_PRESS(VK_LEFT))
				{
					_playerPos.x -= 150.0f * DELTA_TIME;
					this->SetAnimation(_2D_Player::State::L_RUN);
					return;
				}
				if (KEY_PRESS(VK_RIGHT))
				{
					_playerPos.x += 150.0f * DELTA_TIME;
					this->SetAnimation(_2D_Player::State::R_RUN);
					return;
				}
			}
		}
	}

	for (auto& rope : _ropes)
	{
		if (KEY_PRESS(VK_UP))
		{
			if (_ropeCol->IsCollision(rope->GetCol(), false) && _col->IsCollision(rope->GetCol(), false))
			{
				_playerPos.x = rope->GetRopePos().x;
				_playerPos.y += 150.0f * DELTA_TIME;
				this->SetAnimation(_2D_Player::State::CLIMBING);

				if (_col->Top() >= rope->GetCol()->Top())
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
				this->SetAnimation(_2D_Player::State::CLIMBING);
				if (_col->Top() < rope->GetCol()->Bottom())
				{
					for (auto& floorTiles : _tiles)
						for (auto& tile : floorTiles)
						{
							if (_col->IsCollision(tile->GetColl(), false))
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
	
	if (_isJumping == false)
	{
		if (KEY_PRESS(VK_SPACE))
		{
			_isJumping = true;
			return;
		}
	}

	{
		if (KEY_UP(VK_LEFT))
			this->SetAnimation(_2D_Player::State::L_IDLE);
		if (KEY_UP(VK_RIGHT))
			this->SetAnimation(_2D_Player::State::R_IDLE);
		if (KEY_UP(VK_UP))
			this->SetAnimation(_2D_Player::State::CLIMBING_IDLE);
		if (KEY_UP(VK_DOWN))
			this->SetAnimation(_2D_Player::State::CLIMBING_IDLE);
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
			if (_col->IsCollision(tile->GetColl(), false))
			{
				if (_playerPos.y <= tile->GetColl()->Top() + _sprite->GetHalfFrameSize().y - 5.0f)
				{
					this->SetAnimation(_2D_Player::State::L_IDLE);
					_jumpPower = 150.0f;
					_isJumping = false;
				}
			}
		}
}
