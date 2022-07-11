// Dx_0503_KHJ.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "Dx_0503_KHJ.h"

HWND hWnd;

// DirectX 11
// test
// test1
// test2~~~~~~~
// Direct Access
// 그래픽(GPU)에 직접 접근한다.
// WinApi는 픽셀에 들어가는 계산을 CPU가 계산
// => 픽셸에 빛계산등 많은 계산들이 필요한 작업을 CPU에서 해주니까 과부하

// CPU 와 GPU
// CPU : 논리연산, 산술연산 등 복잡한 연산을 하기에 좋음
// GPU : 병렬 연산, 픽셀 처리가 빠름

// DX 그래픽스
// 게임 제작 = 영화

// 외주 를 맡기고 실질적인 공사 대표(인력사무소 대표)
//Microsoft::WRL::ComPtr<ID3D11Device> device; // 컴퓨터의 하드웨어 기능 정검, 리로스 할당
//// 세트장을 실질적으로 꾸미고 보여주는 연출가
//Microsoft::WRL::ComPtr<ID3D11DeviceContext> deviceContext; // 렌더링 대상 결정, 리소스를 그래픽 파이프라인에 바인딩, GPU가 수행할 렌더링 명령 시지
//
//// 백버퍼, dx의 인터페이스로써 1개 이상의 표면을 포함할수 있다, 각각의 표면(버퍼, 텍스쳐)을 출력하기 전에 데이터를 보관
//Microsoft::WRL::ComPtr<IDXGISwapChain> swapChain;
//
//// 후면버퍼 메모리를 가리키는 포인터
//Microsoft::WRL::ComPtr<ID3D11RenderTargetView> renderTargetView;
//
//// 렌더링 파이프라인 단계
//Microsoft::WRL::ComPtr<ID3D11Buffer> vertexBuffer; // 정점보관
//Microsoft::WRL::ComPtr<ID3D11VertexShader> vertexShader; // 보관한 정점을 그리기
//Microsoft::WRL::ComPtr<ID3D11PixelShader> pixelShader; // 정점사이의 픽셀(색상)을 정해줌
//Microsoft::WRL::ComPtr<ID3D11InputLayout> inputLayout; // 버텍스 버퍼가 담고 있는 데이터가 어떤 데이터인지, 셰이더에 어떻게 넘길 것인지 같은 정보를 저장해 두는 것
//
//// view는 왠만해선 다 포인터로 생각
//Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> shaderResourceView; // 판박이
//Microsoft::WRL::ComPtr<ID3D11SamplerState> samplerState; // 매핑을 할 사람(판박이를 어떻게 붙일지)


struct Vertex
{
    XMFLOAT3 pos; // 화면의 좌표
    XMFLOAT2 uv; // 텍스쳐 좌표(그림그릴 사람이 어느만큼 그릴지 알려줄 좌표)
};

//void InitDevice();
//void Render();


#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_DX0503KHJ, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_DX0503KHJ));

    MSG msg = {};
    

    // 클래스 분할
    Device::Create(hWnd);

    ImGui::CreateContext();
    //ImGui::StyleColorsDark();
    ImGui::StyleColorsLight();
    ImGui_ImplWin32_Init(hWnd);
    ImGui_ImplDX11_Init(DEVICE.Get(), DEVICE_CONTEXT.Get());

    Timer::Create();
    InputManager::Create();
    StateManager::Create();
    ShaderManager::Create();
    EffectManager::Create();
    shared_ptr<Program> program = make_shared<Program>();
    //InitDevice();

    // 기본 메시지 루프입니다:
    while (msg.message != WM_QUIT)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
            {
                TranslateMessage(&msg); // 메시지 가공
                DispatchMessage(&msg); // 프로시저(함수)로 메시지 전달
            }
        }

        else
        {
            // Update();
            //Render();
            Timer::GetInstance()->Update();
            InputManager::GetInstance()->Update();
            program->Update();
            program->Render();
            
        }
    }

    // 삭제.
    EffectManager::Delete();
    ShaderManager::Delete();
    StateManager::Delete();
    InputManager::Delete();
    Timer::Delete();

    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    Device::Delete();
    return (int) msg.wParam;
}

