#pragma once
class MPlayer
{
public:

	enum State
	{
		L_IDLE,
		R_IDLE,

		L_RUN,
		R_RUN,

		L_JUMP,
		R_JUMP,

		CLIMBING_UP,
		CLIMBING_DOWN
	};
	
	MPlayer();
	~MPlayer();

	void Update();
	void Render();
	void PostRender();

	void SetPosition(float x, float y);
	void SetAnimation(State aniState);

	void CreateData();

	shared_ptr<Transform> GetTransForm() { return _sprite->GetTransform(); }

private:
	State _aniState = L_IDLE;
	
	shared_ptr<Sprite> _sprite;
	vector<shared_ptr<Action>> _actions;
	shared_ptr<Collider> _col;
};

