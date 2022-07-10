#pragma once
// shaderManager ó�� Ȱ��
class EffectManager
{
public:
	EffectManager();
	~EffectManager();

	// �̱���
	void Add(wstring effctName, Vector2 maxframe, float speed, UINT poolCount = 10); // effectMap�� �߰�

	void Play(string effect, Vector2 pos); // effectMap���� �����ִ� �� ã�Ƽ� �÷���

	void Update();
	void Render();

private:
	static EffectManager* _instace;
	unordered_map<string, vector<shared_ptr<Effect>>> _effectMap;
};

