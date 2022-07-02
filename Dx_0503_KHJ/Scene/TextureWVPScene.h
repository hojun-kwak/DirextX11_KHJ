#pragma once
class TextureWVPScene : public Scene
{
public:
	TextureWVPScene();
	virtual ~TextureWVPScene();

	// Scene을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render() override;

private:
	shared_ptr<Quad> _quad;

	shared_ptr<MatrixBuffer> _worldBuffer;
	XMFLOAT2 _worldPos = { 0.0f, 0.0f };

	shared_ptr<MatrixBuffer> _viewBuffer;
	XMFLOAT2 _cameraPos = { 0.0f, 0.0f };
	float _angle = 0.0f;

	shared_ptr<MatrixBuffer> _projectionBuffer;
};

