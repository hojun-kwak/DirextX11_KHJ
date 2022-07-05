#pragma once
class DunGridScene : public Scene
{
public:

	DunGridScene();
	virtual~DunGridScene();

	// Scene을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render() override;

	virtual void PostRender() override;

private:
	shared_ptr<Player> _player;
	shared_ptr<Aim> _aim;

	shared_ptr<Monster> _monster;

	unsigned int _monsterCount = 5;

	vector<shared_ptr<Monster>> _monsters;

	/*shared_ptr<Sprite> _zelda;

	shared_ptr<Action> _action;*/

	shared_ptr<Zelda> _zelda;

	int _curFrameX = 0;
	int _curFrameY = 0;
};

