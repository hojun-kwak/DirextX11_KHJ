#pragma once
class Scene
{
public:
	Scene();
	virtual ~Scene();

	virtual void Update() abstract;
	virtual void Render() abstract;
	virtual void PreRender() {}
	virtual void PostRender() {}
	virtual void DebugRender() {}

private:
};

