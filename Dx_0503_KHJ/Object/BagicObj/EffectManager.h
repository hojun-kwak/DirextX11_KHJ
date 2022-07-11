#pragma once
// shaderManager ó�� Ȱ��
class EffectManager
{
public:
	static void Create()
	{
		if (_instace == nullptr)
			_instace = new EffectManager();
	}
	static void Delete()
	{
		if (_instace == nullptr)
			delete _instace;
	}

	static EffectManager* GetInstance()
	{
		if (_instace == nullptr)
			return _instace;
	}

public:
	// �̱���
	void Add(wstring effectFile, Vector2 maxframe, float speed, UINT poolCount = 10); // effectMap�� �߰�

	void Play(string effect, Vector2 pos); // effectMap���� �����ִ� �� ã�Ƽ� �÷���

	void Update();
	void Render();

private:
	EffectManager();
	~EffectManager();
private:
	static EffectManager* _instace;
	unordered_map<string, vector<shared_ptr<Effect>>> _effectMap;
};

