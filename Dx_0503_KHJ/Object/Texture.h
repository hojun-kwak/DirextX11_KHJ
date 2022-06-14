#pragma once
class Texture
{
public:
	Texture(wstring file);
	~Texture();

	void Update();
	void Render();

	XMFLOAT2& GetPos() { return _pos; }
	XMFLOAT2& GetScale() { return _scale; }
	float& GetAnlgle() { return _angle; }

	XMMATRIX* GetMatrix() { return &_srtMatrix; }
	// �ּҰ� ��ȯ
	void SetParent(XMMATRIX* matrix) { _parentMatrix = matrix; }

private:
	void CreateVerties();

	vector<VertexUV> _vertices;

	vector<UINT> _indicies;

	shared_ptr<VertexShader>    _vertexShader;
	shared_ptr<PixelShader>     _pixelShader;

	shared_ptr<VertexBuffer>    _vertexBuffer;
	shared_ptr<IndexBuffer>		_indexBuffer;
	shared_ptr<SRV>             _srv;
	shared_ptr<SamplerState>    _sampler;

	XMFLOAT2 _pos = { 0.0f, 0.0f };
	XMFLOAT2 _scale = { 1.0f, 1.0f };
	float _angle = 0.0f;

	XMMATRIX _srtMatrix;

	XMMATRIX* _parentMatrix = nullptr;
	// �Ź� �ٲ�⶧�� ����� �ּҰ�(������)��
	shared_ptr<MatrixBuffer> _worldBuffer;
	// texture_SRT * World�� ���Ѱ��� worldBuffer
};

