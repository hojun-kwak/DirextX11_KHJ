#include "framework.h"
#include "SamplerState.h"

SamplerState::SamplerState()
{
    _sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
    _sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
    _sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    _sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
    _sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
    _sampDesc.MinLOD = 0;
    _sampDesc.MaxLOD = D3D11_FLOAT32_MAX;

    Changed();
}

SamplerState::~SamplerState()
{
}

void SamplerState::PSSet(int slot)
{
    DEVICE_CONTEXT->PSSetSamplers(0, 1, _samplerState.GetAddressOf());
}

void SamplerState::Changed()
{
    if (_samplerState != nullptr)
        _samplerState->Release();

    DEVICE->CreateSamplerState(&_sampDesc, _samplerState.GetAddressOf());
}
