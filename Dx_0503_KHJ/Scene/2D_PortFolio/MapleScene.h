#pragma once
class MapleScene : public Scene
{
public:
	MapleScene();
	virtual ~MapleScene();

	// Scene��(��) ���� ��ӵ�
	virtual void Update() override;
	virtual void Render() override;

	virtual void PostRender() override;

private:
	shared_ptr<Quad> _background;
	shared_ptr<MPlayer> _player;

	shared_ptr<Transform> _playerFollow;
};

