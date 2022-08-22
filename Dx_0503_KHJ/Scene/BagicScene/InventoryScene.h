#pragma once
class InventoryScene : public Scene
{
public:
	InventoryScene();
	virtual ~InventoryScene();

	// Scene을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
	virtual void PreRender() override;
	virtual void Init() override;
private:
	shared_ptr<Inventory> _inventory;
};

