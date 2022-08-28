#pragma once
class _2D_Tile;
class _2D_Rope;
class _2D_Monster;

class _2D_ObjPManager
{
private:
	_2D_ObjPManager();
	~_2D_ObjPManager();

public:
	static void Create()
	{
		if (_instance == nullptr)
			_instance = new _2D_ObjPManager();
	}

	static void Delete()
	{
		if (_instance != nullptr)
			delete _instance;
	}

	static _2D_ObjPManager* GetInstance()
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
	void CreateMonster();

	vector<vector<shared_ptr<_2D_Tile>>> GetTiles() { return _tiles; }
	vector<shared_ptr<_2D_Rope>> GetRopes() { return _ropes; }

private:
	static _2D_ObjPManager* _instance;

	vector<float> _tileFloor = { -360.0f, -150.0f, 60.0f };

	UINT _tileCount = 6;
	vector<vector<shared_ptr<_2D_Tile>>> _tiles;

	UINT _ropeCount = 4;
	vector<shared_ptr<_2D_Rope>> _ropes;

	shared_ptr<_2D_Monster> _mons;
	
};

