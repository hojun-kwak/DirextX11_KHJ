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
	void Attack();
	void Reset();

private:
	shared_ptr<Texture> _texture;
	shared_ptr<class Gun> _gun;
	shared_ptr<Transform> _gunTrans;

	shared_ptr<class Bullet> _bullet;

	int _objpooling = 10;

	//vector<shared_ptr<class Bullet>> _bullets;

	shared_ptr<Collider> _collider;

	shared_ptr<class Monster> _mons;
};

