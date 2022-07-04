#include "framework.h"
#include "DunGridScene.h"

DunGridScene::DunGridScene()
{
	_player = make_shared<Player>();
	_aim = make_shared<Aim>();
	//_monster = make_shared<Monster>();

	_monsters.reserve(_monsterCount);
	for (int i = 0; i < _monsterCount; i++)
	{
		shared_ptr<Monster> temp = make_shared<Monster>();
		temp->GetTrasform()->GetPos().x += (i + 1) * 100;
	
		_monsters.emplace_back(temp);
	}
	_player->SetMonster(_monsters);

	_zelda = make_shared<Sprite>(L"Resource/zelda.png", Vector2(10, 8));
	_zelda->GetTransform()->GetPos() = Vector2(WIN_WIDTH, WIN_HEIGHT) * 0.5f;

	// 1200, 1040
	vector<Action::Clip> clips;
	clips.emplace_back(0, 1040 / 2, 1200 / 10, 1040 / 8, Texture::Add(L"Resource/zelda.png"));

	_action = make_shared<Action>(clips);
	// spite setActionÃß°¡
}

DunGridScene::~DunGridScene()
{
}

void DunGridScene::Update()
{
	_player->Update();
	_aim->Update();
	_zelda->Update();
	//_monster->Update();
	for (auto& mons : _monsters)
	{
		mons->Update();
		if (mons->_monsterHp <= 0)
			mons->_monster_isActive = false;
	}
	_player->MonsAttack(_monsters);

}

void DunGridScene::Render()
{
	_player->Render();
	_aim->Render();
	//_monster->Render();

	for (auto& mons : _monsters)
		mons->Render();
	_zelda->Render();
}

void DunGridScene::PostRender()
{
}
