#pragma once
class Cursors
{
public:
	enum State
	{
		NONE,
		CLICK
	};

	Cursors();
	~Cursors();

	void Update();
	void Render();
	void PostRender();

	void SetPosition(Vector2 mousePos);
	void SetAnimation(State aniState);

	void CreateData();

	void ClickEvent();

	shared_ptr<Transform> GetTransForm() { return _sprite->GetTransform(); }

private:
	State _aniState = NONE;

	Vector2 _mousePos = { 0,0 };
	shared_ptr<Sprite> _sprite;
	vector<shared_ptr<Action>> _actions;
	shared_ptr<Collider> _col;
};

