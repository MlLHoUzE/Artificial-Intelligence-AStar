#include "cSceneGraph.h"

cSceneGraph* cSceneGraph::m_pTheOneGraph = 0;

cSceneGraph::cSceneGraph()
{
	m_root = new cSceneNode("Root", "This is the Root");
}

cSceneGraph::~cSceneGraph()
{
	if (m_root)
	{
		delete m_root;
	}
}

cSceneGraph* cSceneGraph::getInstance(void)
{
	if (cSceneGraph::m_pTheOneGraph == 0)
	{
		cSceneGraph::m_pTheOneGraph = new cSceneGraph();
	}
	return cSceneGraph::m_pTheOneGraph;
}

void cSceneGraph::shutDown(void)
{
	if (cSceneGraph::m_pTheOneGraph != 0)
	{
		delete cSceneGraph::m_pTheOneGraph;
	}
	return;
}

void cSceneGraph::draw(cSceneNode* node)
{
	if (node->getChildren().size() != 0)
	{
		for (std::vector<cSceneNode*>::iterator it = node->getChildren().begin(); it != node->getChildren().end(); ++it)
		{
			
			(*it)->render();

			if ((*it)->getChildren().size())
			{
				draw(*it);
			}
		}
	}
}

void cSceneGraph::setWireframe(bool bWireframe, cSceneNode* node)
{
	if (node->getChildren().size() != 0)
	{
		for (std::vector<cSceneNode*>::iterator it = node->getChildren().begin(); it != node->getChildren().end(); ++it)
		{
			(*it)->setWireframe(bWireframe);

			if ((*it)->getChildren().size())
			{
				setWireframe(bWireframe, (*it));
			}
		}
	}
}

void cSceneGraph::setUseLighting(bool bUseLighting, cSceneNode* node)
{
	if (node->getChildren().size() != 0)
	{
		for (std::vector<cSceneNode*>::iterator it = node->getChildren().begin(); it != node->getChildren().end(); ++it)
		{
			(*it)->setUseLighting(bUseLighting);

			if ((*it)->getChildren().size())
			{
				setUseLighting(bUseLighting, (*it));
			}
		}
	}
}

void cSceneGraph::updateObjects(cSceneNode* node, float dt)
{
	if (node->getChildren().size() != 0)
	{
		for (std::vector<cSceneNode*>::iterator it = node->getChildren().begin(); it != node->getChildren().end(); ++it)
		{
			if ((*it)->shouldUpdate())
			{
				(*it)->Update(dt);
			}

			if ((*it)->getChildren().size())
			{
				updateObjects(*it, dt);
			}
		}
	}
}

void cSceneGraph::addSceneNode(cSceneNode* node)
{
	m_root->addChild(node);
}

cSceneNode* cSceneGraph::getRoot()
{
	return m_root;
}
