#pragma once
class Player
{
public:
	Player();
	~Player();

	void Update();
	void Render();

	void SetMonster(vector<shared_ptr<class Monster>> mons) { _mons = mons; }

private:
	void Move();
	void Aimming();
	void Fire();
	void MonsAttack();
	void Reset();


private:
	shared_ptr<Texture> _texture;
	shared_ptr<class Gun> _gun;
	shared_ptr<Transform> _gunTrans;

	//shared_ptr<class Bullet> _bullet;

	int _objpooling = 10;

	vector<shared_ptr<class Bullet>> _bullets;

	shared_ptr<Collider> _collider;

	vector<shared_ptr<class Monster>> _mons;
};

