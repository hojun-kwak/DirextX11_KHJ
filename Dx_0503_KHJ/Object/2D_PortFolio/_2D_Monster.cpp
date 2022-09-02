#include "framework.h"
#include "_2D_Monster.h"

_2D_Monster::_2D_Monster()
{
	_sprite = make_shared<Sprite>(MAPLE_RED_SNAIL, Vector2(2, 2));
	_col = make_shared<RectCollider>(_sprite->GetHalfFrameSize());
	_col = make_shared<RectCollider>(Vector2(_sprite->GetHalfFrameSize().x - 8.0f, _sprite->GetHalfFrameSize().y - 5.0f));
	_col->SetParent(_sprite->GetTransform());

	/*_MoveS = make_shared<Sprite>(MAPLE_RED_SNAIL, Vector2(2, 2));
	_MoveC = make_shared<RectCollider>(_MoveS->GetHalfFrameSize());
	_MoveC = make_shared<RectCollider>(Vector2(_MoveS->GetHalfFrameSize().x - 8.0f, _MoveS->GetHalfFrameSize().y - 5.0f));
	_MoveC->SetParent(_MoveS->GetTransform());*/

	/*_DeadS = make_shared<Sprite>(MAPLE_RED_SNAIL_DIE, Vector2(3, 2));
	_DeadC = make_shared<RectCollider>(_DeadS->GetHalfFrameSize());
	_DeadC = make_shared<RectCollider>(Vector2(_DeadS->GetHalfFrameSize().x - 8.0f, _DeadS->GetHalfFrameSize().y - 5.0f));
	_DeadC->SetParent(_DeadS->GetTransform());*/

	CreateData();
}

_2D_Monster::~_2D_Monster()
{
}

void _2D_Monster::Update()
{
	if (_isActive == false)
		return;

	this->SetPosition(_monsterPos.x, _monsterPos.y);
	AutoMove();
	_sprite->Update();
	_col->Update();

	/*for (auto& sprite : _sprites)
	{
		if (_aniState == L_DEAD || _aniState == R_DEAD)
		{
			if (sprite.first == "DeadS")
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
		if (_aniState == L_DEAD || _aniState == R_DEAD)
		{
			if (col.first == "DeadC")
				col.second->Update();
		}
		else
		{
			if (col.first == "MoveC")
				col.second->Update();
		}
	}*/
	for (auto& action : _actions)
	{
		action->Update();
		if (!action->IsPlay())
			continue;
		_sprite->SetClipToActionBuffer(action->GetCurClip());
		/*for (auto& sprites : _sprites)
			sprites.second->SetClipToActionBuffer(action->GetCurClip());*/
	}
}

void _2D_Monster::Render()
{
	if (_isActive == false)
		return;

	_sprite->Render();

	/*for (auto& sprite : _sprites)
	{
		if (_aniState == L_DEAD || _aniState == R_DEAD)
		{
			if (sprite.first == "DeadS")
				sprite.second->Render();
		}
		else
		{
			if (sprite.first == "MoveS")
				sprite.second->Render();
		}
	}*/
}

void _2D_Monster::DebugRender()
{
	if (_isActive == false)
		return;

	_col->Render();

	/*for (auto& col : _cols)
	{
		if (_aniState == L_DEAD || _aniState == R_DEAD)
		{
			if (col.first == "DeadC")
				col.second->Render();
		}
		else
		{
			if (col.first == "MoveC")
				col.second->Render();
		}
	}*/
}

void _2D_Monster::SetPosition(float x, float y)
{
	_sprite->GetTransform()->GetPos() = { x,y };
	/*for (auto& sprite : _sprites)
		sprite.second->GetTransform()->GetPos() = { x,y };*/
	_monsterPos = { x,y };
}

void _2D_Monster::SetAnimation(State aniState)
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

void _2D_Monster::CreateData()
{
	/*_sprites.insert(make_pair("MoveS", _MoveS));
	_cols.insert(make_pair("MoveC", _MoveC));
	_sprites.insert(make_pair("DeadS", _DeadS));
	_cols.insert(make_pair("DeadC", _DeadC));*/

	_actions.reserve(4);

	CreateMoveData();
	//CreateDeadData();

	for (auto& action : _actions)
		action->Pause();

	_actions[State::L_IDLE]->Play();

}

