#pragma once
class ShaderManager
{
private:
	ShaderManager();
	~ShaderManager();

public:
	static void Create()
	{
		if (_instance == nullptr)
			_instance = new ShaderManager();
	}
	static void Delete()
	{
		if (_instance != nullptr)
			delete _instance;
	}
	static ShaderManager* GetInstace()
	{
		if (_instance != nullptr)
			return _instance;
	}

	shared_ptr<VertexShader> AddVS(wstring file);
	shared_ptr<PixelShader> AddPS(wstring file);


private:
	static ShaderManager* _instance;
	unordered_map<wstring, shared_ptr<Shader>> _shadersMap; // �ؽ���
};

