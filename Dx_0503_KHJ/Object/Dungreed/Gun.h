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
		_quad->GetTransform()->SetParent(transform);
	}

private:
	shared_ptr<Quad> _quad;
};

