#pragma once
class RectCollider : public Collider
{
public:
	RectCollider();
	virtual ~RectCollider();

private:
	Vector2 _halfSize = { 0,0 };
};

