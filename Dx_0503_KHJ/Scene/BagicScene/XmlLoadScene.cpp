#include "framework.h"
#include "XmlLoadScene.h"

XmlLoadScene::XmlLoadScene()
{
	_data = make_shared<ItemDataes>();
	_itemName = _data->FindItem("Hanil's Keyboard")->name;
	_price = _data->FindItem("Hanil's Keyboard")->price;
}

XmlLoadScene::~XmlLoadScene()
{
}

void XmlLoadScene::Update()
{
}

void XmlLoadScene::Render()
{
}

void XmlLoadScene::PostRender()
{
	ImGui::Text(_itemName.data());
	ImGui::SliderInt("Price", &_price, 0, 5000);
}
