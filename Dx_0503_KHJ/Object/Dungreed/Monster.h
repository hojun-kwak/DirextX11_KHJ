#pragma once
class Monster
{
public:
	Monster();
	~Monster();

	void Update();
	void Render();

	shared_ptr<Collider> GetCollider() { return _collider; }

	bool _monster_isActive = true;
	int _monsterHp = 5;

private:
	shared_ptr<Texture> _texture;
	shared_ptr<Collider> _collider;

};

