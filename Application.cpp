#include "Application.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

bool Application::HandleInput(float deltaTime)
{
	//Escape to Quit
	if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
	{
		PostMessage(_hWnd, WM_DESTROY, 0, 0);
		return false;
	}

	DIMOUSESTATE mouseCurrState;
	DIMouse->Acquire();
	DIMouse->GetDeviceState(sizeof(DIMOUSESTATE), &mouseCurrState);


	//Mouse Input
	if (mouseCurrState.lX != mouseLastState.lX)
		_camera->Yaw(mouseCurrState.lX *_cameraLookSpeed*0.1);
	if (mouseCurrState.lY != mouseLastState.lY)
		_camera->Pitch(mouseCurrState.lY * _cameraLookSpeed*0.1);

	//Control Camera
	if (GetAsyncKeyState('W') & 0x8000)
		_camera->Walk(_cameraWalkSpeed*deltaTime);
	if (GetAsyncKeyState('S') & 0x8000)
		_camera->Walk(-_cameraWalkSpeed*deltaTime);
	if (GetAsyncKeyState('A') & 0x8000)
		_camera->Strafe(-_cameraWalkSpeed*deltaTime);
	if (GetAsyncKeyState('D') & 0x8000)
		_camera->Strafe(_cameraWalkSpeed*deltaTime);
	if (GetAsyncKeyState('E') & 0x8000)
		_camera->Raise(_cameraWalkSpeed*deltaTime);
	if (GetAsyncKeyState('Q') & 0x8000)
		_camera->Raise(-_cameraWalkSpeed*deltaTime);

	mouseLastState = mouseCurrState;

	return false;
}

ID3D11RasterizerState * Application::ViewMode()
{
	//Switch View mode with F1 and F2
	if (GetAsyncKeyState(VK_F1) & 0x8000)//F1
	{
		_pCurrentState = RSWireFrame;
	}
	else if (GetAsyncKeyState(VK_F2) & 0x8000)//F2
	{
		_pCurrentState = RSCull;
	}
	else if (GetAsyncKeyState(VK_F3) & 0x8000)//F3
	{
		_pCurrentState = RSCullNone;
	}

	return(_pCurrentState);
}

Application::Application()
{
	_hInst = nullptr;
	_hWnd = nullptr;
	_driverType = D3D_DRIVER_TYPE_NULL;
	_featureLevel = D3D_FEATURE_LEVEL_11_0;
	_pd3dDevice = nullptr;
	_pImmediateContext = nullptr;
	_pSwapChain = nullptr;
	_pRenderTargetView = nullptr;
	_pVertexShader = nullptr;
	_pPixelShader = nullptr;
	_pVertexLayout = nullptr;
	_pConstantBuffer = nullptr;

	DSLessEqual = nullptr;
	RSCullNone = nullptr;
	RSCull = nullptr;
	RSWireFrame = nullptr;
}

Application::~Application()
{
	Cleanup();
}

