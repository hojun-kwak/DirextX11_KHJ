#pragma once
class Bullet
{
public:
	Bullet();
	~Bullet();

	void Update();
	void Render();

	shared_ptr<Transform> GetTransfom() { return _texture->GetTransform(); }
	shared_ptr<Collider> GetCollider() { return _collider; }

	void SetDirection(Vector2 dir);
	void SetPosition(Vector2 pos) { _texture->GetTransform()->GetPos() = pos; }
	void SetAngle(float angle) { _texture->GetTransform()->GetAngle() = angle; }
	bool _isActive = false;

private:
	shared_ptr<Texture> _texture;
	Vector2 _direction;
	// �����̳� �Ʒ��� ���� �Ѿ��� �ޱ��� ������ ����??

	float _runTime = 0.0f;
	float _destroyTime = 10.0f;

	shared_ptr<Collider> _collider;
};

