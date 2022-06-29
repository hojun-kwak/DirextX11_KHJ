#pragma once
class PixelShader : public Shader
{
public:
	PixelShader(wstring file);
	~PixelShader();

	virtual void Set() override;

private:
	Microsoft::WRL::ComPtr<ID3D11PixelShader> _pixelShader;
};

