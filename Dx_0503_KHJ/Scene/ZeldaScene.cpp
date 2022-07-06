#include "framework.h"
#include "ZeldaScene.h"

ZeldaScene::ZeldaScene()
{
	_zelda = make_shared<Zelda>();
	//_movePos = Vector2(WIN_WIDTH, WIN_HEIGHT) * 0.5f;
}

ZeldaScene::~ZeldaScene()
{
}

void ZeldaScene::Update()
{
	// 키보드를 계속 눌렀을 경우
	{
		if (KEY_DOWN(VK_LEFT))
		{
			_zelda->SetAnimation(_zelda->L_RUN);
			//_movePos.x -= 100 * DELTA_TIME;
		}
		if (KEY_DOWN(VK_RIGHT))
		{
			_zelda->SetAnimation(_zelda->R_RUN);
			//_movePos.x += 100 * DELTA_TIME;
		}
		if (KEY_DOWN(VK_UP))
		{
			_zelda->SetAnimation(_zelda->B_RUN);
			//_movePos.y += 100 * DELTA_TIME;
		}
		if (KEY_DOWN(VK_DOWN))
		{
			_zelda->SetAnimation(_zelda->F_RUN);
			//_movePos.y -= 100 * DELTA_TIME;
		}
	}

	// 키보드에서 손을 떗을 경우
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
	//_zelda->SetPosition(_movePos.x, _movePos.y);
	_zelda->Update();
}

void ZeldaScene::Render()
{
	_zelda->Render();
}

void ZeldaScene::PostRender()
{
	_zelda->PostRender();
}
