#pragma once
class ColliderScene : public Scene
{
public:
	ColliderScene();
	virtual ~ColliderScene();

	virtual void Update() override;
	virtual void Render() override;

	virtual void PostRender() override;

private:
	shared_ptr<RectCollider> _rectCollider1;
	shared_ptr<RectCollider> _rectCollider2;

};
