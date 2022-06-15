#include "framework.h"
#include "Timer.h"

Timer* Timer::_instance = nullptr;
Timer::Timer()
{
	// 1초동안 CPU의 진동수를 반환하는 함수
	QueryPerformanceFrequency((LARGE_INTEGER*)&_periodFrequency);

	// 현재 진동수
	QueryPerformanceCounter((LARGE_INTEGER*)&_curTime);
	QueryPerformanceCounter((LARGE_INTEGER*)&_lastTime);

	_timeScale = 1.0f / (double)_periodFrequency;
}

Timer::~Timer()
{
}

void Timer::Update()
{
	
	// (지금까지 진동한 횟수 - 처음에 진동한 횟수) * (1/초당 진동수) = _runTime
	// (지금까지 진동한 횟수 - Update를 거치기전의 진동수) * (1/초당진동수) = (DELTATIME == _timeTickElased)
	QueryPerformanceCounter((LARGE_INTEGER*)&_curTime);
	_timeTickElased = (double)(_curTime - _lastTime) * _timeScale;

	if (_lockFPS != 0)
	{
		while (_timeTickElased < (1.0 / _lockFPS))
		{
			QueryPerformanceCounter((LARGE_INTEGER*)&_curTime);
			_timeTickElased = (double)(_curTime - _lastTime) * _timeScale;
		}
	}

	// Update를 거치기전의 진동수
	_lastTime = _curTime;

	_frameCount++;
	_oneSecCount += _timeTickElased;
	_runTime += _timeTickElased; // 경과된 시간

	// 1초마다 갱신해야되는 정보
	if (_oneSecCount >= 1)
	{
		_oneSecCount = 0;
		_frameCount = 0;

		_frameRate = _frameCount;
	}
}
