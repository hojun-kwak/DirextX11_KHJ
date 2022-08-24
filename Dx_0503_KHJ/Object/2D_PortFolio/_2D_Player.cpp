#include "framework.h"
#include "_2D_Player.h"

_2D_Player::_2D_Player()
{
	_sprite = make_shared<Sprite>(MAPLE_MOVE, Vector2(4,5));
	_col = make_shared<RectCollider>(_sprite->GetHalfFrameSize());
	_col->SetParent(_sprite->GetTransform());

	CreateData();
}

_2D_Player::~_2D_Player()
{
}

void _2D_Player::Update()
{
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
