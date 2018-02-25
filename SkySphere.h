#ifndef _SKYSPHERE_H
#define _SKYSPHERE_H

#include "Vector.h"
#include "Transform.h"
#include "GeometryGenerator.h"
#include <d3dcompiler.h>
#include "DDSTextureLoader.h"
#include <string>

class SkySphere
{
public:
	SkySphere(ID3D11Device* _pd3dDevice, const wchar_t* fileName);
	~SkySphere();

	void Update(Vector position);
	void Draw(ID3D11DeviceContext * pImmediateContext);

	XMMATRIX GetWorldMatrix() const { return XMLoadFloat4x4(&_world); }

	void LoadTexture(ID3D11Device* _pd3dDevice, const wchar_t* fileName);

private:
	MeshData _geometry;
	
	XMFLOAT4X4 _world;

	ID3D11VertexShader*			_pSkyMapVertexShader;
	ID3D11PixelShader*			_pSkyMapPixelShader;
	ID3D11InputLayout*			_pSkyMapVertexLayout;
	ID3D11DepthStencilState*	_pDSLessEqual;
	ID3D11Texture2D*			_SMTexture;
	ID3D11ShaderResourceView *	_pSkyBoxTexture;

	void CompileShader(ID3D11Device* _pd3dDevice);
};

#endif // !_SKYSPHERE_H