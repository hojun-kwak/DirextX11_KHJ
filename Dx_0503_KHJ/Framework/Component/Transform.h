#pragma once
class Transform
{
public:
	Transform();
	~Transform();

	Vector2& GetPos() { return _pos; }
	Vector2& GetScale() { return _scale; }
	float& GetAnlgle() { return _angle; }

	Vector2 GetWorldPos()
	{
		Vector2 worldPos;
		XMFLOAT4X4 matrix;
		XMStoreFloat4x4(&matrix, _srtMatrix);
		worldPos._x = matrix._41;
		worldPos._y = matrix._42;

		return worldPos;
	}

	const XMMATRIX& GetMatrix() { return _srtMatrix; }
	// �ּҰ� ��ȯ
	void SetParent(shared_ptr<Transform> transform) { _parentMatrix = transform; }

	void UpdateWorldBuffer();
	// world�� ���������� ����
	void SetWorldBuffer(int slot = 0);

private:
	Vector2 _pos = { 0.0f, 0.0f };
	Vector2 _scale = { 1.0f, 1.0f };
	float _angle = 0.0f;

	XMMATRIX _srtMatrix;

	shared_ptr<Transform> _parentMatrix = nullptr;
	// �Ź� �ٲ�⶧�� ����� �ּҰ�(������)��
	shared_ptr<MatrixBuffer> _worldBuffer;
	// texture_SRT * World�� ���Ѱ��� worldBuffer
};

