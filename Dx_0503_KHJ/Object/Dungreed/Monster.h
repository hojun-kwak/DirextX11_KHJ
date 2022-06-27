#pragma once
class Monster
{
public:
	Monster();
	~Monster();

	void Update();
	void Render();

	shared_ptr<Collider> GetCollider() { return _collider; }
	void GetRed() { return _collider->SetRed(); }

	bool _Monster_isActive = true;

private:
	shared_ptr<Texture> _texture;
	shared_ptr<Collider> _collider;

};

