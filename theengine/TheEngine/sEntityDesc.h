#ifndef _sEntityDesc_HG_
#define _sEntityDesc_HG_

#include <string>
#include <glm\vec3.hpp>

struct sEntityDesc
{
	std::string meshName;
	std::string texture00Name;
	std::string texture01Name;
	std::string alphaTextureName;
	std::string typeOfEntity;
	float maxSpeed;
	float angularSpeed;
	glm::vec3 position;
	glm::quat orientation;
	float scale;
	glm::vec4 color;

};

#endif