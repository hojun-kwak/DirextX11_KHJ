#include "framework.h"
#include "ConstantBuffer.h"

// constant = ���
// ������ ��길 �ҿ뵵(��������� �ѱ�)
ConstantBuffer::ConstantBuffer(void* data, UINT count)
	:_data(data)
	,_count(count)
{
	D3D11_BUFFER_DESC bd = {};
	// DEFAULT : GPU���� �а� ���� ���
	// IMMUTABLE : GPU���� �б⸸ ����
	// DYNAMIC : CPU���� ����, GPU���� �б� ����, (map, UnMap ����)
	// STAGING : CPU���� GPU�� �̵�(�б⸸ ����)
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = count;
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	DEVICE->CreateBuffer(&bd, nullptr, _buffer.GetAddressOf());
}

ConstantBuffer::~ConstantBuffer()
{
}

void ConstantBuffer::Update()
{
	DEVICE_CONTEXT->Map(_buffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0 , &_subResource );
	//DEVICE_CONTEXT->UpdateSubresource(_buffer.Get(), 0, nullptr, _data, 0, 0);
	memcpy(_subResource.pData, _data, _count);
	DEVICE_CONTEXT->Unmap(_buffer.Get(), 0);
}

void ConstantBuffer::SetVSBuffer(UINT slot)
{
	DEVICE_CONTEXT->VSSetConstantBuffers(slot, 1, _buffer.GetAddressOf());
	Update();
}

void ConstantBuffer::SetPSBuffer(UINT slot)
{
	DEVICE_CONTEXT->PSSetConstantBuffers(slot, 1, _buffer.GetAddressOf());
	Update();
}
