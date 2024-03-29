#pragma once
class Rope
{
public:
	Rope();
	~Rope();

	void Update();
	void Render();
	void DebugRender();

	void SetPosition(Vector2 pos);

	shared_ptr<Transform> GetTransform() { return _quad->GetTransform(); }
	shared_ptr<Quad> GetQuad() { return _quad; }
	shared_ptr<RectCollider> GetColl() { return _col; }

	Vector2 GetRopePos() { return _ropePos; }

private:
	Vector2 _ropePos = { 0,0 };
	shared_ptr<Quad> _quad;
	shared_ptr<RectCollider> _col;
	shared_ptr<RectCollider> _ropeCol;
};

