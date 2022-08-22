#include "framework.h"
#include "InventoryScene.h"

InventoryScene::InventoryScene()
{
	_inventory = make_shared<Inventory>();
}

InventoryScene::~InventoryScene()
{
}

void InventoryScene::Update()
{
	_inventory->Update();
}

void InventoryScene::Render()
{
	_inventory->Render();
}

void InventoryScene::PostRender()
{
}

void InventoryScene::PreRender()
{
}

void InventoryScene::Init()
{
}
