#pragma once

#pragma comment (lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

#include <windows.h>
#include <d3d11_1.h>
#include <d3dcompiler.h>
#include <directxmath.h>
#include <directxcolors.h>
#include <dinput.h>
#include <Xinput.h>
#include "Commons.h"
#include "DDSTextureLoader.h"
#include "resource.h"
#include "Camera.h"
#include "OrbitCamera.h"
#include "FreeLookCamera.h"
#include "Transform.h"
#include "Collision.h"
#include "OBJLoader.h"
#include "GeometryGenerator.h"
#include "SkySphere.h"
#include <vector>
/*
#include <SpriteFont.h>
#include "CommonStates.h"
#include "Effects.h"
#include "GeometricPrimitive.h"
#include "Model.h"
#include "PrimitiveBatch.h"
#include "ScreenGrab.h"
#include "SpriteBatch.h"
#include "SpriteFont.h"
#include "VertexTypes.h"
*/
#include "GameObject.h"
#include "ParticleSystem.h"

using namespace DirectX;

class Application
{
private:
	HINSTANCE               _hInst;
	HWND                    _hWnd;
	D3D_DRIVER_TYPE         _driverType;
	D3D_FEATURE_LEVEL       _featureLevel;
	ID3D11Device*           _pd3dDevice;
	ID3D11DeviceContext*    _pImmediateContext;
	IDXGISwapChain*         _pSwapChain;
	ID3D11RenderTargetView* _pRenderTargetView;
	ID3D11VertexShader*     _pVertexShader;
	ID3D11PixelShader*      _pPixelShader;
	ID3D11InputLayout*      _pVertexLayout;

	ID3D11Buffer*           _pConstantBuffer;

	ID3D11DepthStencilView* _depthStencilView = nullptr;
	ID3D11Texture2D*		_depthStencilBuffer = nullptr;

	ID3D11ShaderResourceView * _pStoneDiffuseTextureRV = nullptr;
	ID3D11ShaderResourceView * _pStoneSpecularTextureRV = nullptr;
	ID3D11ShaderResourceView * _pStoneAOTextureRV = nullptr;
	ID3D11ShaderResourceView * _pStoneNormalTextureRV = nullptr;

	ID3D11ShaderResourceView * _pGroundDiffuseTextureRV = nullptr;
	ID3D11ShaderResourceView * _pGroundSpecularTextureRV = nullptr;
	ID3D11ShaderResourceView * _pGroundAOTextureRV = nullptr;
	ID3D11ShaderResourceView * _pGroundNormalTextureRV = nullptr;

	ID3D11ShaderResourceView * _pBallDiffuseTextureRV = nullptr;
	ID3D11ShaderResourceView * _pBallSpecularTextureRV = nullptr;
	ID3D11ShaderResourceView * _pBallAOTextureRV = nullptr;
	ID3D11ShaderResourceView * _pBallNormalTextureRV = nullptr;

	ID3D11ShaderResourceView * _pCarDiffuseTextureRV = nullptr;
	ID3D11ShaderResourceView * _pCarSpecularTextureRV = nullptr;

	ID3D11SamplerState * _pSamplerLinear = nullptr;

	SkySphere* _SkySphere;

	Light basicLight;

	vector<GameObject *> _gameObjects;
	ParticleSystem* _particleSystem;

	Camera _StaticCamera;
	OrbitCamera _OrbitCamera;
	FreeLookCamera _FreeLookCamera;
	Camera * _camera;


	float _cameraOrbitRadius = 7.0f;
	float _cameraOrbitRadiusMin = 2.0f;
	float _cameraOrbitRadiusMax = 50.0f;
	float _cameraOrbitAngleYaw = -90.0f;
	float _cameraOrbitAnglePitch = 20.0f;
	float _cameraLookSpeed = 0.01f;
	float _cameraWalkSpeed = 5.0f;

	UINT _WindowHeight;
	UINT _WindowWidth;

	// Render dimensions - Change here to alter screen resolution
	UINT _renderHeight = 1080;
	UINT _renderWidth = 1920;

	ID3D11DepthStencilState* DSLessEqual;
	ID3D11RasterizerState* RSCull;
	ID3D11RasterizerState* RSCullNone;
	ID3D11RasterizerState* RSWireFrame;
	ID3D11RasterizerState* _pCurrentState;

	ID3D11RasterizerState* CCWcullMode;
	ID3D11RasterizerState* CWcullMode;

	ID3D11BlendState * BSTransparency;

	HRESULT hr;

	//Direct Input
	IDirectInputDevice8* DIMouse;
	DIMOUSESTATE mouseLastState;
	LPDIRECTINPUT8 DirectInput;

private:
	HRESULT InitWindow(HINSTANCE hInstance, int nCmdShow);
	HRESULT InitDevice();
	void Cleanup();
	HRESULT CompileShaderFromFile(WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut);
	HRESULT InitShadersAndInputLayout();
	HRESULT InitDirectInput(HINSTANCE hInstance);

public:
	Application();
	~Application();

	HRESULT Initialise(HINSTANCE hInstance, int nCmdShow);

	bool HandleInput(float deltaTime);

	ID3D11RasterizerState* ViewMode();

	void Update(float deltaTime);
	void Draw();
};

