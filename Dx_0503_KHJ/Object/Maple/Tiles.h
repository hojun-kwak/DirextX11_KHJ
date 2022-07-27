#pragma once
class Tiles
{
public:

	enum State
	{
		NONE
	};

	Tiles();
	~Tiles();

	void Update();
	void Render();
	void PostRender();

	void CreateData();

	void SetPosition(Vector2 pos) { pos = _tilePos; }

private:
	Vector2 _tilePos = { 0,0 };

	shared_ptr<Quad> _quad;
	shared_ptr<Collider> _col;

};

