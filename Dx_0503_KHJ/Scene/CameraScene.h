#pragma once
class CameraScene : public Scene
{
public:
	CameraScene();
	virtual ~CameraScene();

	virtual void Update() override;
	virtual void Render() override;
	virtual void PreRender() override;
	virtual void PostRender() override;

	void SavePos();
	void Test(int test);
	Vector2 LoadPos();

private:
	shared_ptr<Quad> _background;
	shared_ptr<Zelda> _zelda;
	shared_ptr<Transform> _zeldaFollow;

	shared_ptr<Button> _button;

	// Render Target
	shared_ptr<RenderTarget> _rtv;
	shared_ptr<Quad> _targetTexture;

	shared_ptr<Quad> _miniPlayer;
};

