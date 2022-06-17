#include "framework.h"
#include "Transform.h"

Transform::Transform()
{
	_worldBuffer = make_shared<MatrixBuffer>();
}

Transform::~Transform()
{
}

void Transform::UpdateWorldBuffer()
{
    XMMATRIX s = XMMatrixScaling(_scale.x, _scale.y, 1);
    XMMATRIX r = XMMatrixRotationZ(_angle);
    XMMATRIX t = XMMatrixTranslation(_pos.x, _pos.y, 0);
    _srtMatrix = s * r * t;

    /*if (_parentMatrix != nullptr)
        _worldBuffer->SetMatrix(_srtMatrix * (*_parentMatrix));
    else
        _worldBuffer->SetMatrix(_srtMatrix);*/

    if (_parentMatrix != nullptr)
        _srtMatrix *= (*_parentMatrix);
    _worldBuffer->SetMatrix(_srtMatrix);
    _worldBuffer->Update();
}

void Transform::SetWorldBuffer(int slot)
{
    _worldBuffer->SetVSBuffer(slot);
}
