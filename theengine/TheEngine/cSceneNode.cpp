#include "cSceneNode.h"

cSceneNode::cSceneNode(std::string name, std::string message) {
	m_name = name;
	m_message = message;
	m_shouldUpdate = true;
}

cSceneNode::~cSceneNode()
{
	if (m_childrenNodes.size() != 0)
	{
		for (std::vector<cSceneNode*>::iterator it = m_childrenNodes.begin(); it != m_childrenNodes.end(); ++it)//loop through all the children of this node and delete them
		{
			delete(*it);
		}
	}
}

bool cSceneNode::shouldUpdate()
{
	return m_shouldUpdate;
}

void cSceneNode::addChild(cSceneNode* Child)	//set the parent of the child to this SceneNode and add the Child to the list of children
{
	Child->setParent(this);
	m_childrenNodes.push_back(Child);
}

/*void SceneNode::GetMessage()const
{
printf(m_message.c_str());
printf("\n");
}*/

cSceneNode* cSceneNode::getParent() const
{
	return m_parent;
}

std::string cSceneNode::getName() const
{
	return m_name;
}

void cSceneNode::render()
{
}

void cSceneNode::renderChildren()
{}

void cSceneNode::Update(float dt)
{}

void cSceneNode::GetWorldMatrix(glm::mat4& matModel)
{}

void cSceneNode::setWireframe(bool bWireframe)
{}

void cSceneNode::setUseLighting(bool bUseLighting)
{}

void cSceneNode::setParent(cSceneNode* parent)
{
	m_parent = parent;
}

std::vector<cSceneNode*> & cSceneNode::getChildren()
{
	return m_childrenNodes;
}

//void cSceneNode::setPosition(glm::vec3 Vector)
//{
//	setPosition(Vector[0], Vector[1], Vector[2]);
//}
//
//void SceneNode::SetPosition(float x, float y, float z)
//{
//	m_transformation[0][3] = x;
//	m_transformation[1][3] = y;
//	m_transformation[2][3] = z;
//}
//
//void SceneNode::SetRotation(GLfloat angle, float x, float y, float z)
//{
//	if (x <= 1)
//		m_transformation[3][0] = angle;
//	if (y <= 1)
//		m_transformation[3][1] = angle;
//	if (z <= 1)
//		m_transformation[3][2] = angle;
//}
//
//void SceneNode::Rotate(GLfloat angle, float x, float y, float z)
//{
//	if (x <= 1)
//		m_transformation[3][0] += angle;
//	if (y <= 1)
//		m_transformation[3][1] += angle;
//	if (z <= 1)
//		m_transformation[3][2] += angle;
//}