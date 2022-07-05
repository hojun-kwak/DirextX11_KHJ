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

	void SetMsg() { _msg = "앞으로 이동"; }

private:
	State _aniState = F_IDLE;

	shared_ptr<Sprite> _sprite;
	vector<shared_ptr<Action>> _actions;
	//shared_ptr<Action> _action;
	shared_ptr<Collider> _collider;
	string _msg = "";
};

