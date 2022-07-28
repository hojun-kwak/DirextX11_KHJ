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

#pragma region ��ư�� ��ư ���̴�
	//1. ��ư
	//	- quad : �̹���
	//	- col : ���콺�� ��ư ���� �ö���ִ���
	//	- text : ��ư�� �̹����� ������ �ɽ��ϴϱ�

	//	2. Quad�� �����ϰ� �׸� �� �ȼ����̴��� �ǵ���� ������ �ٲ����
	//	- � ������ �ٲܰų� ?
	//	= > �� quad�� ���콺�� �÷����ֳ� ? , Ŭ���� �Ǿ��ֳ� ?
	//	->CPU���� �̷�����߰ڴ�.
	//	->GPU�� �� ������ ����("ButtonBuffer")
	//	->GPU���� ������ ���� �ްԲ� ����("ButtonPixelShader")
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
