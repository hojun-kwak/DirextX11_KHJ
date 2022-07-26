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

private:
	shared_ptr<Sprite> _sprite;
	shared_ptr<Collider> _col;

};

