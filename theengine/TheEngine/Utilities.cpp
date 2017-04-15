#define _CRT_SECURE_NO_WARNINGS

#include "Utilities.h"

#include <stdlib.h>     // srand, rand 
#include <glm/gtc/matrix_transform.hpp>
#include <fstream>
#include "cEntityBuilder.h"

// http://stackoverflow.com/questions/686353/c-random-float-number-generation
float getRandFloat( float LO, float HI )
{
	float r3 = LO + 
		static_cast <float> (rand()) / ( static_cast <float> (RAND_MAX/(HI-LO) ) );
	return r3;
}

float calcApproxDistFromAtten(float targetLightLevel, 
							  float attenConst, 
							  float attenLinear,
							  float attenQuad,
							  float accuracy, 
                              float infiniteDistance, 
							  unsigned int maxIterations /*= DEFAULTMAXITERATIONS = 50*/ )
{
	const float DEFAULTINFINITEDISTANCE = 10000.0f;	
//static 
	const float DEFAULDIFFUSEACCURACYTHRESHOLD = 0.001f;

	// See if the accuracy being set it too big for the targetLightLevel, unless targetLightLevel is actually zero (0.0f)
	// If it's actually zero, then adjusting the accuracy to a tenth of zero would give... wait for it...
	//	zero, and we would max out the iterations
	if ( targetLightLevel != 0.0f )	
	{	
		if ( ( accuracy * 10.0f) >= targetLightLevel * 10.0f )
		{	// Adjust the accuracy by a hundreth
			accuracy = targetLightLevel / 10.0f;
		}
	}//if ( targetLightLevel != 0.0f )	

	float targetLightLevelLow = targetLightLevel - accuracy;
	//if ( targetLightLevelLow <= 0.0f )	{ targetLightLevel = 0.0f; }
	float targetLightLevelHigh = targetLightLevel + accuracy;

	// See if we're getting a value at infinite. i.e. at 'infinite distance', is the light level too high already
	//if ( calcDiffuseFromAttenByDistance( DEFAULTINFINITEDISTANCE, accuracy ) > targetLightLevelHigh )
	float diffuseCalculated = calcDiffuseFromAttenByDistance( DEFAULTINFINITEDISTANCE, 
															  attenConst, attenLinear, attenQuad );
															  
	if ( diffuseCalculated > targetLightLevelHigh )
	{	// Yes, so we can never get down to this light level
		return DEFAULTINFINITEDISTANCE;
	}

	// There is a light level somewhere between a distance of 0.0 to DEFAULTINFINITEDISTANCE
	// Set initial guesses
	float distanceGuessLow = 0.0f;
	float distanceGuessHigh = DEFAULTINFINITEDISTANCE;

	unsigned int iterationCount = 0;
	while ( iterationCount < maxIterations )
	{
		// Pick a distance between the high and low
		float curDistanceGuess = ( (distanceGuessHigh - distanceGuessLow) / 2.0f ) + distanceGuessLow;
		// 
		float curDiffuseAtGuessDistance = calcDiffuseFromAttenByDistance( curDistanceGuess, 
																		  attenConst, 
																		  attenLinear, 
																		  attenQuad );
		// Could be three possibilities: too low, too high, or in between
		if ( curDiffuseAtGuessDistance < targetLightLevelLow )
		{	// Light is too dark, so distance is to HIGH. Reduce and guess again.
			distanceGuessHigh = curDistanceGuess;		// Lower the high limit for the guesses
		}
		else if ( curDiffuseAtGuessDistance > targetLightLevelHigh )
		{	// Light is too bright, so distance is to LOW. Increase and guess again
			distanceGuessLow = curDistanceGuess;
		}
		else 
		{	// Nailed it! Light level is within range, so return this distance
			return curDistanceGuess;
		}

		iterationCount++;

	}// while ( iterationCount < maxIterations )
	// If we are here, then we ran out of iterations.
	// Pick a distance between the low and high
	float distance = (distanceGuessHigh - distanceGuessLow) / 2.0f;

	return distance;
}

//const float CLightDescription::DEFAULTZEROTHRESHOLD = 0.0001f;

