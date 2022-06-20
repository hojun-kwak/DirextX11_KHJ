#include "framework.h"
#include "DunGridScene.h"

DunGridScene::DunGridScene()
{
	_player = make_shared<Player>();
	_skill = make_shared<Bullet>();
	_aim = make_shared<Aim>();
}

DunGridScene::~DunGridScene()
{
}

void DunGridScene::Update()
{
	_player->Update();
	_skill->Update();
	_aim->Update();
}

void DunGridScene::Render()
{
	_player->Render();
	_skill->Render();
	_aim->Render();
}
