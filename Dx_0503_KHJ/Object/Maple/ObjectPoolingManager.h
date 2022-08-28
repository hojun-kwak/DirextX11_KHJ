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

	void CreateTiles();
	void CreateRopes();

	vector<vector<shared_ptr<Tiles>>> GetTiles() { return _tiles; }
	vector<shared_ptr<Rope>> GetRopes() { return _ropes; }

private:
	static ObjectPoolingManager* _instance;

	
	UINT _tileCount = 6;

	vector<shared_ptr<Tiles>> _1floorTiles;
	vector<shared_ptr<Tiles>> _2floorTiles;
	vector<shared_ptr<Tiles>> _3floorTiles;

	vector<vector<shared_ptr<Tiles>>> _tiles;
	
	UINT _ropeCount = 4;
	vector<shared_ptr<Rope>> _ropes;
};

