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

	void CreateData();

	vector<shared_ptr<Tiles>> GetTiles() { return _tiles; }

	vector<vector<shared_ptr<Tiles>>> GetTile() { return _test; }

private:
	static ObjectPoolingManager* _instance;

	UINT _floor = 2;
	UINT _tileCount = 6;

	vector<shared_ptr<Tiles>> _tiles;

	vector<shared_ptr<Tiles>> _1floorTiles;
	vector<shared_ptr<Tiles>> _2floorTiles;
	vector<shared_ptr<Tiles>> _3floorTiles;

	// 전체 순회라 map은 무리
	unordered_map < string, vector<shared_ptr<Tiles>>> _tile;
	// 2중벡터 끼워 넣기 나중에 해보자 우선 지금은 노가다로
	vector<vector<shared_ptr<Tiles>>> _test;


};

