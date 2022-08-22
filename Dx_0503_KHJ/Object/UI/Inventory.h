#pragma once
class item;

class Inventory
{
public:
	Inventory();
	~Inventory();

	void Update();
	void Render();

private:
	shared_ptr<ItemIcon> _itemIcon;
};

