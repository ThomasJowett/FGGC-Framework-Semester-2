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
	Appearance(MeshData _geometry, Material _material, ID3D11ShaderResourceView * _textureDiffuseRV, ID3D11ShaderResourceView * _textureSpecularRV, ID3D11ShaderResourceView * _textureAORV);
	~Appearance();

	Material GetMaterial() const {return _material; }
	void SetMaterial(Material material) { _material = material; };
	void SetMaterial(XMFLOAT4 diffuse, XMFLOAT4 ambient, XMFLOAT4 specular, float specularPower);

	MeshData GetGeometry() const { return _geometry; }
	void SetGeometry(MeshData geometry) { _geometry = geometry; }
	void SetGeometry(ID3D11Buffer * vertexBuffer, ID3D11Buffer * indexBuffer, int numberOfIndices, UINT vertexBufferStride, UINT vertexBufferOffset);

	ID3D11ShaderResourceView * GetTextureDiffuseRV() const { return _textureDiffuseRV; }
	void SetTextureDiffuseRV(ID3D11ShaderResourceView * textureRV) { _textureDiffuseRV = textureRV; }

	ID3D11ShaderResourceView * GetTextureSpecularRV() const { return _textureSpecularRV; }
	void SetTextureSpecularRV(ID3D11ShaderResourceView * textureRV) { _textureSpecularRV = textureRV; }

	ID3D11ShaderResourceView * GetTextureAORV() const { return _textureAORV; }
	void SetTextureAORV(ID3D11ShaderResourceView * textureRV) { _textureAORV = textureRV; }

	bool HasTexture() const { return _textureDiffuseRV ? true : false; }
	void Draw(ID3D11DeviceContext * pImmediateContext);

private:

	MeshData _geometry;
	Material _material;

	ID3D11ShaderResourceView * _textureDiffuseRV;
	ID3D11ShaderResourceView * _textureSpecularRV;
	ID3D11ShaderResourceView * _textureAORV;
};

