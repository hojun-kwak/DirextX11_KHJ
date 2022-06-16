#pragma once
class SolaSystemScene : public Scene
{
public:
	SolaSystemScene();
	virtual ~SolaSystemScene();
	
	virtual void Update() override;
	virtual void Render() override;

private:
	shared_ptr<Texture> _sun;
	shared_ptr<Texture> _earth;
	shared_ptr<Texture> _moon;

	shared_ptr<SamplerState> _samplerState;
	shared_ptr<BlendState> _blendState;
};

