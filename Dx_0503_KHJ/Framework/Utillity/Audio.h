#pragma once
using namespace FMOD;
class Audio
{
private:
	Audio();
	~Audio();

public:
	struct SoundInfo
	{
		Sound* sound = nullptr;
		Channel* Channel = nullptr;

		SoundInfo() {}
		~SoundInfo()
		{
			sound->release();
		}
	};
	static void Create()
	{
		if (_instance == nullptr)
			_instance = new Audio();
	}

	static void Delete()
	{
		if (_instance != nullptr)
			delete _instance;
	}

	static Audio* GetInstance()
	{
		if (_instance != nullptr)
			// 오류 코드 작성 가능
			return _instance;

		return nullptr;
	}

	void Update();
	void Add(string key, string file, bool bgm = false);
	void Play(string key, float volume = 1.0f);
	void Stop(string key);
	void Pause(string key);
	void Resume(string key);

	bool IsPlaySound(string key);

private:
	static Audio* _instance;

	FMOD::System* _soundSystem;
	const int MAX_CHNNEL = 15;
	unordered_map<string, SoundInfo*> _soundMap;
};