float calcDiffuseFromAttenByDistance(float distance, 
									 float attenConst, 
									 float attenLinear, 
									 float attenQuad, 
									 float zeroThreshold /*=0.0001f  DEFAULTZEROTHRESHOLD*/)
{
	const float DEFAULTZEROTHRESHOLD = 0.0001f;

	float diffuse = 1.0f;		// Assume full brightness

	float denominator = attenConst + 
	                    attenLinear * distance +
						attenQuad * distance * distance;
	// Is this zero (we don't want a divide by zero, do we)?
	if ( denominator <= zeroThreshold )
	{	// Let's just say it's zero, shall we?
		diffuse = 1.0f;
	}
	else
	{
		float atten = 1.0f / denominator;
		diffuse *= atten;
		if ( diffuse > 1.0f )
		{
			diffuse = 1.0f;
		}
	}//if ( denominator <= zeroThreshold )
	return diffuse;
}

glm::vec3 ClosestPtPointTriangle(glm::vec3 p, glm::vec3 a, glm::vec3 b, glm::vec3 c)
{
	// Check if P in vertex region outside A
	glm::vec3 ab = b - a;
	glm::vec3 ac = c - a;
	glm::vec3 ap = p - a;
	float d1 = glm::dot(ab, ap);		// glm::dot( ab, ap );
	float d2 = glm::dot(ac, ap);
	if (d1 <= 0.0f && d2 <= 0.0f) return a; // barycentric coordinates (1,0,0)

											// Check if P in vertex region outside B
	glm::vec3 bp = p - b;
	float d3 = glm::dot(ab, bp);
	float d4 = glm::dot(ac, bp);
	if (d3 >= 0.0f && d4 <= d3) return b; // barycentric coordinates (0,1,0)

										  // Check if P in edge region of AB, if so return projection of P onto AB
	float vc = d1*d4 - d3*d2;
	if (vc <= 0.0f && d1 >= 0.0f && d3 <= 0.0f) {
		float v = d1 / (d1 - d3);
		return a + v * ab; // barycentric coordinates (1-v,v,0)
	}

	// Check if P in vertex region outside C
	glm::vec3 cp = p - c;
	float d5 = glm::dot(ab, cp);
	float d6 = glm::dot(ac, cp);
	if (d6 >= 0.0f && d5 <= d6) return c; // barycentric coordinates (0,0,1)

										  // Check if P in edge region of AC, if so return projection of P onto AC
	float vb = d5*d2 - d1*d6;
	if (vb <= 0.0f && d2 >= 0.0f && d6 <= 0.0f) {
		float w = d2 / (d2 - d6);
		return a + w * ac; // barycentric coordinates (1-w,0,w)
	}

	// Check if P in edge region of BC, if so return projection of P onto BC
	float va = d3*d6 - d5*d4;
	if (va <= 0.0f && (d4 - d3) >= 0.0f && (d5 - d6) >= 0.0f) {
		float w = (d4 - d3) / ((d4 - d3) + (d5 - d6));
		return b + w * (c - b); // barycentric coordinates (0,1-w,w)
	}

	// P inside face region. Compute Q through its barycentric coordinates (u,v,w)
	float denom = 1.0f / (va + vb + vc);
	float v = vb * denom;
	float w = vc * denom;
	return a + ab * v + ac * w; // = u*a + v*b + w*c, u = va * denom = 1.0f - v - w
}

std::vector<glm::vec3> loadMap(std::string fileName)
{
	std::string fullFileName = "Assets//textures//" + fileName;

	std::ifstream theFile;

	theFile.open(fullFileName);

	theFile.seekg(2);
	int fileSize;
	theFile.read((char*)&fileSize, sizeof(int));

	theFile.seekg(10);
	int beginning;
	theFile.read((char*)&beginning, sizeof(int));

	theFile.seekg(18);
	int columns;
	theFile.read((char*)&columns, sizeof(int));

	theFile.seekg(22);
	int rows;
	theFile.read((char*)&rows, sizeof(int));

	int image_size = 0;
	columns += (3 * columns) % 4;
	image_size = 3 * columns * rows;

	theFile.seekg(beginning);
	std::vector<glm::vec3> data;
	int R = 0;
	int G = 0;
	int B = 0;
	//, G, B;
	glm::vec3 tmp;
	for (int i = beginning-3; i < image_size + 51; i += 3)
	{
		theFile.seekg(i);
		theFile.read((char*)&B, sizeof(int));
		if (B < 0) tmp.b = 1;
		else tmp.b = 0;
		theFile.seekg(i+1);
		theFile.read((char*)&G, sizeof(int));
		if (G < 0) tmp.g = 1;
		else tmp.g = 0;
		theFile.seekg(i+2);
		theFile.read((char*)&R, sizeof(int));
		if (R < 0) tmp.r = 1;
		else tmp.r = 0;
		
		data.push_back(tmp);
	}


	return data;

}

