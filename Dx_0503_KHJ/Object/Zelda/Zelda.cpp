#include "framework.h"
#include "Zelda.h"

Zelda::Zelda()
{
	_sprite = make_shared<Sprite>(L"Resource/zelda.png", Vector2(10, 8));
	_sprite->GetTransform()->GetPos() = Vector2(WIN_WIDTH, WIN_HEIGHT) * 0.5f;
	_collider = make_shared<RectCollider>(_sprite->GetHalfFrameSize());
	_collider->SetParent(_sprite->GetTransform());

	CreateData();
}

Zelda::~Zelda()
{
}

void Zelda::Update()
{
	_sprite->Update();
	Move();
	/*_action->Update();
	_sprite->SetClip(_action->GetCurClip());*/

	for (auto& action : _actions)
	{
		action->Update();
		if (!action->IsPlay())
			continue;
		//_sprite->SetClip(action->GetCurClip());
		_sprite->SetClipToActionBuffer(action->GetCurClip());
	}
	_collider->Update();
}

void Zelda::Render()
{
	_sprite->Render();
}

void Zelda::PostRender()
{
	ImGui::Text(_msg.data());
	// 나중에 안보이게 할때 postRender을 꺼준다.
	_collider->Render();
}

void Zelda::SetPosition(float x, float y)
{
	_sprite->GetTransform()->GetPos() = { x,y };
}

void Zelda::SetAnimation(State aniState)
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

