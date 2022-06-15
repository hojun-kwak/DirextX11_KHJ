#pragma once
class Timer
{
public:
	Timer();
	~Timer();

	static void Create()
	{
		if (_instance == nullptr)
			_instance = new Timer();
	}

	static void Delete()
	{
		if (_instance != nullptr)
			delete _instance;
	}

	static Timer* GetInstance()
	{
		if (_instance != nullptr)
			// ���� �ڵ� �ۼ� ����
			return _instance;

		return nullptr;
	}

	void Update();

	double GetDetatime() { return (double)_timeTickElased; }
	int GetFPS() { return (int)_lockFPS; }
	void SetFPS(double fps) { _lockFPS = fps; }

private:
	static Timer* _instance;

	double _timeScale = 0;
	double _timeTickElased = 0;

	__int64 _curTime = 0;
	__int64 _lastTime = 0;
	__int64 _periodFrequency = 0; // �ð��� �󵵼�
	
	int _frameRate = 0;
	int _frameCount = 0;

	double _oneSecCount = 0;
	double _runTime = 0;

	double _lockFPS = 0;

};

