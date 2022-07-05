#pragma once
class ZeldaScene : public Scene
{
public:
	ZeldaScene();
	virtual ~ZeldaScene();

	// Scene을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render() override;

	void PostRender();

private:
	shared_ptr<Zelda> _zelda;
};

