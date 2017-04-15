#ifndef _cObjectEntity_HG_
#define _cObjectEntity_HG_

#include "iEntity.h"
#include "sRenderingInfo.h"
#include "sPhysicsInfo.h"
class cObjectEntity : public iEntity
{
public:
	cObjectEntity() {};
	virtual ~cObjectEntity() {}

	virtual void SetMediator(iMediator* pMediator);

	virtual void GetPhysicsInfo(sPhysicsInfo& physicsInfo);
	virtual void SetPhysicsInfo(sPhysicsInfo physicsInfo);
	virtual void SetPosition(glm::vec3& position, glm::quat orientation);
	virtual void SetMeshEntry(int NumIndices, int BaseIndex, int BaseVertex);
	virtual void GetMeshEntry(sMeshEntry& meshEntry);
	virtual void GetRenderingInfo(sRenderingInfo& renderingInfo);
	virtual void SetRenderingInfo(sRenderingInfo renderingInfo);
	//virtual void GetModelMatrix(glm::mat4& modelMatrix);
	virtual void SetID(int ID);
	virtual int GetID();
	virtual void GetColor(glm::vec4& color);
	virtual void Scale(float scale);
	virtual void SetWorldMatrix(glm::mat4 matModel);
	virtual void GetWorldMatrix(glm::mat4& matModel);
	virtual void PreRender();
	virtual void render();

	void setWireframe(bool bWireframe);
	void setUseLighting(bool bUseLighting);

	void updatePhysicsTris();


	virtual void Update(float dt);	//will be overwritten by an "enemy" type class which will run AI

private:
	int m_ID;
	//iMediator* m_pMediator;
	sRenderingInfo m_renderingInfo;
	sPhysicsInfo m_physicsInfo;
	glm::mat4 m_worldMatrix;

	int m_test;
};

#endif
