#pragma once
class _2D_Monster
{
public:
	enum State
	{
		L_IDLE,
		R_IDLE,

		L_RUN,
		R_RUN,

		L_DEAD,
		R_DEAD
	};

	_2D_Monster();
	~_2D_Monster();

	void Update();
	void Render();
	void DebugRender();

	void SetPosition(float x, float y);
	void SetAnimation(State aniState);

	void CreateData();
	void AutoMove();
	bool _isActive = false;

private:
	State _aniState = L_IDLE;

	Vector2 _monsterPos = { 0,0 };

	shared_ptr<Sprite> _sprite;
	vector<shared_ptr<Action>> _actions;
	shared_ptr<Collider> _col;
};

