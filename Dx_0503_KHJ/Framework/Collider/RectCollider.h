#pragma once
class RectCollider : public Collider
{
private:
	struct ObbDesc
	{
		Vector2 _position;
		Vector2 _direction[2];

		float _length[2];
	};

public:
	RectCollider(const Vector2& halfSize = { 1.0f,1.0f });
	virtual ~RectCollider();

	virtual void Update() override;
	virtual void Render() override;
	virtual void CreateData() override;

	virtual bool IsCollision(const Vector2& pos) override;
	virtual bool IsCollision(shared_ptr<RectCollider> rect, bool isObb) override;
	virtual bool IsCollision(shared_ptr<CircleCollider> circle, bool isObb) override;

	float Left() { return GetWorldPosition()._x - GetWorldHalfX(); }
	float Right() { return GetWorldPosition()._x + GetWorldHalfX(); }
	float Top() { return GetWorldPosition()._y + GetWorldHalfY(); }
	float Bottom() { return GetWorldPosition()._y - GetWorldHalfY(); }

	float GetWorldHalfX() { return _halfSize._x * GetWorldScale()._x; }
	float GetWorldHalfY() { return _halfSize._y * GetWorldScale()._y; }

	ObbDesc GetObb();

	bool AABB(shared_ptr<RectCollider> rect);
	bool OBB(shared_ptr<RectCollider> rect);

	bool AABB(shared_ptr<class CircleCollider> circle);
	bool OBB(shared_ptr<class CircleCollider> circle);


	float SeoareatAxis(Vector2 separate, Vector2 e1, Vector2 e2);

private:
	Vector2 _halfSize = { 0,0 };
	Vector2 _center;




};