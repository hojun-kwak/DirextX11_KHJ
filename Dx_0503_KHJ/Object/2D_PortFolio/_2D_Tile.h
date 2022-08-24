#pragma once
class _2D_Tile
{
public:
	_2D_Tile();
	~_2D_Tile();

	void Update();
	void Render();
	void DebugRender();

	void SetPosition(float x, float y);
private:
	Vector2 _tilePos = { 0,0 };

	shared_ptr<Quad> _quad;
	shared_ptr<RectCollider> _col;
};

