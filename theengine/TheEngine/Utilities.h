#ifndef _Utilities_HG_
#define _Utilities_HG_

#include <glm\vec3.hpp>
#include <string>
#include <vector>

float getRandFloat( float LO, float HI );

float calcApproxDistFromAtten(float targetLightLevel, 
							  float attenConst, 
							  float attenLinear,
							  float attenQuad,
							  float accuracy, 
                              float infiniteDistance, 
							  unsigned int maxIterations = 50 /*DEFAULTMAXITERATIONS*/ );

float calcDiffuseFromAttenByDistance(float distance, 
									 float attenConst, 
									 float attenLinear, 
									 float attenQuad, 
									 float zeroThreshold =0.0001f /*DEFAULTZEROTHRESHOLD*/);

glm::vec3 ClosestPtPointTriangle(glm::vec3 p, glm::vec3 a, glm::vec3 b, glm::vec3 c);

std::vector<glm::vec3> loadMap(std::string fileName);

void CreateScene(std::vector<glm::vec3> map);
void ResetScene(std::vector<glm::vec3> map);

#endif
