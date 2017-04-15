#ifndef _cSceneGraph_HG_
#define _cSceneGraph_HG_

#include "cSceneNode.h"

class cSceneGraph
{
public:
	~cSceneGraph();

	static cSceneGraph* getInstance(void);
	static void shutDown(void);

	void draw(cSceneNode* node);
	void updateObjects(cSceneNode* node, float dt);
	void addSceneNode(cSceneNode* node);
	void setWireframe(bool bWireFrame, cSceneNode* node);
	void setUseLighting(bool bUseLighting, cSceneNode* node);
	cSceneNode* getRoot();
private:
	cSceneNode* m_root;
	cSceneGraph();

	static cSceneGraph* m_pTheOneGraph;
};

#endif