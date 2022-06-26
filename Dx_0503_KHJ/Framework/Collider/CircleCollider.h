#pragma once
class CircleCollider
{
public:
	CircleCollider(const float radius = 1.0f);
	~CircleCollider();

	void CreateData();

	void Update();
	void Render();

	const Vector2& GetWorldPosition() { return _transform->GetWorldPos(); }
	Vector2& GetLocalPosition() { return _transform->GetPos(); }
	float& GetAngle() { return _transform->GetAnlgle(); }

private:
	float _radius = 0.0f;
	Vector2 _center;

	vector<VertexPos> _verices;
	shared_ptr<VertexBuffer> _vertexBuffer;

	shared_ptr<VertexShader> _vertexShader;
	shared_ptr<PixelShader> _pixelShader;
	shared_ptr<ColorBuffer> _colorBuffer;

	shared_ptr<Transform> _parent;
	shared_ptr<Transform> _transform;

};

