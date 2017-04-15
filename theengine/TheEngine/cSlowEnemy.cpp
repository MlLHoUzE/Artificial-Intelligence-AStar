#include "cSlowEnemy.h"
#include "Render.h"
#include "Globals.h"
#include <iostream>
cSlowEnemy::cSlowEnemy()
{
	m_physicsInfo.speed = 2.f;
	m_decisionCounter = 30.f;
	m_pathIndex = 0;

	cPathNode* node = new cPathNode();
	node->TravelCostFactor = 0;
	int randX, randZ;
	while (node->TravelCostFactor != 1)
	{
		randX = rand() % 20;
		randZ = rand() % 20;
		g_pAStarManager->GetNodeByCoordinates(randX, randZ, node);
	}

	m_physicsInfo.position = node->Position;
}

void cSlowEnemy::SetMediator(iMediator* pMediator)
{
	m_pMediator = pMediator;
}

void cSlowEnemy::GetPhysicsInfo(sPhysicsInfo& physicsInfo)
{
	physicsInfo = this->m_physicsInfo;
}

void cSlowEnemy::SetPhysicsInfo(sPhysicsInfo physicsInfo)
{
	m_physicsInfo = physicsInfo;
}

void cSlowEnemy::SetPosition(glm::vec3& position, glm::quat orientation)
{
	m_physicsInfo.position = position;
	m_physicsInfo.orientation = orientation;
}
void cSlowEnemy::SetMeshEntry(int numIndices, int baseIndex, int baseVertex)
{
	m_renderingInfo.meshEntry.numIndices = numIndices;
	m_renderingInfo.meshEntry.baseIndex = baseIndex;
	m_renderingInfo.meshEntry.baseVertex = baseVertex;
}
void cSlowEnemy::GetMeshEntry(sMeshEntry& meshEntry)
{
	meshEntry = m_renderingInfo.meshEntry;
}

void cSlowEnemy::GetRenderingInfo(sRenderingInfo& renderingInfo)
{
	renderingInfo = m_renderingInfo;
}

void cSlowEnemy::SetRenderingInfo(sRenderingInfo renderingInfo)
{
	m_renderingInfo = renderingInfo;
}

//virtual void GetModelMatrix(glm::mat4& modelMatrix);
void cSlowEnemy::SetID(int ID)
{
	m_ID = ID;
}
int cSlowEnemy::GetID()
{
	return m_ID;
}
void cSlowEnemy::GetColor(glm::vec4& color)
{
	color = m_renderingInfo.color;
}


void cSlowEnemy::Scale(float scale)
{
	m_renderingInfo.scale = scale;
}
//void cSlowEnemy::Update(float dt)
//{
//
//}
void cSlowEnemy::PreRender()
{
	if (m_physicsInfo.bIsStatic) return;
	m_renderingInfo.modelMatrix = glm::mat4_cast(m_physicsInfo.orientation);
	m_renderingInfo.modelMatrix[3] = glm::vec4(m_physicsInfo.position, 1.0f);
}

void cSlowEnemy::SetWorldMatrix(glm::mat4 matModel)
{
	this->m_worldMatrix = matModel;
}

void cSlowEnemy::GetWorldMatrix(glm::mat4& matModel)
{
	matModel = this->m_worldMatrix;
}

void cSlowEnemy::render()
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

bool cSlowEnemy::CheckStraightLine()
{
	glm::vec3 pos1;
	glm::vec3 pos2;
	if (m_path.empty()) return false;
	if (m_path.size() == 1)return true;
	pos1 = m_path[0]->Position;
	pos2 = m_path[1]->Position;

	//check all x's
	int counter = 1;
	while (fabs(pos1.x - pos2.x) == 0)
	{
		counter++;
		if (counter + 1 > m_path.size())return true;
		pos1 = pos2;
		pos2 = m_path[counter]->Position;
	}
	pos1 = m_path[0]->Position;
	pos2 = m_path[1]->Position;
	while (fabs(pos1.z - pos2.z) == 0)
	{
		counter++;
		if (counter + 1 > m_path.size())return true;
		pos1 = pos2;
		pos2 = m_path[counter]->Position;
	}
	return false;
}

