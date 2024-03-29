#pragma once
class Action
{
public:
	struct Clip
	{
		Vector2 _startPos;
		Vector2 _size;
		shared_ptr<Texture> _texture;

		Clip(float x, float y, float w, float h, shared_ptr<Texture> texture)
			: _startPos({ x,y }), _size({ w,h }), _texture(texture)
		{}
	};

	enum Type
	{
		END,
		LOOP,
		PINPONG
	};

	Action(vector<Clip> clips, string name = "", Type type = LOOP, float speed = 0.1f);
	~Action();

	void Update();

	void Play();
	void Pause();
	void Reset();
	void Stop();

	void SetEndEvent(CallBack event) { _endEvent = event; }

	string SetEvent(CallBackA test) { _endEventA = test; }

	Clip GetCurClip() { return _clips[_curClipNum]; }
	bool IsPlay() { return _isPlay; }

	Type GetAniType() { return _repeatType; }

private:
	bool _isPlay = true;
	vector<Clip> _clips;
	Type _repeatType;

	UINT _curClipNum = 0;

	float _time = 0.0f;
	float _speed;

	bool _isReverse = false;

	string _actionName = "";

	// 세팅은 내가 컴파일 전에 세팅
	// 호출 나중에 니가 알아서
	CallBack _endEvent = nullptr;

	CallBackA _endEventA = nullptr;
};

