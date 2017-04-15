#ifndef _sRenderingInfo_HG_
#define _sRenderingInfo_HG_

#include <string>
#include <glm\vec4.hpp>
#include <glm\mat4x4.hpp>
#include "sMeshEntry.h"

struct sRenderingInfo
{
	sRenderingInfo() : bIsVisible(true), bIsWireframe(false), bUseDebugColors(false), bIsImposter(false) {};
	bool bIsVisible;
	bool bIsWireframe;
	bool bUseDebugColors;
	bool bIsImposter;
	std::string texture00Name;
	std::string texture01Name;
	std::string alphaTextureName;
	std::string meshName;
	sMeshEntry meshEntry;
	glm::vec4 color;
	glm::mat4 modelMatrix;
	float scale;
};

#endif