#pragma once
class _2D_Cursor
{
public:
	enum State
	{
		NONE,
		CLICK
	};

	_2D_Cursor();
	~_2D_Cursor();

	void Update();
	void Render();
	void DebugRender();

	void SetPosition(Vector2 mousePos);
	void SetAnimation(State aniState);

	void CreateData();
	void ClickEvent();

private:
	State _aniState = NONE;

	Vector2 _mousePos = { 0,0 };
	shared_ptr<Sprite> _sprite;
	vector<shared_ptr<Action>> _actions;
	shared_ptr<Collider> _col;

};