void _2D_Monster::CreateMoveData()
{
	// 92 100
	float maple_monster_depth = 100.0f;
	float w = 92.0f / 2.0f;
	float h = maple_monster_depth / 2.0f;

	float y = 0;
	{
		clips.emplace_back(0, y, w, h, Texture::Add(MAPLE_RED_SNAIL));
	}
	_actions.push_back(make_shared<Action>(clips, "L_IDLE"));
	clips.clear();
	{
		clips.emplace_back(0 + w, y, w, h, Texture::Add(MAPLE_RED_SNAIL));
	}
	_actions.push_back(make_shared<Action>(clips, "L_STEP_BACK"));
	clips.clear();

	y = maple_monster_depth * (1.0f / 2.0f);
	{
		clips.emplace_back(0, y, w, h, Texture::Add(MAPLE_RED_SNAIL));
	}
	_actions.push_back(make_shared<Action>(clips, "R_IDLE"));
	clips.clear();
	{
		clips.emplace_back(0 + w, y, w, h, Texture::Add(MAPLE_RED_SNAIL));
	}
	_actions.push_back(make_shared<Action>(clips, "R_STEP_BACK"));
	clips.clear();
}

void _2D_Monster::CreateDeadData()
{
	// 173 / 92
	float maple_monster_depth = 92.0f;
	float w = 173.0f / 3.0f;
	float h = maple_monster_depth / 2.0f;

	float y = 0;
	{
		clips.emplace_back(0, y, w, h, Texture::Add(MAPLE_RED_SNAIL_DIE));
		clips.emplace_back(0 + w, y, w, h, Texture::Add(MAPLE_RED_SNAIL_DIE));
		clips.emplace_back(0 + w * 2, y, w, h, Texture::Add(MAPLE_RED_SNAIL_DIE));
	}
	shared_ptr<Action> L_die = make_shared<Action>(clips, "L_DEAD", Action::LOOP);
	_actions.push_back(L_die);
	clips.clear();

	y = maple_monster_depth * (1.0f / 2.0f);
	{
		clips.emplace_back(0, y, w, h, Texture::Add(MAPLE_RED_SNAIL_DIE));
		clips.emplace_back(0 + w, y, w, h, Texture::Add(MAPLE_RED_SNAIL_DIE));
		clips.emplace_back(0 + w * 2, y, w, h, Texture::Add(MAPLE_RED_SNAIL_DIE));
	}
	shared_ptr<Action> R_die = make_shared<Action>(clips, "R_DEAD", Action::LOOP);
	_actions.push_back(R_die);
	clips.clear();
}

void _2D_Monster::AutoMove()
{
	_monsterPos.y = _tiles[0]->GetColl()->Top() + 10.0f;
	if (_dir == _2D_Monster::Direction::LEFT)
	{
		if (_monsterPos.x >= _tiles[0]->GetPos().x)
		{
			_monsterPos.x -= 100.0f * DELTA_TIME;
			this->SetAnimation(_2D_Monster::State::L_IDLE);
			return;
		}
		else
		{
			_dir = _2D_Monster::Direction::RIGHT;
			return;
		}
	}
	if (_dir == _2D_Monster::Direction::RIGHT)
	{
		if (_monsterPos.x <= _tiles[5]->GetPos().x)
		{
			_monsterPos.x += 100.0f * DELTA_TIME;
			this->SetAnimation(_2D_Monster::State::R_IDLE);
			return;
		}
		else
		{
			_dir = _2D_Monster::Direction::LEFT;
			return;
		}
	}
}

void _2D_Monster::Attacked()
{
	if(_dir == _2D_Monster::Direction::LEFT)
		_aniState = _2D_Monster::State::L_STEP_BACK;
	if (_dir == _2D_Monster::Direction::RIGHT)
		_aniState = _2D_Monster::State::R_STEP_BACK;
}
