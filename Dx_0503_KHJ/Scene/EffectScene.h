#pragma once
class EffectScene : public Scene
{
public:
	EffectScene();
	virtual ~EffectScene();

	// Scene을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
private:
	shared_ptr<Quad> _quad;
};

