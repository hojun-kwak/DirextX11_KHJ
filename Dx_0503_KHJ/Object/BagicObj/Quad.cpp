#include "framework.h"
#include "Quad.h"

Quad::Quad(wstring file, wstring vs, wstring ps)
{
    _vertexShader = ADD_VS(vs);
    _pixelShader = ADD_PS(ps);

    _texture = Texture::Add(file);
    _halfSize = _texture->GetSize() * 0.5f;

    CreateData();
    UINT stride = sizeof(VertexUV);
    UINT count = _vertices.size();

    _vertexBuffer = make_shared<VertexBuffer>(_vertices.data(), stride, count);
    _indexBuffer = make_shared<IndexBuffer>(_indicies.data(), _indicies.size());

    _transform = make_shared<Transform>();
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
    SAMPLER_STATE->PSSet(0);

    _vertexShader->Set();
    _pixelShader->Set();

    DEVICE_CONTEXT->DrawIndexed(_indicies.size(), 0, 0);
}

void Quad::CreateData()
{
    {
        _vertices.emplace_back(-_halfSize.x, _halfSize.y, 0, 0); // 왼쪽위
        _vertices.emplace_back(_halfSize.x, _halfSize.y, 1, 0); // 오른쪽 위
        _vertices.emplace_back(-_halfSize.x, -_halfSize.y, 0, 1); // 왼쪽 아래
        _vertices.emplace_back(_halfSize.x, -_halfSize.y, 1, 1); // 오른쪽 아래
    }
    _indicies.push_back(0);
    _indicies.push_back(1);
    _indicies.push_back(2);

    _indicies.push_back(2);
    _indicies.push_back(1);
    _indicies.push_back(3);
}
