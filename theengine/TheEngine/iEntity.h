#ifndef _iEntity_HG_
#define _iEntity_HG_


//#include "cMeshTypeManager.h"
#include "iMediator.h"
#include "sMeshEntry.h"
#include "sPhysicsInfo.h"
#include <glm\mat4x4.hpp>



class iEntity : public cSceneNode
{
public:

	enum eEntityState
	{
		STATE_FLEE,
		STATE_SEEK,
		STATE_ARRIVE
	};

	virtual ~iEntity() {};

	virtual void SetMediator(iMediator* pMediator) = 0;
	virtual void GetPhysicsInfo(sPhysicsInfo& physicsInfo) = 0;
	virtual void SetPhysicsInfo(sPhysicsInfo physicsInfo) = 0;
	virtual void SetPosition(glm::vec3& position, glm::quat orientation) = 0;
	virtual void SetMeshEntry(int NumIndices, int BaseIndex, int BaseVertex) = 0;
	virtual void SetRenderingInfo(sRenderingInfo renderingInfo) = 0;
	virtual void GetRenderingInfo(sRenderingInfo& renderingInfo) = 0;
	//virtual void GetModelMatrix(glm::mat4& modelMatrix) = 0;
	virtual int GetID() = 0;
	virtual void GetColor(glm::vec4& color) = 0;
	virtual void GetMeshEntry(sMeshEntry& meshEntry) = 0;
	virtual void SetID(int ID) = 0;
	virtual void Scale(float scale) = 0;
	virtual void Update(float dt) = 0;
	virtual void SetWorldMatrix(glm::mat4 matModel) = 0;
	virtual void GetWorldMatrix(glm::mat4& matModel) = 0;
	virtual void render() = 0;
	//virtual void checkState(glm::vec3 targetPosition, glm::vec3 direction) = 0;
	virtual void PreRender() = 0;
	virtual void updatePhysicsTris() = 0;
	//virtual void setSpeed(float speed) = 0;

};



#endif
