#pragma once
class SolaSystemScene : public Scene
{
public:
	SolaSystemScene();
	virtual ~SolaSystemScene();
	
	virtual void Update() override;
	virtual void Render() override;

private:
	shared_ptr<Quad> _sun;
	shared_ptr<Quad> _earth;
	shared_ptr<Quad> _moon;

	shared_ptr<SamplerState> _samplerState;
	shared_ptr<BlendState> _blendState;
};

