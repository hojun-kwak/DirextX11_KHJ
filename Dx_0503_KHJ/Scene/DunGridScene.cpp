#include "framework.h"
#include "DunGridScene.h"

DunGridScene::DunGridScene()
{
	_player = make_shared<Player>();
	_aim = make_shared<Aim>();
	_monster = make_shared<Monster>();

	_player->SetMonster(_monster);

}

DunGridScene::~DunGridScene()
{
}

void DunGridScene::Update()
{
	_player->Update();
	_aim->Update();
	_monster->Update();

}

void DunGridScene::Render()
{
	_player->Render();
	_aim->Render();
	_monster->Render();

}

void DunGridScene::PostRender()
{
	ImGui::SliderInt("Mons HP", &_monster->_monsterHp, 0, 5);
}
