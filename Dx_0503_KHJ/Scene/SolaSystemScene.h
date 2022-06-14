#pragma once
class SolaSystemScene : public Scene
{
public:
	SolaSystemScene();
	virtual ~SolaSystemScene();
	
	virtual void Update() override;
	virtual void Render() override;

private:
	shared_ptr<Texture> _texture1;
	shared_ptr<Texture> _texture2;
	shared_ptr<Texture> _texture3;
};

