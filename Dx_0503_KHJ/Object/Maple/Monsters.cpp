#include "framework.h"
#include "Monsters.h"

Monsters::Monsters()
{
	_sprite = make_shared<Sprite>(MAPLE_MONSTER, Vector2(3,8));
	_col = make_shared<RectCollider>(_sprite->GetHalfFrameSize());
	_col->SetParent(_sprite->GetTransform());

	CreateData();
}

Monsters::~Monsters()
{
}

void Monsters::Update()
{
	_sprite->Update();
	Move();
	for (auto& action : _actions)
	{
		action->Update();
		if (!action->IsPlay())
			continue;
		_sprite->SetClipToActionBuffer(action->GetCurClip());
	}
	_col->Update();
}

void Monsters::Render()
{
	_sprite->Render();
}

void Monsters::PostRender()
{
	_col->Render();
}

void Monsters::SetPosition(float x, float y)
{
	_sprite->GetTransform()->GetPos() = { x,y };
	_monsterPos = { x,y };
}

void Monsters::SetAnimation(State aniState)
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

void Monsters::CreateData()
{
	// 176 360
	float maple_monster_depth = 360.0f;

	_actions.reserve(1);
	vector<Action::Clip> clips;
	float w = 176.0f / 3.0f;
	float h = maple_monster_depth / 8.0f;

	float y = 0;
	{
		clips.emplace_back(0, y, w, h, Texture::Add(MAPLE_MONSTER));
	}
	_actions.push_back(make_shared<Action>(clips, "L_IDLE"));
	clips.clear();

	for (auto& action : _actions)
		action->Pause();

	_actions[State::L_IDLE]->Play();
}

void Monsters::Move()
{
	this->SetPosition(_monsterPos.x, _monsterPos.y);

	{
		_monsterPos.x -= 150.0f * DELTA_TIME;
		this->SetAnimation(Monsters::State::L_IDLE);
	}
}
