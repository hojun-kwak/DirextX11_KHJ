#include "framework.h"
#include "Inventory.h"

#include "../Dungreed/Item.h"

Inventory::Inventory()
{
	_itemIcon = make_shared<ItemIcon>();
	_itemIcon->SetIcon("Sword", CENTER);
}

Inventory::~Inventory()
{
}

void Inventory::Update()
{
}

void Inventory::Render()
{
	_itemIcon->Render();
}
