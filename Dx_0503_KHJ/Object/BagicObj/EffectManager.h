#pragma once
// shaderManager 처럼 활용
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
	// 싱글턴
	void Add(wstring effectFile, Vector2 maxframe, float speed, UINT poolCount = 10); // effectMap에 추가

	void Play(string effect, Vector2 pos); // effectMap에서 꺼져있는 애 찾아서 플레이

	void Update();
	void Render();

private:
	EffectManager();
	~EffectManager();
private:
	static EffectManager* _instace;
	unordered_map<string, vector<shared_ptr<Effect>>> _effectMap;
};

