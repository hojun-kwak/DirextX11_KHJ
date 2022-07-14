#pragma once
class Zelda
{
public:

	enum State
	{
		F_IDLE,
		L_IDLE,
		B_IDLE,
		R_IDLE,

		F_RUN,
		L_RUN,
		B_RUN,
		R_RUN
	};

	Zelda();
	~Zelda();

	void Update();
	void Render();
	void PostRender();

	void SetPosition(float x, float y);
	void SetAnimation(State aniState);

	void CreateData();

	void Move();

	void SetL_Msg() { _msg = "Left_Run"; }
	void SetR_Msg() { _msg = "Right_Run"; }
	void SetF_Msg() { _msg = "Front_Run"; }
	void SetB_Msg() { _msg = "Back_Run"; }

	shared_ptr<Sprite> GetSprite() { return _sprite; }

	//void SetMsg() { _msg = "Right RUN!!!"; }
	// 
	// 이렇게 반환해서는 쓸수없는것인가??
	// define 의 콜백을 void가 아닌 string으로 썻는데??
	 string SetMsg(string msg) { return _msg = msg; }
	
	 string _msg = "START";

	 shared_ptr<Transform> GetTransForm() { return _sprite->GetTransform(); }

private:
	State _aniState = F_IDLE;

	Vector2 _zeldaPos = { 0,0 };
	shared_ptr<Sprite> _sprite;
	vector<shared_ptr<Action>> _actions;
	//shared_ptr<Action> _action;
	shared_ptr<Collider> _collider;
	
};