HRESULT Application::Initialise(HINSTANCE hInstance, int nCmdShow)
{
	if (FAILED(InitWindow(hInstance, nCmdShow)))
	{
		return E_FAIL;
	}

	RECT rc;
	GetClientRect(_hWnd, &rc);
	_WindowWidth = rc.right - rc.left;
	_WindowHeight = rc.bottom - rc.top;

	if (FAILED(InitDevice()))
	{
		Cleanup();

		return E_FAIL;
	}

	if (FAILED(InitDirectInput(hInstance)))
	{
		MessageBox(0, L"Direct Input Inititalization - Failed", L"Error", MB_OK);
		return E_FAIL;
	}

	CreateDDSTextureFromFile(_pd3dDevice, L"Resources\\Stone_Diffuse.dds", nullptr, &_pStoneDiffuseTextureRV);
	CreateDDSTextureFromFile(_pd3dDevice, L"Resources\\Stone_Specular.dds", nullptr, &_pStoneSpecularTextureRV);
	CreateDDSTextureFromFile(_pd3dDevice, L"Resources\\Stone_AO.dds", nullptr, &_pStoneAOTextureRV);
	CreateDDSTextureFromFile(_pd3dDevice, L"Resources\\Stone_Normal.dds", nullptr, &_pStoneNormalTextureRV);
	CreateDDSTextureFromFile(_pd3dDevice, L"Resources\\Floor_Diffuse.dds", nullptr, &_pGroundDiffuseTextureRV);
	CreateDDSTextureFromFile(_pd3dDevice, L"Resources\\Floor_Specular.dds", nullptr, &_pGroundSpecularTextureRV);
	CreateDDSTextureFromFile(_pd3dDevice, L"Resources\\Floor_AO.dds", nullptr, &_pGroundAOTextureRV);
	CreateDDSTextureFromFile(_pd3dDevice, L"Resources\\Floor_Normal.dds", nullptr, &_pGroundAOTextureRV);
	CreateDDSTextureFromFile(_pd3dDevice, L"Resources\\Ball_Diffuse.dds", nullptr, &_pBallDiffuseTextureRV);
	CreateDDSTextureFromFile(_pd3dDevice, L"Resources\\Ball_Specular.dds", nullptr, &_pBallSpecularTextureRV);
	CreateDDSTextureFromFile(_pd3dDevice, L"Resources\\Ball_AO.dds", nullptr, &_pBallAOTextureRV);
	CreateDDSTextureFromFile(_pd3dDevice, L"Resources\\Ball_Normal.dds", nullptr, &_pBallAOTextureRV);
	CreateDDSTextureFromFile(_pd3dDevice, L"Resources\\Car_Diffuse.dds", nullptr, &_pCarDiffuseTextureRV);
	CreateDDSTextureFromFile(_pd3dDevice, L"Resources\\Car_Specular.dds", nullptr, &_pCarSpecularTextureRV);

	// Setup Camera
	Vector3D eye = { 0.0f, 4.0f,-4.0f };
	Vector3D at = { 0.0f, 0.0f, 0.0f };
	Vector3D up = { 0.0f, 1.0f, 0.0f };

	_StaticCamera.Initialise(eye, at, up, XM_PIDIV2, (float)_renderWidth, (float)_renderHeight, 0.01f, 10000.0f);
	_OrbitCamera.Initialise(eye, at, up, XM_PIDIV2, (float)_renderWidth, (float)_renderHeight, 0.01f, 10000.0f);
	_OrbitCamera.SetDistance(3.0f);
	_FreeLookCamera.Initialise(eye, at, up, XM_PIDIV2, (float)_renderWidth, (float)_renderHeight, 0.01f, 10000.0f);
	_camera = &_FreeLookCamera;
	//_camera = &_OrbitCamera;

	// Setup the scene's light
	basicLight.AmbientLight = XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);
	basicLight.DiffuseLight = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	basicLight.SpecularLight = XMFLOAT4(0.8f, 0.8f, 0.8f, 1.0f);
	basicLight.SpecularPower = 20.0f;
	basicLight.LightVecW = XMFLOAT3(0.0f, 1.0f, -1.0f);

	//Setup the geometery
	MeshData cubeGeometry = GeometryGenerator::CreateCube(1.0f, 1.0f, 1.0f, _pd3dDevice);
	MeshData sphereGeometry = GeometryGenerator::CreateSphere(1.0f, 200, 100, _pd3dDevice);

	MeshData planeGeometry = GeometryGenerator::CreateGrid(25.0f, 25.0f, 10, 10, 4.0f, 4.0f, _pd3dDevice);

	MeshData ballGeometry = OBJLoader::Load("Resources\\Ball.obj", _pd3dDevice, true);
	MeshData carGeometry = OBJLoader::Load("Resources\\Car.obj", _pd3dDevice, true);

	//Setup the materials
	Material shinyMaterial;
	shinyMaterial.ambient = XMFLOAT4(0.3f, 0.3f, 0.3f, 1.0f);
	shinyMaterial.diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	shinyMaterial.specular = XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);
	shinyMaterial.specularPower = 10.0f;

	Material noSpecMaterial;
	noSpecMaterial.ambient = XMFLOAT4(0.1f, 0.1f, 0.1f, 1.0f);
	noSpecMaterial.diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	noSpecMaterial.specular = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);
	noSpecMaterial.specularPower = 0.0f;

	//Setup Physics Materials
	PhysicsMaterial bounceyBall;
	bounceyBall.elasticity = 0.8;
	bounceyBall.friction = 0.8;
	bounceyBall.inertiaTensor = {
		4.0f, 0.0f, 0.0f,
		0.0f, 4.0f, 0.0f,
		0.0f, 0.0f, 4.0f
	};

	//create the Game objects
	Appearance* appearance = new Appearance(planeGeometry, noSpecMaterial, _pGroundDiffuseTextureRV, _pGroundSpecularTextureRV, _pGroundAOTextureRV);
	Transform * transform = new Transform({ 0.0f, 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f });
	ParticleModel* physicsModel = new ParticleModel(0.0f, { 0.0f, 0.0f, 0.0f }, transform);
	physicsModel->SetPhysicsMaterial(bounceyBall);
	Collider* collider = new AABB(transform, 25.0f, 0.0f, 25.0f);

	GameObject * gameObject = new GameObject("Floor", appearance, transform, nullptr, collider);
	_gameObjects.push_back(gameObject);

	appearance = new Appearance(carGeometry, shinyMaterial, _pCarDiffuseTextureRV, _pCarSpecularTextureRV, _pBallAOTextureRV);
	transform = new Transform({ 0.0f, 1.0f, -10.0f }, { 0.0f, 0.0f, 0.0f }, { 0.01f, 0.01f, 0.01f });
	physicsModel = new RigidBody(100.0f, { 0.0f, 0.0f,0.0f }, transform, { 0.0f, 1.0f, 0.0f }, 0.0f);
	physicsModel->SetPhysicsMaterial(bounceyBall);
	//collider = new AABB(transform, 0.5f, 1.0f, 2.0f);
	collider = new Sphere(1.0f, transform);

	gameObject = new Car("Car", appearance, transform, physicsModel, collider);
	_gameObjects.push_back(gameObject);

	for (int i = 0; i < 5; i++)
	{
		appearance = new Appearance(ballGeometry, shinyMaterial, _pBallDiffuseTextureRV, _pBallSpecularTextureRV, _pBallAOTextureRV);
		transform = new Transform({ -5.0f + (i * 2.5f), 1.0f, 1.0f }, { 1.0f, 0.0f, 0.0f, 0.0f }, { 0.01f, 0.01f, 0.01f });
		physicsModel = new RigidBody(10.0f, { 0.0f, 0.0f, 0.0f }, transform, { 0.0f, 1.0f, 0.0f }, 0.0001f);
		physicsModel->SetPhysicsMaterial(bounceyBall);
		collider = new Sphere(1.0f, transform);

		gameObject = new GameObject("Ball " + std::to_string(i), appearance, transform, physicsModel, collider);

		_gameObjects.push_back(gameObject);
	}


	appearance = new Appearance(cubeGeometry, shinyMaterial, _pStoneDiffuseTextureRV, _pStoneSpecularTextureRV, _pStoneAOTextureRV);
	_particleSystem = new ParticleSystem(appearance, 10.0f);

	_SkySphere = new SkySphere(_pd3dDevice, L"Resources\\grasscube1024.dds");

	return S_OK;
}

