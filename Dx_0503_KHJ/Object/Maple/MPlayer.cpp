#include "framework.h"
#include "MPlayer.h"

MPlayer::MPlayer()
{
	//_sprite = make_shared<Sprite>(L"Resource/Maple/charactorNormal.png", Vector2(4, 6));
	_sprite = make_shared<Sprite>(L"Resource/zelda.png", Vector2(10, 8));
	_sprite->GetTransform()->GetPos() = Vector2(WIN_WIDTH, WIN_HEIGHT) * 0.5f;
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
}

void MPlayer::CreateData()
{

	_actions.reserve(1);
	{
		vector<Action::Clip> clips;
		//692 / 360;
		// 4 * 6
		float w = 1200.0f / 10.0f;
		float h = 1040.0f / 8.0f;

		float y = 0;
		{
			clips.emplace_back(0, y, w, h, Texture::Add(L"Resource/zelda.png"));
		}
		_actions.push_back(make_shared<Action>(clips, "L_IDLE"));
		clips.clear();

		
	}

	for (auto& action : _actions)
		action->Pause();
}
