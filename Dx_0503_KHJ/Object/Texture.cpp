#include "framework.h"
#include "Texture.h"

Texture::Texture(wstring file)
{
    _vertexShader = make_shared<VertexShader>(L"Shaders/TextureVertexShader.hlsl");
    _pixelShader = make_shared<PixelShader>(L"Shaders/TexturePixelShader.hlsl");

    _srv = make_shared<SRV>(file);
    _sampler = make_shared<SamplerState>();

    CreateVerties();
    UINT stride = sizeof(VertexUV);
    UINT count = _vertices.size();

    _vertexBuffer = make_shared<VertexBuffer>(_vertices.data(), stride, count);
    _indexBuffer = make_shared<IndexBuffer>(_indicies.data(), _indicies.size());

    _transform = make_shared<Transform>();
}

Texture::~Texture()
{
}

void Texture::CreateVerties()
{
    {
        // 왼쪽 위
        VertexUV v;
        v.pos = XMFLOAT3(-100.0f, 100.0f, 0.0f);
        v.uv = { 0.0f, 0.0f };
        _vertices.push_back(v);

        // 오른쪽 위
        v.pos = XMFLOAT3(100.0f, 100.0f, 0.0f);
        v.uv = { 1.0f, 0.0f };
        _vertices.push_back(v);

        // 오른쪽 아래
        v.pos = XMFLOAT3(100.0f, -100.0f, 0.0f);
        v.uv = { 1.0f, 1.0f };
        _vertices.push_back(v);

        // 왼쪽 아래
        v.pos = XMFLOAT3(-100.0f, -100.0f, 0.0f);
        v.uv = { 0.0f, 1.0f };
        _vertices.push_back(v);
    }
    _indicies.push_back(0);
    _indicies.push_back(1);
    _indicies.push_back(2);

    _indicies.push_back(0);
    _indicies.push_back(2);
    _indicies.push_back(3);
}

void Texture::Update()
{
    _transform->UpdateWorldBuffer();
}

void Texture::Render()
{
    _transform->SetWorldBuffer(0);

    _vertexBuffer->IASet(0);
    _indexBuffer->IASet();

    DEVICE_CONTEXT->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    _srv->PsSet(0);
    _sampler->Set(0);

    _vertexShader->Set();
    _pixelShader->PsSet();

    DEVICE_CONTEXT->DrawIndexed(_indicies.size(), 0, 0);
}
