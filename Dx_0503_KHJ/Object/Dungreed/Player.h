#pragma once
class Player
{
public:
	Player();
	~Player();

	void Update();
	void Render();

private:
	void Move();
	void Aimming();

private:
	shared_ptr<Texture> _texture;
	shared_ptr<class Gun> _gun;
	shared_ptr<Transform> _gunTrans;
};

