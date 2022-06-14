#include "framework.h"
#include "SRV.h"

SRV::SRV(wstring file)
{
    ScratchImage image;
    LoadFromWICFile(file.data(), WIC_FLAGS_NONE, nullptr, image);

    CreateShaderResourceView(DEVICE.Get(), image.GetImages(), image.GetImageCount(), image.GetMetadata(),
        _shaderResourceView.GetAddressOf());
}

SRV::~SRV()
{
}

void SRV::PsSet(int slot)
{
    DEVICE_CONTEXT->PSSetShaderResources(slot, 1, _shaderResourceView.GetAddressOf());
}
