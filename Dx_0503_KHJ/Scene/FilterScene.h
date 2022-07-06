#pragma once
class FilterScene : public Scene
{
public:
	FilterScene();
	virtual ~FilterScene();

	// Scene을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;

private:
	shared_ptr<Quad> _quad;
	shared_ptr<FilterBuffer> _filterBuffer;
};

