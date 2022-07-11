#include "framework.h"
#include "EffectScene.h"

EffectScene::EffectScene()
{
	EffectManager::GetInstance()->Add(L"Resource/Effects/skill_core_4x4.png", Vector2(4, 4), 0.07f);
}

EffectScene::~EffectScene()
{
}

void EffectScene::Update()
{
	if (KEY_DOWN('W'))
	{
		EffectManager::GetInstance()->Play("skill_core_4x4", CENTER);
	}
}

void EffectScene::Render()
{
}

void EffectScene::PostRender()
{
}