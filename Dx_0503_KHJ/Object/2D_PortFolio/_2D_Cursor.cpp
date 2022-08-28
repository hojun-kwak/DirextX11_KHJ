#include "framework.h"
#include "_2D_Cursor.h"

_2D_Cursor::_2D_Cursor()
{
	_sprite = make_shared<Sprite>(MAPLE_MOUSE_CURSOR, Vector2(4, 1));
	_col = make_shared<RectCollider>(_sprite->GetHalfFrameSize());
	_col->SetParent(_sprite->GetTransform());

	CreateData();
}

_2D_Cursor::~_2D_Cursor()
{
}

void _2D_Cursor::Update()
{
	_sprite->Update();
	ClickEvent();

	for (auto& action : _actions)
	{
		action->Update();
		if (!action->IsPlay())
			continue;
		_sprite->SetClipToActionBuffer(action->GetCurClip());
	}
	_col->Update();
}

void _2D_Cursor::Render()
{
	_sprite->Render();
}

void _2D_Cursor::DebugRender()
{
	_col->Render();
}

void _2D_Cursor::SetPosition(Vector2 mousePos)
{
	_sprite->GetTransform()->GetPos() = mousePos;
	_mousePos = mousePos;
}

void _2D_Cursor::SetAnimation(State aniState)
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

void _2D_Cursor::CreateData()
{
	// 148 39
	_actions.reserve(1);
	vector<Action::Clip> clips;
	float w = 140.0f / 4.0f;
	float h = 39.0f / 1.0f;

	float y = 0;
	{
		clips.emplace_back(0, y, w, h, Texture::Add(MAPLE_MOUSE_CURSOR));
		_actions.push_back(make_shared<Action>(clips, "NONE"));
		clips.clear();
	}
	{
		clips.emplace_back(0 + w * 2, y, w, h, Texture::Add(MAPLE_MOUSE_CURSOR));
		_actions.push_back(make_shared<Action>(clips, "CLICK"));
		clips.clear();
	}

	for (auto& action : _actions)
		action->Pause();

	_actions[State::NONE]->Play();
}

void _2D_Cursor::ClickEvent()
{
	if (KEY_PRESS(VK_LBUTTON))
		this->SetAnimation(_2D_Cursor::State::CLICK);

	if (KEY_UP(VK_LBUTTON))
		this->SetAnimation(_2D_Cursor::State::NONE);
}
