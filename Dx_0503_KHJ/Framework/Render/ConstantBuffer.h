#pragma once

class ConstantBuffer
{
public:
	// ������ data�� ����Ű�� ������ ����� ���� ������
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


