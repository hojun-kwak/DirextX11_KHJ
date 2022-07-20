#pragma once
class CameraScene : public Scene
{
public:
	CameraScene();
	virtual ~CameraScene();

	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;

	void SavePos();
	Vector2 LoadPos();

private:
	shared_ptr<Quad> _background;
	shared_ptr<Zelda> _zelda;
	shared_ptr<Transform> _zeldaFollow;
};

