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
	float w = _sprite->GetHalfFrameSize().x * 2.0f;
	float h = _sprite->GetHalfFrameSize().y * 2.0f;

	for (int i = 0; i < _maxFrame.y; i++)
	{
		for (int j = 0; j < _maxFrame.x; j++)
		{
			clips.emplace_back(i * w, j * h, w, h, Texture::Add(file));
		}
	}
	// Dx_0503_KHJ\Resource\Effects\skill_core_4x4.png
	size_t t = file.find(L"Effects/", 0);
	/*string temp;
	file.assign(temp.begin(), temp.end());
	temp = file.substr(0, t + 8);*/
	string temp = WstringToString(file.substr(0, t + 8));
	temp.substr(temp.length() - 4);

	/*wstring str = file.substr(29);
	str = file.substr(file.length()-4);*/
	_action = make_shared<Action>(clips, temp,Action::END, speed);
}

void Effect::Play(Vector2 pos)
{
	_sprite->GetTransform()->GetPos() = pos;
	_action->Play();
}
