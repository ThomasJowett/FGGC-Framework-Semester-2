#ifndef _GEOMETRYGENERATOR_H
#define _GEOMETRYGENERATOR_H

#include <vector>
#include "Commons.h"

class GeometryGenerator
{
public:
	GeometryGenerator();
	~GeometryGenerator();

	static MeshData CreateCube(float width, float height, float depth, ID3D11Device* _pd3dDevice);

	static MeshData CreateSphere(float radius, UINT longitudeLines, UINT latitudeLines, ID3D11Device * _pd3dDevice);

	static MeshData CreateGeosphere(float radius, UINT numSubdivisions);

	static MeshData CreateCylinder(float bottomRadius, float topRadius, float hieght, UINT sliceCount, UINT stackCount);

	static MeshData CreateGrid(float width, float length, UINT widthLines, UINT lengthLines, float tileU, float tileV, ID3D11Device* _pd3dDevice);

	static MeshData CreateFullscreenQuad(ID3D11Device * _pd3dDevice);

	void SubdivideMesh(MeshData& meshData);

private:
	void BuildCylinderTopCap(float bottomRadius, float topRadius, float height, UINT sliceCount, UINT stackCount, MeshData& meshData);
	void BuildCylinderBottomCap(float bottomRadius, float topRadius, float height, UINT sliceCount, UINT stackCount, MeshData& meshData);
};

#endif // !_GEOMETRYGENERATOR_H