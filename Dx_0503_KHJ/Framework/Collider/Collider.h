#pragma once

class CircleCollider;
class RectCollider;

class Collider
{
public:
	enum class ColType
	{
		DEFAULT,
		CIRCLE,
		RECT
	};

public:
	Collider();
	virtual ~Collider();

	virtual void Update();
	virtual void Render();

	virtual void CreateData() abstract;

	virtual bool IsCollision(const Vector2& pos) abstract;
	virtual bool IsCollision(shared_ptr<RectCollider> rect, bool isObb = false) abstract;
	virtual bool IsCollision(shared_ptr<CircleCollider> circle, bool isObb = false) abstract;

	bool IsCollision(shared_ptr<Collider> col, bool isObb = false);

	const Vector2& GetWorldPosition() { return _transform->GetWorldPos(); }
	const Vector2& GetWorldScale() { return _transform->GetWorldScale(); }

	Vector2& GetLocalPosition() { return _transform->GetPos(); }
	float& GetAngle() { return _transform->GetAngle(); }

	void SetRed() { _colorBuffer->SetColor(RED); }
	void SetGreen() { _colorBuffer->SetColor(GREEN); }

	void SetParent(shared_ptr<Transform> parent) { _transform->SetParent(parent); }
	shared_ptr<Transform> GetParent() { return _transform->GetParent(); }


protected:

	Vector2 _center;

	ColType _type = ColType::DEFAULT;

	//Math
	vector<VertexPos> _vertices;
	shared_ptr<VertexBuffer> _vertexBuffer;

	shared_ptr<VertexShader> _vertexShader;
	shared_ptr<PixelShader> _pixelShader;

	//Collider 초록색으로 보통 세팅이 되어있다
	shared_ptr<ColorBuffer> _colorBuffer;

	shared_ptr<Transform> _parent;
	shared_ptr<Transform> _transform;
};

