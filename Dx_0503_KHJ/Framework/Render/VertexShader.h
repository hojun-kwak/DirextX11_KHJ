#pragma once
class VertexShader : public Shader
{
	friend class ShaderManager;

public:
	VertexShader(wstring file);
	~VertexShader();

	void CreateInputLayOut();

	virtual void Set() override;

private:
	Microsoft::WRL::ComPtr<ID3D11VertexShader> _vertexShader;
	Microsoft::WRL::ComPtr<ID3D11InputLayout> _inputLayout; // 서식
	Microsoft::WRL::ComPtr<ID3D11ShaderReflection> _reflection; // 반사
};

