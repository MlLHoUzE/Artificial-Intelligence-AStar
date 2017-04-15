#ifndef _cEntityFactory_HG_
#define _cEntityFactory_HG_

#include "iEntity.h"
#include <string>

class cEntityFactory
{
public:
	iEntity* CreateEntity(std::string typeOfEntity);
};

#endif