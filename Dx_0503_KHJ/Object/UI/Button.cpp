#include "framework.h"
#include "Button.h"

Button::Button()
{
	_state = Button::ButtonState::NONE;

	_quad = make_shared<Quad>(L"Resource/UI/Button.png", L"Shaders/TextureVertexShader.hlsl", L"Shaders/ButtonPixelShader.hlsl");

	_col = make_shared<RectCollider>(_quad->GetHalfSize());
	_col->SetParent(_quad->GetTransform());

	_buttonBuffer = make_shared<ButtonBuffer>();
	_buttonBuffer->data.state = 0;
	_buttonBuffer->data.hovered = 0.3f;
	_buttonBuffer->data.clicked = 0.5f;

#pragma region 버튼과 버튼 쉐이더
	//1. 버튼
	//	- quad : 이미지
	//	- col : 마우스가 버튼 위에 올라와있는지
	//	- text : 버튼에 이미지만 있으면 심심하니까

	//	2. Quad를 생성하고 그릴 때 픽셀셰이더를 건드려서 색깔을 바꿔야함
	//	- 어떤 식으로 바꿀거냐 ?
	//	= > 이 quad가 마우스가 올려져있나 ? , 클릭이 되어있냐 ?
	//	->CPU에서 이루어져야겠다.
	//	->GPU에 이 정보를 전달("ButtonBuffer")
	//	->GPU에서 정보를 전달 받게끔 설정("ButtonPixelShader")
#pragma endregion 
}

Button::~Button()
{
}

void Button::Update()
{
	_quad->Update();
	_col->Update();

	SetState();
}

void Button::PostRender()
{
	_buttonBuffer->SetPSBuffer(0);
	_quad->Render();

	{
		wstring text = StringToWstring(_text);
		float offSetX = _quad->GetHalfSize().x * 0.5f + 15.0f;
		float offSetY = _quad->GetHalfSize().y * 0.5f;
		float sizeX = _quad->GetHalfSize().x;
		float sizeY = _quad->GetHalfSize().y;

		float left = _textPos.x - sizeX + offSetX;
		float top = WIN_HEIGHT - _textPos.y - sizeY + offSetY;
		float right = _textPos.x + sizeX + offSetX;
		float bottom = WIN_HEIGHT - _textPos.y + sizeY + offSetY;
		RECT rect = { left,top, right, bottom };
		DirectWrite::GetInstance()->RenderText(text, rect);
	}

	ImGui::SliderFloat("HoverColor", &_buttonBuffer->data.hovered, 0.0f, 1.0f);
	ImGui::SliderFloat("ClickColor", &_buttonBuffer->data.clicked, 0.0f, 1.0f);
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
	if (_col->IsCollision(MOUSE_POS))
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

	switch (_state)
	{
	case Button::NONE:
		_buttonBuffer->data.state = 0;
		break;
	case Button::HOVER:
		_buttonBuffer->data.state = 1;
		break;
	case Button::CLICK:
		_buttonBuffer->data.state = 2;
		break;
	default:
		break;
	}
}
