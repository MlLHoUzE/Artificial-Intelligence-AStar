#include "cPlayer.h"
#include "Input.h"
#include "Render.h"
#include <iostream>
#include "Utilities.h"
cPlayer* cPlayer::m_pTheOnePlayer = 0;

cPlayer::cPlayer()
{
	this->m_physicsInfo.speed = 50.f;
	this->m_physicsInfo.angularSpeed = 5.f;
	
}


void cPlayer::Init()
{
	createAABBs();
	g_pMeshManager->GetPlayerTriangles(m_vecMyTriangles);

	for (int i = 0; i != m_pVecAABBs.size(); i++)
	{
		for (int j = 0; j != m_vecMyTriangles.size(); j++)
		{
			m_pVecAABBs[i]->AddChildAABBFromTriangle(m_vecMyTriangles[j], m_vecMyTriangles[j]);
		}
	}
}

cPlayer* cPlayer::getInstance(void)
{
	if (cPlayer::m_pTheOnePlayer == 0)
	{
		cPlayer::m_pTheOnePlayer = new cPlayer();
	}
	return cPlayer::m_pTheOnePlayer;
}

void cPlayer::shutDown(void)
{
	if (cPlayer::m_pTheOnePlayer != 0)
	{
		delete cPlayer::m_pTheOnePlayer;
	}
	return;
}

void cPlayer::GetNextPosition(glm::vec3& position, float distance)
{
	position = m_physicsInfo.position + m_physicsInfo.velocity * distance;
}

void cPlayer::SetPhysicsInfo(sPhysicsInfo physicsInfo)
{
	m_physicsInfo = physicsInfo;
}

void cPlayer::SetRenderingInfo(sRenderingInfo renderingInfo)
{
	m_renderingInfo = renderingInfo;
}

void cPlayer::GetPhysicsInfo(sPhysicsInfo& physicsInfo)
{
	physicsInfo = m_physicsInfo;
}
void cPlayer::GetRenderingInfo(sRenderingInfo& renderingInfo)
{
	renderingInfo = m_renderingInfo;
}

