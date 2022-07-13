#include "framework.h"
#include "CameraScene.h"

CameraScene::CameraScene()
{
	_background = make_shared<Quad>(L"Resource/LostArk.png");
	//_background->GetTransform()->GetScale() *= 5.0f;

	_zelda = make_shared<Zelda>();

	_zeldaFollow = make_shared<Transform>();

	Camera::GetInstance()->SetTarget(_zelda->GetTransForm());

	Vector2 LeftBottom = { -_background->GetHalfSize().x, -_background->GetHalfSize().y };
	Vector2 RightTop = { _background->GetHalfSize().x, _background->GetHalfSize().y };
	Camera::GetInstance()->SetLeftBottom(LeftBottom);
	Camera::GetInstance()->SetRightTop(RightTop);

}

CameraScene::~CameraScene()
{
}

void CameraScene::Update()
{
	Move();
	_background->Update();
	_zelda->Update();
	_zelda->SetPosition(_movePos.x, _movePos.y);

	/*float distance = _zelda->GetTransForm()->GetPos().Distance(_zeldaFollow->GetPos());
	if(distance >= 30.0f)
	{
		_zeldaFollow->GetPos() = LERP(_zeldaFollow->GetPos(), _zelda->GetTransForm()->GetPos(), DELTA_TIME);
	}*/

}

void CameraScene::Render()
{
	_background->Render();
	_zelda->Render();
}

void CameraScene::PostRender()
{
	_zelda->PostRender();
}

void CameraScene::Move()
{
	
	{
		if (KEY_PRESS(VK_UP))
		{
			_movePos.y += 150 * DELTA_TIME;
			_zelda->SetAnimation(_zelda->B_RUN);

			return;
		}

		if (KEY_PRESS(VK_LEFT))
		{
			_movePos.x -= 150 * DELTA_TIME;
			_zelda->SetAnimation(Zelda::State::L_RUN);

			return;
		}

		if (KEY_PRESS(VK_DOWN))
		{
			_movePos.y -= 150 * DELTA_TIME;
			_zelda->SetAnimation(Zelda::State::F_RUN);

			return;
		}

		if (KEY_PRESS(VK_RIGHT))
		{
			_movePos.x += 150 * DELTA_TIME;
			_zelda->SetAnimation(Zelda::State::R_RUN);

			return;
		}
	}
	{
		if (KEY_UP(VK_LEFT))
			_zelda->SetAnimation(_zelda->L_IDLE);
		if (KEY_UP(VK_RIGHT))
			_zelda->SetAnimation(_zelda->R_IDLE);
		if (KEY_UP(VK_UP))
			_zelda->SetAnimation(_zelda->B_IDLE);
		if (KEY_UP(VK_DOWN))
			_zelda->SetAnimation(_zelda->F_IDLE);
	}
}