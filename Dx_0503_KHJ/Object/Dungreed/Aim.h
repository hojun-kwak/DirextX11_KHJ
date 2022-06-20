#pragma once
class Aim
{
public:
	Aim();
	~Aim();

	shared_ptr<Transform> GetTransfom() { return _texture->GetTransform(); }

	void Update();
	void Render();

private:
	shared_ptr<Texture> _texture;
};

