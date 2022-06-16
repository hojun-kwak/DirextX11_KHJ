#pragma once

#define KEYMAX 255

class InputManager
{
private:

	enum
	{
		NONE,
		DOWN,
		UP,
		PRESS
	};

	InputManager();
	~InputManager();

public:
	static void Create()
	{
		if (_instance == nullptr)
			_instance = new InputManager();
	}

	static void Delete()
	{
		if (_instance != nullptr)
			delete _instance;
	}

	static InputManager* GetInstance()
	{
		if (_instance != nullptr)
			// 오류 코드 작성 가능
			return _instance;

		return nullptr;
	}

	void Update();

	bool Down(UINT key) { return _mapState[key] == DOWN; }
	bool Up(UINT key) { return _mapState[key] == UP; }
	bool Press(UINT key) { return _mapState[key] == PRESS; }
	Vector2& GetMousePos() { return _mousePos; }

private:
	static InputManager* _instance;

	byte _curState[KEYMAX];
	byte _oldState[KEYMAX];
	byte _mapState[KEYMAX];

	Vector2 _mousePos = { 0.0f,0.0f };
};

