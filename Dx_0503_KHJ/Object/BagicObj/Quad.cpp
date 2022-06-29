#include "framework.h"
#include "Quad.h"

Quad::Quad(wstring file)
{
    _vertexShader = ADD_VS(L"Shaders/TextureVertexShader.hlsl");
    _pixelShader = ADD_PS(L"Shaders/TexturePixelShader.hlsl");

    CreateData();
    UINT stride = sizeof(VertexUV);
    UINT count = _vertices.size();

    _vertexBuffer = make_shared<VertexBuffer>(_vertices.data(), stride, count);
    _indexBuffer = make_shared<IndexBuffer>(_indicies.data(), _indicies.size());

    _transform = make_shared<Transform>();

    // size
    _texture = Texture::Add(file);
    _halfSize = _texture->GetSize() * 0.5f;
}

Quad::~Quad()
{
}

void Quad::Update()
{
    _transform->UpdateWorldBuffer();
}

void Quad::Render()
{
    _transform->SetWorldBuffer(0);

    _vertexBuffer->IASet(0);
    _indexBuffer->IASet();

    IASetPT();

    // Texture
    _texture->Set(0);
    SAMPLER_STATE->Set(0);

    _vertexShader->Set();
    _pixelShader->Set();

    DEVICE_CONTEXT->DrawIndexed(_indicies.size(), 0, 0);
}

void Quad::CreateData()
{
    {
        // 왼쪽 위
        _vertices.emplace_back(-_halfSize._x, _halfSize._y, 0, 0);

        // 오른쪽 위
        _vertices.emplace_back(_halfSize._x, _halfSize._y, 0, 0);

        // 오른쪽 아래
        _vertices.emplace_back(_halfSize._x, -_halfSize._y, 0, 0);

        // 왼쪽 아래
        _vertices.emplace_back(-_halfSize._x, -_halfSize._y, 0, 0);
    }
    _indicies.push_back(0);
    _indicies.push_back(1);
    _indicies.push_back(2);

    _indicies.push_back(2);
    _indicies.push_back(1);
    _indicies.push_back(3);
}
