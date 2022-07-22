#include "framework.h"
#include "MPlayer.h"

MPlayer::MPlayer()
{
	_sprite = make_shared<Sprite>(Texture::Add(L"Resource/Maple/charactorNormal.png"), Vector2(4, 6));
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
	for (auto& action : _actions)
	{
		action->Update();
		if (!action->IsPlay())
			continue;
		_sprite->SetClipToActionBuffer(action->GetCurClip());
	}
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
	//_sprite->GetTransform()->GetPos() = { x,y };
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
	// test
	//_actions.reserve(1);
	//{
	//	vector<Action::Clip> clips;
	//	//692 / 360;
	//	// 4 * 6
	//	float w = 1200.0f / 10.0f;
	//	float h = 1040.0f / 8.0f;

	//	float y = 0;
	//	{
	//		clips.emplace_back(0, y, w, h, Texture::Add(L"Resource/zelda.png"));
	//		clips.emplace_back(0 + w, y, w, h, Texture::Add(L"Resource/zelda.png"));
	//		clips.emplace_back(0 + w * 2, y, w, h, Texture::Add(L"Resource/zelda.png"));
	//	}
	//	_actions.push_back(make_shared<Action>(clips, "L_IDLE"));
	//	clips.clear();
	//}

	_actions.reserve(1);
	vector<Action::Clip> clips;
	float w = 224.0f / 4.0f;
	float h = 360.0f / 6.0f;

	float y = 0;
	{
		clips.emplace_back(0 , y, w, h, Texture::Add(L"Resource/Maple/charactorNormal.png"));
	}
	_actions.push_back(make_shared<Action>(clips, "L_IDLE"));
	clips.clear();

	{
		clips.emplace_back(0 + w, y, w, h, Texture::Add(L"Resource/Maple/charactorNormal.png"));
	}
	_actions.push_back(make_shared<Action>(clips, "R_IDLE"));
	clips.clear();

	/*y = 360.0f * (1.0f / 6.0f);
	{
		clips.emplace_back(0, y, w, h, Texture::Add(L"Resource/Maple/charactorNormal.png"));
		clips.emplace_back(0 + w, y, w, h, Texture::Add(L"Resource/Maple/charactorNormal.png"));
		clips.emplace_back(0 + w * 2, y, w, h, Texture::Add(L"Resource/Maple/charactorNormal.png"));
	}
	shared_ptr<Action> leftRun = make_shared<Action>(clips, "L_RUN", Action::LOOP);
	_actions.push_back(leftRun);
	clips.clear();

	y = 360.0f * (2.0f / 6.0f);
	{
		clips.emplace_back(0, y, w, h, Texture::Add(L"Resource/Maple/charactorNormal.png"));
		clips.emplace_back(0 + w, y, w, h, Texture::Add(L"Resource/Maple/charactorNormal.png"));
		clips.emplace_back(0 + w * 2, y, w, h, Texture::Add(L"Resource/Maple/charactorNormal.png"));
	}
	shared_ptr<Action> rightRun = make_shared<Action>(clips, "R_RUN", Action::LOOP);
	_actions.push_back(rightRun);
	clips.clear();*/

	y = 360.0f * (3.0f / 6.0f);
	{
		clips.emplace_back(0, y, w, h, Texture::Add(L"Resource/Maple/charactorNormal.png"));
	}
	_actions.push_back(make_shared<Action>(clips, "L_JUMP"));
	clips.clear();

	y = 360.0f * (4.0f / 6.0f);
	{
		clips.emplace_back(0, y, w, h, Texture::Add(L"Resource/Maple/charactorNormal.png"));
	}
	_actions.push_back(make_shared<Action>(clips, "R_JUMP"));
	clips.clear();

	/*y = 360.0f * (5.0f / 6.0f);
	{
		clips.emplace_back(0, y, w, h, Texture::Add(L"Resource/Maple/charactorNormal.png"));
		clips.emplace_back(0 + w, y, w, h, Texture::Add(L"Resource/Maple/charactorNormal.png"));
	}
	shared_ptr<Action> climbing = make_shared<Action>(clips, "CLIMBING", Action::LOOP);
	_actions.push_back(climbing);
	clips.clear();*/

	for (auto& action : _actions)
		action->Pause();

	_actions[State::R_IDLE]->Play();
}
