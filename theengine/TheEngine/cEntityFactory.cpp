#include "cEntityFactory.h"

//include the types of entities here
#include "cObjectEntity.h"
#include "cDebugAABBEntity.h"
#include "cEnemy.h"
#include "cSlowEnemy.h"

iEntity* cEntityFactory::CreateEntity(std::string typeOfEntity)
{
	iEntity* pEntityToReturn = 0;

	if (typeOfEntity == "Enemy")
	{
		pEntityToReturn = new cEnemy();
	}
	else if (typeOfEntity == "SlowEnemy")
	{
		pEntityToReturn = new cSlowEnemy();
	}
	else if (typeOfEntity == "Ground")
	{
		pEntityToReturn = new cObjectEntity();
		sPhysicsInfo physicsInfo;
		physicsInfo.bIsStatic = true;
		pEntityToReturn->SetPhysicsInfo(physicsInfo);
	}
	else if (typeOfEntity == "DebugAABB")
	{
		pEntityToReturn = new cDebugAABBEntity();
		g_pPlayer->addChild(pEntityToReturn);
		
	}

	return pEntityToReturn;
}