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
	void DebugSetColor();

	void SetPosition(float x, float y);
	void SetAnimation(State aniState);

	void CreateData();

	void Operation();

	void Jumpimg();

	shared_ptr<Transform> GetTransForm() { return _sprite->GetTransform(); }
	void SetTile(vector<vector<shared_ptr<class _2D_Tile>>> tiles) { _tiles = tiles; }
	void SetRope(vector<shared_ptr<class _2D_Rope>> ropes) { _ropes = ropes; }

private:
	State _aniState = _2D_Player::State::L_IDLE;

	Vector2 _playerPos = { 0,0 };
	shared_ptr<Sprite> _sprite;
	vector<shared_ptr<Action>> _actions;
	shared_ptr<RectCollider> _col;
	shared_ptr<RectCollider> _ropeCol;

	vector<vector<shared_ptr<class _2D_Tile>>> _tiles;
	vector<shared_ptr<_2D_Rope>> _ropes;

	bool _isJumping = false;
	float _jumpPower = 150.0f;
	float _gravity = 15.0f;
};

