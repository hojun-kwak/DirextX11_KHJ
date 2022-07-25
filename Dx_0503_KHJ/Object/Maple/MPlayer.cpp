#include "framework.h"
#include "MPlayer.h"

MPlayer::MPlayer()
{
	_sprite = make_shared<Sprite>(MAPLE_1,Vector2(4,5));
	//_sprite = make_shared<Sprite>(L"Resource/zelda.png", Vector2(10, 8));
	//_sprite->GetTransform()->GetPos() = Vector2(WIN_WIDTH, WIN_HEIGHT) * 0.5f;
	_col = make_shared<RectCollider>(_sprite->GetHalfFrameSize());
	_col->SetParent(_sprite->GetTransform());

	CreateData();
}

MPlayer::~MPlayer()
{
}

void MPlayer::Update()
{
	_sprite->Update();
	Operation();

	for (auto& action : _actions)
	{
		action->Update();
		if (!action->IsPlay())
			continue;
		_sprite->SetClipToActionBuffer(action->GetCurClip());
	}
	_col->Update();
}

void MPlayer::Render()
{
	_sprite->Render();
}

void MPlayer::PostRender()
{
	_col->Render();
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
		clips.emplace_back(0, y, w, h, Texture::Add(MAPLE_1));
	}
		_actions.push_back(make_shared<Action>(clips, "L_IDLE"));
		clips.clear();
	{
		clips.emplace_back(0 + w, y, w, h, Texture::Add(MAPLE_1));
	}
	_actions.push_back(make_shared<Action>(clips, "R_IDLE"));
	clips.clear();

	y = maple_player1_depth * (1.0f / 5.0f);
	{
		clips.emplace_back(0, y, w, h, Texture::Add(MAPLE_1));
		clips.emplace_back(0 + w, y, w, h, Texture::Add(MAPLE_1));
		clips.emplace_back(0 + w * 2, y, w, h, Texture::Add(MAPLE_1));
	}
	shared_ptr<Action> leftRun = make_shared<Action>(clips, "L_RUN", Action::LOOP);
	_actions.push_back(leftRun);
	clips.clear();

	y = maple_player1_depth * (2.0f / 5.0f);
	{
		clips.emplace_back(0, y, w, h, Texture::Add(MAPLE_1));
		clips.emplace_back(0 + w, y, w, h, Texture::Add(MAPLE_1));
		clips.emplace_back(0 + w * 2, y, w, h, Texture::Add(MAPLE_1));
	}
	shared_ptr<Action> rightRun = make_shared<Action>(clips, "R_RUN", Action::LOOP);
	_actions.push_back(rightRun);
	clips.clear();

	y = maple_player1_depth * (3.0f / 5.0f);
	{
		clips.emplace_back(0, y, w, h, Texture::Add(MAPLE_1));
	}
	_actions.push_back(make_shared<Action>(clips, "L_JUMP"));
	clips.clear();

	{
		clips.emplace_back(0 + w, y, w, h, Texture::Add(MAPLE_1));
	}
	_actions.push_back(make_shared<Action>(clips, "R_JUMP"));
	clips.clear();

	y = maple_player1_depth * (4.0f / 5.0f);
	{
		clips.emplace_back(0, y, w, h, Texture::Add(MAPLE_1));
		clips.emplace_back(0 + w, y, w, h, Texture::Add(MAPLE_1));
	}
	shared_ptr<Action> climbing = make_shared<Action>(clips, "CLIMBING", Action::LOOP);
	_actions.push_back(climbing);
	clips.clear();

	for (auto& action : _actions)
		action->Pause();

	_actions[State::L_IDLE]->Play();
}

void MPlayer::Operation()
{
	this->SetPosition(_playerPos.x, _playerPos.y);
	{
		if (KEY_PRESS(VK_LEFT))
		{
			_playerPos.x -= 150.0f * DELTA_TIME;
			this->SetAnimation(MPlayer::State::L_RUN);
			return;
		}
		if (KEY_PRESS(VK_RIGHT))
		{
			_playerPos.x += 150.0f * DELTA_TIME;
			this->SetAnimation(MPlayer::State::R_RUN);
			return;
		}
		if (KEY_PRESS(VK_DOWN))
		{
			_playerPos.y -= 150.0f * DELTA_TIME;
			this->SetAnimation(MPlayer::State::CLIMBING);
			return;
		}
		if (KEY_PRESS(VK_UP))
		{
			_playerPos.y += 150.0f * DELTA_TIME;
			this->SetAnimation(MPlayer::State::CLIMBING);
			return;
		}
	}
	{
		if (KEY_UP(VK_LEFT))
			this->SetAnimation(MPlayer::State::L_IDLE);
		if (KEY_UP(VK_RIGHT))
			this->SetAnimation(MPlayer::State::R_IDLE);
	}
}