void cPlayer::Update(float dt)
{
	
	bool pressW = nInput::IsKeyPressed::W();
	bool pressS = nInput::IsKeyPressed::S();
	bool pressA = nInput::IsKeyPressed::A();
	bool pressD = nInput::IsKeyPressed::D();
	bool pressQ = nInput::IsKeyPressed::Q();
	bool pressE = nInput::IsKeyPressed::E();

	
	//camera controls:
	//up/down = zoom in/zoom out
	//left/right = pan left/pan right
	glm::vec3 up(0.f, 1.f, 0.f);
	glm::vec3 forward(0.f, 0.f, 1.f);
	forward = m_physicsInfo.orientation * forward;
	float linearSpeed = 0;
	float linearSpeedUp = 0;
	float angularSpeed = m_physicsInfo.angularSpeed;
	//m_physicsInfo.velocity = glm::vec3(0.f, 0.f, 0.f);
	//movement controls:
	// w/s = forward / backward
	if (pressW != pressS)
	{
		linearSpeed = pressW ? m_physicsInfo.speed : -m_physicsInfo.speed;

		//m_transform = glm::translate(m_transform, glm::vec3(0.0f, 0.0f, linearSpeed * dt));
		//SetPosition(glm::vec3(linearSpeed, 0.f, 0.f));
		m_physicsInfo.velocity = forward * linearSpeed;
		
	}
	//m_physicsInfo.acceleration += forward * linearSpeed;
	/*if (physicsInfo.position.x < gAreaInfo->Min.x)
	{
		physicsInfo.position.x = gAreaInfo->Max.x;
	}
	else if (physicsInfo.position.x > gAreaInfo->Max.x)
	{
		physicsInfo.position.x = gAreaInfo->Min.x;
	}

	if (physicsInfo.position.z < gAreaInfo->Min.z)
	{
		physicsInfo.position.z = gAreaInfo->Max.z;
	}
	else if (physicsInfo.position.z > gAreaInfo->Max.z)
	{
		physicsInfo.position.z = gAreaInfo->Min.z;
	}*/

	if (pressA != pressD)
	{
		if (pressD) angularSpeed *= -1.f;
		m_physicsInfo.orientation = glm::rotate(m_physicsInfo.orientation, angularSpeed * dt, up);
		//m_transform = glm::rotate(m_transform, angularSpeed*dt, glm::vec3(0.f, 1.f, 0.f));
	}

	//if (pressQ != pressE)
	//{
	//	linearSpeedUp = pressQ ? m_physicsInfo.speed : -m_physicsInfo.speed;
	//	//m_transform = glm::rotate(m_transform, angularSpeed*dt, glm::vec3(0.f, 1.f, 0.f));
	//	m_physicsInfo.velocity += up * linearSpeedUp;
	//}
	//m_physicsInfo.acceleration += up * linearSpeedUp;



	//m_physicsInfo.velocity += m_physicsInfo.acceleration * dt;
	if (m_physicsInfo.velocity.x > 15.f)
		m_physicsInfo.velocity.x = 15.f;
	if (m_physicsInfo.velocity.y > 15.f)
		m_physicsInfo.velocity.y = 15.f;
	if (m_physicsInfo.velocity.z > 15.f)
		m_physicsInfo.velocity.z = 15.f;

	

	m_physicsInfo.lastPosition = m_physicsInfo.position;
	m_physicsInfo.position = m_physicsInfo.position + (m_physicsInfo.velocity * dt);


	if (m_physicsInfo.position.x < m_goalPos.x + 5 && m_physicsInfo.position.x > m_goalPos.x - 5)
	{
		if (m_physicsInfo.position.z < m_goalPos.z + 5 && m_physicsInfo.position.z > m_goalPos.z - 5)
		{
			std::cout << "Win" << std::endl;
			g_bWin = true;
		}
	}
	
	//m_physicsInfo.velocity = glm::vec3(0.f, 0.f, 0.f);

}

void cPlayer::SetGoal(glm::vec3 position)
{
	m_goalPos = position;
}