//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DX0503KHJ));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_DX0503KHJ);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   RECT rc = { 0,0,WIN_WIDTH,WIN_HEIGHT };
   AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, false);

   hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
       0, 0, rc.right - rc.left, rc.bottom - rc.top, nullptr, nullptr, hInstance, nullptr);
      /*CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);*/

   SetMenu(hWnd, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    if (ImGui_ImplWin32_WndProcHandler(hWnd, message, wParam, lParam))
        return true;

    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_MOUSEMOVE:
    {
        MOUSE_POS.x = (float)LOWORD(lParam);
        MOUSE_POS.y = -((float)HIWORD(lParam) - WIN_HEIGHT * 0.5f) + WIN_HEIGHT * 0.5f;
    }
    break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

//void InitDevice()
//{
//    RECT rc;
//    GetClientRect(hWnd, &rc);
//    UINT width = rc.right - rc.left;
//    UINT height = rc.bottom - rc.top;
//
//    // 컴퓨터 환경에 맞춰 다운그레이드
//    D3D_FEATURE_LEVEL featureLevels[] =
//    {
//        D3D_FEATURE_LEVEL_11_0,
//        D3D_FEATURE_LEVEL_10_1,
//        D3D_FEATURE_LEVEL_10_0
//    };
//
//    UINT featureSize = ARRAYSIZE(featureLevels);
//
//    // swapchain 설명서
//    DXGI_SWAP_CHAIN_DESC sd = {};
//    sd.BufferCount = 1;
//    sd.BufferDesc.Width = width;
//    sd.BufferDesc.Height = height;
//    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
//    sd.BufferDesc.RefreshRate.Numerator = 60;
//    sd.BufferDesc.RefreshRate.Denominator = 1;
//    // 화면 주사율(화면프레임갱신 속도) =  Numerator/Denominator
//    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
//    sd.OutputWindow = hWnd;
//    sd.SampleDesc.Count = 1;
//    sd.SampleDesc.Quality = 0;
//    sd.Windowed = true; // 창모드 활성여부
//
//    D3D11CreateDeviceAndSwapChain(
//        nullptr,
//        D3D_DRIVER_TYPE_HARDWARE,
//        0,
//        D3D11_CREATE_DEVICE_DEBUG,
//        featureLevels,
//        featureSize,
//        D3D11_SDK_VERSION,
//        &sd,
//        &swapChain,
//        &device,
//        nullptr,
//        &deviceContext
//    );
//
//    Microsoft::WRL::ComPtr<ID3D11Texture2D> backBuffer;
//
//    swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), &backBuffer);
//    device->CreateRenderTargetView(backBuffer.Get(), nullptr, &renderTargetView);
//
//    deviceContext->OMSetRenderTargets(1, renderTargetView.GetAddressOf(), nullptr);
//
//    // 카메라 시점
//    D3D11_VIEWPORT vp;
//    vp.Width = width;
//    vp.Height = height;
//    vp.MinDepth = 0.0f;
//    vp.MaxDepth = 1.0f;
//    vp.TopLeftX = 0;
//    vp.TopLeftY = 0;
//    deviceContext->RSSetViewports(1, &vp);
//
//    DWORD flags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG;
//
//    // vertextShader로 만들 도구
//    Microsoft::WRL::ComPtr<ID3DBlob> vertexBlob;
//    D3DCompileFromFile(L"Shaders/TutorialShader.hlsl", nullptr, nullptr, "VS", "vs_5_0", flags, 0, &vertexBlob, nullptr);
//
//    D3D11_INPUT_ELEMENT_DESC layout[] =
//    {
//        {
//            "POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT, 0,0, D3D11_INPUT_PER_VERTEX_DATA,0
//        },
//        {
//            // 위에있는거 보다 12칸 뒤에있다.
//            "UV",0,DXGI_FORMAT_R32G32_FLOAT, 0,12, D3D11_INPUT_PER_VERTEX_DATA,0
//        }
//    };
//
//    UINT layoutSize = ARRAYSIZE(layout);
//
//    // Shader 정보 전달
//    device->CreateInputLayout(layout, layoutSize, vertexBlob->GetBufferPointer(), vertexBlob->GetBufferSize(), inputLayout.GetAddressOf());
//
//    device->CreateVertexShader(vertexBlob->GetBufferPointer(), vertexBlob->GetBufferSize(), nullptr, &vertexShader);
//
//    // pixelShader로 만들 도구
//    Microsoft::WRL::ComPtr<ID3D10Blob> pixelBlob;
//    D3DCompileFromFile(L"Shaders/TutorialShader.hlsl", nullptr, nullptr, "PS", "ps_5_0", flags, 0, &pixelBlob, nullptr);
//
//    device->CreatePixelShader(pixelBlob->GetBufferPointer(), pixelBlob->GetBufferSize(), nullptr, &pixelShader);
//
//    // 도형 위치 설정
//    vector<Vertex> vertices;
//    {
//        Vertex v;
//
//        // 왼쪽 위
//        v.pos = XMFLOAT3(-0.5f, 0.5f, 0.0f);
//        v.uv = { 0.0f,0.0f };
//        vertices.push_back(v);
//
//        // 오른쪽 아래
//        v.pos = { XMFLOAT3(0.5f,-0.5f,0.0f) };
//        v.uv = { 1.0f,1.0f };
//        vertices.push_back(v);
//
//        // 왼쪽 아래
//        v.pos = { XMFLOAT3(-0.5f,-0.5f,0.0f) };
//        v.uv = { 0.0f,1.0f };
//        vertices.push_back(v);
//
//        // 왼쪽 위
//        v.pos = { XMFLOAT3(-0.5f,0.5f,0.0f) };
//        v.uv = { 0.0f,0.0f };
//        vertices.push_back(v);
//
//        // 오른쪽 위
//        v.pos = { XMFLOAT3(0.5f,0.5f,0.0f) };
//        v.uv = { 1.0f,0.0f };
//        vertices.push_back(v);
//
//        // 오른쪽 아래
//        v.pos = { XMFLOAT3(0.5f,-0.5f,0.0f) };
//        v.uv = { 1.0f,1.0f };
//        vertices.push_back(v);
//    }
//
//
//    // 실제 vertex를 넘겨줄곳
//    D3D11_BUFFER_DESC bd = {};
//    bd.Usage = D3D11_USAGE_DEFAULT;
//    bd.ByteWidth = sizeof(Vertex) * vertices.size();
//    bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
//
//    D3D11_SUBRESOURCE_DATA initData = {};
//    initData.pSysMem = vertices.data();
//
//    // 정점 정보들을 담는 정점 버퍼 생성
//    device->CreateBuffer(&bd, &initData, vertexBuffer.GetAddressOf());
//
//    // 판박이 만들기(텍스쳐 로드)
//    ScratchImage image;
//    LoadFromWICFile(L"Resource/VRising.png", WIC_FLAGS_NONE, nullptr, image);
//    CreateShaderResourceView(device.Get(), image.GetImages(), image.GetImageCount(), image.GetMetadata(), shaderResourceView.GetAddressOf());
//
//    D3D11_SAMPLER_DESC sampDesc = {};
//    sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
//    sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
//    sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
//    sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
//    sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
//    sampDesc.MinLOD = 0;
//    sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
//
//    device->CreateSamplerState(&sampDesc, samplerState.GetAddressOf());
//}

//void Render()
//{
//    FLOAT myColorR = 184.0f / 255.0f;
//    FLOAT myColorG = 248.0f / 255.0f;
//    FLOAT myColorB = 251.0f / 255.0f;
//    FLOAT clearColor[4] = { myColorR,myColorG,myColorB,1.0f };
//
//    deviceContext->ClearRenderTargetView(renderTargetView.Get(), clearColor);
//    // 한칸씩 vertex를 넣어준다.
//    UINT stride = sizeof(Vertex);
//    UINT offset = 0;
//
//    // 감독에게 정보 넘기고
//    deviceContext->IASetInputLayout(inputLayout.Get());
//
//
//
//    deviceContext->IASetVertexBuffers(0, 1, vertexBuffer.GetAddressOf(), &stride, &offset);
//    // 어떤 모양으로 그릴지
//    deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
//
//    // 이미지를 넣기 위해 deviceContext에게 일을 시킴
//    deviceContext->PSSetShaderResources(0, 1, shaderResourceView.GetAddressOf());
//    deviceContext->PSSetSamplers(0, 1, samplerState.GetAddressOf());
//
//    // shader
//    deviceContext->VSSetShader(vertexShader.Get(), nullptr, 0);
//    deviceContext->PSSetShader(pixelShader.Get(), nullptr, 0);
//
//    deviceContext->Draw(6, 0);
//    swapChain->Present(0,0);
//
//}
