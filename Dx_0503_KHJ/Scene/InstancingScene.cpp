#include "framework.h"
#include "InstancingScene.h"

InstancingScene::InstancingScene()
{
	//_quads.reserve(_poolCount);

	//for (int i = 0; i < _poolCount; i++)
	//{
	//	shared_ptr<Quad> quad = make_shared<Quad>(L"Resource/Player.png");
	//	quad->GetTransform()->GetPos() = { (float)MathUtillity::RandomInt(0,WIN_WIDTH), (float)MathUtillity::RandomInt(0,WIN_HEIGHT) };
	//	quad->GetTransform()->GetScale() *= MathUtillity::RandomFloat(0.0f, 1.0f);
	//	_quads.emplace_back(quad);
	//}

	_quad = make_shared<Quad>(L"Resource/zelda.png",
		L"Shaders/InstancingVertexShader.hlsl",
		L"Shaders/InstancingPixelShader.hlsl");


	_instancingDataes.resize(_poolCount);

	for (auto& data : _instancingDataes)
	{
		Transform transform;
		transform.GetPos() = { (float)MathUtillity::RandomInt(0,WIN_WIDTH), (float)MathUtillity::RandomInt(0,WIN_HEIGHT) };
		transform.GetScale() *= MathUtillity::RandomFloat(0.0f, 0.2f);

		transform.UpdateWorldBuffer();

		data.matrix = XMMatrixTranspose(transform.GetMatrix());

		data.maxFrame = { 10,8 };
		data.curFrame = { MathUtillity::RandomInt(0,10), MathUtillity::RandomInt(0,8) };
	}

	_instanceBuffer = make_shared<VertexBuffer>(_instancingDataes.data(), sizeof(InstanceData), _poolCount);

	SOUND->Add("BGM_1", "Resource/Sound/BGM.wav");
	SOUND->Add("ATTACK", "Resource/Sound/attack.wav");

	SOUND->Play("BGM_1");
}

InstancingScene::~InstancingScene()
{
}

void InstancingScene::Update()
{
	if (KEY_DOWN(VK_SPACE))
		SOUND->Play("ATTACK");
}

void InstancingScene::Render()
{
	_instanceBuffer->IASet(1);

	_quad->SetRender();

	DEVICE_CONTEXT->DrawIndexedInstanced(6, _poolCount, 0, 0, 0);
}
