#include "framework.h"
#include "ZeldaScene.h"

ZeldaScene::ZeldaScene()
{
	_zelda = make_shared<Zelda>();
	_movePos = { WIN_WIDTH * 0.5f, WIN_HEIGHT * 0.5f };
	_zelda->SetPosition(WIN_WIDTH * 0.5f, WIN_HEIGHT * 0.5f);
	//_movePos = Vector2(WIN_WIDTH, WIN_HEIGHT) * 0.5f;
}

ZeldaScene::~ZeldaScene()
{
}

void ZeldaScene::Update()
{
	//_zelda->SetPosition(_movePos.x, _movePos.y);
	Move();
	_zelda->Update();
	_zelda->SetPosition(_movePos.x, _movePos.y);
}

void ZeldaScene::Render()
{
	_zelda->Render();
}

void ZeldaScene::PostRender()
{
	_zelda->PostRender();
}

void ZeldaScene::Move()
{
	if (KEY_PRESS(VK_UP))
	{
		_movePos.y += 50 * DELTA_TIME;
		_zelda->SetAnimation(_zelda->B_RUN);

		return;
	}

	if (KEY_PRESS(VK_LEFT))
	{
		_movePos.x -= 50 * DELTA_TIME;
		_zelda->SetAnimation(Zelda::State::L_RUN);

		return;
	}

	if (KEY_PRESS(VK_RIGHT))
	{
		_movePos.y -= 50 * DELTA_TIME;
		_zelda->SetAnimation(Zelda::State::F_RUN);

		return;
	}

	if (KEY_PRESS(VK_DOWN))
	{
		_movePos.x += 50 * DELTA_TIME;
		_zelda->SetAnimation(Zelda::State::R_RUN);

		return;
	}

	// 키보드를 계속 눌렀을 경우
	//{
	//	if (KEY_DOWN(VK_LEFT))
	//	{
	//		_zelda->SetAnimation(_zelda->L_RUN);
	//		//_movePos.x -= 100 * DELTA_TIME;
	//	}
	//	if (KEY_DOWN(VK_RIGHT))
	//	{
	//		_zelda->SetAnimation(_zelda->R_RUN);
	//		//_movePos.x += 100 * DELTA_TIME;
	//	}
	//	if (KEY_DOWN(VK_UP))
	//	{
	//		_zelda->SetAnimation(_zelda->B_RUN);
	//		//_movePos.y += 100 * DELTA_TIME;
	//	}
	//	if (KEY_DOWN(VK_DOWN))
	//	{
	//		_zelda->SetAnimation(_zelda->F_RUN);
	//		//_movePos.y -= 100 * DELTA_TIME;
	//	}
	//}

	//// 키보드에서 손을 떗을 경우
	//{
	//	if (KEY_UP(VK_LEFT))
	//		_zelda->SetAnimation(_zelda->L_IDLE);
	//	if (KEY_UP(VK_RIGHT))
	//		_zelda->SetAnimation(_zelda->R_IDLE);
	//	if (KEY_UP(VK_UP))
	//		_zelda->SetAnimation(_zelda->B_IDLE);
	//	if (KEY_UP(VK_DOWN))
	//		_zelda->SetAnimation(_zelda->F_IDLE);
	//}
}
