#include "framework.h"
#include "ZeldaScene.h"

ZeldaScene::ZeldaScene()
{
	_zelda = make_shared<Zelda>();
}

ZeldaScene::~ZeldaScene()
{
}

void ZeldaScene::Update()
{
	// Ű���带 ��� ������ ���
	{
		if (KEY_DOWN(VK_LEFT))
			_zelda->SetAnimation(_zelda->L_RUN);
		if (KEY_DOWN(VK_RIGHT))
			_zelda->SetAnimation(_zelda->R_RUN);
		if (KEY_DOWN(VK_UP))
			_zelda->SetAnimation(_zelda->B_RUN);
		if (KEY_DOWN(VK_DOWN))
			_zelda->SetAnimation(_zelda->F_RUN);
	}

	// Ű���忡�� ���� ���� ���
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
