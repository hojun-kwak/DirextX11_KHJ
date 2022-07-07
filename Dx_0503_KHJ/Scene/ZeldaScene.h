#pragma once
class ZeldaScene : public Scene
{
public:
	ZeldaScene();
	virtual ~ZeldaScene();

	// Scene��(��) ���� ��ӵ�
	virtual void Update() override;
	virtual void Render() override;

	void PostRender();

	void Move();

private:
	shared_ptr<Zelda> _zelda;

	Vector2 _movePos = {0.0f, 0.0f};
};