void Zelda::CreateData()
{
	_actions.reserve(8);

	// Action 세팅
	{
		vector<Action::Clip> clips;
		float w = 1200.0f / 10.0f;
		float h = 1040.0f / 8.0f;

		// 앞 가만히
		float y = 0;
		{
			clips.emplace_back(0, y, w, h, Texture::Add(L"Resource/zelda.png"));
			clips.emplace_back(0 + w, y, w, h, Texture::Add(L"Resource/zelda.png"));
			clips.emplace_back(0 + w * 2, y, w, h, Texture::Add(L"Resource/zelda.png"));
		}

		_actions.push_back(make_shared<Action>(clips, "F_IDLE"));
		clips.clear();

		// 왼 가만히
		y = 1040.0f * (1.0f / 8.0f);
		{
			clips.emplace_back(0, y, w, h, Texture::Add(L"Resource/zelda.png"));
			clips.emplace_back(0 + w, y, w, h, Texture::Add(L"Resource/zelda.png"));
			clips.emplace_back(0 + w * 2, y, w, h, Texture::Add(L"Resource/zelda.png"));
		}
		_actions.push_back(make_shared<Action>(clips, "L_IDLE"));
		clips.clear();

		// 뒤 가만히
		y = 1040.0f * (2.0f / 8.0f);
		{
			clips.emplace_back(0, y, w, h, Texture::Add(L"Resource/zelda.png"));
		}
		_actions.push_back(make_shared<Action>(clips, "B_IDLE"));
		clips.clear();

		// 오 가만히
		y = 1040.0f * (3.0f / 8.0f);
		{
			clips.emplace_back(0, y, w, h, Texture::Add(L"Resource/zelda.png"));
			clips.emplace_back(0 + w, y, w, h, Texture::Add(L"Resource/zelda.png"));
			clips.emplace_back(0 + w * 2, y, w, h, Texture::Add(L"Resource/zelda.png"));
		}
		shared_ptr<Action> rightIDLE = make_shared<Action>(clips, "R_IDLE");
		_actions.push_back(rightIDLE);
		clips.clear();

		y = 1040 * 0.5f;
		// 앞으로 달리기
		{
			clips.emplace_back(0, y, w, h, Texture::Add(L"Resource/zelda.png"));
			clips.emplace_back(0 + w, y, w, h, Texture::Add(L"Resource/zelda.png"));
			clips.emplace_back(0 + w * 2, y, w, h, Texture::Add(L"Resource/zelda.png"));
			clips.emplace_back(0 + w * 3, y, w, h, Texture::Add(L"Resource/zelda.png"));
			clips.emplace_back(0 + w * 4, y, w, h, Texture::Add(L"Resource/zelda.png"));
			clips.emplace_back(0 + w * 5, y, w, h, Texture::Add(L"Resource/zelda.png"));
			clips.emplace_back(0 + w * 6, y, w, h, Texture::Add(L"Resource/zelda.png"));
			clips.emplace_back(0 + w * 7, y, w, h, Texture::Add(L"Resource/zelda.png"));
			clips.emplace_back(0 + w * 8, y, w, h, Texture::Add(L"Resource/zelda.png"));
			clips.emplace_back(0 + w * 9, y, w, h, Texture::Add(L"Resource/zelda.png"));
		}
		//_actions.push_back(make_shared<Action>(clips, "F_RUN"));
		shared_ptr<Action> frontRUN = make_shared<Action>(clips, "F_RUN", Action::LOOP);
		frontRUN->SetEndEvent(std::bind(&Zelda::SetF_Msg, this));
		_actions.push_back(frontRUN);
		clips.clear();

		y = 1040 * (5.0f / 8.0f);
		// 왼으로 달리기
		{
			clips.emplace_back(0, y, w, h, Texture::Add(L"Resource/zelda.png"));
			clips.emplace_back(0 + w, y, w, h, Texture::Add(L"Resource/zelda.png"));
			clips.emplace_back(0 + w * 2, y, w, h, Texture::Add(L"Resource/zelda.png"));
			clips.emplace_back(0 + w * 3, y, w, h, Texture::Add(L"Resource/zelda.png"));
			clips.emplace_back(0 + w * 4, y, w, h, Texture::Add(L"Resource/zelda.png"));
			clips.emplace_back(0 + w * 5, y, w, h, Texture::Add(L"Resource/zelda.png"));
			clips.emplace_back(0 + w * 6, y, w, h, Texture::Add(L"Resource/zelda.png"));
			clips.emplace_back(0 + w * 7, y, w, h, Texture::Add(L"Resource/zelda.png"));
			clips.emplace_back(0 + w * 8, y, w, h, Texture::Add(L"Resource/zelda.png"));
			clips.emplace_back(0 + w * 9, y, w, h, Texture::Add(L"Resource/zelda.png"));
		}
		//_actions.push_back(make_shared<Action>(clips, "L_RUN"));
		shared_ptr<Action> LeftRun = make_shared<Action>(clips, "L_RUN", Action::LOOP);
		LeftRun->SetEndEvent(std::bind(&Zelda::SetL_Msg, this));
		//LeftRun->SetEvent(std::bind(&Zelda::SetMsg, this));
		_actions.push_back(LeftRun);
		clips.clear();

		y = 1040 * (6.0f / 8.0f);
		// 뒤로 달리기
		{
			clips.emplace_back(0, y, w, h, Texture::Add(L"Resource/zelda.png"));
			clips.emplace_back(0 + w, y, w, h, Texture::Add(L"Resource/zelda.png"));
			clips.emplace_back(0 + w * 2, y, w, h, Texture::Add(L"Resource/zelda.png"));
			clips.emplace_back(0 + w * 3, y, w, h, Texture::Add(L"Resource/zelda.png"));
			clips.emplace_back(0 + w * 4, y, w, h, Texture::Add(L"Resource/zelda.png"));
			clips.emplace_back(0 + w * 5, y, w, h, Texture::Add(L"Resource/zelda.png"));
			clips.emplace_back(0 + w * 6, y, w, h, Texture::Add(L"Resource/zelda.png"));
			clips.emplace_back(0 + w * 7, y, w, h, Texture::Add(L"Resource/zelda.png"));
			clips.emplace_back(0 + w * 8, y, w, h, Texture::Add(L"Resource/zelda.png"));
			clips.emplace_back(0 + w * 9, y, w, h, Texture::Add(L"Resource/zelda.png"));
		}
		//_actions.push_back(make_shared<Action>(clips, "B_RUN"));
		shared_ptr<Action> backRun = make_shared<Action>(clips, "B_RUN", Action::LOOP);
		backRun->SetEndEvent(std::bind(&Zelda::SetB_Msg, this));
		_actions.push_back(backRun);
		clips.clear();

		y = 1040 * (7.0f / 8.0f);
		// 오른 달리기
		{
			clips.emplace_back(0, y, w, h, Texture::Add(L"Resource/zelda.png"));
			clips.emplace_back(0 + w, y, w, h, Texture::Add(L"Resource/zelda.png"));
			clips.emplace_back(0 + w * 2, y, w, h, Texture::Add(L"Resource/zelda.png"));
			clips.emplace_back(0 + w * 3, y, w, h, Texture::Add(L"Resource/zelda.png"));
			clips.emplace_back(0 + w * 4, y, w, h, Texture::Add(L"Resource/zelda.png"));
			clips.emplace_back(0 + w * 5, y, w, h, Texture::Add(L"Resource/zelda.png"));
			clips.emplace_back(0 + w * 6, y, w, h, Texture::Add(L"Resource/zelda.png"));
			clips.emplace_back(0 + w * 7, y, w, h, Texture::Add(L"Resource/zelda.png"));
			clips.emplace_back(0 + w * 8, y, w, h, Texture::Add(L"Resource/zelda.png"));
			clips.emplace_back(0 + w * 9, y, w, h, Texture::Add(L"Resource/zelda.png"));
		}
		//_actions.push_back(make_shared<Action>(clips, "R_RUN"));
		shared_ptr<Action> rightRun = make_shared<Action>(clips, "R_RUN", Action::LOOP);
		rightRun->SetEndEvent(std::bind(&Zelda::SetL_Msg, this));
		_actions.push_back(rightRun);
		clips.clear();
	}

	// R_RUN을 쓰면 벡터 크기 오류
	for (auto& action : _actions)
		action->Pause();

	//_actions[State::F_IDLE]->Play();
}

void Zelda::Move()
{
	if (KEY_PRESS(VK_LEFT))
	{
		_sprite->GetTransform()->GetPos().x -= 100 * DELTA_TIME;
	}

	if (KEY_PRESS(VK_RIGHT))
	{
		_sprite->GetTransform()->GetPos().x += 100 * DELTA_TIME;
	}

	if (KEY_PRESS(VK_UP))
	{
		_sprite->GetTransform()->GetPos().y += 100 * DELTA_TIME;
	}

	if (KEY_PRESS(VK_DOWN))
	{
		_sprite->GetTransform()->GetPos().y -= 100 * DELTA_TIME;
	}
}
