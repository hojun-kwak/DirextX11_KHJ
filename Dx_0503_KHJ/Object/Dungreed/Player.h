#pragma once
class Player
{
public:
	enum State
	{
		GROUND,
		JUMPING,
		ATTACK
	};
	Player();
	~Player();

	void Update();
	void Render();

	void SetMonster(vector<shared_ptr<class Monster>> mons) { _mons = mons; }

	void MonsAttack(vector<shared_ptr<class Monster>> monster);

private:
	void Move();
	void Aimming();
	void Fire();
	void Jump();
	void Reset();


private:
	shared_ptr<Quad> _quad;
	shared_ptr<class Gun> _gun;
	shared_ptr<Transform> _gunTrans;

	//shared_ptr<class Bullet> _bullet;

	int _objpooling = 10;

	vector<shared_ptr<class Bullet>> _bullets;

	shared_ptr<Collider> _collider;

	vector<shared_ptr<class Monster>> _mons;

	float _jumpPower = 300.0f;
	float _gravity = 100.0f;
	State _state = GROUND;
};

