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
	// �ּҰ� ��ȯ
	void SetParent(XMMATRIX* matrix) { _parentMatrix = matrix; }

	void UpdateWorldBuffer();
	// world�� ���������� ����
	void SetWorldBuffer(int slot = 0);

private:
	XMFLOAT2 _pos = { 0.0f, 0.0f };
	XMFLOAT2 _scale = { 1.0f, 1.0f };
	float _angle = 0.0f;

	XMMATRIX _srtMatrix;

	XMMATRIX* _parentMatrix = nullptr;
	// �Ź� �ٲ�⶧�� ����� �ּҰ�(������)��
	shared_ptr<MatrixBuffer> _worldBuffer;
	// texture_SRT * World�� ���Ѱ��� worldBuffer
};

