#pragma once

struct ItemData
{
	string name;
	int value = 0;
	int price = 0;
	int type = 0;
	int attack = 0;
	int defence = 0;
};

class ItemDataes
{
public:
	ItemDataes();
	~ItemDataes();

	ItemData* FindItem(string name);

	void InitData();

private:
	unordered_map<string, ItemData> _items;
};

