﻿// header.h: 표준 시스템 포함 파일
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
#include <unordered_map>
#include <map>
#include <algorithm>
#include <wrl.h>
#include <string>
#include <memory>
#include <functional>
#include <time.h>

#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>

#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"d3dcompiler.lib")
#pragma comment(lib,"dxguid.lib")

using namespace DirectX;
using namespace std;

// 정적 라이브러리 DirectX Tex
#include "../DirectXTex/DirectXTex.h"

// DirectWrite
#include <d2d1_1.h>
#include <dwrite.h>

#pragma comment(lib,"d2d1.lib")
#pragma comment(lib, "dwrite.lib")

// ImGui
#include "../ImGui/imgui.h"
#include "../ImGui/imgui_impl_dx11.h"
#include "../ImGui/imgui_impl_win32.h"

#include "Libary/FMOD/inc/fmod.hpp"
#pragma comment(lib,"Libary/FMOD/fmod_vc.lib")

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
#include "Framework/Render/Shader.h"
#include "Framework/Render/VertexShader.h"
#include "Framework/Render/PixelShader.h"
#include "Framework/Render/ShaderManager.h"
#include "Framework/Render/RenderTarget.h"

// Component
#include "Framework/Component/Transform.h"

// Utillity
#include "Framework/Utillity/InputManager.h"
#include "Framework/Utillity/Timer.h"
#include "Framework/Utillity/Utillity.h"
#include "Framework/Utillity/BinaryWriter.h"
#include "Framework/Utillity/BinaryReader.h"
#include "Framework/Utillity/DirectWrite.h"
#include "Framework/Utillity/tinyxml2.h"
#include "Framework/Utillity/MathUtillity.h"
#include "Framework/Utillity/Audio.h"

// Camera
#include "Framework/Camera/Camera.h"

// Collider
#include "Framework/Collider/Collider.h"
#include "Framework/Collider/RectCollider.h"
#include "Framework/Collider/CircleCollider.h"

// Texture
#include "Framework/Texture/SRV.h"
#include "Framework/Texture/SamplerState.h"
#include "Framework/Texture/BlendState.h"
#include "Framework/Texture/RasterizerState.h"
#include "Framework/Texture/StateManager.h"
#include "Framework/Texture/Texture.h"

// Animation
#include "Framework/Animation/Action.h"

// Bagic
#include "Object/BagicObj/Quad.h"
#include "Object/BagicObj/Sprite.h"
#include "Object/BagicObj/Effect.h"
#include "Object/BagicObj/EffectManager.h"

// UI
#include "Object/UI/Button.h"
#include "Object/UI/MiniMap.h"
#include "Object/UI/ItemIcon.h"
#include "Object/UI/Inventory.h"

// Dungreed
#include "Object/Dungreed/Player.h"
#include "Object/Dungreed/Gun.h"
#include "Object/Dungreed/Bullet.h"
#include "Object/Dungreed/Aim.h"
#include "Object/Dungreed/Monster.h"
#include "Object/Zelda/Zelda.h"
#include "Object/Zelda/ItemDataes.h"

// 2D_PortFolio
#include "Object/2D_PortFolio/_2D_ObjPManager.h"
#include "Object/2D_PortFolio/_2D_Cursor.h"
#include "Object/2D_PortFolio/_2D_Player.h"
#include "Object/2D_PortFolio/_2D_Tile.h"
#include "Object/2D_PortFolio/_2D_Rope.h"
#include "Object/2D_PortFolio/_2D_Monster.h"

// Maple
#include "Object/Maple/MPlayer.h"
#include "Object/Maple/Tiles.h"
#include "Object/Maple/Cursors.h"
#include "Object/Maple/Monsters.h"
#include "Object/Maple/Rope.h"
#include "Object/Maple/ObjectPoolingManager.h"

// Scene
#include "Scene/Scene.h"
#include "Scene/SceneManager.h"

// Program
#include "Program/Program.h"



