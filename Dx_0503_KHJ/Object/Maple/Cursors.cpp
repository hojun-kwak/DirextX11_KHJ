#include "framework.h"
#include "Cursors.h"

Cursors::Cursors()
{
	_sprite = make_shared<Sprite>(MAPLE_MOUSE_CURSOR, Vector2(4,1));
	_col = make_shared<RectCollider>(_sprite->GetHalfFrameSize());
	_col->SetParent(_sprite->GetTransform());

	CreateData();
}

Cursors::~Cursors()
{
}

void Cursors::Update()
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

void Cursors::Render()
{
	_sprite->Render();
}

void Cursors::PostRender()
{
	_col->Render();
}

void Cursors::SetPosition(Vector2 mousePos)
{
	_sprite->GetTransform()->GetPos() = CENTER;
	_mousePos = CENTER;
}

void Cursors::SetAnimation(State aniState)
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

void Cursors::CreateData()
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

void Cursors::ClickEvent()
{
	if (KEY_PRESS(VK_LBUTTON))
		this->SetAnimation(Cursors::State::CLICK);

	if (KEY_UP(VK_LBUTTON))
		this->SetAnimation(Cursors::State::NONE);
}
