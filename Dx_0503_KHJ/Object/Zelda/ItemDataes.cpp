#include "framework.h"
#include "ItemDataes.h"

ItemDataes::ItemDataes()
{
	//_items.reserve(10);
	InitData();
}

ItemDataes::~ItemDataes()
{
}

ItemData* ItemDataes::FindItem(string name)
{
	if(_items.count(name) == 0)
		return nullptr;

	return &_items[name];
}

void ItemDataes::InitData()
{
	string path = "Resource/XML/";
	string file = "ItemData.xml";
	tinyxml2::XMLDocument* document = new tinyxml2::XMLDocument();
	document->LoadFile((path + file).c_str());

	tinyxml2::XMLElement* atlas = document->FirstChildElement("Workbook");
	tinyxml2::XMLElement* workSheet = atlas->FirstChildElement("Worksheet");
	tinyxml2::XMLElement* table = workSheet->FirstChildElement("Table");
	tinyxml2::XMLElement* row = table->FirstChildElement("Row");

	row = row->NextSiblingElement();

	while (row != nullptr)
	{
		tinyxml2::XMLElement* cell = row->FirstChildElement();
		tinyxml2::XMLElement* data = cell->FirstChildElement();

		ItemData itemData;
		itemData.name = data->GetText();

		cell = cell->NextSiblingElement();
		data = cell->FirstChildElement();
		itemData.price = data->IntText();

		cell = cell->NextSiblingElement();
		data = cell->FirstChildElement();
		itemData.value = data->IntText();

		cell = cell->NextSiblingElement();
		data = cell->FirstChildElement();
		itemData.type = data->IntText();

		cell = cell->NextSiblingElement();
		data = cell->FirstChildElement();
		itemData.attack = data->IntText();

		cell = cell->NextSiblingElement();
		data = cell->FirstChildElement();
		itemData.defence = data->IntText();

		_items[itemData.name] = itemData;
		row = row->NextSiblingElement();
	}
}
