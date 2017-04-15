#include "cObjectEntity.h"
#include "Render.h"



void cObjectEntity::SetMediator(iMediator* pMediator)
{

}

void cObjectEntity::GetPhysicsInfo(sPhysicsInfo& physicsInfo)
{
	physicsInfo = this->m_physicsInfo;
}

void cObjectEntity::SetPhysicsInfo(sPhysicsInfo physicsInfo)
{
	m_physicsInfo = physicsInfo;
}

void cObjectEntity::SetPosition(glm::vec3& position, glm::quat orientation)
{
	m_physicsInfo.position = position;
	m_physicsInfo.orientation = orientation;
}
void cObjectEntity::SetMeshEntry(int numIndices, int baseIndex, int baseVertex)
{
	m_renderingInfo.meshEntry.numIndices = numIndices;
	m_renderingInfo.meshEntry.baseIndex = baseIndex;
	m_renderingInfo.meshEntry.baseVertex = baseVertex;
}
void cObjectEntity::GetMeshEntry(sMeshEntry& meshEntry)
{
	meshEntry = m_renderingInfo.meshEntry;
}

void cObjectEntity::GetRenderingInfo(sRenderingInfo& renderingInfo)
{
	renderingInfo = m_renderingInfo;
}

void cObjectEntity::SetRenderingInfo(sRenderingInfo renderingInfo)
{
	m_renderingInfo = renderingInfo;
}

//virtual void GetModelMatrix(glm::mat4& modelMatrix);
void cObjectEntity::SetID(int ID)
{
	m_ID = ID;
}
int cObjectEntity::GetID()
{
	return m_ID;
}
void cObjectEntity::GetColor(glm::vec4& color)
{
	color = m_renderingInfo.color;
}


void cObjectEntity::Scale(float scale)
{
	m_renderingInfo.scale = scale;
}
//void cObjectEntity::Update(float dt)
//{
//
//}
void cObjectEntity::PreRender()
{
	//if (m_physicsInfo.bIsStatic) return;
	m_renderingInfo.modelMatrix = glm::mat4_cast(m_physicsInfo.orientation);
	m_renderingInfo.modelMatrix[3] = glm::vec4(m_physicsInfo.position, 1.0f);
}

void cObjectEntity::SetWorldMatrix(glm::mat4 matModel)
{
	this->m_worldMatrix = matModel;
}

void cObjectEntity::GetWorldMatrix(glm::mat4& matModel)
{
	matModel = this->m_worldMatrix;
}

void cObjectEntity::render()
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

void cObjectEntity::Update(float dt)
{

}

void cObjectEntity::setWireframe(bool bWireframe)
{
	this->m_renderingInfo.bIsWireframe = bWireframe;
}

void cObjectEntity::setUseLighting(bool bUseLighting)
{
	this->m_renderingInfo.bUseDebugColors = bUseLighting;
}

void cObjectEntity::updatePhysicsTris()
{
	std::vector<sTriangle> tris;
	g_pMeshManager->GetEnvironmentalTriangles(tris);

	PreRender();

	sTriangle temp;
	for (int i = 0; i < tris.size(); i++)
	{
		temp.v1 = m_renderingInfo.modelMatrix * glm::vec4(tris[i].v1, 1.f);
		temp.v2 = m_renderingInfo.modelMatrix * glm::vec4(tris[i].v2, 1.f);
		temp.v3 = m_renderingInfo.modelMatrix * glm::vec4(tris[i].v3, 1.f);
		this->m_physicsInfo.physicsTris.push_back(temp);
	}
	
}