HRESULT Application::InitShadersAndInputLayout()
{
    // Compile the vertex shader
    ID3DBlob* pVSBlob = nullptr;
    hr = CompileShaderFromFile(L"DX11 Framework.fx", "VS", "vs_4_0", &pVSBlob);

    if (FAILED(hr))
    {
        MessageBox(nullptr,
                   L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK);
        return hr;
    }

	// Create the vertex shader
	hr = _pd3dDevice->CreateVertexShader(pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), nullptr, &_pVertexShader);

	if (FAILED(hr))
	{	
		pVSBlob->Release();
        return hr;
	}

	// Compile the pixel shader
	ID3DBlob* pPSBlob = nullptr;
    hr = CompileShaderFromFile(L"DX11 Framework.fx", "PS", "ps_4_0", &pPSBlob);

    if (FAILED(hr))
    {
        MessageBox(nullptr,
                   L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK);
        return hr;
    }

	// Create the pixel shader
	hr = _pd3dDevice->CreatePixelShader(pPSBlob->GetBufferPointer(), pPSBlob->GetBufferSize(), nullptr, &_pPixelShader);
	pPSBlob->Release();

    if (FAILED(hr))
        return hr;
	
    // Define the input layout
    D3D11_INPUT_ELEMENT_DESC layout[] =
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	UINT numElements = ARRAYSIZE(layout);

    // Create the input layout
	hr = _pd3dDevice->CreateInputLayout(layout, numElements, pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), &_pVertexLayout);

	pVSBlob->Release();

	if (FAILED(hr))
        return hr;

    // Set the input layout
    _pImmediateContext->IASetInputLayout(_pVertexLayout);

	D3D11_SAMPLER_DESC sampDesc;
	ZeroMemory(&sampDesc, sizeof(sampDesc));
	sampDesc.Filter = D3D11_FILTER_ANISOTROPIC;
	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sampDesc.MinLOD = 0;
	sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
	hr = _pd3dDevice->CreateSamplerState(&sampDesc, &_pSamplerLinear);

	return hr;
}

HRESULT Application::InitDirectInput(HINSTANCE hInstance)
{
	hr = DirectInput8Create(hInstance,
		DIRECTINPUT_VERSION,
		IID_IDirectInput8,
		(void**)&DirectInput,
		NULL);

	hr = DirectInput->CreateDevice(GUID_SysMouse, &DIMouse, NULL);

	hr = DIMouse->SetDataFormat(&c_dfDIMouse);
	hr = DIMouse->SetCooperativeLevel(_hWnd, DISCL_EXCLUSIVE | DISCL_NOWINKEY | DISCL_FOREGROUND);

	return hr;
}

