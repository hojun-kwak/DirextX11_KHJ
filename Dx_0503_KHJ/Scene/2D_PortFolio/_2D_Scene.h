#pragma once
class _2D_Scene : public Scene
{
public:
	_2D_Scene();
	virtual ~_2D_Scene();

	// Scene을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render() override;

	virtual void PostRender() override;
	virtual void DebugRender() override;

	void CameraSetting();

private:
	shared_ptr<Quad> _background;
	shared_ptr<_2D_Player> _player;
	shared_ptr<Transform> _playerFollow;
};

