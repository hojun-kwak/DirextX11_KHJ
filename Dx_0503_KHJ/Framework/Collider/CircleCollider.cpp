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

void CircleCollider::Update()
{
	Collider::Update();
}

bool CircleCollider::IsCollision(const Vector2 pos)
{
	if (GetRadius() >= _center.Distance(pos))
		return true;

	return false;
}

bool CircleCollider::IsCollision(shared_ptr<RectCollider> rect, bool isObb)
{
	return rect->IsCollision(make_shared<CircleCollider>(*this), isObb);
}

bool CircleCollider::IsCollision(shared_ptr<CircleCollider> circle, bool isObb)
{
	float distance = (_center - circle->_center).Length();
	float distance2 = GetRadius() + circle->GetRadius();

	return distance2 > distance;
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
