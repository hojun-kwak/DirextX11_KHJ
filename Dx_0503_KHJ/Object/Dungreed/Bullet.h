#pragma once
class Bullet
{
public:
	Bullet();
	~Bullet();

	void Update();
	void Render();

	bool _isActive = false;

private:
	shared_ptr<Texture> _texture;
};

