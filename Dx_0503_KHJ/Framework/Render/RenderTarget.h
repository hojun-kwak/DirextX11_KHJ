#pragma once
class RenderTarget
{
public:
	RenderTarget(float width, float height);
	~RenderTarget();

	void Set();

	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> GetSRV() { return _srv; }
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> GetRTV() { return _rtv; }

private:
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> _srv;
	Microsoft::WRL::ComPtr<ID3D11Texture2D> _rtvTexture;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> _rtv;

	float _width = 0.0f;
	float _height = 0.0f;
};