void cSlowEnemy::Update(float dt)
{
	glm::vec3 myForward = m_physicsInfo.orientation * glm::vec3(0.f, 0.f, 1.f);
	glm::vec3 targetPos;
	if (!m_path.empty())
		targetPos = m_path.back()->Position;
	glm::vec3 rotationAxis;
	float yAxisValue;
	glm::vec3 targetDirection;
	glm::vec3 myPos;

	int row = 0;
	int col = 0;
	g_pAStarManager->GetNode(m_physicsInfo.position, &row, &col);
	glm::vec3 playerPos;
	m_pMediator->getPlayerPosition(playerPos);
	int playerRow = 0;
	int playerCol = 0;
	g_pAStarManager->GetNode(playerPos, &playerRow, &playerCol);
	m_decisionCounter += dt;

	if (fabs((m_physicsInfo.position.x - targetPos.x)) < 0.5f && fabs(m_physicsInfo.position.z - targetPos.z) < 0.5f)
	{
		cPathNode* myNode = new cPathNode();;
		g_pAStarManager->GetNodeByCoordinates(row, col, myNode);
		cPathNode* playerNode = new cPathNode();
		g_pAStarManager->GetNodeByCoordinates(playerRow, playerCol, playerNode);
		if (myNode->Position == playerNode->Position)
		{
			std::cout << "You Lose" << std::endl;
			return;
		}
		if (m_path.size() != 1)
		m_path.pop_back();
		targetPos = m_path.back()->Position;
		
	}
	targetDirection = glm::normalize(m_physicsInfo.position - targetPos);
	if (m_decisionCounter > 2.0f)
	{
		//make decision
		m_pathIndex = 0;


		if (g_pAStarManager->GetPath(row, col, playerRow, playerCol, m_path))
		{
			if (m_path.size() != 1)
			m_path.pop_back();
			targetPos = m_path.back()->Position;
		}
		targetDirection = glm::normalize(m_physicsInfo.position - targetPos);
		m_decisionCounter = 0;
		m_bDecision = true;
	}

	if (m_bDecision && CheckStraightLine())
	{
		m_physicsInfo.speed = 4.5f;
		m_bDecision = false;
	}
	else if (rand() % 101 < 20 && m_bDecision)
	{
		m_pathIndex = 0;
		cPathNode* node = new cPathNode();
		node->TravelCostFactor = 0;
		int randX, randZ;
		while (node->TravelCostFactor != 1)
		{
			randX = rand() % 20;
			randZ = rand() % 20;
			g_pAStarManager->GetNodeByCoordinates(randX, randZ, node);
		}

		if (g_pAStarManager->GetPath(row, col, randX, randZ, m_path))
		{
			if (m_path.size() != 1)
			m_path.pop_back();
			targetPos = m_path.back()->Position;
		}
		targetDirection = glm::normalize(m_physicsInfo.position - targetPos);
		m_physicsInfo.speed = 2.5f;
		m_bDecision = false;
	}

	


	//we have a stright line to player
	rotationAxis = glm::cross(myForward, targetDirection);
	yAxisValue = rotationAxis.y > 0.f ? -1.f : 1.f;

	m_physicsInfo.velocity = targetDirection * -m_physicsInfo.speed;

	m_physicsInfo.position = m_physicsInfo.position + m_physicsInfo.velocity * dt;

	rotationAxis = glm::vec3(0.f, yAxisValue, 0.f);

	float rotationVelocity = 5.f * glm::abs(rotationAxis.y);
	float rotation = rotationVelocity * dt;

	//m_physicsInfo.orientation = glm::rotate(m_physicsInfo.orientation, rotation, rotationAxis);





}

void cSlowEnemy::setWireframe(bool bWireframe)
{
	this->m_renderingInfo.bIsWireframe = bWireframe;
}

void cSlowEnemy::setUseLighting(bool bUseLighting)
{
	this->m_renderingInfo.bUseDebugColors = bUseLighting;
}

void cSlowEnemy::updatePhysicsTris()
{}