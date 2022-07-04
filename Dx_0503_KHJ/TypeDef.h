#pragma once

#define WIN_WIDTH 1280
#define WIN_HEIGHT 720

#define DEVICE Device::GetInstance()->GetDevice()
#define DEVICE_CONTEXT Device::GetInstance()->GetDeviceContext()

#define DELTA_TIME Timer::GetInstance()->GetDetatime()

#define KEY_DOWN(k) InputManager::GetInstance()->Down(k)
#define KEY_UP(k) InputManager::GetInstance()->Up(k)
#define KEY_PRESS(k) InputManager::GetInstance()->Press(k)
#define MOUSE_POS		InputManager::GetInstance()->GetMousePos()

#define SAMPLER_STATE		StateManager::GetInstance()->GetSamplerState()
#define ALPHA_STATE			StateManager::GetInstance()->GetAlphaState()
#define ADDITIVE_STATE		StateManager::GetInstance()->GetAdditiveState()
#define BLEND_STATE			StateManager::GetInstance()->GetBlendState()
#define CULL_MODE_STATE		StateManager::GetInstance()->GetRasterizerState()

#define PI 3.141592

#define RED XMFLOAT4(1,0,0,1)
#define GREEN XMFLOAT4(0,1,0,1)
#define BLUE XMFLOAT4(0,0,1,1)
#define WHITE XMFLOAT4(1,1,1,1)
#define BLACK XMFLOAT4(0,0,0,1)

#define ADD_VS(k)		ShaderManager::GetInstance()->AddVS(k)
#define ADD_PS(k)		ShaderManager::GetInstance()->AddPS(k)

// 매개 변수를 보이드로 가질수있는 함수
typedef function<void()> CallBack;