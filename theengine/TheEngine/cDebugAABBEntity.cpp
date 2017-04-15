#include "cDebugAABBEntity.h"
#include "Render.h"




void cDebugAABBEntity::SetMediator(iMediator* pMediator)
{

}

void cDebugAABBEntity::GetPhysicsInfo(sPhysicsInfo& physicsInfo)
{
	physicsInfo = this->m_physicsInfo;
}

void cDebugAABBEntity::SetPhysicsInfo(sPhysicsInfo physicsInfo)
{
	m_physicsInfo = physicsInfo;
}

void cDebugAABBEntity::SetPosition(glm::vec3& position, glm::quat orientation)
{
	m_physicsInfo.position = position;
	m_physicsInfo.orientation = orientation;
	m_offset = position;
}
void cDebugAABBEntity::SetMeshEntry(int numIndices, int baseIndex, int baseVertex)
{
	m_renderingInfo.meshEntry.numIndices = numIndices;
	m_renderingInfo.meshEntry.baseIndex = baseIndex;
	m_renderingInfo.meshEntry.baseVertex = baseVertex;
}
void cDebugAABBEntity::GetMeshEntry(sMeshEntry& meshEntry)
{
	meshEntry = m_renderingInfo.meshEntry;
}

void cDebugAABBEntity::GetRenderingInfo(sRenderingInfo& renderingInfo)
{
	renderingInfo = m_renderingInfo;
}

void cDebugAABBEntity::SetRenderingInfo(sRenderingInfo renderingInfo)
{
	m_renderingInfo = renderingInfo;
}

//virtual void GetModelMatrix(glm::mat4& modelMatrix);
void cDebugAABBEntity::SetID(int ID)
{
	m_ID = ID;
}
int cDebugAABBEntity::GetID()
{
	return m_ID;
}
void cDebugAABBEntity::GetColor(glm::vec4& color)
{
	color = m_renderingInfo.color;
}


void cDebugAABBEntity::Scale(float scale)
{
	m_renderingInfo.scale = scale;
}
//void cDebugAABBEntity::Update(float dt)
//{
//
//}
void cDebugAABBEntity::PreRender()
{
	if (m_physicsInfo.bIsStatic) return;
	m_renderingInfo.modelMatrix = glm::mat4_cast(m_physicsInfo.orientation);
	m_renderingInfo.modelMatrix[3] = glm::vec4(m_physicsInfo.position, 1.0f);
}

void cDebugAABBEntity::SetWorldMatrix(glm::mat4 matModel)
{
	this->m_worldMatrix = matModel;
}

void cDebugAABBEntity::GetWorldMatrix(glm::mat4& matModel)
{
	matModel = this->m_worldMatrix;
}

void cDebugAABBEntity::render()
{
	if (!this->m_parent)
	{
		DrawObject(this, m_renderingInfo.modelMatrix);
	}
	else
	{
		glm::mat4 parentModelMat;
		this->m_parent->GetWorldMatrix(parentModelMat);
		DrawObject(this, parentModelMat);
	}
}

void cDebugAABBEntity::Update(float dt)
{
	glm::vec3 targetPos;
	g_pPlayer->GetNextPosition(targetPos, 0.f);
	//this->m_physicsInfo.position = targetPos + this->m_offset;
	//this->m_renderingInfo.scale = 10.f;
	this->m_renderingInfo.bIsWireframe = true;
	this->m_renderingInfo.bUseDebugColors = true;
}

void cDebugAABBEntity::setWireframe(bool bWireframe)
{
	this->m_renderingInfo.bIsWireframe = bWireframe;
}

void cDebugAABBEntity::setUseLighting(bool bUseLighting)
{
	this->m_renderingInfo.bUseDebugColors = bUseLighting;
}

void cDebugAABBEntity::updatePhysicsTris()
{

}