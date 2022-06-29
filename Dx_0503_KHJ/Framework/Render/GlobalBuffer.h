#pragma once

// 전역함수
inline void IASetPT(D3D_PRIMITIVE_TOPOLOGY type = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST)
{
	DEVICE_CONTEXT->IASetPrimitiveTopology(type);
}

class MatrixBuffer : public ConstantBuffer
{
	struct Data
	{
		XMMATRIX _matrix;
	};
public:
	MatrixBuffer()
		: ConstantBuffer(&_data, sizeof(Data))
	{
		// 4*4 단위 행렬로 초기화
		_data._matrix = XMMatrixIdentity();
	}

	// GPU가 알게 전치행렬로 바꿈
	void SetMatrix(XMMATRIX matrix)
	{
		_data._matrix = XMMatrixTranspose(matrix);
	}

private:
	Data _data;
};

// 색깔넘기는 용
class ColorBuffer : public ConstantBuffer
{
public:
	struct Data
	{
		XMFLOAT4 color;
	};

	ColorBuffer()
		: ConstantBuffer(&_data, sizeof(Data))
	{
		_data.color = { 1,1,1,1 };
	};

	void SetColor(const XMFLOAT4 color) { _data.color = color; }

private:
	Data _data;
};