HRESULT Application::InitWindow(HINSTANCE hInstance, int nCmdShow)
{
    // Register class
    WNDCLASSEX wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, (LPCTSTR)IDI_TUTORIAL1);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW );
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = nullptr;
    wcex.lpszClassName = L"TutorialWindowClass";
    wcex.hIconSm = LoadIcon(wcex.hInstance, (LPCTSTR)IDI_TUTORIAL1);
    if (!RegisterClassEx(&wcex))
        return E_FAIL;

    // Create window
    _hInst = hInstance;
    RECT rc = {0, 0, 960, 540};
    AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
    _hWnd = CreateWindow(L"TutorialWindowClass", L"FGGC Semester 2 Framework, J005627b", WS_OVERLAPPEDWINDOW,
                         CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top, nullptr, nullptr, hInstance,
                         nullptr);
    if (!_hWnd)
		return E_FAIL;

    ShowWindow(_hWnd, nCmdShow);

    return S_OK;
}

HRESULT Application::CompileShaderFromFile(WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut)
{
    hr = S_OK;

    DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined(DEBUG) || defined(_DEBUG)
    // Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
    // Setting this flag improves the shader debugging experience, but still allows 
    // the shaders to be optimized and to run exactly the way they will run in 
    // the release configuration of this program.
    dwShaderFlags |= D3DCOMPILE_DEBUG;
#endif

    ID3DBlob* pErrorBlob;
    hr = D3DCompileFromFile(szFileName, nullptr, nullptr, szEntryPoint, szShaderModel, 
        dwShaderFlags, 0, ppBlobOut, &pErrorBlob);

    if (FAILED(hr))
    {
        if (pErrorBlob != nullptr)
            OutputDebugStringA((char*)pErrorBlob->GetBufferPointer());

        if (pErrorBlob) pErrorBlob->Release();

        return hr;
    }

    if (pErrorBlob) pErrorBlob->Release();

    return S_OK;
}

