#include "framework.h"
#include "ConstantBuffer.h"

// constant = 상수
// 간단한 계산만 할용도(행렬제곰을 넘김)
ConstantBuffer::ConstantBuffer(void* data, UINT count)
	:_data(data)
	,_count(count)
{
	D3D11_BUFFER_DESC bd = {};
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = count;
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

	DEVICE->CreateBuffer(&bd, nullptr, _buffer.GetAddressOf());
}

ConstantBuffer::~ConstantBuffer()
{
}

void ConstantBuffer::Update()
{
	DEVICE_CONTEXT->UpdateSubresource(_buffer.Get(), 0, nullptr, _data, 0, 0);
}

void ConstantBuffer::SetVSBuffer(UINT slot)
{
	DEVICE_CONTEXT->VSSetConstantBuffers(slot, 1, _buffer.GetAddressOf());
}

void ConstantBuffer::SetPSBuffer(UINT slot)
{
	DEVICE_CONTEXT->PSSetConstantBuffers(slot, 1, _buffer.GetAddressOf());
}