void cPlayer::render()
{
	if (!this->getParent())
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

void cPlayer::SetWorldMatrix(glm::mat4 matModel)
{
	this->m_worldMatrix = matModel;
}

void cPlayer::GetWorldMatrix(glm::mat4& matModel)
{
	matModel = this->m_worldMatrix;
}

void cPlayer::PreRender()
{
	if (m_physicsInfo.bIsStatic) return;
	m_renderingInfo.modelMatrix = glm::mat4_cast(m_physicsInfo.orientation);
	m_renderingInfo.modelMatrix[3] = glm::vec4(m_physicsInfo.position, 1.f);
}

void cPlayer::setWireframe(bool bWireframe)
{
	this->m_renderingInfo.bIsWireframe = bWireframe;
}

void cPlayer::setUseLighting(bool bUseLighting)
{
	this->m_renderingInfo.bUseDebugColors = bUseLighting;
}

void cPlayer::createAABBs()
{
	glm::vec3 floorxyz;
	//front left
	CAABB* temp = new CAABB();
	temp->boxWidth = 1.5f;
	temp->minXYZ = glm::vec3(2.1f, -1.5f, 2.f);
	temp->UpdateMaxFromMinAndWidth();
	temp->smallestChildBoxWidth = 2.f;
	floorxyz = glm::vec3(floor(temp->minXYZ.x / temp->boxWidth) * temp->boxWidth, floor(temp->minXYZ.y / temp->boxWidth) * temp->boxWidth, floor(temp->minXYZ.z / temp->boxWidth) * temp->boxWidth);
	temp->ID = temp->CalculateIDFull(floorxyz, temp->boxWidth);

	this->m_pVecAABBs.push_back(temp);

	//front right
	CAABB* temp2 = new CAABB();
	temp2->boxWidth = 1.5f;
	temp2->minXYZ = glm::vec3(-3.6f, -1.5f, 2.f);
	temp2->UpdateMaxFromMinAndWidth();
	temp2->smallestChildBoxWidth = 2.f;
	floorxyz = glm::vec3(floor(temp2->minXYZ.x / temp2->boxWidth) * temp2->boxWidth, floor(temp2->minXYZ.y / temp2->boxWidth) * temp2->boxWidth, floor(temp2->minXYZ.z / temp2->boxWidth) * temp2->boxWidth);

	temp2->ID = temp->CalculateIDFull(floorxyz, temp2->boxWidth);

	this->m_pVecAABBs.push_back(temp2);

	//back left
	CAABB* temp3 = new CAABB();
	temp3->boxWidth = 1.5f;
	temp3->minXYZ = glm::vec3(2.1f, -1.5f, -5.f);
	temp3->UpdateMaxFromMinAndWidth();
	temp3->smallestChildBoxWidth = 2.f;
	floorxyz = glm::vec3(floor(temp3->minXYZ.x / temp3->boxWidth) * temp3->boxWidth, floor(temp3->minXYZ.y / temp3->boxWidth) * temp3->boxWidth, floor(temp3->minXYZ.z / temp3->boxWidth) * temp3->boxWidth);

	temp3->ID = temp->CalculateIDFull(floorxyz, temp3->boxWidth);

	this->m_pVecAABBs.push_back(temp3);

	//back right
	CAABB* temp4 = new CAABB();
	temp4->boxWidth = 1.5f;
	temp4->minXYZ = glm::vec3(-3.6f, -1.5f, -5.f);
	temp4->UpdateMaxFromMinAndWidth();
	temp4->smallestChildBoxWidth = 2.f;
	floorxyz = glm::vec3(floor(temp4->minXYZ.x / temp4->boxWidth) * temp4->boxWidth, floor(temp4->minXYZ.y / temp4->boxWidth) * temp4->boxWidth, floor(temp4->minXYZ.z / temp4->boxWidth) * temp4->boxWidth);

	temp4->ID = temp->CalculateIDFull(floorxyz, temp4->boxWidth);

	this->m_pVecAABBs.push_back(temp4);

	//Nose
	CAABB* temp5 = new CAABB();
	temp5->boxWidth = 4.f;
	temp5->minXYZ = glm::vec3(-2.f, -2.f, 5.f);
	temp5->UpdateMaxFromMinAndWidth();
	temp5->smallestChildBoxWidth = 5.f;
	floorxyz = glm::vec3(floor(temp5->minXYZ.x / temp5->boxWidth) * temp5->boxWidth, floor(temp5->minXYZ.y / temp5->boxWidth) * temp5->boxWidth, floor(temp5->minXYZ.z / temp5->boxWidth) * temp5->boxWidth);

	temp5->ID = temp->CalculateIDFull(floorxyz, temp5->boxWidth);

	this->m_pVecAABBs.push_back(temp5);

	//Back
	CAABB* temp6 = new CAABB();
	temp6->boxWidth = 4.f;
	temp6->minXYZ = glm::vec3(-2.f, -2.f, -10.f);
	temp6->UpdateMaxFromMinAndWidth();
	temp6->smallestChildBoxWidth = 5.f;
	floorxyz = glm::vec3(floor(temp6->minXYZ.x / temp6->boxWidth) * temp6->boxWidth, floor(temp6->minXYZ.y / temp6->boxWidth) * temp6->boxWidth, floor(temp6->minXYZ.z / temp6->boxWidth) * temp6->boxWidth);

	temp6->ID = temp->CalculateIDFull(floorxyz, temp6->boxWidth);

	this->m_pVecAABBs.push_back(temp6);

}