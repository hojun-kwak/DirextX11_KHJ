#include "framework.h"
#include "Audio.h"

Audio* Audio::_instance = nullptr;
Audio::Audio()
{
	System_Create(&_soundSystem);
	_soundSystem->init(MAX_CHNNEL, FMOD_INIT_NORMAL, nullptr);
}

Audio::~Audio()
{
	for (auto info : _soundMap)
		delete info.second;
	_soundSystem->release();
}

void Audio::Update()
{
	_soundSystem->update();
}

void Audio::Add(string key, string file, bool bgm)
{
	if (_soundMap.count(key) > 0)
		return;

	SoundInfo* info = new SoundInfo();

	if (bgm)
		_soundSystem->createStream(file.c_str(), FMOD_LOOP_NORMAL, nullptr, IN & info->sound);
	else
		_soundSystem->createSound(file.c_str(), FMOD_DEFAULT, nullptr, IN & info->sound);

	_soundMap[key] = info;
}

void Audio::Play(string key, float volum)
{
	if (_soundMap.count(key) == 0)
		return;

	_soundSystem->playSound(_soundMap[key]->sound, nullptr, false, IN &_soundMap[key]->Channel);
	_soundMap[key]->Channel->setVolume(volum);
}

void Audio::Stop(string key)
{
	if (_soundMap.count(key) == 0)
		return;

	_soundMap[key]->Channel->stop();
}

void Audio::Pause(string key)
{
	if (_soundMap.count(key) == 0)
		return;

	_soundMap[key]->Channel->setPaused(true);
}

void Audio::Resume(string key)
{
	if (_soundMap.count(key) == 0)
		return;


	_soundMap[key]->Channel->setPaused(false);
}

bool Audio::IsPlaySound(string key)
{
	if (_soundMap.count(key) == 0)
		return false;

	bool isPlay = false;
	_soundMap[key]->Channel->isPlaying(IN & isPlay);

	return isPlay;
}
