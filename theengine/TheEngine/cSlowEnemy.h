#ifndef _cSlowEnemy_HG_
#define _cSlowEnemy_HG_

#include "iEntity.h"
#include "sRenderingInfo.h"
#include "sPhysicsInfo.h"
#include "iMediator.h"

class cSlowEnemy : public iEntity
{
public:
	cSlowEnemy();

	virtual ~cSlowEnemy() {};

	virtual void SetMediator(iMediator* pMediator);
	virtual void GetPhysicsInfo(sPhysicsInfo& physicsInfo);
	virtual void SetPhysicsInfo(sPhysicsInfo physicsInfo);
	virtual void SetPosition(glm::vec3& position, glm::quat orientation);
	virtual void SetMeshEntry(int NumIndices, int BaseIndex, int BaseVertex);
	virtual void SetRenderingInfo(sRenderingInfo renderingInfo);
	virtual void GetRenderingInfo(sRenderingInfo& renderingInfo);
	virtual int GetID();
	virtual void GetColor(glm::vec4& color);
	virtual void GetMeshEntry(sMeshEntry& meshEntry);
	virtual void SetID(int ID);
	virtual void Scale(float scale);
	virtual void Update(float dt);
	virtual void SetWorldMatrix(glm::mat4 matModel);
	virtual void GetWorldMatrix(glm::mat4& matModel);
	virtual void render();
	virtual void PreRender();
	virtual void updatePhysicsTris();

	void setWireframe(bool bWireframe);
	void setUseLighting(bool bUseLighting);
	bool CheckStraightLine();

private:
	sPhysicsInfo m_physicsInfo;
	sRenderingInfo m_renderingInfo;
	glm::mat4 m_worldMatrix;
	int m_ID;
	iMediator* m_pMediator;

	std::vector<cPathNode*> m_path;

	float m_decisionCounter;
	int m_pathIndex;
	bool m_bDecision;

};

#endif