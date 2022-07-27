#include "framework.h"
#include "CircleCollider.h"

CircleCollider::CircleCollider(float radius)
	: _radius(radius)
{
	CreateData();
}

CircleCollider::~CircleCollider()
{
}

void CircleCollider::CreateData()
{
	_type = Collider::ColType::CIRCLE;

	VertexPos vertex;

	// 원의 정점
	for (int i = 0; i < 37; i++)
	{
		float theta = PI * 2 / 36;
		vertex.pos.x = _radius * cosf(theta * i);
		vertex.pos.y = _radius * sinf(theta * i);
		vertex.pos.z = 0;

		_vertices.push_back(vertex);
	}

	Collider::CreateData();
}

void CircleCollider::Update()
{
	Collider::Update();
}

void CircleCollider::Render()
{
	Collider::Render();
}

bool CircleCollider::IsCollision(const Vector2& pos)
{
	float distance = _transform->GetWorldPos().Distance(pos);
	float radius = GetRadius();
	if (distance < radius)
		return true;

	return false;
}

bool CircleCollider::IsCollision(shared_ptr<CircleCollider> other, bool isObb)
{
	Vector2 t = other->GetWorldPosition();
	Vector2 t2 = this->GetWorldPosition();
	Vector2 t3 = t2 - t;
	float distance = (t3).Length();
	if (distance < GetRadius() + other->GetRadius())
		return true;

	return false;
}

bool CircleCollider::IsCollision(shared_ptr<RectCollider> other, bool obb)
{
	return other->IsCollision(make_shared<CircleCollider>(*this), obb);
}
