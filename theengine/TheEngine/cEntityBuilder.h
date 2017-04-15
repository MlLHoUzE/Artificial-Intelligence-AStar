#ifndef _cEntityBuilder_HG_
#define _cEntityBuilder_HG_

#include <string>
#include "iEntity.h"

class cEntityBuilder
{
public:
	~cEntityBuilder();
	static cEntityBuilder* getInstance(void);
	static void shutDown(void);

	iEntity* createEntity(std::string typeOfEntity);

private:
	cEntityBuilder();
	static int m_entityID;
	static cEntityBuilder* m_pTheOneBuilder;
};

#endif