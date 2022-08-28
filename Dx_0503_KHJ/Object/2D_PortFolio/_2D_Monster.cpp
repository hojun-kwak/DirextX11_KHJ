#include "framework.h"
#include "_2D_Monster.h"

_2D_Monster::_2D_Monster()
{
	_sprite = make_shared<Sprite>(MAPLE_RED_SNAIL, Vector2(3, 6));
	_col = make_shared<RectCollider>(_sprite->GetHalfFrameSize());
	_col = make_shared<RectCollider>(Vector2(_sprite->GetHalfFrameSize().x - 8.0f, _sprite->GetHalfFrameSize().y));
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
	// 176 360
	float maple_monster_depth = 273.0f;

	_actions.reserve(2);
	vector<Action::Clip> clips;
	float w = 176.0f / 3.0f;
	float h = maple_monster_depth / 6.0f;

	float y = 0;
	{
		clips.emplace_back(0, y, w, h, Texture::Add(MAPLE_RED_SNAIL));
	}
	_actions.push_back(make_shared<Action>(clips, "L_IDLE"));
	clips.clear();

	for (auto& action : _actions)
		action->Pause();

	_actions[State::L_IDLE]->Play();
}

void _2D_Monster::AutoMove()
{
}
