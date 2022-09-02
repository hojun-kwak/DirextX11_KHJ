#pragma once
class _2D_Rope
{
public:
	_2D_Rope();
	~_2D_Rope();

	void Update();
	void Render();
	void DebugRender();

	void SetPosition(Vector2 pos);

	shared_ptr<Quad> GetQuad() { return _quad; }
	shared_ptr<RectCollider> GetCol() { return _col; }

	Vector2 GetRopePos() { return _ropePos; }

	bool _isActive = false;
private:
	Vector2 _ropePos = { 0,0 };
	shared_ptr<Quad> _quad;
	shared_ptr<RectCollider> _col;
};

