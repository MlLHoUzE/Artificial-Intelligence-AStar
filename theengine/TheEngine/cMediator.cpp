#include "cMediator.h"
//#include "global.h"
#include <iostream>
#include "Globals.h"


cMediator::cMediator()
{
	m_pEntityBuilder->getInstance();
	
}

void cMediator::createEntity(sEntityDesc* entityDesc)//, std::vector<unsigned int>* indices, std::vector<sMeshVertex>* vertices)
{

	int shadProgID = g_pShaderManager->getIDFromFriendlyName("phong");
	unsigned int test;
	int test2;
	float test3;
	if(!g_pMeshManager->LookUpMeshInfo(entityDesc->meshName, test, test2, test3))
	g_pMeshManager->LoadPlyFileIntoGLBuffer(shadProgID, entityDesc->meshName, false, false);
	iEntity* curEntity;
	curEntity = m_pEntityBuilder->createEntity(entityDesc->typeOfEntity);
	if (curEntity == NULL) return;
	//curEntity->SetPosition(entityDesc->position, entityDesc->orientation);
	
	
	//curEntity->Scale(entityDesc->scale);
	curEntity->SetMediator(this);
	sRenderingInfo renderingInfo;
	renderingInfo.meshName = entityDesc->meshName;
	renderingInfo.bIsImposter = false;
	renderingInfo.bIsVisible = true;
	renderingInfo.bIsWireframe = false;
	renderingInfo.bUseDebugColors = false;
	renderingInfo.scale = entityDesc->scale;
	renderingInfo.texture00Name = entityDesc->texture00Name;
	renderingInfo.texture01Name = entityDesc->texture01Name;
	renderingInfo.color = entityDesc->color;
	renderingInfo.alphaTextureName = entityDesc->alphaTextureName;
	curEntity->SetRenderingInfo(renderingInfo);

	if (curEntity->getParent() == NULL)
	{
		curEntity->SetMediator(this);
		sRenderingInfo renderingInfo;
		renderingInfo.meshName = entityDesc->meshName;
		renderingInfo.bIsImposter = false;
		renderingInfo.bIsVisible = true;
		renderingInfo.bIsWireframe = false;
		renderingInfo.bUseDebugColors = false;
		renderingInfo.scale = entityDesc->scale;
		renderingInfo.texture00Name = entityDesc->texture00Name;
		renderingInfo.texture01Name = entityDesc->texture01Name;
		renderingInfo.color = entityDesc->color;
		renderingInfo.alphaTextureName = entityDesc->alphaTextureName;
		curEntity->SetRenderingInfo(renderingInfo);
		g_pSceneGraph->addSceneNode(curEntity);
		return;
	}
	else
	{
		curEntity->SetPosition(entityDesc->position, entityDesc->orientation);
		curEntity->SetMediator(this);
		sRenderingInfo renderingInfo;
		renderingInfo.meshName = entityDesc->meshName;
		renderingInfo.bIsImposter = false;
		renderingInfo.bIsVisible = false;
		renderingInfo.bIsWireframe = false;
		renderingInfo.bUseDebugColors = false;
		renderingInfo.scale = entityDesc->scale;
		renderingInfo.texture00Name = entityDesc->texture00Name;
		renderingInfo.texture01Name = entityDesc->texture01Name;
		renderingInfo.color = entityDesc->color;
		renderingInfo.alphaTextureName = entityDesc->alphaTextureName;
		curEntity->SetRenderingInfo(renderingInfo);

		this->vec_spheres.push_back(curEntity);
	}


	//	curEnemy->SetMeshEntry(m_angryMesh.NumIndices, m_angryMesh.BaseIndex, m_angryMesh.BaseVertex);
	//	//curEnemy->SetColor(glm::vec4(1.0, 1.0, 0.0, 1.0));
	//		
	//	gEnemies.push_back(curEnemy);
		
	//}
	//for (int index = 0; index != enemyDesc->numberOfEnemies/2; index++)
	//{

	//	curEnemy = m_pEnemyBuilder->createEnemy("Curious");
	//	curEnemy->SetPosition(glm::vec3(getRandFloat(gAreaInfo->Min.x, gAreaInfo->Max.x),
	//		getRandFloat(gAreaInfo->Min.y, gAreaInfo->Max.y),
	//		getRandFloat(gAreaInfo->Min.z, gAreaInfo->Max.z)));
	//	curEnemy->setSpeed(getRandFloat(enemyDesc->minSpeed, enemyDesc->maxSpeed));
	//	curEnemy->Scale(1.f);
	//	curEnemy->setMediator(this);
	//	curEnemy->SetMeshEntry(m_curiousMesh.NumIndices, m_curiousMesh.BaseIndex, m_curiousMesh.BaseVertex);
	//	//curEnemy->SetColor(glm::vec4(1.0, 1.0, 0.0, 1.0));

	//	gEnemies.push_back(curEnemy);

	//}
}

void cMediator::setPlayer(cPlayer* player)
{
	m_ThePlayer = player;
	return;
}

void cMediator::getTargetPosition(glm::vec3 &targetPosition, float distance)
{
	//glm::vec3 targetPosition;
	m_ThePlayer->GetNextPosition(targetPosition, distance);
	return;
}

void cMediator::getPlayerPosition(glm::vec3 &playerPosition)
{
	sPhysicsInfo tempPhysicsInfo;
	//playerPosition = m_ThePlayer->physicsInfo.Position;
	m_ThePlayer->GetPhysicsInfo(tempPhysicsInfo);
	playerPosition = tempPhysicsInfo.position;
	return;
}

void cMediator::getPlayerForward(glm::vec3& playerForward)
{
	//playerForward = m_ThePlayer->physicsInfo.Orientation * glm::vec3(0.f, 0.f, 1.f);
	sPhysicsInfo tempPhysicsInfo;
	m_ThePlayer->GetPhysicsInfo(tempPhysicsInfo);
	playerForward = tempPhysicsInfo.orientation * glm::vec3(0.f, 0.f, 1.);
	return;
}

//iEntity* cMediator::m_pFindEntityByID(int ID)
//{
//	for (int index = 0; index != gEnemies.size(); index++)
//	{
//		if (ID == gEnemies[index]->GetID())
//		{
//			return gEnemies[index];
//		}
//	}
//
//	return NULL;
//}

//void cMediator::deleteEnemy(int ID)
//{
//
//	
//	std::cout << "Delete Called" << std::endl;
//	for ( int index = 0; index != gEnemies.size(); index++)
//	{
//		if (gEnemies[index]->GetID() == ID)
//		{
//			gEnemies.erase(gEnemies.begin() + index);
//			break;
//		}
//	}
//	gEnemies.shrink_to_fit();
//}

void cMediator::spawnEnemy(int ID)
{
	
	
}