#pragma once
#include <directxmath.h>
#include <d3d11_1.h>
#include <string>

#include "Commons.h"

using namespace DirectX;
using namespace std;

class Appearance
{
public:
	Appearance();
	Appearance(MeshData _geometry, Material _material, ID3D11ShaderResourceView * _textureRV);
	~Appearance();

	Material GetMaterial() const {return _material; }
	void SetMaterial(Material material) { _material = material; };
	void SetMaterial(XMFLOAT4 diffuse, XMFLOAT4 ambient, XMFLOAT4 specular, float specularPower);

	MeshData GetGeometry() const { return _geometry; }
	void SetGeometry(MeshData geometry) { _geometry = geometry; }
	void SetGeometry(ID3D11Buffer * vertexBuffer, ID3D11Buffer * indexBuffer, int numberOfIndices, UINT vertexBufferStride, UINT vertexBufferOffset);

	ID3D11ShaderResourceView * GetTextureRV() const { return _textureRV; }
	void SetTextureRV(ID3D11ShaderResourceView * textureRV) { _textureRV = textureRV; }

	bool HasTexture() const { return _textureRV ? true : false; }
	void Draw(ID3D11DeviceContext * pImmediateContext);

private:

	MeshData _geometry;
	Material _material;

	ID3D11ShaderResourceView * _textureRV;
};

