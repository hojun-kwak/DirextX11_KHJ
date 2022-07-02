#pragma once
class TextureScene : public Scene
{
public:
    TextureScene();
    virtual ~TextureScene();

    // Scene을(를) 통해 상속됨
    virtual void Update() override;
    virtual void Render() override;

private:
    // 사각형에 텍스쳐 맵핑하는데 필요한 것들
    // 1. inputLayOut
    // 2. VertexBuffer
    // 3. 그리는 방법(Primitive Topology)
    // 4. SRV
    // 5. Sampler
    // 6. VS
    // 7. PS

    /*shared_ptr<VertexShader>    _vertexShader;
    shared_ptr<PixelShader>     _pixelShader;

    shared_ptr<VertexBuffer>    _vertexBuffer;
    shared_ptr<SRV>             _srv;
    shared_ptr<SamplerState>    _sampler;*/

    shared_ptr<Quad> _quad;
    
};

