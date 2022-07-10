#pragma once
class Effect
{
public:
	Effect(wstring file, Vector2 maxframe, float speed);
	~Effect();

	void Update();
	void Render();

	void CreateAction(wstring file, float speed);
	void Play(Vector2 pos);

	void End() { _isActive = false; }

	bool _isActive = true;

private:

	shared_ptr<Sprite> _sprite;
	shared_ptr<Action> _action;

	Vector2 _maxFrame;

};

