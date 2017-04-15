#ifndef _cAStarClasses_HG_
#define _cAStarClasses_HG_

#include <glm\vec3.hpp>
#include <vector>

class cPathConnection;
class cPathNode
{
public:
	float Radius;  // used to determined if an entity is on this node
	glm::vec3 Position;

	float TravelCostFactor;
	std::vector<cPathConnection*> Connections;


	cPathNode();
	~cPathNode();
};

class cPathConnection
{
public:
	float Distance;
	float DistanceSquared;
	cPathNode* NodeA;
	cPathNode* NodeB;

	cPathConnection(cPathNode* nodeA, cPathNode* nodeB);
	~cPathConnection();

	cPathNode* GetOther(cPathNode* node);
};

#endif