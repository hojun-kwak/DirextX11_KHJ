#include "framework.h"
#include "EffectScene.h"

EffectScene::EffectScene()
{
	EffectManager::GetInstance()->Add(L"Resource/Effects/skill_core_4x4.png", Vector2(4, 4), 0.07f);
	_quad = make_shared<Quad>(L"Resource/VRising.png");
	_quad->GetTransform()->GetPos() = CENTER;
}

EffectScene::~EffectScene()
{
}

void EffectScene::Update()
{
	if (KEY_DOWN('W'))
	{
		EffectManager::GetInstance()->Play("skill_core_4x4", CENTER);
		Camera::GetInstance()->ShakeStart(2.0f, 1.0f);
	}
	_quad->Update();
}

void EffectScene::Render()
{
	_quad->Render();
}

void EffectScene::PostRender()
{
}