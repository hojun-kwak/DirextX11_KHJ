#pragma once
class EffectScene : public Scene
{
public:
	EffectScene();
	virtual ~EffectScene();

	// Scene��(��) ���� ��ӵ�
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
private:
	shared_ptr<Quad> _quad;
};

