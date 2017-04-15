#include "cAStarManager.h"
#include "sAStarHelper.h"
#include <iostream>

cAStarManager* cAStarManager::m_pTheOneManager = 0;

cAStarManager::~cAStarManager()
{
	Clear();
}

cAStarManager::cAStarManager()
{

}
cAStarManager* cAStarManager::GetInstance()
{
	if (m_pTheOneManager == 0)
	{
		return new cAStarManager();
	}
	return m_pTheOneManager;
}

void cAStarManager::shutDown(void)
{
	if (cAStarManager::m_pTheOneManager != 0)
	{
		delete cAStarManager::m_pTheOneManager;
	}
	return;
}

void cAStarManager::SetNodes(std::vector<std::vector<cPathNode*>> nodes)
{
	m_vecNodes = nodes;

	for (int idxRow = 0; idxRow < 20 - 1; idxRow++)
	{
		for (int idxCol = 0; idxCol < 20 - 1; idxCol++)
		{
			// grab dem nodes
			cPathNode* node = m_vecNodes[idxRow][idxCol];				// node
			cPathNode* neighbourEast = m_vecNodes[idxRow][idxCol + 1];	// east (right) neighbour
			cPathNode* neighbourSouth = m_vecNodes[idxRow + 1][idxCol];	// south (down) neighbour
																	// make the connections
			cPathConnection* connectEW = new cPathConnection(node, neighbourEast);
			cPathConnection* connectNS = new cPathConnection(node, neighbourSouth);
			// add the connections
			m_vecConnections.push_back(connectEW);
			m_vecConnections.push_back(connectNS);
			// let the nodes know about their connections
			node->Connections.push_back(connectEW);
			neighbourEast->Connections.push_back(connectEW);
			node->Connections.push_back(connectNS);
			neighbourSouth->Connections.push_back(connectNS);
		}
	}
}

void cAStarManager::Clear()
{
	std::vector<std::vector<cPathNode*>>::iterator itRow = m_vecNodes.begin();
	while (itRow != m_vecNodes.end())
	{
		std::vector<cPathNode*>::iterator itNode = itRow->begin();
		while (itNode != itRow->end())
		{
			delete (*itNode);
			itNode++;
		}
		itRow->clear();
		itRow++;
	}
	m_vecNodes.clear();
	std::vector<cPathConnection*>::iterator itConnection = m_vecConnections.begin();
	while (itConnection != m_vecConnections.end())
	{
		delete (*itConnection);
		itConnection++;
	}
	m_vecConnections.clear();
}

float cAStarManager::ManhattanDistance(cPathNode* nodeA, cPathNode* nodeB)
{
	glm::vec3 sep = nodeA->Position - nodeB->Position;
	return abs(sep.x) + abs(sep.y) + abs(sep.z);
}

