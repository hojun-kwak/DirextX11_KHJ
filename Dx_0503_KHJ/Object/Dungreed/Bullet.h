#pragma once
class Bullet
{
public:
	Bullet();
	~Bullet();

	void Update();
	void Render();

	shared_ptr<Transform> GetTransfom() { return _quad->GetTransform(); }
	shared_ptr<Collider> GetCollider() { return _collider; }

	void SetDirection(Vector2 dir);
	void SetPosition(Vector2 pos) { _quad->GetTransform()->GetPos() = pos; }
	void SetAngle(float angle) { _quad->GetTransform()->GetAngle() = angle; }
	bool _isActive = false;

private:
	shared_ptr<Quad> _quad;
	Vector2 _direction;
	// 왼쪽이냐 아래냐 따라 총알의 앵글을 움직여 볼까??

	float _runTime = 0.0f;
	float _destroyTime = 10.0f;

	shared_ptr<Collider> _collider;
};

