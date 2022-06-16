#pragma once
class StateManager
{
private:
	StateManager();
	~StateManager();
public:
	static void Create()
	{
		if (_instance == nullptr)
			_instance = new StateManager();
	}

	static void Delete()
	{
		if (_instance != nullptr)
			delete _instance;
	}

	static StateManager* GetInstance()
	{
		if (_instance != nullptr)
			return _instance;

		return nullptr;
	}

	shared_ptr<SamplerState> GetSamplerState() { return _samplerState; }
	shared_ptr<BlendState> GetAlphaState() { return _alphaState; }
	shared_ptr<BlendState> GetAdditiveState() { return _additiveState; }
	shared_ptr<BlendState> GetBlendState() { return _blendState; }
	shared_ptr<RasterizerState> GetRasterizerState() { return _rasterizerState; }

private:
	static StateManager* _instance;

	shared_ptr<SamplerState> _samplerState;
	shared_ptr<BlendState> _alphaState;
	shared_ptr<BlendState> _additiveState;
	shared_ptr<BlendState> _blendState;
	shared_ptr<RasterizerState> _rasterizerState;
};

