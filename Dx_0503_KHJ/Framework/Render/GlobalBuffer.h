#pragma once

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
		// 4*4 ���� ��ķ� �ʱ�ȭ
		_data._matrix = XMMatrixIdentity();
	}

	// GPU�� �˰� ��ġ��ķ� �ٲ�
	void SetMatrix(XMMATRIX matrix)
	{
		_data._matrix = XMMatrixTranspose(matrix);
	}

private:
	Data _data;
};

// ����ѱ�� ��
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

private:
	Data _data;
};