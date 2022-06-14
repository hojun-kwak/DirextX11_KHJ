#pragma once

class ConstantBuffer
{
public:
	// 포인터 data가 가리키는 변수에 저장된 값이 정수형
	ConstantBuffer(void* data, UINT count);
	~ConstantBuffer();

	void Update();
	
	void SetVSBuffer(UINT slot);
	void SetPSBuffer(UINT slot);

private:
	Microsoft::WRL::ComPtr<ID3D11Buffer> _buffer;

	void* _data;
	UINT _count;

};


