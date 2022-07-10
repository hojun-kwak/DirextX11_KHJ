#pragma once
// shaderManager 처럼 활용
class EffectManager
{
public:
	EffectManager();
	~EffectManager();

	// 싱글턴
	void Add(wstring effctName, Vector2 maxframe, float speed, UINT poolCount = 10); // effectMap에 추가

	void Play(string effect, Vector2 pos); // effectMap에서 꺼져있는 애 찾아서 플레이

	void Update();
	void Render();

private:
	static EffectManager* _instace;
	unordered_map<string, vector<shared_ptr<Effect>>> _effectMap;
};

