#include "framework.h"
#include "Effect.h"

Effect::Effect(wstring file, Vector2 maxframe, float speed)
	:_maxFrame(maxframe)
{
	_sprite = make_shared<Sprite>(file, maxframe);
	CreateAction(file, speed);
	//_action = make_shared<Action>();
	_action->SetEndEvent(std::bind(&Effect::End, this));
}

Effect::~Effect()
{
}

void Effect::Update()
{
	if (!_isActive)
		return;

	_sprite->Update();
	_action->Update();
	_sprite->SetClipToActionBuffer(_action->GetCurClip());
}

void Effect::Render()
{
	if (!_isActive)
		return;

	_sprite->Render();
}

void Effect::CreateAction(wstring file, float speed)
{
	vector<Action::Clip> clips;
	float w = _sprite->GetHalfFrameSize().x * 2;
	float h = _sprite->GetHalfFrameSize().y * 2;

	for (int y = 0; y < _maxFrame.y; y++)
	{
		for (int x = 0; x < _maxFrame.x; x++)
		{
			clips.emplace_back(x * w, y * h, w, h, Texture::Add(file));
		}
	}

	size_t t = file.find(L"Effects/", 0);
	string temp = WstringToString(file.substr(t + 8, file.length()));

	_action = make_shared<Action>(clips, temp.substr(0, temp.length() - 4), Action::END, speed);
}

void Effect::Play(Vector2 pos)
{
	_isActive = true;
	_sprite->GetTransform()->GetPos() = pos;
	_action->Play();
}

void Effect::Stop(Vector2 pos)
{
	_isActive = false;
	_sprite->GetTransform()->GetPos() = pos;
	_action->Stop();
}
