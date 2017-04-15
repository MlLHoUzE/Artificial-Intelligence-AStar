#include "cEntityBuilder.h"
#include "cEntityFactory.h"
#include <iostream>

cEntityBuilder* cEntityBuilder::m_pTheOneBuilder = 0;
int cEntityBuilder::m_entityID = 0;

cEntityBuilder::~cEntityBuilder()
{

}

cEntityBuilder::cEntityBuilder()
{

}

cEntityBuilder* cEntityBuilder::getInstance(void)
{
	if (cEntityBuilder::m_pTheOneBuilder == 0)
	{
		cEntityBuilder::m_pTheOneBuilder = new cEntityBuilder();
	}
	return cEntityBuilder::m_pTheOneBuilder;
}

void cEntityBuilder::shutDown(void)
{
	if (cEntityBuilder::m_pTheOneBuilder != 0)
	{
		delete cEntityBuilder::m_pTheOneBuilder;
	}
	return;
}

iEntity* cEntityBuilder::createEntity(std::string typeOfEntity)
{
	iEntity* pEntityToReturn = 0;
	cEntityFactory* pEntityFactory = new cEntityFactory();

	if (typeOfEntity == "Enemy")
	{
		pEntityToReturn = pEntityFactory->CreateEntity(typeOfEntity);
		//add things to entity.  ie. AI behaviour
	}
	else if (typeOfEntity == "SlowEnemy")
	{
		pEntityToReturn = pEntityFactory->CreateEntity(typeOfEntity);
	}
	else if (typeOfEntity == "Ground")
	{
		pEntityToReturn = pEntityFactory->CreateEntity(typeOfEntity);
	}
	else if (typeOfEntity == "DebugAABB")
	{
		pEntityToReturn = pEntityFactory->CreateEntity(typeOfEntity);
	}
	else
	{
		std::cout << "invalid entity type" << std::endl;
		return NULL;
	}

	pEntityToReturn->SetID(cEntityBuilder::m_entityID);
	cEntityBuilder::m_entityID++;
	delete pEntityFactory;

	return pEntityToReturn;
}
