#include "GeometryGenerator.h"



GeometryGenerator::GeometryGenerator()
{
}


GeometryGenerator::~GeometryGenerator()
{
}

MeshData GeometryGenerator::CreateCube(float width, float height, float depth, ID3D11Device* _pd3dDevice)
{
	float w2 = 0.5f*width;
	float h2 = 0.5f*height;
	float d2 = 0.5f*depth;

	MeshData cubeGeometry;

	SimpleVertex vertices[24] = 
	{
		{ XMFLOAT3(-w2, h2, -d2), XMFLOAT3(-1.0f, 1.0f, -1.0f), XMFLOAT2(1.0f, 0.0f) },
		{ XMFLOAT3(w2, h2, -d2), XMFLOAT3(1.0f, 1.0f, -1.0f), XMFLOAT2(0.0f, 0.0f) },
		{ XMFLOAT3(w2, h2, d2), XMFLOAT3(1.0f, 1.0f, 1.0f), XMFLOAT2(0.0f, 1.0f) },
		{ XMFLOAT3(-w2, h2, d2), XMFLOAT3(-1.0f, 1.0f, 1.0f), XMFLOAT2(1.0f, 1.0f) },

		{ XMFLOAT3(-w2, -h2, -d2), XMFLOAT3(-1.0f, -1.0f, -1.0f), XMFLOAT2(0.0f, 0.0f) },
		{ XMFLOAT3(w2, -h2, -d2), XMFLOAT3(1.0f, -1.0f, -1.0f), XMFLOAT2(1.0f, 0.0f) },
		{ XMFLOAT3(w2, -h2, d2), XMFLOAT3(1.0f, -1.0f, 1.0f), XMFLOAT2(1.0f, 1.0f) },
		{ XMFLOAT3(-w2, -h2, d2), XMFLOAT3(-1.0f, -1.0f, 1.0f), XMFLOAT2(0.0f, 1.0f) },

		{ XMFLOAT3(-w2, -h2, d2), XMFLOAT3(-1.0f, -1.0f, 1.0f), XMFLOAT2(0.0f, 1.0f) },
		{ XMFLOAT3(-w2, -h2, -d2), XMFLOAT3(-1.0f, -1.0f, -1.0f), XMFLOAT2(1.0f, 1.0f) },
		{ XMFLOAT3(-w2, h2, -d2), XMFLOAT3(-1.0f, 1.0f, -1.0f), XMFLOAT2(1.0f, 0.0f) },
		{ XMFLOAT3(-w2, h2, d2), XMFLOAT3(-1.0f, 1.0f, 1.0f), XMFLOAT2(0.0f, 0.0f) },

		{ XMFLOAT3(w2, -h2, d2), XMFLOAT3(1.0f, -1.0f, 1.0f), XMFLOAT2(1.0f, 1.0f) },
		{ XMFLOAT3(w2, -h2, -d2), XMFLOAT3(1.0f, -1.0f, -1.0f), XMFLOAT2(0.0f, 1.0f) },
		{ XMFLOAT3(w2, h2, -d2), XMFLOAT3(1.0f, 1.0f, -1.0f), XMFLOAT2(0.0f, 0.0f) },
		{ XMFLOAT3(w2, h2, d2), XMFLOAT3(1.0f, 1.0f, 1.0f), XMFLOAT2(1.0f, 0.0f) },

		{ XMFLOAT3(-w2, -h2, -d2), XMFLOAT3(-1.0f, -1.0f, -1.0f), XMFLOAT2(0.0f, 1.0f) },
		{ XMFLOAT3(w2, -h2, -d2), XMFLOAT3(1.0f, -1.0f, -1.0f), XMFLOAT2(1.0f, 1.0f) },
		{ XMFLOAT3(w2, h2, -d2), XMFLOAT3(1.0f, 1.0f, -1.0f), XMFLOAT2(1.0f, 0.0f) },
		{ XMFLOAT3(-w2, h2, -d2), XMFLOAT3(-1.0f, 1.0f, -1.0f), XMFLOAT2(0.0f, 0.0f) },

		{ XMFLOAT3(-w2, -h2, d2), XMFLOAT3(-1.0f, -1.0f, 1.0f), XMFLOAT2(1.0f, 1.0f) },
		{ XMFLOAT3(w2, -h2, d2), XMFLOAT3(1.0f, -1.0f, 1.0f), XMFLOAT2(0.0f, 1.0f) },
		{ XMFLOAT3(w2, h2, d2), XMFLOAT3(1.0f, 1.0f, 1.0f), XMFLOAT2(0.0f, 0.0f) },
		{ XMFLOAT3(-w2, h2, d2), XMFLOAT3(-1.0f, 1.0f, 1.0f), XMFLOAT2(1.0f, 0.0f) },
	};

	ID3D11Buffer* vertexBuffer;

	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(SimpleVertex) * 24;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = vertices;

	_pd3dDevice->CreateBuffer(&bd, &InitData, &vertexBuffer);

	cubeGeometry.vertexBuffer = vertexBuffer;

	WORD indices[] =
	{
		3, 1, 0,
		2, 1, 3,

		6, 4, 5,
		7, 4, 6,

		11, 9, 8,
		10, 9, 11,

		14, 12, 13,
		15, 12, 14,

		19, 17, 16,
		18, 17, 19,

		22, 20, 21,
		23, 20, 22
	};

	ID3D11Buffer* indexBuffer;

	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(WORD) * 36;
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = 0;

	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = indices;
	_pd3dDevice->CreateBuffer(&bd, &InitData, &indexBuffer);

	cubeGeometry.numberOfIndices = 36;
	cubeGeometry.indexBuffer = indexBuffer;
	
	cubeGeometry.vertexBufferOffset = 0;
	cubeGeometry.vertexBufferStride = sizeof(SimpleVertex);

	return cubeGeometry;
}

