#pragma once
class Monsters
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

	Monsters();
	~Monsters();

	void Update();
	void Render();
	void PostRender();

	void SetPosition(float x, float y);
	void SetAnimation(State aniState);

	void CreateData();

	void Move();

	shared_ptr<Transform> GetTransForm() { return _sprite->GetTransform(); }

	bool _isActive = false;

private:
	State _aniState = L_IDLE;

	Vector2 _monsterPos = { 0,0 };

	shared_ptr<Sprite> _sprite;
	vector<shared_ptr<Action>> _actions;
	shared_ptr<Collider> _col;
};

