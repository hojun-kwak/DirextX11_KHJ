#include "framework.h"
#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(void* data, UINT stride, UINT count, UINT offset)
    :_stride(stride)
    ,_count(count)
    ,_offset(offset)
    //,_data(data)
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
    //bd.Usage = D3D11_USAGE_DYNAMIC;
    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.ByteWidth = _stride * _count;
    bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    //bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

    D3D11_SUBRESOURCE_DATA initData = {};
    initData.pSysMem = data;
    /*initData.SysMemPitch = 0;
    initData.SysMemSlicePitch = 0;*/

    // 정점 정보들을 담는 정점 버퍼
    DEVICE->CreateBuffer(&bd, &initData, _vertexBuffer.GetAddressOf());
}

//void VertexBuffer::Update()
//{
//    DEVICE_CONTEXT->Map(_vertexBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &_subResource);
//    //DEVICE_CONTEXT->UpdateSubresource(_buffer.Get(), 0, nullptr, _data, 0, 0);
//    memcpy(_subResource.pData, _data, (_count * _stride));
//    DEVICE_CONTEXT->Unmap(_vertexBuffer.Get(), 0);
//}

void VertexBuffer::IASet(int slot)
{
    DEVICE_CONTEXT->IASetVertexBuffers(slot, 1, _vertexBuffer.GetAddressOf(), &_stride, &_offset);
    //Update();
}