HRESULT Application::InitDevice()
{
    hr = S_OK;

    UINT createDeviceFlags = 0;

#ifdef _DEBUG
    createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

    D3D_DRIVER_TYPE driverTypes[] =
    {
        D3D_DRIVER_TYPE_HARDWARE,
        D3D_DRIVER_TYPE_WARP,
        D3D_DRIVER_TYPE_REFERENCE,
    };

    UINT numDriverTypes = ARRAYSIZE(driverTypes);

    D3D_FEATURE_LEVEL featureLevels[] =
    {
        D3D_FEATURE_LEVEL_11_0,
        D3D_FEATURE_LEVEL_10_1,
        D3D_FEATURE_LEVEL_10_0,
    };

	UINT numFeatureLevels = ARRAYSIZE(featureLevels);

	UINT sampleCount = 4;

    DXGI_SWAP_CHAIN_DESC sd;
    ZeroMemory(&sd, sizeof(sd));
    sd.BufferCount = 1;
    sd.BufferDesc.Width = _renderWidth;
    sd.BufferDesc.Height = _renderHeight;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferDesc.RefreshRate.Numerator = 60;
    sd.BufferDesc.RefreshRate.Denominator = 1;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow = _hWnd;
	sd.SampleDesc.Count = sampleCount;
    sd.SampleDesc.Quality = 0;
    sd.Windowed = TRUE;

    for (UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++)
    {
        _driverType = driverTypes[driverTypeIndex];
        hr = D3D11CreateDeviceAndSwapChain(nullptr, _driverType, nullptr, createDeviceFlags, featureLevels, numFeatureLevels,
                                           D3D11_SDK_VERSION, &sd, &_pSwapChain, &_pd3dDevice, &_featureLevel, &_pImmediateContext);
        if (SUCCEEDED(hr))
            break;
    }

    if (FAILED(hr))
        return hr;

    // Create a render target view
    ID3D11Texture2D* pBackBuffer = nullptr;
    hr = _pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);

    if (FAILED(hr))
        return hr;

    hr = _pd3dDevice->CreateRenderTargetView(pBackBuffer, nullptr, &_pRenderTargetView);
    pBackBuffer->Release();

    if (FAILED(hr))
        return hr;

    // Setup the viewport
    D3D11_VIEWPORT vp;
    vp.Width = (FLOAT)_renderWidth;
    vp.Height = (FLOAT)_renderHeight;
    vp.MinDepth = 0.0f;
    vp.MaxDepth = 1.0f;
    vp.TopLeftX = 0;
    vp.TopLeftY = 0;
    _pImmediateContext->RSSetViewports(1, &vp);

	InitShadersAndInputLayout();

    // Set primitive topology
    _pImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// Create the constant buffer
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(ConstantBuffer);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
    hr = _pd3dDevice->CreateBuffer(&bd, nullptr, &_pConstantBuffer);

    if (FAILED(hr))
        return hr;

	D3D11_TEXTURE2D_DESC depthStencilDesc;

	depthStencilDesc.Width = _renderWidth;
	depthStencilDesc.Height = _renderHeight;
	depthStencilDesc.MipLevels = 1;
	depthStencilDesc.ArraySize = 1;
	depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilDesc.SampleDesc.Count = sampleCount;
	depthStencilDesc.SampleDesc.Quality = 0;
	depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
	depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthStencilDesc.CPUAccessFlags = 0;
	depthStencilDesc.MiscFlags = 0;

	_pd3dDevice->CreateTexture2D(&depthStencilDesc, nullptr, &_depthStencilBuffer);
	_pd3dDevice->CreateDepthStencilView(_depthStencilBuffer, nullptr, &_depthStencilView);

	_pImmediateContext->OMSetRenderTargets(1, &_pRenderTargetView, _depthStencilView);

	// Rasterizer
	D3D11_RASTERIZER_DESC cmdesc;

	ZeroMemory(&cmdesc, sizeof(D3D11_RASTERIZER_DESC));
	cmdesc.FillMode = D3D11_FILL_SOLID;
	cmdesc.CullMode = D3D11_CULL_BACK;
	hr = _pd3dDevice->CreateRasterizerState(&cmdesc, &RSCullNone);

	ZeroMemory(&cmdesc, sizeof(D3D11_RASTERIZER_DESC));
	cmdesc.FillMode = D3D11_FILL_SOLID;
	cmdesc.CullMode = D3D11_CULL_NONE;
	hr = _pd3dDevice->CreateRasterizerState(&cmdesc, &RSCullNone);

	ZeroMemory(&cmdesc, sizeof(D3D11_RASTERIZER_DESC));
	cmdesc.FillMode = D3D11_FILL_WIREFRAME;
	cmdesc.CullMode = D3D11_CULL_NONE;
	hr = _pd3dDevice->CreateRasterizerState(&cmdesc, &RSWireFrame);

	D3D11_DEPTH_STENCIL_DESC dssDesc;
	ZeroMemory(&dssDesc, sizeof(D3D11_DEPTH_STENCIL_DESC));
	dssDesc.DepthEnable = true;
	dssDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	dssDesc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;

	_pd3dDevice->CreateDepthStencilState(&dssDesc, &DSLessEqual);

	ZeroMemory(&cmdesc, sizeof(D3D11_RASTERIZER_DESC));

	cmdesc.FillMode = D3D11_FILL_SOLID;
	cmdesc.CullMode = D3D11_CULL_BACK;

	cmdesc.FrontCounterClockwise = true;
	hr = _pd3dDevice->CreateRasterizerState(&cmdesc, &CCWcullMode);

	cmdesc.FrontCounterClockwise = false;
	hr = _pd3dDevice->CreateRasterizerState(&cmdesc, &CWcullMode);

	_pCurrentState = RSCull;

	//Create Blend Description 
	D3D11_BLEND_DESC blendDesc;
	ZeroMemory(&blendDesc, sizeof(blendDesc));

	//Create Blend Render Target 
	D3D11_RENDER_TARGET_BLEND_DESC rtbd;
	ZeroMemory(&rtbd, sizeof(rtbd));

	rtbd.BlendEnable = true;
	rtbd.SrcBlend = D3D11_BLEND_SRC_COLOR;
	rtbd.DestBlend = D3D11_BLEND_BLEND_FACTOR;
	rtbd.BlendOp = D3D11_BLEND_OP_ADD;
	rtbd.SrcBlendAlpha = D3D11_BLEND_ONE;
	rtbd.DestBlendAlpha = D3D11_BLEND_ZERO;
	rtbd.BlendOpAlpha = D3D11_BLEND_OP_ADD;
	rtbd.RenderTargetWriteMask = D3D10_COLOR_WRITE_ENABLE_ALL;

	blendDesc.AlphaToCoverageEnable = false;
	blendDesc.RenderTarget[0] = rtbd;

	_pd3dDevice->CreateBlendState(&blendDesc, &BSTransparency);

    return S_OK;
}

