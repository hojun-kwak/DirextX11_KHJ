#pragma once
class RasterizerState
{
public:
	RasterizerState();
	~RasterizerState();

	void Changed();

private:
	Microsoft::WRL::ComPtr<ID3D11RasterizerState> _state;
	D3D11_RASTERIZER_DESC _desc;
};

