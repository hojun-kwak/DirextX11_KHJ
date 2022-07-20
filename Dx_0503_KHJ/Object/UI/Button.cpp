#include "framework.h"
#include "Button.h"

Button::Button()
{
	_state = Button::ButtonState::NONE;

	_quad = make_shared<Quad>(L"Resource/UI/Button.png",L"shaders/TextureVertexShader.hlsl", L"shaders/ButtonPixelShader.hlsl");
	_quad->SetParent(Camera::GetInstance()->GetTransform());

	_col = make_shared<RectCollider>(_quad->GetHalfSize());
	_col->SetParent(_quad->GetTransform());

	_buttonBuffer = make_shared<ButtonBuffer>();
	_buttonBuffer->data.state = 0;
	_buttonBuffer->data.hovered = 0.3f;
	_buttonBuffer->data.clicked = 0.5f;
}

Button::~Button()
{
}

void Button::Update()
{
	_quad->Update();
	_col->Update();
	SetState();

	if (_col->IsCollision(MOUSE_WOLRD_POS))
	{
		_state = HOVER;
		if (KEY_PRESS(VK_LBUTTON))
		{
			_state = CLICK;
		}
		if (KEY_UP(VK_LBUTTON))
		{
			if (_callback != nullptr)
				_callback();

			if (_callbackParam != nullptr)
				_callbackParam(_param);
		}
	}
	else
	{
		_state = NONE;
	}


}

void Button::PostRender()
{
	_buttonBuffer->SetPSBuffer(0);
	_quad->Render();
	_col->Render();

	{
		// 글자 사이즈를 바꾸고 싶으면 offset을 수정
		wstring text = StringToWstring(_text);
		float offSetX = _quad->GetHalfSize().x * _quad->GetTransform()->GetScale().x * 0.5f + 15.0f;
		float offSetY = _quad->GetHalfSize().y * _quad->GetTransform()->GetScale().y * 0.5f;
		float sizeX = _quad->GetHalfSize().x * _quad->GetTransform()->GetScale().x;
		float sizeY = _quad->GetHalfSize().y * _quad->GetTransform()->GetScale().y;

		float left = _textPos.x - sizeX + offSetX;
		float top = WIN_HEIGHT - _textPos.y - sizeY + offSetY;
		float right = _textPos.x + sizeX + offSetX;
		float bottom = WIN_WIDTH - _textPos.y + sizeY + offSetY;
		RECT rect = { left,top, right, bottom };
		DirectWrite::GetInstance()->RenderText(text, rect);
	}
}

void Button::SetPosition(Vector2 pos)
{
	_quad->GetTransform()->GetPos() = pos;
	_textPos = pos;
}

void Button::SetScale(Vector2 scale)
{
	_quad->GetTransform()->GetScale() = scale;
}

void Button::SetText(string text)
{
	_text = text;
}

void Button::SetState()
{
	switch (_state)
	{
	case Button::NONE:
	{
		_buttonBuffer->data.state = 0;
		break;
	}
	case Button::HOVER:
	{
		_buttonBuffer->data.state = 1;
		break;
	}
	case Button::CLICK:
	{
		_buttonBuffer->data.state = 2;
		break;
	}
	default:
		break;
	}
}
