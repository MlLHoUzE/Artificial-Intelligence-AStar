#ifndef _sAStarHelper_HG_
#define _sAStarHelper_HG_
#include "cAStarClasses.h"

struct sAStarHelper
{
	int row;
	int col;
	cPathNode* Node;
	sAStarHelper* Parent;
	float gScore;
	float fScore;
};

#endif