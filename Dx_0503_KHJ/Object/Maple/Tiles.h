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
	void DebugRender();

	void CreateData();

	void SetPosition(Vector2 pos);
	Vector2 GetPos() { return _tilePos; }

	shared_ptr<Transform> GetTransform() { return _quad->GetTransform(); }
	shared_ptr<Quad> GetQuad() { return _quad; }
	shared_ptr<RectCollider> GetColl() { return _col; }

	bool _isActive = false;
private:
	Vector2 _tilePos = { 0,0 };

	shared_ptr<Quad> _quad;
	shared_ptr<RectCollider> _col;


};

