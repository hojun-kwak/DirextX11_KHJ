#pragma once
class DunGridScene : public Scene
{
public:

	DunGridScene();
	virtual~DunGridScene();

	// Scene��(��) ���� ��ӵ�
	virtual void Update() override;
	virtual void Render() override;


private:
	shared_ptr<Texture> _Character;
	shared_ptr<Texture> _Gun;
	shared_ptr<Texture> _Skill;
	shared_ptr<Texture> _MousePointer;

	bool skillActive = false;

	shared_ptr<SamplerState> _samplerState;
	shared_ptr<BlendState> _blendState;
	
};

