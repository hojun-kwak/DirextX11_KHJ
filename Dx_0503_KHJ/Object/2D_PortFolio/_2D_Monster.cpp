#include "framework.h"
#include "_2D_Monster.h"

_2D_Monster::_2D_Monster()
{
	_sprite = make_shared<Sprite>(MAPLE_RED_SNAIL, Vector2(2, 2));
	_col = make_shared<RectCollider>(_sprite->GetHalfFrameSize());
	_col = make_shared<RectCollider>(Vector2(_sprite->GetHalfFrameSize().x - 8.0f, _sprite->GetHalfFrameSize().y - 5.0f));
	_col->SetParent(_sprite->GetTransform());

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
	for (auto& action : _actions)
	{
		action->Update();
		if (!action->IsPlay())
			continue;
		_sprite->SetClipToActionBuffer(action->GetCurClip());
	}
	_col->Update();
}

void _2D_Monster::Render()
{
	if (_isActive == false)
		return;

	_sprite->Render();
}

void _2D_Monster::DebugRender()
{
	if (_isActive == false)
		return;

	_col->Render();
}

void _2D_Monster::SetPosition(float x, float y)
{
	_sprite->GetTransform()->GetPos() = { x,y };
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
	// 92 100
	float maple_monster_depth = 100.0f;

	_actions.reserve(4);
	vector<Action::Clip> clips;
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
		clips.emplace_back(0 , y, w, h, Texture::Add(MAPLE_RED_SNAIL));
	}
	_actions.push_back(make_shared<Action>(clips, "R_IDLE"));
	clips.clear();
	{
		clips.emplace_back(0 + w, y, w, h, Texture::Add(MAPLE_RED_SNAIL));
	}
	_actions.push_back(make_shared<Action>(clips, "R_STEP_BACK"));
	clips.clear();

	for (auto& action : _actions)
		action->Pause();

	_actions[State::L_IDLE]->Play();
}

void _2D_Monster::AutoMove()
{
	_monsterPos.y = _tiles[1][0]->GetColl()->Top() + 10.0f;
	if (_dir == _2D_Monster::Direction::LEFT)
	{
		if (_monsterPos.x >= _tiles[1][0]->GetPos().x)
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
		if (_monsterPos.x <= _tiles[1][5]->GetPos().x)
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