MeshData GeometryGenerator::CreateSphere(float radius, UINT longitudeLines, UINT latitudeLines, ID3D11Device * _pd3dDevice)
{
	if (longitudeLines < 3)
		longitudeLines = 3;
	if (latitudeLines < 2)
		latitudeLines = 2;
	MeshData sphereGeometry;

	//Compute vertices

	float phiStep = XM_PI/latitudeLines;
	float thetaStep = 2.0f*XM_PI/longitudeLines;

	std::vector<SimpleVertex> vertices;

	SimpleVertex topVertex = { XMFLOAT3(0.0f, radius, 0.0f), XMFLOAT3(0.0f, 1.0f, 0.0f), XMFLOAT2(0.0f, 0.0f) };
	SimpleVertex bottomVertex = { XMFLOAT3(0.0f, -radius, 0.0f), XMFLOAT3(0.0f, -1.0f, 0.0f), XMFLOAT2(0.0f, 1.0f) };

	vertices.push_back(topVertex);

	for (UINT i = 1; i <= latitudeLines - 1; ++i)
	{
		float phi = i*phiStep;

		for (UINT j = 0; j <= longitudeLines; ++j)
		{
			float theta = j*thetaStep;
			SimpleVertex vertex;

			vertex.PosL.x = radius*sinf(phi)*cosf(theta);
			vertex.PosL.y = radius*cosf(phi);
			vertex.PosL.z = radius*sinf(phi)*sinf(theta);

			Vector3D position = { vertex.PosL.x, vertex.PosL.y, vertex.PosL.z };
			position.Normalize();

			vertex.NormL.x = position.x;
			vertex.NormL.y = position.y;
			vertex.NormL.z = position.z;

			vertex.TexCoord.x = theta / XM_2PI;
			vertex.TexCoord.y = phi / XM_PI;

			vertices.push_back(vertex);
		}
	}

	vertices.push_back(bottomVertex);

	ID3D11Buffer* vertexBuffer;

	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(SimpleVertex) * vertices.size();
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));


	InitData.pSysMem = &vertices[0];

	_pd3dDevice->CreateBuffer(&bd, &InitData, &vertexBuffer);

	sphereGeometry.vertexBuffer = vertexBuffer;

	//Compute indices

	std::vector<WORD>indices;

	for (UINT i = 1; i <= longitudeLines; ++i)
	{
		indices.push_back(0);
		indices.push_back(i + 1);
		indices.push_back(i);
	}

	UINT baseIndex = 1;
	UINT ringVertexCount = longitudeLines + 1;
	for (UINT i = 0; i < latitudeLines - 2; ++i)
	{
		for (UINT j = 0; j < longitudeLines; ++j)
		{
			indices.push_back(baseIndex + i*ringVertexCount + j);
			indices.push_back(baseIndex + i*ringVertexCount + j + 1);
			indices.push_back(baseIndex + (i + 1)*ringVertexCount + j);

			indices.push_back(baseIndex + (i + 1)*ringVertexCount + j);
			indices.push_back(baseIndex + i*ringVertexCount + j + 1);
			indices.push_back(baseIndex + (i + 1)*ringVertexCount + j + 1);
		}
	}

	UINT southPoleIndex = vertices.size()-1;

	baseIndex = southPoleIndex - ringVertexCount;

	for (UINT i = 0; i < longitudeLines; ++i)
	{
		indices.push_back(southPoleIndex);
		indices.push_back(baseIndex + i);
		indices.push_back(baseIndex + i + 1);
	}

	ID3D11Buffer* indexBuffer;

	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(WORD) * indices.size();
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = 0;

	ZeroMemory(&InitData, sizeof(InitData));

	InitData.pSysMem = &indices[0];
	_pd3dDevice->CreateBuffer(&bd, &InitData, &indexBuffer);

	sphereGeometry.numberOfIndices = indices.size();
	sphereGeometry.indexBuffer = indexBuffer;

	sphereGeometry.vertexBufferOffset = 0;
	sphereGeometry.vertexBufferStride = sizeof(SimpleVertex);


	return sphereGeometry;
}

