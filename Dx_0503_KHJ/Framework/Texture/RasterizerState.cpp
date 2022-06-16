#include "framework.h"
#include "RasterizerState.h"

RasterizerState::RasterizerState()
{
	_desc.CullMode = D3D11_CULL_NONE;
	_desc.FillMode = D3D11_FILL_SOLID;

	Changed();
}

RasterizerState::~RasterizerState()
{
}

void RasterizerState::Changed()
{
	if (_state != nullptr)
		_state->Release();

	DEVICE->CreateRasterizerState(&_desc, _state.GetAddressOf());

}
