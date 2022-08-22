#pragma once
class XmlLoadScene : public Scene
{
public:
	XmlLoadScene();
	virtual ~XmlLoadScene();

	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;

private:
	shared_ptr<ItemDataes> _data;
	string _itemName;
	int _price = 0;
};

