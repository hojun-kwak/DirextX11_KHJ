#pragma once
class IndexBuffer
{
public:
	// ������ data�� ����Ű�� ������ ����� ���� ������
	IndexBuffer(void* data, UINT count);
	~IndexBuffer();

	void IASet();

private:
	Microsoft::WRL::ComPtr<ID3D11Buffer> _buffer;
};

