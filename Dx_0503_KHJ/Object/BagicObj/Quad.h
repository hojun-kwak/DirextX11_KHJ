#pragma once
class Quad
{
public:
	Quad(wstring file, wstring vs = L"Shaders/TextureVertexShader.hlsl", wstring ps = L"Shaders/TexturePixelShader.hlsl");
	Quad(wstring file, Vector2 size, wstring vs = L"Shaders/TextureVertexShader.hlsl", wstring ps = L"Shaders/TexturePixelShader.hlsl");
	~Quad();

	virtual void Update();
	virtual void Render();
	void SetRender();

	virtual void CreateData();

	shared_ptr<Transform> GetTransform() { return _transform; }
	Vector2 GetHalfSize();
	void SetParent(shared_ptr<Transform> parent) { _transform->SetParent(parent); }
	void SetTexture(shared_ptr<Texture> texture) { _texture = texture; }

	Vector2 LeftBottom();
	Vector2 RightTop();

protected:
	Quad() {}

	shared_ptr<Transform> _transform;

	//Texture
	shared_ptr<Texture> _texture;

	// Mesh
	vector<VertexUV> _vertices;
	vector<UINT> _indicies;
	shared_ptr<VertexBuffer>    _vertexBuffer;
	shared_ptr<IndexBuffer>		_indexBuffer;

	// Material
	shared_ptr<VertexShader>    _vertexShader;
	shared_ptr<PixelShader>     _pixelShader;

	Vector2 _halfSize = { 1,1 };
};

