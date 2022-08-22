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
	shared_ptr<Collider> _circleCollider1;
	shared_ptr<Collider> _circleCollider2;
	shared_ptr<Collider> _rectCollider1;
	shared_ptr<Collider> _rectCollider2;

};

