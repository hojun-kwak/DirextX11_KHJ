#pragma once
class ObjectPoolingManager
{
private:
	ObjectPoolingManager();
	~ObjectPoolingManager();
public:
	static void Create()
	{
		if (_instance == nullptr)
			_instance = new ObjectPoolingManager();
	}

	static void Delete()
	{
		if (_instance != nullptr)
			delete _instance;
	}

	static ObjectPoolingManager* GetInstance()
	{
		if (_instance != nullptr)
			// 오류 코드 작성 가능
			return _instance;

		return nullptr;
	}

	void Update();
	void Render();
	void PostRender();
	void DebugRender();

private:
	static ObjectPoolingManager* _instance;
	shared_ptr<Tiles> _tiles;
};

