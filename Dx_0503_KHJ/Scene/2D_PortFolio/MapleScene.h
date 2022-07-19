#pragma once
class MapleScene : public Scene
{
public:
	MapleScene();
	virtual ~MapleScene();

	// Scene을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;

private:
};

