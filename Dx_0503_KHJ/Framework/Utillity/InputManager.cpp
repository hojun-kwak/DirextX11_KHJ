#include "framework.h"
#include "InputManager.h"

InputManager* InputManager::_instance = nullptr;
InputManager::InputManager()
	:_curState{}
	, _oldState{}
	, _mapState{}
{

}

InputManager::~InputManager()
{
}

void InputManager::Update()
{
	memcpy(_oldState, _curState,sizeof(_oldState));

	GetKeyboardState(_curState);

	for (int i = 0; i < KEYMAX; i++)
	{
		byte key = _curState[i] & 0x80; // 비트연산자
		_curState[i] = key ? 1 : 0; // 삼항 연산자

		int old = _oldState[i];
		int cur = _curState[i];

		// 지금 막 누른상태
		if (old == 0 && cur == 1)
		{
			_mapState[i] = DOWN;
		}

		// 눌렀다 땟을떄
		else if (old == 0 && cur == 1)
		{
			_mapState[i] = UP;
		}

		// 계속 누른상태
		else if (old == 1 && cur == 1)
		{
			_mapState[i] = PRESS;
		}
		else
			_mapState[i] = NONE;
	}
}
