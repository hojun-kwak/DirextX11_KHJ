#pragma once
class IndexBuffer
{
public:
	// 포인터 data가 가리키는 변수에 저장된 값이 정수형
	IndexBuffer(void* data, UINT count);
	~IndexBuffer();

	void IASet();

private:
	Microsoft::WRL::ComPtr<ID3D11Buffer> _buffer;
};

