#pragma once
class RectCollider
{
public:
	RectCollider(const Vector2 halfSize = { 1.0f, 1.0f });
	~RectCollider();

	void CreateData();
	
	void Update();
	void Render();

	Vector2& GetPosition() { return _transform->GetPos(); }

	bool IsCollision(shared_ptr<RectCollider> rect);
	bool IsCollision(Vector2 pos);

	bool _isActive;
	bool _isCollision = false;

	float Left() { return _center._x - _halfSize._x; }
	float Right() { return _center._x + _halfSize._x; }
	float Top() { return _center._y + _halfSize._y; }
	float Bottom() { return _center._y - _halfSize._y; }

	// rect rect
	// rect Á¡(mousePoint)

private:
	Vector2 _halfSize = { 0,0 };
	Vector2 _center;

	// Mesh(»À´ë)
	vector<VertexPos> _verices;
	shared_ptr<VertexBuffer> _vertexBuffer;

	shared_ptr<VertexShader> _vertexShader;
	shared_ptr<PixelShader> _pixelShader;
	shared_ptr<ColorBuffer> _colorBuffer;

	shared_ptr<Transform> _parent;
	shared_ptr<Transform> _transform;
};

