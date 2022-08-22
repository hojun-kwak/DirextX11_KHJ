#include "framework.h"
#include "ItemIcon.h"

ItemIcon::ItemIcon()
{
	_itemAtlas = make_shared<Quad>(L"Resource/item.png",
		L"Shaders/InstancingVertexShader.hlsl",
		L"Shaders/InstancingPixelShader.hlsl");

	SetItemIconTable();

	_instanceBuffer = make_shared<VertexBuffer>(_instancingDataes.data(), sizeof(InstanceData), _poolCount);
}

ItemIcon::~ItemIcon()
{
}

void ItemIcon::Render()
{
	_instanceBuffer->IASet(1);

	_itemAtlas->SetRender();

	DEVICE_CONTEXT->DrawIndexedInstanced(6, _poolCount, 0, 0, 0);
}

void ItemIcon::SetIcon(string name, Vector2 pos)
{
	for (auto& data : _iconTable[name])
	{
		if (data.isActive == false)
		{
			data.isActive = true;
			data.transform->GetPos() = pos;
			data.transform->UpdateWorldBuffer();
			data.data->matrix = XMMatrixTranspose(data.transform->GetMatrix());
			break;
		}
	}
}

void ItemIcon::SetItemIconTable()
{
	_instancingDataes.resize(_poolCount);

	for (int i = 0; i < _poolCount; i++)
	{
		int temp = i / 10;
		IconData data;
		shared_ptr<Transform> t = make_shared<Transform>();
		t->GetPos().x = -3000.0f;
		t->GetScale().x /= 11.0f;
		t->GetScale().y /= 5.0f;
		t->UpdateWorldBuffer();
		_instancingDataes[i].matrix = XMMatrixTranspose(t->GetMatrix());

		data.isActive = false;
		data.data = make_shared<InstanceData>(_instancingDataes[i]);
		data.transform = t;

		switch (temp)
		{
		case 0:
		{
			_instancingDataes[i].curFrame = { 0,0 };

			data.name = "Sword";
			_iconTable["Sword"].push_back(data);
		}
		break;
		case 1:
		{
			_instancingDataes[i].curFrame = { 1,0 };

			data.name = "Armor";
			_iconTable["Armor"].push_back(data);
		}
		break;
		case 2:
		{
			_instancingDataes[i].curFrame = { 2,0 };
			data.name = "Shose";
			_iconTable["Shose"].push_back(data);
		}
		break;
		case 3:
		{
			_instancingDataes[i].curFrame = { 3,0 };
			data.name = "Lamp";
			_iconTable["Lamp"].push_back(data);
		}
		break;
		case 4:
		{
			_instancingDataes[i].curFrame = { 4,0 };
			data.name = "Potion";
			_iconTable["Potion"].push_back(data);
		}
		break;
		default:
			break;
		}
		_instancingDataes[i].maxFrame = { 11, 5 };
	}
}
