#pragma once
class Transform
{
public:
	Transform();
	~Transform();

	Vector2& GetPos() { return _pos; }
	Vector2& GetScale() { return _scale; }
	float& GetAngle() { return _angle; }

	Vector2 GetWorldPos()
	{
		Vector2 worldPos;
		XMFLOAT4X4 matrix;
		XMStoreFloat4x4(&matrix, _srtMatrix);
		worldPos._x = matrix._41;
		worldPos._y = matrix._42;

		return worldPos;
	}

	const Vector2& GetWorldScale()
	{
		if (_parentMatrix)
			return Vector2(_scale._x * _parentMatrix->GetScale()._x, _scale._y * _parentMatrix->GetScale()._y);
		return _scale;
	}

	const XMMATRIX& GetMatrix() { return _srtMatrix; }
	// 주소값 반환
	void SetParent(shared_ptr<Transform> transform) { _parentMatrix = transform; }
	shared_ptr<Transform> GetParent() { return _parentMatrix; }

	void UpdateWorldBuffer();
	// world에 나오기위한 조건
	void SetWorldBuffer(int slot = 0);

private:
	Vector2 _pos = { 0.0f, 0.0f };
	Vector2 _scale = { 1.0f, 1.0f };
	float _angle = 0.0f;

	XMMATRIX _srtMatrix;

	shared_ptr<Transform> _parentMatrix = nullptr;
	// 매번 바뀌기때를 대비해 주소값(포인터)로
	shared_ptr<MatrixBuffer> _worldBuffer;
	// texture_SRT * World를 곱한값이 worldBuffer
};

