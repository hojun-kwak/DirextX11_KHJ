#pragma once
class RectCollider
{
private:
	struct ObbDesc
	{
		Vector2 _position;
		Vector2 _direction[2]; // 사각형의 평행한 단위 벡터
		float _lenght[2]; // 사각형의 평행한 실이
	};


public:
	RectCollider(const Vector2 halfSize = { 1.0f, 1.0f });
	~RectCollider();

	void CreateData();
	
	void Update();
	void Render();

	const Vector2& GetWorldPosition() { return _transform->GetWorldPos(); }
	Vector2& GetLocalPosition() { return _transform->GetPos(); }
	float& GetAngle() { return _transform->GetAnlgle(); }

	bool IsCollision(shared_ptr<RectCollider> rect, bool obb);
	bool IsCollision(const Vector2& pos);

	bool _isCollision = false;

	float Left() { return _center._x - _halfSize._x; }
	float Right() { return _center._x + _halfSize._x; }
	float Top() { return _center._y + _halfSize._y; }
	float Bottom() { return _center._y - _halfSize._y; }

	ObbDesc GetObb();
	bool AABB(shared_ptr<RectCollider> rect);
	bool OBB(shared_ptr<RectCollider> rect);

	float SepareateAxis(Vector2 separate, Vector2 e1, Vector2 e2);

	// rect rect
	// rect 점(mousePoint)

private:
	Vector2 _halfSize = { 0,0 };
	Vector2 _center;

	// Mesh(뼈대)
	vector<VertexPos> _verices;
	shared_ptr<VertexBuffer> _vertexBuffer;

	shared_ptr<VertexShader> _vertexShader;
	shared_ptr<PixelShader> _pixelShader;
	shared_ptr<ColorBuffer> _colorBuffer;

	shared_ptr<Transform> _parent;
	shared_ptr<Transform> _transform;

};

