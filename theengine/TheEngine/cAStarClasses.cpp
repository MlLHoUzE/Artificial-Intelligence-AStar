#include "cAStarClasses.h"
#include <glm\gtx\normalize_dot.hpp>
cPathNode::cPathNode() : TravelCostFactor(1.f)
{

}

cPathNode::~cPathNode()
{
	Connections.clear();
}

cPathConnection::cPathConnection(cPathNode* nodeA, cPathNode* nodeB)
	: NodeA(nodeA), NodeB(nodeB)
{
	glm::vec3 temp = NodeA->Position - NodeB->Position;
	DistanceSquared = dot(temp,temp);
	Distance = sqrt(DistanceSquared);
}

cPathConnection::~cPathConnection()
{

}

cPathNode* cPathConnection::GetOther(cPathNode* node)
{
	return (node == NodeA) ? NodeB : NodeA;
}