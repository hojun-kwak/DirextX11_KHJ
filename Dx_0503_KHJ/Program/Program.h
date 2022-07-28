#pragma once
class Program
{
public:
	Program();
	~Program();

	void Update();
	void Render();

private:
	bool _OnOff = false;
	shared_ptr<Scene> _scene;
};

