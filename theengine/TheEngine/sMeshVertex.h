#ifndef _sMeshVertex_HG_
#define _sMeshVertex_HG_

#include <glm\vec4.hpp>

struct sMeshVertex
{
	glm::vec4 position;
	glm::vec4 texCoord;
	glm::vec4 normal;
};

#endif