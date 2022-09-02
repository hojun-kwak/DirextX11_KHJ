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

		/*L_DEAD,
		R_DEAD*/
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
	void SetTile(vector<shared_ptr<_2D_Tile>> tiles) { _tiles = tiles; }

	void CreateData();

	void CreateMoveData();
	void CreateDeadData();

	void AutoMove();

	void SetDir(Direction dir) { _dir = dir; }

	void Attacked();

	shared_ptr<RectCollider> GetCol() { return _col; }
	bool _isActive = false;

private:
	State _aniState = L_IDLE;
	Direction _dir = LEFT;

	Vector2 _monsterPos = { 0,0 };

	vector<Action::Clip> clips;
	vector<shared_ptr<Action>> _actions;

	shared_ptr<Sprite> _sprite;
	shared_ptr<RectCollider> _col;

	/*shared_ptr<Sprite> _MoveS;
	shared_ptr<RectCollider> _MoveC;

	shared_ptr<Sprite> _DeadS;
	shared_ptr<RectCollider> _DeadC;

	unordered_map<string, shared_ptr<Sprite>> _sprites;
	unordered_map<string, shared_ptr<RectCollider>> _cols;*/

	vector<shared_ptr<_2D_Tile>> _tiles;
};

