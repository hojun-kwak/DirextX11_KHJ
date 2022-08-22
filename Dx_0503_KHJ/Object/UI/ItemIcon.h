#pragma once
class ItemIcon
{
public:
	struct InstanceData
	{
		XMMATRIX matrix;
		Vector2 curFrame;
		Vector2 maxFrame;
	};

	struct IconData
	{
		bool isActive;
		string name;
		shared_ptr<InstanceData> data;
		shared_ptr<Transform> transform;
	};

	ItemIcon();
	~ItemIcon();

	void Render();

	void SetIcon(string name, Vector2 pos);

private:
	void SetItemIconTable();

	shared_ptr<Quad> _itemAtlas;
	unordered_map<string, vector<IconData>> _iconTable;

	vector<InstanceData> _instancingDataes;
	vector<shared_ptr<Transform>> _dataTransform;
	shared_ptr<VertexBuffer> _instanceBuffer;

	UINT _poolCount = 50;
};

