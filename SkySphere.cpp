#include "SkySphere.h"

static SkySphere* instance = 0;

SkySphere::SkySphere(ID3D11Device* _pd3dDevice, const wchar_t* fileName)
{
	_SMTexture = nullptr;
	_pSkyMapVertexShader = nullptr;
	_pSkyMapPixelShader = nullptr;
	_pSkyBoxTexture = nullptr;
	_pDSLessEqual = nullptr;

	_geometry = GeometryGenerator::CreateSphere(5.0f, 1, 1, _pd3dDevice);

	CompileShader(_pd3dDevice);
	LoadTexture(_pd3dDevice, fileName);

	XMStoreFloat4x4(&_world, XMMatrixIdentity());
}

SkySphere::~SkySphere()
{
}

void SkySphere::Update(Vector position)
{
	XMStoreFloat4x4(&_world, XMMatrixTranslation(position.x, position.y, position.z));
}

void SkySphere::Draw(ID3D11DeviceContext * pImmediateContext)
{
	pImmediateContext->IASetInputLayout(_pSkyMapVertexLayout);
	pImmediateContext->VSSetShader(_pSkyMapVertexShader, nullptr, 0);
	pImmediateContext->PSSetShader(_pSkyMapPixelShader, nullptr, 0);
	pImmediateContext->OMSetDepthStencilState(_pDSLessEqual, 0);
	pImmediateContext->PSSetShaderResources(4, 1, &_pSkyBoxTexture);
	pImmediateContext->IASetVertexBuffers(0, 1, &_geometry.vertexBuffer, &_geometry.vertexBufferStride, &_geometry.vertexBufferOffset);
	pImmediateContext->IASetIndexBuffer(_geometry.indexBuffer, DXGI_FORMAT_R16_UINT, 0);

	pImmediateContext->DrawIndexed(_geometry.numberOfIndices, 0, 0);
}

void SkySphere::LoadTexture(ID3D11Device* _pd3dDevice, const wchar_t* fileName)
{
	// Create the resource view
	CreateDDSTextureFromFileEx(_pd3dDevice, fileName, 0, D3D11_USAGE_DEFAULT, D3D11_BIND_SHADER_RESOURCE, 0, D3D11_RESOURCE_MISC_TEXTURECUBE, false, (ID3D11Resource**)&_SMTexture, &_pSkyBoxTexture, nullptr);

	D3D11_TEXTURE2D_DESC SMTextureDesc;
	_SMTexture->GetDesc(&SMTextureDesc);

	D3D11_SHADER_RESOURCE_VIEW_DESC SMViewDesc;
	SMViewDesc.Format = SMTextureDesc.Format;
	SMViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURECUBE;
	SMViewDesc.TextureCube.MipLevels = SMTextureDesc.MipLevels;
	SMViewDesc.TextureCube.MostDetailedMip = 0;
	_pd3dDevice->CreateShaderResourceView(_SMTexture, &SMViewDesc, &_pSkyBoxTexture);
}

void SkySphere::CompileShader(ID3D11Device* _pd3dDevice)
{
	HRESULT hr = S_OK;
	
	//compile vertex shader
	ID3DBlob* pVSBlob = nullptr;
	DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
	ID3DBlob* pErrorBlob;
	hr = D3DCompileFromFile(L"DX11 Framework.fx", nullptr, nullptr, "SKYMAP_VS", "vs_4_0", dwShaderFlags, 0, &pVSBlob, &pErrorBlob);

	if (FAILED(hr))
	{
		MessageBox(nullptr,
			L"The FX file cannot compile the SkyMap Vertex Shader.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK);
	}
	hr = _pd3dDevice->CreateVertexShader(pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), nullptr, &_pSkyMapVertexShader);
	
	//compile Pixel shader
	ID3DBlob* pPSBlob = nullptr;
	hr = D3DCompileFromFile(L"DX11 Framework.fx", nullptr, nullptr, "SKYMAP_PS", "ps_4_0", dwShaderFlags, 0, &pPSBlob, &pErrorBlob);

	if (FAILED(hr))
	{
		MessageBox(nullptr,
			L"The FX file cannot compile the SkyMap Pixel Shader.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK);
	}

	_pd3dDevice->CreatePixelShader(pPSBlob->GetBufferPointer(), pPSBlob->GetBufferSize(), nullptr, &_pSkyMapPixelShader);
	pPSBlob->Release();

	// Create the input layout

	D3D11_INPUT_ELEMENT_DESC Skymaplayout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	UINT numElements = ARRAYSIZE(Skymaplayout);

	hr = _pd3dDevice->CreateInputLayout(Skymaplayout, numElements, pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), &_pSkyMapVertexLayout);
	pVSBlob->Release();

	if (FAILED(hr))
	{
		MessageBox(nullptr,
			L"Cannot Create SkyMap Input layout.", L"Error", MB_OK);
	}

	//Create the depth stencil

	D3D11_DEPTH_STENCIL_DESC dssDesc;
	ZeroMemory(&dssDesc, sizeof(D3D11_DEPTH_STENCIL_DESC));
	dssDesc.DepthEnable = true;
	dssDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	dssDesc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;

	_pd3dDevice->CreateDepthStencilState(&dssDesc, &_pDSLessEqual);
}
