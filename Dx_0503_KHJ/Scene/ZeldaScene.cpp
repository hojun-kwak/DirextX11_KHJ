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
	_zelda->Update();
}

void ZeldaScene::Render()
{
	_zelda->Render();
}

void ZeldaScene::PostRender()
{
}
