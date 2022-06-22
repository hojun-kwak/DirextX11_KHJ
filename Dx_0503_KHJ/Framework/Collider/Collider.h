#pragma once
class Collider
{
public:
	Collider();
	virtual ~Collider();

	virtual void CreateData();

	virtual void Update();
	virtual void Render();

	void SetParent(shared_ptr<Transform> parent) { _parent = parent; }

protected:
	Vector2 _center;
	
	// Mesh(����)
	vector<VertexPos> _verices;
	shared_ptr<VertexBuffer> _vertexBuffer;

	shared_ptr<VertexShader> _vertexShader;
	shared_ptr<PixelShader> _pixelShader;
	shared_ptr<ColorBuffer> _colorBuffer;

	shared_ptr<Transform> _parent;
	shared_ptr<Transform> _transform;

};