void CreateScene(std::vector<glm::vec3> map)
{
	int zPos = -100;
	int xPos = -100;
	std::vector < std::vector<cPathNode*>> Nodes;
	std::vector<cPathNode*> row;
	for (int i = 0; i < map.size(); i++, xPos+= 10)
	{
		
		if (i % 20 == 0)	//after every row
		{
			if(i > 1)
			Nodes.push_back(row);	//add this row to the list of all nodes
			row.clear();	//clear the old row
			zPos+=10;
			xPos = -100;
			
			
		}
		cPathNode* node = new cPathNode();	//create a row
		node->Position = glm::vec3(xPos, 0, zPos);
		node->Radius = 5.f;
		node->TravelCostFactor = 1;
		if (map[i].r == 1 && map[i].g == 0 && map[i].b == 0)	//create a wall
		{
			cEntityBuilder* theBuilder = cEntityBuilder::getInstance();
			iEntity* wall = theBuilder->createEntity("Ground");

			wall->SetPosition(glm::vec3(xPos, 0, zPos), glm::vec3(0.f, 0.f, 0.f));


			//curEntity->Scale(entityDesc->scale);
			sRenderingInfo renderingInfo;
			renderingInfo.meshName = "cubex10.ply";
			renderingInfo.bIsImposter = false;
			renderingInfo.bIsVisible = true;
			renderingInfo.bIsWireframe = false;
			renderingInfo.bUseDebugColors = false;
			renderingInfo.scale = 1.f;
			renderingInfo.texture00Name = "brick_texture.bmp";
			renderingInfo.color = glm::vec4(1.f, 1.f, 1.f, 1.f);
			wall->SetRenderingInfo(renderingInfo);

			g_pSceneGraph->addSceneNode(wall);

			wall->updatePhysicsTris();

			sPhysicsInfo physicsTemp;
			wall->GetPhysicsInfo(physicsTemp);
			for (int i = 0; i < physicsTemp.physicsTris.size(); i++)	//get teh physical triangles based off the location of the object
			{
				environTris.push_back(physicsTemp.physicsTris[i]);
			}
			node->TravelCostFactor = 100000;	//set this nodes travel cost to really high so that the AStar will never use it

			//create a wall
		}
		else if(map[i].r == 0 && map[i].g == 1 && map[i].b == 0)
		{
			//create player spawn
			sPhysicsInfo physicsIn;
			
			g_pPlayer->GetPhysicsInfo(physicsIn);
			physicsIn.position = glm::vec3(xPos, 0, zPos);

			g_pPlayer->SetPhysicsInfo(physicsIn);
			
			//create node

		}
		else if (map[i].r == 0 && map[i].g == 0 && map[i].b == 1)
		{
			//create the goal
			//create node
			g_pPlayer->SetGoal(glm::vec3(xPos, 0, zPos));
			cEntityBuilder* theBuilder = cEntityBuilder::getInstance();
			iEntity* lamp = theBuilder->createEntity("Ground");

			lamp->SetPosition(glm::vec3(xPos, 0, zPos), glm::vec3(0.f, 0.f, 0.f));


			//curEntity->Scale(entityDesc->scale);
			sRenderingInfo renderingInfo;
			renderingInfo.meshName = "lamp.ply";
			renderingInfo.bIsImposter = false;
			renderingInfo.bIsVisible = true;
			renderingInfo.bIsWireframe = false;
			renderingInfo.bUseDebugColors = false;
			renderingInfo.scale = 1.f;
			renderingInfo.texture00Name = "brick_texture.bmp";
			renderingInfo.color = glm::vec4(1.f, 1.f, 1.f, 1.f);
			lamp->SetRenderingInfo(renderingInfo);

			g_pSceneGraph->addSceneNode(lamp);

		}

		row.push_back(node);
	}
	Nodes.push_back(row);
	g_pAStarManager->SetNodes(Nodes);
	
}

void ResetScene(std::vector<glm::vec3> map)
{
	int zPos = -100;
	int xPos = -100;
	for (int i = 0; i < map.size(); i++, xPos += 10)
	{

		if (i % 20 == 0)	//after every row
		{
			zPos += 10;
			xPos = -100;


		}
		if (map[i].r == 0 && map[i].g == 1 && map[i].b == 0)
		{
			//create player spawn
			sPhysicsInfo physicsIn;

			g_pPlayer->GetPhysicsInfo(physicsIn);
			physicsIn.position = glm::vec3(xPos, 0, zPos);

			g_pPlayer->SetPhysicsInfo(physicsIn);

			//create node

		}
	}
}
