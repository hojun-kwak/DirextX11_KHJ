#pragma once

class ConstantBuffer
{
public:
	// 포인터 data가 가리키는 변수에 저장된 값이 정수형
	ConstantBuffer(void* data, UINT count);
	~ConstantBuffer();

	
	void SetVSBuffer(UINT slot);
	void SetPSBuffer(UINT slot);

private:
	void Update();
	Microsoft::WRL::ComPtr<ID3D11Buffer> _buffer;
	D3D11_MAPPED_SUBRESOURCE _subResource;

	void* _data;
	UINT _count;

};


