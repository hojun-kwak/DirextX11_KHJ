#pragma once
class Texture
{
public:
	Texture(wstring file);
	~Texture();

	void Update();
	void Render();

	shared_ptr<Transform> GetTransform() { return _transform; }

private:
	void CreateVerties();

	shared_ptr<Transform> _transform;

	vector<VertexUV> _vertices;

	vector<UINT> _indicies;

	shared_ptr<VertexShader>    _vertexShader;
	shared_ptr<PixelShader>     _pixelShader;

	shared_ptr<VertexBuffer>    _vertexBuffer;
	shared_ptr<IndexBuffer>		_indexBuffer;
	shared_ptr<SRV>             _srv;
	shared_ptr<SamplerState>    _sampler;

	
};

