#ifndef _cAStarManager_HG_
#define _cAStarManager_HG_
#include "cAStarClasses.h"

class cAStarManager
{
public:
	~cAStarManager();
	static cAStarManager* GetInstance(void);
	static void shutDown(void);
	void SetNodes(std::vector<std::vector<cPathNode*>>  nodes);

	bool GetPath(int rowStart, int colStart, int rowFin, int colFin, std::vector<cPathNode*>& path);

	void GetNode(glm::vec3 position, int* row, int* col);
	void GetNodeByCoordinates(int row, int col, cPathNode* node);
private:
	cAStarManager();

	static cAStarManager* m_pTheOneManager;

	std::vector<std::vector<cPathNode*>> m_vecNodes;
	std::vector<cPathConnection*> m_vecConnections;
	float ManhattanDistance(cPathNode* nodeA, cPathNode* nodeB);

	void Clear();



};

#endif