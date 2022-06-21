#pragma once
class Gun
{
public:
	Gun();
	~Gun();

	void Update();
	void Render();

	void SetPlayer(shared_ptr<Transform> transform)
	{
		_texture->GetTransform()->SetParent(transform);
	}

private:
	shared_ptr<Texture> _texture;
};

