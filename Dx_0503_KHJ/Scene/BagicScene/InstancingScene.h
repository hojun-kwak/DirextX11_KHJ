#pragma once
class InstancingScene : public Scene
{
public:
	struct InstanceData
	{
		XMMATRIX matrix;
		Vector2 curFrame;
		Vector2 maxFrame;
	};

	InstancingScene();
	virtual ~InstancingScene();

	virtual void Update() override;
	virtual void Render() override;

private:
	shared_ptr<Quad> _quad;

	vector<InstanceData> _instancingDataes;
	shared_ptr<VertexBuffer> _instanceBuffer;
	shared_ptr<Transform> _transform;

	UINT _poolCount = 50;
};

