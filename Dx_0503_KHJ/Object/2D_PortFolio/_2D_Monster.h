#pragma once
class _2D_Monster
{
public:
	enum State
	{
		L_IDLE,
		L_STEP_BACK,

		R_IDLE,
		R_STEP_BACK,

		L_DEAD,
		R_DEAD
	};

	enum Direction
	{
		LEFT,
		RIGHT
	};

	_2D_Monster();
	~_2D_Monster();

	void Update();
	void Render();
	void DebugRender();

	void SetPosition(float x, float y);
	void SetAnimation(State aniState);
	void SetTile(vector<vector<shared_ptr<_2D_Tile>>> tiles) { _tiles = tiles; }

	void CreateData();
	void AutoMove();
	bool _isActive = false;

private:
	State _aniState = L_IDLE;
	Direction _dir = LEFT;

	Vector2 _monsterPos = { 0,0 };

	shared_ptr<Sprite> _sprite;
	vector<shared_ptr<Action>> _actions;
	shared_ptr<Collider> _col;

	vector<vector<shared_ptr<_2D_Tile>>> _tiles;
};

