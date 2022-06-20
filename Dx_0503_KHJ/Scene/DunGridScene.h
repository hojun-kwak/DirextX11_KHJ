#pragma once
class DunGridScene : public Scene
{
public:

	DunGridScene();
	virtual~DunGridScene();

	// Scene을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render() override;


private:
	//shared_ptr<Texture> _Character;
	//shared_ptr<Texture> _Gun;
	//shared_ptr<Texture> _Skill;

	shared_ptr<Player> _player;
	//shared_ptr<Gun> _gun;
	shared_ptr<Bullet> _skill;

	shared_ptr<Texture> _MousePointer;

	bool skillActive = false;
	
};

