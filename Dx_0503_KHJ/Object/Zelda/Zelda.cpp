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
	/*_action->Update();
	_sprite->SetClip(_action->GetCurClip());*/

	for (auto& action : _actions)
	{
		action->Update();
		if (!action->IsPlay())
			continue;
		_sprite->SetClip(action->GetCurClip());
	}

	_collider->Update();
}

void Zelda::Render()
{
	_sprite->Render();
	_collider->Render();
}

void Zelda::PostRender()
{
	ImGui::Text(_msg.data());
}

void Zelda::SetPosition(float x, float y)
{
}

void Zelda::SetAnimation(State aniState)
{
	for (auto& action : _actions)
	{
		action->Stop();
	}
	_actions[aniState]->Play();
}

void Zelda::CreateData()
{
	_actions.reserve(8);

	{
		vector<Action::Clip> clips;
		float w = 1200.0f / 10.0f;
		float h = 1040.0f / 8.0f;

		// 정면
		float y = 0;
		{
			clips.emplace_back(0, y, w, h, Texture::Add(L"Resource/zelda.png"));
			clips.emplace_back(0 + w, y, w, h, Texture::Add(L"Resource/zelda.png"));
			clips.emplace_back(0 + w * 2, y, w, h, Texture::Add(L"Resource/zelda.png"));
		}
		_actions.push_back(make_shared<Action>(clips, "F_IDLE"));
		clips.clear();

		// 왼쪽
		y = 1040.0f * (1.0f / 8.0f);
		{
			clips.emplace_back(0, y, w, h, Texture::Add(L"Resource/zelda.png"));
			clips.emplace_back(0 + w, y, w, h, Texture::Add(L"Resource/zelda.png"));
			clips.emplace_back(0 + w * 2, y, w, h, Texture::Add(L"Resource/zelda.png"));
		}
		_actions.push_back(make_shared<Action>(clips, "L_IDLE"));
		clips.clear();

		// 뒤
		y = 1040.0f * (2.0f / 8.0f);
		{
			clips.emplace_back(0, y, w, h, Texture::Add(L"Resource/zelda.png"));
		}
		_actions.push_back(make_shared<Action>(clips, "B_IDLE"));
		clips.clear();

		// 오른쪽
		y = 1040.0f * (3.0f / 8.0f);
		{
			shared_ptr<Action> frontRun = make_shared<Action>(clips, "R_IDLE");
			clips.emplace_back(0, y, w, h, Texture::Add(L"Resource/zelda.png"));
			clips.emplace_back(0 + w, y, w, h, Texture::Add(L"Resource/zelda.png"));
			clips.emplace_back(0 + w * 2, y, w, h, Texture::Add(L"Resource/zelda.png"));
		}
		_actions.push_back(make_shared<Action>(clips, "R_IDLE"));
		clips.clear();

		y = 1040 * 0.5f;
		// ������ �޸���
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
		_actions.push_back(make_shared<Action>(clips, "F_RUN"));
		clips.clear();

		y = 1040 * (5.0f / 8.0f);
		// ������ �޸���
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
		_actions.push_back(make_shared<Action>(clips, "L_RUN"));
		clips.clear();

		y = 1040 * (6.0f / 8.0f);
		// �ڷ� �޸���
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
		_actions.push_back(make_shared<Action>(clips, "B_RUN"));
		clips.clear();

		y = 1040 * (7.0f / 8.0f);
		// ���� �޸���
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
		_actions.push_back(make_shared<Action>(clips, "R_RUN"));
		clips.clear();

	}

	for (auto& action : _actions)
		action->Pause();

	_actions[State::R_RUN]->Play();


}