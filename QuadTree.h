#ifndef _QUADTREE_H
#define _QUADTREE_H

#include <vector>
#include "Vector.h"
#include "Collider.h"
#include "GameObject.h"


class QuadTree
{
public:

	int MAXOBJECTS, MAXLEVELS;
	QuadTree();
	QuadTree(AABB* boundary, int level);

	~QuadTree();

	bool Insert(GameObject* gameobject);
	void Subdivide();
	std::vector<GameObject*>QueryRange(AABB* range);
	int GetIndex(GameObject* gameobject);
	std::vector<GameObject*>Retrieve(GameObject* gameobject);

	void Clear();

private:
	int _level;
	QuadTree* _nodes[4];

	AABB* _boundary;

	std::vector<GameObject*> _gameObjects;
};
#endif // !_QUADTREE_H
