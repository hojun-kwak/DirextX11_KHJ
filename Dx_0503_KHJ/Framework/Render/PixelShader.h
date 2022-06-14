#pragma once
class PixelShader
{
public:
	PixelShader(wstring file);
	~PixelShader();

	void CreateBlob(wstring file);
	void CreatePixelShader();

	void PsSet();

private:
	Microsoft::WRL::ComPtr<ID3D11PixelShader> _pixelShader;
	Microsoft::WRL::ComPtr<ID3DBlob> _blob;
};

