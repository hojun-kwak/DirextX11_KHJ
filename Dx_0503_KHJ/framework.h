// header.h: 표준 시스템 포함 파일
// 또는 프로젝트 특정 포함 파일이 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
// Windows 헤더 파일
#include <windows.h>
// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <vector>
#include <map>
#include <algorithm>
#include <wrl.h>
#include <string>
#include <memory>


#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>

#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"d3dcompiler.lib")

using namespace DirectX;
using namespace std;

// 정적 라이브러리 DirectX Tex
#include "../DirectXTex/DirectXTex.h"

// ImGui
#include "../ImGui/imgui.h"
#include "../ImGui/imgui_impl_dx11.h"
#include "../ImGui/imgui_impl_win32.h"

// Types
#include "TypeDef.h"

// Device
#include "Framework/Device/Device.h"

// Math
#include "Framework/Math/Vector2.h"

// Render
#include "Framework/Render/VertexLayOuts.h"
#include "Framework/Render/ConstantBuffer.h"
#include "Framework/Render/GlobalBuffer.h"
#include "Framework/Render/IndexBuffer.h"
#include "Framework/Render/VertexBuffer.h"
#include "Framework/Render/VertexShader.h"
#include "Framework/Render/PixelShader.h"

// Utillity
#include "Framework/Utillity/InputManager.h"
#include "Framework/Utillity/Timer.h"

// Texture
#include "Framework/Texture/SRV.h"
#include "Framework/Texture/SamplerState.h"
#include "Framework/Texture/BlendState.h"
#include "Framework/Texture/RasterizerState.h"
#include "Framework/Texture/StateManager.h"

// Component
#include "Framework/Component/Transform.h"

// Collider
#include "Framework/Collider/Collider.h"
#include "Framework/Collider/RectCollider.h"
#include "Framework/Collider/CircleCollider.h"

// Obj
#include "Object/Texture.h"

// Dungreed
#include "Object/Dungreed/Player.h"
#include "Object/Dungreed/Gun.h"
#include "Object/Dungreed/Bullet.h"
#include "Object/Dungreed/Aim.h"

// Scene
#include "Scene/Scene.h"

// Program
#include "Program/Program.h"



