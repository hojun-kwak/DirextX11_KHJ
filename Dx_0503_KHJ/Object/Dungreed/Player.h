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
	void Fire();

private:
	shared_ptr<Texture> _texture;
	shared_ptr<class Gun> _gun;
	shared_ptr<Transform> _gunTrans;

	shared_ptr<class Bullet> _bullet;
};

