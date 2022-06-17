#pragma once
class Transform
{
public:
	Transform();
	~Transform();

	XMFLOAT2& GetPos() { return _pos; }
	XMFLOAT2& GetScale() { return _scale; }
	float& GetAnlgle() { return _angle; }

	XMMATRIX* GetMatrix() { return &_srtMatrix; }
	// 주소값 반환
	void SetParent(XMMATRIX* matrix) { _parentMatrix = matrix; }

	void UpdateWorldBuffer();
	// world에 나오기위한 조건
	void SetWorldBuffer(int slot = 0);

private:
	XMFLOAT2 _pos = { 0.0f, 0.0f };
	XMFLOAT2 _scale = { 1.0f, 1.0f };
	float _angle = 0.0f;

	XMMATRIX _srtMatrix;

	XMMATRIX* _parentMatrix = nullptr;
	// 매번 바뀌기때를 대비해 주소값(포인터)로
	shared_ptr<MatrixBuffer> _worldBuffer;
	// texture_SRT * World를 곱한값이 worldBuffer
};

