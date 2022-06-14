#include "framework.h"
#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(void* data, UINT stride, UINT count, UINT offset)
    :_stride(stride)
    ,_count(count)
    ,_offset(offset)
{
    CreateVertexBuffer(data);
}

VertexBuffer::~VertexBuffer()
{
}


void VertexBuffer::CreateVertexBuffer(void* data)
{
    // Vertex 버퍼: Vertex
    D3D11_BUFFER_DESC bd = {};
    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.ByteWidth = _stride * _count;
    bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;

    D3D11_SUBRESOURCE_DATA initData = {};
    initData.pSysMem = data;

    // 정점 정보들을 담는 정점 버퍼
    DEVICE->CreateBuffer(&bd, &initData, _vertexBuffer.GetAddressOf());
}

void VertexBuffer::IASet(int slot)
{
    DEVICE_CONTEXT->IASetVertexBuffers(slot, 1, _vertexBuffer.GetAddressOf(), &_stride, &_offset);
}
