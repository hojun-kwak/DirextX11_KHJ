#include "framework.h"
#include "DunGridScene.h"

DunGridScene::DunGridScene()
{
	_player = make_shared<Player>();
	_aim = make_shared<Aim>();

}

DunGridScene::~DunGridScene()
{
}

void DunGridScene::Update()
{
	_player->Update();
	_aim->Update();

}

void DunGridScene::Render()
{
	_player->Render();
	_aim->Render();


}
