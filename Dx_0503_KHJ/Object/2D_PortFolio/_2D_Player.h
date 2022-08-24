#pragma once
class _2D_Player
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

		CLIMBING_IDLE,
		CLIMBING
	};

	_2D_Player();
	~_2D_Player();

	void Update();
	void Render();
	void PostRender();
	void DebugRender();

	void SetPosition(float x, float y);
	void SetAnimation(State aniState);

	void CreateData();

	shared_ptr<Transform> GetTransForm() { return _sprite->GetTransform(); }

private:
	State _aniState = L_IDLE;

	Vector2 _playerPos = { 0,0 };
	shared_ptr<Sprite> _sprite;
	vector<shared_ptr<Action>> _actions;
	shared_ptr<RectCollider> _col;

	bool _isJumping = false;
	float _jumpPower = 150.0f;
	float _gravity = 15.0f;
};

