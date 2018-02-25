#include "Appearance.h"

Appearance::Appearance()
{
}

Appearance::Appearance(MeshData geometry, Material material, ID3D11ShaderResourceView * textureDiffuseRV, ID3D11ShaderResourceView * textureSpecularRV, ID3D11ShaderResourceView * textureAORV) : _geometry(geometry), _material(material), _textureDiffuseRV(textureDiffuseRV), _textureSpecularRV(textureSpecularRV), _textureAORV(textureAORV)
{
}


Appearance::~Appearance()
{
	delete &_geometry;
}

void Appearance::SetMaterial(XMFLOAT4 diffuse, XMFLOAT4 ambient, XMFLOAT4 specular, float specularPower)
{
	_material.diffuse = diffuse;
	_material.ambient = ambient;
	_material.specular = specular;
	_material.specularPower = specularPower;
}

void Appearance::SetGeometry(ID3D11Buffer * vertexBuffer, ID3D11Buffer * indexBuffer, int numberOfIndices, UINT vertexBufferStride, UINT vertexBufferOffset)
{
	_geometry.vertexBuffer = vertexBuffer;
	_geometry.indexBuffer = indexBuffer;
	_geometry.numberOfIndices = numberOfIndices;

	_geometry.vertexBufferStride = vertexBufferStride;
	_geometry.vertexBufferOffset = vertexBufferOffset;
}

void Appearance::Draw(ID3D11DeviceContext * pImmediateContext)
{
	// NOTE: We are assuming that the constant buffers and all other draw setup has already taken place

	// Set vertex and index buffers
	pImmediateContext->IASetVertexBuffers(0, 1, &_geometry.vertexBuffer, &_geometry.vertexBufferStride, &_geometry.vertexBufferOffset);
	pImmediateContext->IASetIndexBuffer(_geometry.indexBuffer, DXGI_FORMAT_R16_UINT, 0);

	pImmediateContext->DrawIndexed(_geometry.numberOfIndices, 0, 0);
}