void Application::Cleanup()
{
    if (_pImmediateContext) _pImmediateContext->ClearState();
	if (_pSamplerLinear) _pSamplerLinear->Release();

	if (_pStoneDiffuseTextureRV) _pStoneDiffuseTextureRV->Release();
	if (_pStoneSpecularTextureRV) _pStoneSpecularTextureRV->Release();
	if (_pStoneAOTextureRV) _pStoneAOTextureRV->Release();
	if (_pStoneNormalTextureRV) _pStoneNormalTextureRV->Release();

	if (_pGroundDiffuseTextureRV) _pGroundDiffuseTextureRV->Release();
	if (_pGroundSpecularTextureRV) _pGroundSpecularTextureRV->Release();
	if (_pGroundAOTextureRV) _pGroundAOTextureRV->Release();
	if (_pGroundNormalTextureRV) _pGroundNormalTextureRV->Release();

	if (_pBallDiffuseTextureRV) _pBallDiffuseTextureRV->Release();
	if (_pBallSpecularTextureRV) _pBallSpecularTextureRV->Release();
	if (_pBallAOTextureRV) _pBallAOTextureRV->Release();
	if (_pBallNormalTextureRV) _pBallNormalTextureRV->Release();

	if (_pCarDiffuseTextureRV) _pCarDiffuseTextureRV->Release();
	if (_pCarSpecularTextureRV) _pCarSpecularTextureRV->Release();

    if (_pConstantBuffer) _pConstantBuffer->Release();

    if (_pVertexLayout) _pVertexLayout->Release();
    if (_pVertexShader) _pVertexShader->Release();
    if (_pPixelShader) _pPixelShader->Release();
    if (_pRenderTargetView) _pRenderTargetView->Release();
    if (_pSwapChain) _pSwapChain->Release();
    if (_pImmediateContext) _pImmediateContext->Release();
    if (_pd3dDevice) _pd3dDevice->Release();
	if (_depthStencilView) _depthStencilView->Release();
	if (_depthStencilBuffer) _depthStencilBuffer->Release();

	if (DSLessEqual) DSLessEqual->Release();
	if (RSCullNone) RSCullNone->Release();
	if (RSCull) RSCull->Release();
	if (RSWireFrame) RSWireFrame->Release();

	if (CCWcullMode) CCWcullMode->Release();
	if (CWcullMode) CWcullMode->Release();

	for (auto gameObject : _gameObjects)
	{
		if (gameObject)
		{
			delete gameObject;
			gameObject = nullptr;
		}
	}

	DIMouse->Unacquire();
	DIMouse->Release();
	DirectInput->Release();
}

