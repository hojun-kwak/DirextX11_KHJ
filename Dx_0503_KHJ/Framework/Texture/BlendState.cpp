#include "framework.h"
#include "BlendState.h"

BlendState::BlendState()
{
	_blendDesc.AlphaToCoverageEnable = false;
	_blendDesc.IndependentBlendEnable = false;

	_blendDesc.RenderTarget[0].BlendEnable = false;
	_blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	_blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	_blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;

	_blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	_blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_INV_SRC_ALPHA;
	_blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;

	_blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	Changed();
}

BlendState::~BlendState()
{
}

void BlendState::SetState()
{
	float blendFactor[] = { 0,0,0,0 };
	DEVICE_CONTEXT->OMSetBlendState(_state.Get(), blendFactor, 0xffffffff);
}

void BlendState::Alpha()
{
	_blendDesc.RenderTarget[0].BlendEnable = true;
	_blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	_blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	_blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;

	Changed();
}

void BlendState::Additive()
{
	_blendDesc.RenderTarget[0].BlendEnable = true;
	_blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	_blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
	_blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;

	Changed();
}

void BlendState::Changed()
{
	if (_state != nullptr)
		_state->Release();

	DEVICE->CreateBlendState(&_blendDesc, _state.GetAddressOf());
}
