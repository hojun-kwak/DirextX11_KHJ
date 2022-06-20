#pragma once
class Bullet
{
public:
	Bullet();
	~Bullet();

	void Update();
	void Render();

	shared_ptr<Transform> GetTransfom() { return _texture->GetTransform(); }
	void SetDirection(Vector2 dir);
	void SetPosition(Vector2 pos) { _texture->GetTransform()->GetPos() = pos; }
	bool _isActive = false;

private:
	shared_ptr<Texture> _texture;
	Vector2 _direction;
	// 왼쪽이냐 아래냐 따라 총알의 앵글을 움직여 볼까??
};