void Application::Update(float deltaTime)
{
	HandleInput(deltaTime);

	// Move gameobject
	if (GetAsyncKeyState('1'))
	{
		_gameObjects[1]->GetPhysicsComponent()->AddForce(Vector3D{ 50.0f, 0.0f, 0.0f });
		_gameObjects[2]->GetPhysicsComponent()->AddForce(Vector3D{ 50.0f, 0.0f, 0.0f });
		_gameObjects[3]->GetPhysicsComponent()->AddForce(Vector3D{ 0.0f, 200.0f, 0.0f });
		_gameObjects[4]->GetPhysicsComponent()->AddForce(Vector3D{ 50.0f, 0.0f, 0.0f });
		//_gameObjects[5]->GetPhysicsComponent()->AddForce(Vector3D{ 20.0f, 0.0f, 0.0f });
		
	}

	if (GetAsyncKeyState('2'))
	{
		//_gameObjects[1]->GetPhysicsComponent()->AddForce(Vector3D{ 20.0f, 0.0f, 0.0f });
		_gameObjects[2]->GetPhysicsComponent()->AddForce(Vector3D{ -50.0f, 0.0f, 0.0f });
		//_gameObjects[3]->GetParticleModel()->AddForce(Vector{ 0.0f, -10.0f, 0.0f }*(_gameObjects[3]->GetParticleModel()->GetMass()));
		//_gameObjects[4]->GetParticleModel()->AddForce(Vector{ 0.0f, -10.0f, 0.0f }*(_gameObjects[4]->GetParticleModel()->GetMass()));
		//_gameObjects[5]->GetParticleModel()->AddForce(Vector{ -20.0f, 0.0f, 0.0f }*(_gameObjects[5]->GetParticleModel()->GetMass()));
	}

	if (GetAsyncKeyState('3'))
	{
		_particleSystem->Activate(_gameObjects[1]->GetTransform()->GetPosition(), { 0.0f, 50.0f, 0.0f }, 10.0f, 10.0f, 10000000.0f, 1.0f);
	}

	if (GetAsyncKeyState('4'))
	{
		_particleSystem->Deactivate();
	}
	if (GetAsyncKeyState('5'))
	{
		ParticleModel* tempPhysicsComp = _gameObjects[1]->GetPhysicsComponent();

		RigidBody* physicsComp = dynamic_cast<RigidBody*>(tempPhysicsComp);
		physicsComp->AddPointForce(Vector3D{ 0.0f, 0.0f, -50.0f }, { 0.0f, 0.2f,0.0f });
	}
	if (GetAsyncKeyState('6'))
	{
		ParticleModel* tempPhysicsComp = _gameObjects[1]->GetPhysicsComponent();

		RigidBody* physicsComp = dynamic_cast<RigidBody*>(tempPhysicsComp);
		physicsComp->AddPointForce(Vector3D{ 0.0f, 0.0f, 50.0f }, { 0.0f, 0.2f, 0.0f });
	}
	if (GetAsyncKeyState('6'))
	{
		//_gameObjects[1]->GetPhysicsComponent()->AddForce(Vector3D{ 0.0f, 0.0f, -50.0f });
	}
	if (GetAsyncKeyState('7'))
	{
		_gameObjects[1]->GetPhysicsComponent()->AddForce(Vector3D{ 50.0f, 0.0f, 0.0f });
	}
	if (GetAsyncKeyState('8'))
	{
		_gameObjects[1]->GetPhysicsComponent()->AddForce(Vector3D{ -50.0f, 0.0f, 0.0f });
	}
	_camera->Update();
	_particleSystem->Update(deltaTime);
	_SkySphere->Update(_camera->GetPosition());

	// Update objects
	for (auto gameObject : _gameObjects)
	{
		gameObject->Update(deltaTime);
		if (gameObject->GetPhysicsComponent() != nullptr)
		{
			if (gameObject->GetPhysicsComponent()->GetSimulatePhysics())
			{
				if (gameObject->GetTransform()->GetPosition().y < 0.0f)
				{
					gameObject->GetTransform()->SetPosition(gameObject->GetTransform()->GetPosition().x, 0.0f , gameObject->GetTransform()->GetPosition().z);
					gameObject->GetPhysicsComponent()->SetVelocity(Vector3D::Reflect(gameObject->GetPhysicsComponent()->GetVelocity(), { 0.0f,-1.0f,0.0f })* 0.8);
				}
				
				if (gameObject->GetTransform()->GetPosition().y > 20.0f)
				{
					gameObject->GetTransform()->SetPosition(gameObject->GetTransform()->GetPosition().x, 20.0f , gameObject->GetTransform()->GetPosition().z);
					gameObject->GetPhysicsComponent()->SetVelocity(Vector3D::Reflect(gameObject->GetPhysicsComponent()->GetVelocity(), { 0.0f, 1.0f, 0.0f })* 0.8);
				}
				if (gameObject->GetTransform()->GetPosition().x > 20.0f)
				{
					gameObject->GetTransform()->SetPosition(20.0f, gameObject->GetTransform()->GetPosition().y, gameObject->GetTransform()->GetPosition().z);
					gameObject->GetPhysicsComponent()->SetVelocity(Vector3D::Reflect(gameObject->GetPhysicsComponent()->GetVelocity(), { 1.0f, 0.0f, 0.0f }) * 0.8);
				}
				if (gameObject->GetTransform()->GetPosition().x < -20.0f)
				{
					gameObject->GetTransform()->SetPosition(-20.0f, gameObject->GetTransform()->GetPosition().y, gameObject->GetTransform()->GetPosition().z);
					gameObject->GetPhysicsComponent()->SetVelocity(Vector3D::Reflect(gameObject->GetPhysicsComponent()->GetVelocity(), { -1.0f, 0.0f, 0.0f })* 0.8);
				}
				
			}
		}
	}

	//Check objects collisions
	Collision::DetectCollisions(_gameObjects);


	//Collision::ResolveCollision(Collision::DetectCollisions(_gameObjects));
	//Collision::ResolveCollision(Collision::DetectCollisions(_gameObjects));
	//Collision::ResolveCollision(Collision::DetectCollisions(_gameObjects));
}

