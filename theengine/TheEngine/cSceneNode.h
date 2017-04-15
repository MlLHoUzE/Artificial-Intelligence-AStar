#ifndef _cSceneNode_HG_
#define _cSceneNode_HG_

#include <string>
#include <vector>
#include <glm\mat4x4.hpp>

class cSceneNode
{
public:
	cSceneNode(std::string name = "default", std::string message = "SceneNode");
	~cSceneNode();

	void addChild(cSceneNode* child);
	std::vector<cSceneNode*> & getChildren();
	cSceneNode* getParent() const;
	std::string getName() const;
	virtual void render();
	void renderChildren();
	virtual void Update(float dt);
	bool shouldUpdate();
	virtual void GetWorldMatrix(glm::mat4& matModel);
	virtual void setWireframe(bool bWireframe);
	virtual void setUseLighting(bool bUseLighting);

protected:
	void setParent(cSceneNode* parent);
	std::vector<cSceneNode*> m_childrenNodes;
	cSceneNode* m_parent;
	bool m_shouldUpdate;
	std::string m_message, m_name;
};

#endif