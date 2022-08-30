#include "framework.h"
#include "EffectManager.h"

EffectManager* EffectManager::_instace = nullptr;

EffectManager::EffectManager()
{
}

EffectManager::~EffectManager()
{
}

void EffectManager::Add(wstring effectFile, Vector2 maxframe, float speed, UINT poolCount)
{
	size_t t = effectFile.find(L"Effects/", 0);
	string temp = WstringToString(effectFile.substr(t + 8, effectFile.length()));
	temp = temp.substr(0, temp.size() - 4);

	if (_effectMap.count(temp) > 0)
		return;

	vector<shared_ptr<Effect>> v;
	v.reserve(poolCount);

	for (int i = 0; i < poolCount; i++)
	{
		shared_ptr<Effect> effect = make_shared<Effect>(effectFile, maxframe, speed);
		v.emplace_back(effect);
	}

	_effectMap[temp] = v;
}

void EffectManager::Play(string effect, Vector2 pos)
{
	if (_effectMap.count(effect) == 0)
		return;

	for (auto& effect : _effectMap[effect])
	{
		if (effect->_isActive == false)
		{
			effect->Play(pos);
			return;
		}
	}
}

void EffectManager::Stop(string effect, Vector2 pos)
{
	if (_effectMap.count(effect) == 0)
		return;

	for (auto& effect : _effectMap[effect])
	{
		if (effect->_isActive == false)
		{
			effect->Stop(pos);
			return;
		}
	}
}

void EffectManager::Update()
{
	for (auto& effects : _effectMap)
	{
		for (auto& effect : effects.second)
		{
			effect->Update();
		}
	}
}

void EffectManager::Render()
{
	for (auto& effects : _effectMap)
	{
		for (auto& effect : effects.second)
		{
			effect->Render();
		}
	}
}