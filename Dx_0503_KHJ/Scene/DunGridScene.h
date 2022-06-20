#pragma once
class DunGridScene : public Scene
{
public:

	DunGridScene();
	virtual~DunGridScene();

	// Scene��(��) ���� ��ӵ�
	virtual void Update() override;
	virtual void Render() override;

private:
	shared_ptr<Player> _player;
	shared_ptr<Aim> _aim;
		
};

