#ifndef _CAABB_HG_
#define _CAABB_HG_

#include <vector>
#include <map>
#include <glm\vec3.hpp>
#include "sTriangle.h"
#include "sAABBID.h"

struct CPoint
{
	CPoint( float x, float y, float z ) : x(x), y(y), z(z) {};
	CPoint() : x(0.0f), y(0.0f), z(0.0f) {};
	float x,y,z;
};

// Each AABB has a 10x10x10 "child" AABBs inside
class CAABB
{
public:
	CAABB() {};
	CAABB( CPoint minXYZ, float length );
	glm::vec3 minXYZ;
	glm::vec3 maxXYZ;
	void UpdateMaxFromMinAndWidth(void) 
	{
		this->maxXYZ.x = this->minXYZ.x + this->boxWidth;
		this->maxXYZ.y = this->minXYZ.y + this->boxWidth;
		this->maxXYZ.z = this->minXYZ.z + this->boxWidth;
	};
	float boxWidth;
	float smallestChildBoxWidth;
	//sAABBID ID;
	// Hash identifier for this AABB (related to the location in space)
//	45200.0, 67000.0, 85700.0
//	45000.0, 67000.0, 85000.0   minXYZ
//
//	1 meters.
//
//	850 670 450				32bits --> 0 to 4,000,000,000

	unsigned int CalculateID(CPoint minXYZ)
	{
		//xxx,yyy,zzz; 
		//float boxWidth = 100.0f;		// Nudge nudge, wink wink
		unsigned int zPart = (unsigned int)(minXYZ.z/boxWidth) *       1;
		unsigned int yPart = (unsigned int)(minXYZ.y/boxWidth) *    1000;
		unsigned int xPart = (unsigned int)(minXYZ.x/boxWidth) * 1000000; 
		unsigned int ID = xPart + yPart + zPart;
		return ID;
	}

	glm::vec3 CalculateMinXYZFromPointAndWidth(glm::vec3 xyz, float width);

	// The ID is a 9 digit value
	// xxx,yyy,zzz
	// First digit indicates +ve with 1, -ve with 0
	// So can only handle a range of -99 to 99 box widths
	// I'd suggest doing 10x10x10, so the values will be -9 "109" to +9 "009",
	//  mainly because:
	//  - The range from -99 to +99 is 100 boxes on either side
	//    of the zero, or 200x200x200 = 8,000,000 boxes
	//    (which is a LOT of boxes)
	//    A range of -9 to 9 or 10 boxes on either side of the zero, 
	//    which is 20x20x20 = 8,000 boxes 
	// If the location is beyond this range, well, it's going to be messed up
	int64_t CalculateIDFull(glm::vec3 xyz)
	{
		
		unsigned int zPart = static_cast<unsigned int>(fabs(xyz.z)/boxWidth) *       1;
		zPart += ( xyz.z < 0.0f ? 1000 : 0 );
		int test = static_cast<unsigned int>(fabs(xyz.y) / boxWidth);// *1000;
		test = (fabs(xyz.y) / boxWidth) * 1000;
		unsigned int yPart = static_cast<unsigned int>(fabs(xyz.y)/boxWidth) *    10000;
		yPart += ( xyz.y < 0.0f ? 10000000 : 0 );
		int64_t xPart = static_cast<int64_t>(fabs(xyz.x)/boxWidth) * 100000000; 
		xPart += ( xyz.x < 0.0f ? 100000000000 : 0 );
		int64_t ID = xPart + yPart + zPart;
		return ID;
	}
	
	int64_t CalculateIDFull(glm::vec3 xyz, float testBoxWidth)
	{
		unsigned int zPart = static_cast<unsigned int>(fabs(xyz.z)/ testBoxWidth) *       1;
		zPart += (xyz.z < 0.0f ? 1000 : 0);
		unsigned int yPart = static_cast<unsigned int>(fabs(xyz.y)/ testBoxWidth) *    10000;
		yPart += ( xyz.y < 0.0f ? 10000000 : 0 );
		int64_t xPart = static_cast<int64_t>(fabs(xyz.x)/ testBoxWidth) * 100000000;
		xPart += ( xyz.x < 0.0f ? 100000000000 : 0 );
		int64_t ID = xPart + yPart + zPart;
		return ID;
	}

	int64_t ID;		// 32 bit int  ( 1,xxx,yyy,zzz)

	bool getTriangles(glm::vec3 xyz, std::vector<sTriangle>& triangles);
	// Up to 1000x1000x1000 AABBs
	std::vector< CAABB* > vecChildAABBs;
	//we pass a triangle from model and aabb is created
	//to store the "contact" information...
	void AddChildAABBFromTriangle(sTriangle triangleToTest, sTriangle baseTriangle);

	//20x20x20 AABBs (-vs "box width" to +ve box width)
	std::map<int64_t /*ID*/, CAABB*> mapChildAABBs;
	std::vector<sTriangle> vecTriangles;
	std::vector<sTriangle> vecTrisToTest;
	//CAABB* pVecAABBS[100][100][100] = {0};	// 4 Mbytes

	//std::map< > mapObjectIDsInsideMeNow;

	//pVecAABBS[40][54][50] = new CAABB();
};

#endif
