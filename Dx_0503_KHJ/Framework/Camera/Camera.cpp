#include "framework.h"
#include "Camera.h"

Camera* Camera::_instance = nullptr;

Camera::Camera()
{
	_transform = make_shared<Transform>();
	_transform->SetMatrixBuffer(1);
	_projectionBuffer = make_shared<MatrixBuffer>();
}

Camera::~Camera()
{
}

void Camera::Update()
{
	if (_target == nullptr)
		FreeMode();
	else
		FollowMode();

	Shake();

	_transform->UpdateWorldBuffer();
	_transform->SetMatrixBuffer(1);
}

void Camera::PostRender()
{
	ImGui::Text("CameraInfo");
	ImGui::Text("CameraX : %.1f, CameraY : %.1f", _transform->GetPos().x * (-1.0f), _transform->GetPos().y * (-1.0f));
}

void Camera::ShakeStart(float magintude, float duration, float reduceDamping)
{
	_magnitude = magintude;
	_duration = duration;
	_reduceDamping = reduceDamping;
}

void Camera::SetViewPort(UINT width, UINT height)
{
	D3D11_VIEWPORT vp;
	vp.Width = width;
	vp.Height = height;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	DEVICE_CONTEXT->RSSetViewports(1, &vp);
}

void Camera::SetProjectionBuffer(UINT width, UINT height)
{
	XMMATRIX projection = XMMatrixOrthographicOffCenterLH(0, width, 0, height, 0.0f, 1.0f);
	_projectionBuffer->SetMatrix(projection);
	_projectionBuffer->SetVSBuffer(2);
}

void Camera::FreeMode()
{
	if (KEY_PRESS(VK_RBUTTON))
	{
		if (KEY_PRESS('W'))
		{
			_transform->GetPos().y -= _speed * DELTA_TIME;
		}
		if (KEY_PRESS('S'))
		{
			_transform->GetPos().y += _speed * DELTA_TIME;
		}
		if (KEY_PRESS('A'))
		{
			_transform->GetPos().x += _speed * DELTA_TIME;
		}
		if (KEY_PRESS('D'))
		{
			_transform->GetPos().x -= _speed * DELTA_TIME;
		}
	}
}

void Camera::FollowMode()
{
	Vector2 targetPos = _target->GetPos() - _offset;
	if (targetPos.x < _leftBottom.x)
		targetPos.x = _leftBottom.x;

	if (targetPos.x > _rightTop.x)
		targetPos.x = _rightTop.x;

	if (targetPos.y < _leftBottom.y)
		targetPos.y = _leftBottom.y;

	if (targetPos.y > _rightTop.y)
		targetPos.y = _rightTop.y;

	_transform->GetPos() = LERP(_transform->GetPos(), targetPos, DELTA_TIME * _speed);
}

void Camera::Shake()
{
	if (_duration <= 0.0f)
	{
		_transform->GetPos() = _originPos;
		return;
	}

	_duration -= DELTA_TIME;
	_magnitude -= DELTA_TIME * _reduceDamping;

	if (_magnitude < 0.0f)
	{
		_magnitude = 0.0f;
		_duration = 0.0f;
	}

	Vector2 temp;
	float minT = -_magnitude *((float)rand() / (float)RAND_MAX);
	float maxT = +_magnitude *((float)rand() / (float)RAND_MAX);
	//(float)(rand()%45) / 10;
	_transform->GetPos() = _originPos + Vector2(minT, maxT);
}