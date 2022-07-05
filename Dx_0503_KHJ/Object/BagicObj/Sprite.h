#pragma once
class Sprite : public Quad
{
public:
	Sprite(wstring file, Vector2 maxFrame = Vector2{ 1,1 });
	~Sprite();

	virtual void Update() override;
	virtual void Render() override;

	virtual void CreateData() override;

	Vector2 GetHalfFrameSize();
	void SetFrameBuffer(int x, int y) { _frameBuffer->data.curFrame = { (float)x, (float)y }; }
	void SetClip(Action::Clip clip);

private:
	Vector2 _maxFrame;
	shared_ptr<FrameBuffer> _frameBuffer;
};

