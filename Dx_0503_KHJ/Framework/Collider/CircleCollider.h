#pragma once
class CircleCollider :public Collider
{
public:
	CircleCollider(float radius);
	virtual ~CircleCollider();

	// Collider을(를) 통해 상속됨
	virtual void Update() override;

	virtual void CreateData() override;

	virtual bool IsCollision(const Vector2 pos) override;
	virtual bool IsCollision(shared_ptr<RectCollider> rect, bool isObb = false) override;
	virtual bool IsCollision(shared_ptr<CircleCollider> circle, bool isObb = false) override;

	float GetRadius() { return _radius * _transform->GetWorldScale()._x; }

private:
	float _radius;
};



