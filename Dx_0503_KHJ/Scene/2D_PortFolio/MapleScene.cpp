#include "framework.h"
#include "MapleScene.h"

MapleScene::MapleScene()
{
	_background = make_shared<Quad>(L"Resource/Maple/background2.png");
	_background->GetTransform()->GetPos() = { CENTER };

	_player = make_shared<MPlayer>();
	_player->GetTransForm()->GetPos() = { CENTER };

}

MapleScene::~MapleScene()
{
}

void MapleScene::Update()
{
	_background->Update();
	_player->Update();
}

void MapleScene::Render()
{
	//_background->Render();
	_player->Render();
}

void MapleScene::PostRender()
{
	if (KEY_PRESS('A'))
	{
		_player->PostRender();
	}
}
