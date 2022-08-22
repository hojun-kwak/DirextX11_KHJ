#include "framework.h"
#include "SceneManager.h"

#include "../Scene/BagicScene/TextureScene.h"
#include "../Scene/BagicScene/TextureWVPScene.h"
#include "../Scene/BagicScene/SolaSystemScene.h"
#include "../Scene/BagicScene/DungridScene.h"
#include "../Scene/BagicScene/ColliderScene.h"
#include "../Scene/BagicScene/ZeldaScene.h"
#include "../Scene/BagicScene/FilterScene.h"
#include "../Scene/BagicScene/EffectScene.h"
#include "../Scene/BagicScene/CameraScene.h"
#include "../Scene/BagicScene/XmlLoadScene.h"
#include "../Scene/BagicScene/InstancingScene.h"
#include "../Scene/BagicScene/InventoryScene.h"

#include "../Scene/2D_PortFolio/MapleScene.h"

SceneManager* SceneManager::_instance = nullptr;

SceneManager::SceneManager()
{
	/*_sceneTable["DunGreed"] = make_shared<DunGridScene>();
	_sceneTable["Zelda"] = make_shared<ZeldaScene>();
	_sceneTable["Texture"] = make_shared<TextureScene>();*/
	//_sceneTable["InstancingScene"] = make_shared<InstancingScene>();
	_sceneTable["Inventory"] = make_shared<InventoryScene>();

	_curScene = _sceneTable["Inventory"];
	assert(!_curScene.expired());
}

SceneManager::~SceneManager()
{
}

void SceneManager::Update()
{
	assert(!_curScene.expired());
		_curScene.lock()->Update();
}

void SceneManager::Render()
{
	assert(!_curScene.expired());
		_curScene.lock()->Render();
}

void SceneManager::PreRender()
{
	assert(!_curScene.expired());
		_curScene.lock()->PreRender();
}

void SceneManager::PostRender()
{
	assert(!_curScene.expired());
		_curScene.lock()->PostRender();
}

void SceneManager::SetScene(string name)
{
	if (_sceneTable.count(name) == 0)
		return;

	_curScene = _sceneTable[name];
	_curScene.lock()->Init();
}