MeshData GeometryGenerator::CreateGrid(float width, float length, UINT widthLines, UINT lengthLines, float tileU, float tileV, ID3D11Device * _pd3dDevice)
{
	if (widthLines < 2)
		widthLines == 2;
	if (lengthLines < 2)
		lengthLines == 2;

	MeshData gridGeometry;
	UINT vertexCount = widthLines*lengthLines;
	UINT faceCount = (widthLines - 1)*(lengthLines - 1) * 2;

	float halfWidth = 0.5f*width;
	float halfLength = 0.5*length;

	float dx = width / (lengthLines - 1);
	float dz = length/ (widthLines - 1);

	float du = tileU / (lengthLines - 1);
	float dv = tileV / (widthLines - 1);

	std::vector<SimpleVertex>vertices;
	vertices.resize(vertexCount);

	for (UINT i = 0; i < widthLines; ++i)
	{
		float z = halfLength - i*dz;
		for (UINT j = 0; j < lengthLines; ++j)
		{
			float x = -halfWidth + j*dx;

			vertices[i*lengthLines + j].PosL = XMFLOAT3(x, 0.0f, z);
			vertices[i*lengthLines + j].NormL = XMFLOAT3(0.0f, 1.0f, 0.0f);
			vertices[i*lengthLines + j].TexCoord.x = j*du;
			vertices[i*lengthLines + j].TexCoord.y = i*dv;
		}
	}

	ID3D11Buffer* vertexBuffer;

	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(SimpleVertex) * vertexCount;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));

	InitData.pSysMem = &vertices[0];

	_pd3dDevice->CreateBuffer(&bd, &InitData, &vertexBuffer);

	gridGeometry.vertexBuffer = vertexBuffer;

	std::vector<WORD>indices;
	indices.resize(faceCount*3);

	UINT k = 0;
	for (UINT i = 0; i < lengthLines - 1; ++i)
	{
		for (UINT j = 0; j < widthLines - 1; ++j)
		{
			indices[k] = i*lengthLines + j;
			indices[k + 1] = i*lengthLines + j + 1;
			indices[k + 2] = (i + 1)*lengthLines + j;

			indices[k + 3] = (i + 1)*lengthLines + j;
			indices[k + 4] = i*lengthLines + j + 1;
			indices[k + 5] = (i + 1)*lengthLines + j + 1;

			k += 6;
		}
	}

	ID3D11Buffer* indexBuffer;

	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(WORD) * faceCount * 3;
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = 0;

	ZeroMemory(&InitData, sizeof(InitData));

	InitData.pSysMem = &indices[0];
	_pd3dDevice->CreateBuffer(&bd, &InitData, &indexBuffer);

	gridGeometry.numberOfIndices = faceCount * 3;
	gridGeometry.indexBuffer = indexBuffer;

	gridGeometry.vertexBufferOffset = 0;
	gridGeometry.vertexBufferStride = sizeof(SimpleVertex);

	return gridGeometry;
}

MeshData GeometryGenerator::CreateFullscreenQuad(ID3D11Device * _pd3dDevice)
{
	MeshData fullScreenQuad;
	SimpleVertex vertices[] = 
	{
		{ XMFLOAT3(-1.0f, -1.0f, -1.0f), XMFLOAT3(-1.0f, -1.0f, -1.0f), XMFLOAT2(0.0f, 1.0f) },//0
		{ XMFLOAT3(-1.0f, 1.0f, -1.0f), XMFLOAT3(-1.0f, 1.0f, -1.0f), XMFLOAT2(0.0f, 0.0f) },//1
		{ XMFLOAT3(1.0f, 1.0f, -1.0f), XMFLOAT3(1.0f, 1.0f, -1.0f), XMFLOAT2(1.0f, 0.0f) },//2
		{ XMFLOAT3(1.0f, -1.0f, -1.0f), XMFLOAT3(1.0f, -1.0f, -1.0f), XMFLOAT2(1.0f, 1.0f) },//3
	};

	D3D11_BUFFER_DESC bd;

	ID3D11Buffer* vertexBuffer;

	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(SimpleVertex) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));

	InitData.pSysMem = vertexBuffer;

	fullScreenQuad.vertexBuffer = vertexBuffer;

	_pd3dDevice->CreateBuffer(&bd, &InitData, &vertexBuffer);

	WORD indices[] = {
		0, 1, 2,
		0, 2, 3,
	};

	ID3D11Buffer* indexBuffer;

	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(WORD) * 2 * 3;
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = 0;

	InitData.pSysMem = indexBuffer;

	fullScreenQuad.indexBuffer = indexBuffer;
	fullScreenQuad.numberOfIndices = 2 * 3;

	_pd3dDevice->CreateBuffer(&bd, &InitData, &indexBuffer);

	fullScreenQuad.vertexBufferOffset = 0;
	fullScreenQuad.vertexBufferStride = sizeof(SimpleVertex);

	return fullScreenQuad;
}
