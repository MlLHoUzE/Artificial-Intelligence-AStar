#include "cEntity.h"
#include "Render.h"


cEntity::cEntity()
{
	m_test = 5;
}

void cEntity::SetMediator(iMediator* pMediator)
{

}

void cEntity::GetPhysicsInfo(sPhysicsInfo& physicsInfo)
{
	physicsInfo = this->m_physicsInfo;
}

void cEntity::SetPhysicsInfo(sPhysicsInfo physicsInfo)
{
	m_physicsInfo = physicsInfo;
}

void cEntity::SetPosition(glm::vec3& position, glm::quat orientation)
{
	m_physicsInfo.position = position;
	m_physicsInfo.orientation = orientation;
}
void cEntity::SetMeshEntry(int numIndices, int baseIndex, int baseVertex)
{
	m_renderingInfo.meshEntry.numIndices = numIndices;
	m_renderingInfo.meshEntry.baseIndex = baseIndex;
	m_renderingInfo.meshEntry.baseVertex = baseVertex;
}
void cEntity::GetMeshEntry(sMeshEntry& meshEntry)
{
	meshEntry = m_renderingInfo.meshEntry;
}

void cEntity::GetRenderingInfo(sRenderingInfo& renderingInfo)
{
	renderingInfo = m_renderingInfo;
}

void cEntity::SetRenderingInfo(sRenderingInfo renderingInfo)
{
	m_renderingInfo = renderingInfo;
}

//virtual void GetModelMatrix(glm::mat4& modelMatrix);
void cEntity::SetID(int ID)
{
	m_ID = ID;
}
int cEntity::GetID()
{
	return m_ID;
}
void cEntity::GetColor(glm::vec4& color)
{
	color = m_renderingInfo.color;
}


void cEntity::Scale(float scale)
{
	m_renderingInfo.scale = scale;
}
//void cEntity::Update(float dt)
//{
//
//}
void cEntity::PreRender()
{
	if (m_physicsInfo.bIsStatic) return;
	m_renderingInfo.modelMatrix = glm::mat4_cast(m_physicsInfo.orientation);
	m_renderingInfo.modelMatrix[3] = glm::vec4(m_physicsInfo.position, 1.0f);
}

void cEntity::SetWorldMatrix(glm::mat4 matModel)
{
	this->m_worldMatrix = matModel;
}

void cEntity::GetWorldMatrix(glm::mat4& matModel)
{
	matModel = this->m_worldMatrix;
}

void cEntity::render()
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

void cEntity::Update(float dt)
{
}

void cEntity::setWireframe(bool bWireframe)
{
	this->m_renderingInfo.bIsWireframe = bWireframe;
}

void cEntity::setUseLighting(bool bUseLighting)
{
	this->m_renderingInfo.bUseDebugColors = bUseLighting;
}