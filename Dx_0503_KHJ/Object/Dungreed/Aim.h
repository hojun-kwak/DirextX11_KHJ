#pragma once
class Aim
{
public:
	Aim();
	~Aim();

	shared_ptr<Transform> GetTransfom() { return _quad->GetTransform(); }

	void Update();
	void Render();

private:
	shared_ptr<Quad> _quad;
};

