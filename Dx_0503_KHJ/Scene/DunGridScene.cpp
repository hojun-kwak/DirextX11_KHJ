#include "framework.h"
#include "DunGridScene.h"

DunGridScene::DunGridScene()
{
	_player = make_shared<Player>();
	_aim = make_shared<Aim>();
	//_monster = make_shared<Monster>();

	float x = 0.0f;
	_monsters.reserve(_monsterCount);
	for (int i = 0; i < _monsterCount; i++)
	{
		shared_ptr<Monster> temp = make_shared<Monster>();
		temp->GetTrasform()->GetPos()._x += x;
		x = (i + 1) * 100;
		_monsters.emplace_back(temp);
	}
	_player->SetMonster(_monsters);

}

DunGridScene::~DunGridScene()
{
}

void DunGridScene::Update()
{
	_player->Update();
	_aim->Update();
	//_monster->Update();
	for (auto& mons : _monsters)
		mons->Update();

}

void DunGridScene::Render()
{
	_player->Render();
	_aim->Render();
	//_monster->Render();

	for (auto& mons : _monsters)
		mons->Render();

}

void DunGridScene::PostRender()
{
	//ImGui::SliderInt("Mons HP", &_monster->_monsterHp, 0, 5);
	/*for (int i = 0; i < _monsterCount; i++)
	{
		for (auto& mons : _monsters)
		{
			ImGui::Text("Monster %d : %d", i + 1, (UINT)mons->_monsterHp);
		}
	}*/
}