void Application::Draw()
{
    //
    // Clear buffers
    //

	float ClearColor[4] = { 0.5f, 0.5f, 0.5f, 1.0f }; // red,green,blue,alpha
    _pImmediateContext->ClearRenderTargetView(_pRenderTargetView, ClearColor);
	_pImmediateContext->ClearDepthStencilView(_depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	ConstantBuffer cb;

	XMFLOAT4X4 viewAsFloats = _camera->GetView();
	XMFLOAT4X4 projectionAsFloats = _camera->GetProjection();

	XMMATRIX view = XMLoadFloat4x4(&viewAsFloats);
	XMMATRIX projection = XMLoadFloat4x4(&projectionAsFloats);

	cb.View = XMMatrixTranspose(view);
	cb.Projection = XMMatrixTranspose(projection);

	cb.light = basicLight;
	cb.EyePosW = _camera->GetPosition();
	
    //
    // Setup buffers and render scene
    //
	_pImmediateContext->VSSetConstantBuffers(0, 1, &_pConstantBuffer);
	_pImmediateContext->PSSetConstantBuffers(0, 1, &_pConstantBuffer);
	_pImmediateContext->PSSetSamplers(0, 1, &_pSamplerLinear);

	//Draw SkySphere
	_pImmediateContext->RSSetState(RSCullNone);
	cb.World = XMMatrixTranspose(_SkySphere->GetWorldMatrix());
	_pImmediateContext->UpdateSubresource(_pConstantBuffer, 0, nullptr, &cb, 0, 0);
	_SkySphere->Draw(_pImmediateContext);
	
	//Reset the shaders
	_pImmediateContext->RSSetState(ViewMode());
	_pImmediateContext->IASetInputLayout(_pVertexLayout);

	_pImmediateContext->VSSetShader(_pVertexShader, nullptr, 0);
	_pImmediateContext->PSSetShader(_pPixelShader, nullptr, 0);
	_pImmediateContext->OMSetDepthStencilState(NULL, 0);
	
	//render the particles
	for (auto particle : _particleSystem->GetParticles())
	{
		// Get render material
		Material material = particle->GetAppearance()->GetMaterial();

		// Copy material to shader
		cb.surface.AmbientMtrl = material.ambient;
		cb.surface.DiffuseMtrl = material.diffuse;
		cb.surface.SpecularMtrl = material.specular;

		// Set world matrix
		cb.World = XMMatrixTranspose(particle ->GetTransform()->GetWorldMatrix());

		// Set texture
		if (particle->GetAppearance()->HasTexture())
		{
			ID3D11ShaderResourceView * textureDiffuseRV = particle->GetAppearance()->GetTextureDiffuseRV();
			ID3D11ShaderResourceView * textureSpecularRV = particle->GetAppearance()->GetTextureSpecularRV();
			ID3D11ShaderResourceView * textureAORV = particle->GetAppearance()->GetTextureAORV();
			_pImmediateContext->PSSetShaderResources(0, 1, &textureDiffuseRV);
			_pImmediateContext->PSSetShaderResources(1, 1, &textureSpecularRV);
			_pImmediateContext->PSSetShaderResources(2, 1, &textureAORV);
			cb.HasTexture = 1.0f;
		}
		else
		{
			cb.HasTexture = 0.0f;
		}

		// Update constant buffer
		_pImmediateContext->UpdateSubresource(_pConstantBuffer, 0, nullptr, &cb, 0, 0);

		// Draw object
		particle->Draw(_pImmediateContext);
	}

	// Render all scene objects
	for (auto gameObject : _gameObjects)
	{
		// Get render material
		Material material = gameObject->GetAppearance()->GetMaterial();

		// Copy material to shader
		cb.surface.AmbientMtrl = material.ambient;
		cb.surface.DiffuseMtrl = material.diffuse;
		cb.surface.SpecularMtrl = material.specular;

		// Set world matrix
		cb.World = XMMatrixTranspose(gameObject->GetTransform()->GetWorldMatrix());

		// Set texture
		if (gameObject->GetAppearance()->HasTexture())
		{
			ID3D11ShaderResourceView * textureDiffuseRV = gameObject->GetAppearance()->GetTextureDiffuseRV();
			ID3D11ShaderResourceView * textureSpecularRV = gameObject->GetAppearance()->GetTextureSpecularRV();
			ID3D11ShaderResourceView * textureAORV = gameObject->GetAppearance()->GetTextureAORV();
			_pImmediateContext->PSSetShaderResources(0, 1, &textureDiffuseRV);
			_pImmediateContext->PSSetShaderResources(1, 1, &textureSpecularRV);
			_pImmediateContext->PSSetShaderResources(2, 1, &textureAORV);
			cb.HasTexture = 1.0f;
		}
		else
		{
			cb.HasTexture = 0.0f;
		}

		// Update constant buffer
		_pImmediateContext->UpdateSubresource(_pConstantBuffer, 0, nullptr, &cb, 0, 0);

		// Draw object
		gameObject->Draw(_pImmediateContext);
	}

    //
    // Present our back buffer to our front buffer
    //
    _pSwapChain->Present(0, 0);
}