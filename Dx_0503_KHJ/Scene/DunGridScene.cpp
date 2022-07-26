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

	_zelda = make_shared<Zelda>();

	//_zelda = make_shared<Sprite>(L"Resource/zelda.png", Vector2(10, 8));
	//_zelda->GetTransform()->GetPos() = Vector2(WIN_WIDTH, WIN_HEIGHT) * 0.5f;

	//// 1200, 1040
	//vector<Action::Clip> clips;

	//float y = 1040 * 0.5f;
	//float w = 1200 / 10;
	//float h = 1040 / 8;

	//{ // 달리기
	//	clips.emplace_back(0 + w * 0, y, w, h, Texture::Add(L"Resource/zelda.png")); // 달리기 첫번째
	//	clips.emplace_back(0 + w * 1, y, w, h, Texture::Add(L"Resource/zelda.png"));
	//	clips.emplace_back(0 + w * 2, y, w, h, Texture::Add(L"Resource/zelda.png"));
	//	clips.emplace_back(0 + w * 3, y, w, h, Texture::Add(L"Resource/zelda.png"));
	//	clips.emplace_back(0 + w * 4, y, w, h, Texture::Add(L"Resource/zelda.png"));
	//	clips.emplace_back(0 + w * 5, y, w, h, Texture::Add(L"Resource/zelda.png"));
	//	clips.emplace_back(0 + w * 6, y, w, h, Texture::Add(L"Resource/zelda.png"));
	//	clips.emplace_back(0 + w * 7, y, w, h, Texture::Add(L"Resource/zelda.png"));
	//	clips.emplace_back(0 + w * 8, y, w, h, Texture::Add(L"Resource/zelda.png"));
	//	clips.emplace_back(0 + w * 9, y, w, h, Texture::Add(L"Resource/zelda.png"));
	//}
	//_action = make_shared<Action>(clips);
	// spite setAction추가
}

DunGridScene::~DunGridScene()
{
}

void DunGridScene::Update()
{
	_player->Update();
	_aim->Update();
	_zelda->Update();

	/*_action->Update();
	_zelda->SetClip(_action->GetCurClip());*/

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
	_zelda->Render();
	for (auto& mons : _monsters)
		mons->Render();
}

void DunGridScene::PostRender()
{
}
