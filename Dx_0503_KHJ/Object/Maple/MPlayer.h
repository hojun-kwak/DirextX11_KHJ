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

		CLIMBING
	};

	enum JumpingState
	{
		NONE,
		UP,
		DOWN
	};
	
	MPlayer();
	~MPlayer();

	void Update();
	void Render();
	void PostRender();
	void DebugRender();

	void SetPosition(float x, float y);
	void SetAnimation(State aniState);

	void CreateData();

	void Operation();
	void Jumpimg();

	shared_ptr<Transform> GetTransForm() { return _sprite->GetTransform(); }
	shared_ptr<Collider> GetCol() { return _col; }
	void SetPositioning(shared_ptr<class Tiles> tile);

private:
	bool _isJumping = false;

	State _aniState = L_IDLE;
	JumpingState _jumpState = NONE;

	Vector2 _playerPos = { 0,0 };
	shared_ptr<Sprite> _sprite;
	vector<shared_ptr<Action>> _actions;
	shared_ptr<Collider> _col;

	shared_ptr<class Tiles> _tile;

	float _jumpTime = 0.0f;
	//float _jumpHeight = _playerPos.y + 50.0f;
	float _jumpPower = 50.0f;
};

