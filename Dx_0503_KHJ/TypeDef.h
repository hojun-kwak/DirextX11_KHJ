#pragma once

#define WIN_WIDTH 1280
#define WIN_HEIGHT 720

#define CENTER Vector2(WIN_WIDTH * 0.5f, WIN_HEIGHT * 0.5f)

#define DEVICE Device::GetInstance()->GetDevice()
#define DEVICE_CONTEXT Device::GetInstance()->GetDeviceContext()

#define DELTA_TIME Timer::GetInstance()->GetDetatime()

#define KEY_DOWN(k) InputManager::GetInstance()->Down(k)
#define KEY_UP(k) InputManager::GetInstance()->Up(k)
#define KEY_PRESS(k) InputManager::GetInstance()->Press(k)
#define MOUSE_POS		InputManager::GetInstance()->GetMousePos()
#define MOUSE_WOLRD_POS Camera::GetInstance()->GetMouseWorldPos()

#define SAMPLER_STATE		StateManager::GetInstance()->GetSamplerState()
#define ALPHA_STATE			StateManager::GetInstance()->GetAlphaState()
#define ADDITIVE_STATE		StateManager::GetInstance()->GetAdditiveState()
#define BLEND_STATE			StateManager::GetInstance()->GetBlendState()
#define CULL_MODE_STATE		StateManager::GetInstance()->GetRasterizerState()

#define SOUND				Audio::GetInstance()

#define PI 3.141592

#define RED XMFLOAT4(1,0,0,1)
#define GREEN XMFLOAT4(0,1,0,1)
#define BLUE XMFLOAT4(0,0,1,1)
#define WHITE XMFLOAT4(1,1,1,1)
#define BLACK XMFLOAT4(0,0,0,1)

#define ADD_VS(k)		ShaderManager::GetInstance()->AddVS(k)
#define ADD_PS(k)		ShaderManager::GetInstance()->AddPS(k)

#define LERP(s,e,t) { s + (e - s) * t }
//#define LERP(s,e,t) { s * (1 - t)+ e * t }

#define MAPLE_1 L"Resource/Maple/charactorNormal.png"
#define MAPLE_TILES L"Resource/Maple/MainTile.png"
#define MAPLE_MONSTER L"Resource/Maple/Red_snail.png"

#define MAPLE_MOUSE_CURSOR L"Resource/Maple/Cursor.png"

// 매개 변수를 보이드로 가질수있는 함수
typedef function<void()> CallBack;
typedef function<void(int)> CallBackParam;

typedef function<string(string msg)> CallBackA;