bool cAStarManager::GetPath(int rowStart, int colStart, int rowFin, int colFin, std::vector<cPathNode*>& path)
{
	path.resize(0);
	std::vector<std::vector<sAStarHelper*>> helpers;

	unsigned int numRows = 20;
	unsigned int numCols = 20;

	//initialize helpers
	for (unsigned int rowIndex = 0; rowIndex < numRows; rowIndex++)
	{
		helpers.push_back(std::vector<sAStarHelper*>());
		for (unsigned int colIndex = 0; colIndex < numCols; colIndex++)
		{
			sAStarHelper* helper = new sAStarHelper();
			helper->row = rowIndex;
			helper->col = colIndex;
			helper->Node = m_vecNodes[rowIndex][colIndex];
			helper->Parent = 0;
			helper->fScore = FLT_MAX;
			helper->gScore = FLT_MAX;
			helpers[rowIndex].push_back(helper);
		}
	}

	cPathNode* startNode = m_vecNodes[rowStart][colStart];
	cPathNode* endNode = m_vecNodes[rowFin][colFin];

	std::vector<sAStarHelper*> closedSet;
	std::vector<sAStarHelper*> openSet;

	//set up open set
	openSet.push_back(helpers[rowStart][colStart]);
	helpers[rowStart][colStart]->gScore = 0.f;
	helpers[rowStart][colStart]->fScore = helpers[rowStart][colStart]->gScore + ManhattanDistance(startNode, endNode);

	sAStarHelper* current;

	while (!openSet.empty())
	{	//find node with lowest fScore
		current = 0;
		float bestF = FLT_MAX;
		unsigned int openSetSize = openSet.size();
		unsigned int idxOpenBestF = 0;

		for (unsigned int idx = 0; idx < openSetSize; idx++)
		{
			if (openSet[idx]->fScore < bestF)
			{
				bestF = openSet[idx]->fScore;
				current = openSet[idx];
				idxOpenBestF = idx;
			}
		}

		if (current == 0)return false;

		if (current->Node == endNode)	//we are at the final node
		{
			std::cout << "Final Path: " << std::endl;
			std::cout << current->Node->TravelCostFactor << std::endl;// << " " << current->col << std::endl;
			if (current->Node->TravelCostFactor == 100)
			{
				bool sexybreakPoint = true;
			}
			path.push_back(current->Node);
			sAStarHelper* parent = current->Parent;
			while (parent != 0)
			{
			std::cout << parent->Node->TravelCostFactor << std::endl; //parent->row << " " << parent->col << std::endl;
			if (parent->Node->TravelCostFactor == 100)
			{
				bool sexybreakPoint = true;
			}
			path.push_back(parent->Node);
			parent = parent->Parent;
			}
			openSet.clear();
			break;
		}
		else
		{
			//add to closed set
			closedSet.push_back(current);
			//remove from openset
			openSet.erase(openSet.begin() + idxOpenBestF);

			std::vector<cPathConnection*>::iterator itPath = current->Node->Connections.begin();
			while (itPath != current->Node->Connections.end())
			{
				cPathNode* neighbourNode = (*itPath)->GetOther(current->Node);
				sAStarHelper* neighbourHelper = 0;
				for (unsigned int idxRow = 0; idxRow < numRows && !neighbourHelper; idxRow++)
				{
					for (unsigned int idxCol = 0; idxCol < numCols && !neighbourHelper; idxCol++)
					{
						if (neighbourNode == helpers[idxRow][idxCol]->Node)
						{
							neighbourHelper = helpers[idxRow][idxCol];
						}
					}
				}

				//is this node in closed set
				if (std::find(closedSet.begin(), closedSet.end(), neighbourHelper) != closedSet.end())
				{
					itPath++;
					continue;	//ignore the neighbour which has already been evaluated
				}

				float tempGScore = current->gScore + (*itPath)->Distance * neighbourNode->TravelCostFactor;

				//if not in openSet already
				if (std::find(openSet.begin(), openSet.end(), neighbourHelper) == openSet.end())
				{
					openSet.push_back(neighbourHelper);
				}
				else if (tempGScore >= neighbourHelper->gScore)
				{
					itPath++;
					continue;	//this is not a better path
				}

				neighbourHelper->Parent = current;
				neighbourHelper->gScore = tempGScore;
				neighbourHelper->fScore = neighbourHelper->gScore + ManhattanDistance(neighbourNode, endNode);

				itPath++;
			}
		}

	}

	for (unsigned int idxRow = 0; idxRow < numRows; idxRow++)
	{
		for (unsigned int idxCol = 0; idxCol < numCols; idxCol++)
		{
			delete helpers[idxRow][idxCol];
		}
	}

	return !path.empty();
}

void cAStarManager::GetNode(glm::vec3 position, int* row, int* col)
{
	for (int idxRow = 0; idxRow < m_vecNodes[0].size(); idxRow++)
	{
		for (int idxCol = 0; idxCol < m_vecNodes.size(); idxCol++)
		{
			glm::vec3 tempPos = m_vecNodes[idxRow][idxCol]->Position;
			float minX = tempPos.x - m_vecNodes[idxRow][idxCol]->Radius;
			float maxX = tempPos.x + m_vecNodes[idxRow][idxCol]->Radius;
			float minZ = tempPos.z - m_vecNodes[idxRow][idxCol]->Radius;
			float maxZ = tempPos.z + m_vecNodes[idxRow][idxCol]->Radius;

			if (position.x > minX && position.x < maxX)
			{
				if (position.z > minZ && position.z < maxZ)
				{
					*row = idxRow;
					*col = idxCol;
					return;
				}
			}
		}
	}
}

void cAStarManager::GetNodeByCoordinates(int row, int col, cPathNode* node)
{
	
	*node = *m_vecNodes[row][col];
	return;
				
}