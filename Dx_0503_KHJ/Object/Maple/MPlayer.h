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

	MPlayer();
	~MPlayer();

	void Update();
	void Render();
	void PostRender();
	void DebugRender();

	void SetPosition(float x, float y);
	void SetAnimation(State aniState);

	void SetTile(vector<shared_ptr<class Tiles>> tile) { _tile = tile; }

	void CreateData();

	void Operation();
	void Jumpimg();

	shared_ptr<Transform> GetTransForm() { return _sprite->GetTransform(); }
	shared_ptr<Collider> GetCol() { return _col; }
	shared_ptr<Sprite> GetSprite() { return _sprite; }

private:
	State _aniState = L_IDLE;

	Vector2 _playerPos = { 0,0 };
	shared_ptr<Sprite> _sprite;
	vector<shared_ptr<Action>> _actions;
	shared_ptr<Collider> _col;

	vector<shared_ptr<class Tiles>> _tile;

	bool _isJumping = false;
	float _jumpPower = 150.0f;
	float _gravity = 15.0f;
};

