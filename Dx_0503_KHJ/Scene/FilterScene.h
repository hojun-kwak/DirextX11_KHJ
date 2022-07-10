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
	shared_ptr<IMGSizeBuffer> _imgSizeBuffer;

	shared_ptr<Quad> _sun;
	shared_ptr<FilterBuffer> _sunfilterBuffer;

	shared_ptr<Effect> _effect;
};

