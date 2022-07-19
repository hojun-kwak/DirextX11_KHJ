#pragma once
class Button
{
public:
	enum ButtonState
	{
		NONE,
		HOVER,
		CLICK
	};

	Button();
	~Button();

	void Update();
	void PostRender();

	void SetPosition(Vector2 pos);
	void SetScale(Vector2 scale);
	void SetText(string text);

	void SetState();
	
	shared_ptr<RectCollider> GetRectCollider() { return _col; }

private:
	ButtonState _state;

	shared_ptr<Quad> _quad;
	shared_ptr<RectCollider> _col;

	string _text;
	Vector2 _textPos = { 0,0 };

	shared_ptr<ButtonBuffer> _buttonBuffer;
};

