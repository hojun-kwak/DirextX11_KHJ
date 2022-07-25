#pragma once
class Tiles
{
public:
	Tiles();
	~Tiles();

	void Update();
	void Render();

	void CreateData();

private:
	shared_ptr<Sprite> _sprite;
	shared_ptr<Collider> _col;
};

