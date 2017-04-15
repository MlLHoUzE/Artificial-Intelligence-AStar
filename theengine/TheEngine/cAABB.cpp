#include "CAABB.h"
#include <glm\gtc\matrix_transform.hpp>
glm::vec3 CAABB::CalculateMinXYZFromPointAndWidth(glm::vec3 xyz, float width)
{
	glm::vec3 calcMinXYZ;
	calcMinXYZ.x = floor(xyz.x / width) * width;
	calcMinXYZ.y = floor(xyz.y / width) * width;
	calcMinXYZ.z = floor(xyz.z / width) * width;
	return calcMinXYZ;
}


void CAABB::AddChildAABBFromTriangle(sTriangle triangleToTest, sTriangle baseTriangle)
{
	
	//check triangle size
	this->vecTrisToTest.clear();
	this->vecTrisToTest.push_back(triangleToTest);

	if (this->boxWidth == 10000)
	{//if we are at world box level, generate all the smaller triangles to test
		

		//for (std::vector<sTriangle>::iterator itCurrentTri = this->vecTrisToTest.begin(); itCurrentTri != this->vecTrisToTest.end(); itCurrentTri++)
		for (int i = 0; i != vecTrisToTest.size(); )
		{
			//calculate side lengths
			float longestSide = abs(glm::distance(vecTrisToTest[i].v1, vecTrisToTest[i].v2));
			if (abs(glm::distance(vecTrisToTest[i].v2, vecTrisToTest[i].v3)) > longestSide) longestSide = abs(glm::distance(vecTrisToTest[i].v2, vecTrisToTest[i].v3));
			if (abs(glm::distance(vecTrisToTest[i].v3, vecTrisToTest[i].v1)) > longestSide) longestSide = abs(glm::distance(vecTrisToTest[i].v3, vecTrisToTest[i].v1));
			if (longestSide > this->smallestChildBoxWidth)
			{//divide triangle

			 //create new verts
				glm::vec3 vertV1V2 = (vecTrisToTest[i].v1 + vecTrisToTest[i].v2) / 2.f;
				glm::vec3 vertV2V3 = (vecTrisToTest[i].v2 + vecTrisToTest[i].v3) / 2.f;
				glm::vec3 vertV3V1 = (vecTrisToTest[i].v3 + vecTrisToTest[i].v1) / 2.f;

				//create new triangles

				sTriangle t1;
				t1.v1 = vecTrisToTest[i].v1;
				t1.v2 = vertV1V2;
				t1.v3 = vertV3V1;

				sTriangle t2;
				t2.v1 = vertV1V2;
				t2.v2 = vecTrisToTest[i].v2;
				t2.v3 = vertV2V3;

				sTriangle t3;
				t3.v1 = vertV3V1;
				t3.v2 = vertV2V3;
				t3.v3 = vecTrisToTest[i].v3;

				sTriangle t4;
				t4.v1 = vertV2V3;
				t4.v2 = vertV3V1;
				t4.v3 = vertV1V2;

				//add the three new triangles
				this->vecTrisToTest.push_back(t1);
				this->vecTrisToTest.push_back(t2);
				this->vecTrisToTest.push_back(t3);
				this->vecTrisToTest.push_back(t4);

				//remove original from the vector
				this->vecTrisToTest.erase(vecTrisToTest.begin() + i);
				this->vecTrisToTest.shrink_to_fit();

				
				//repeat until entire list has small triangles
			}
			else
			{
				i++;
			}
		}
	
	}

	for (int i = 0; i != this->vecTrisToTest.size(); i++)
	{
		glm::vec3 v1(this->vecTrisToTest[i].v1.x, vecTrisToTest[i].v1.y, vecTrisToTest[i].v1.z);
		int64_t v1ID;
		if (this->boxWidth == 10000)
		{
			float v1X;
			if (vecTrisToTest[i].v1.x < 0.f)
				v1X = ceil(vecTrisToTest[i].v1.x / this->boxWidth) * this->boxWidth;
			else
				v1X = floor(vecTrisToTest[i].v1.x / this->boxWidth) * this->boxWidth;

			float v1Y;
			if (vecTrisToTest[i].v1.y < 0.f)
				v1Y = ceil(vecTrisToTest[i].v1.y / this->boxWidth) * this->boxWidth;
			else
				v1Y = floor(vecTrisToTest[i].v1.y / this->boxWidth) * this->boxWidth;

			float v1Z;
			if (vecTrisToTest[i].v1.z < 0.f)
				v1Z = ceil(vecTrisToTest[i].v1.z / this->boxWidth) * this->boxWidth;
			else
				v1Z = floor(vecTrisToTest[i].v1.z / this->boxWidth) * this->boxWidth;

			v1ID = this->CalculateIDFull(glm::vec3(v1X, v1Y, v1Z), this->boxWidth);
		}
		else
		{
			float v1X;
			float v1Y;
			float v1Z;
			v1X = floor(vecTrisToTest[i].v1.x / this->boxWidth) * this->boxWidth;
			v1Y = floor(vecTrisToTest[i].v1.y / this->boxWidth) * this->boxWidth;
			v1Z = floor(vecTrisToTest[i].v1.z / this->boxWidth) * this->boxWidth;
			v1ID = this->CalculateIDFull(glm::vec3(v1X, v1Y, v1Z), this->boxWidth);
		}




		if (v1ID == this->ID)
		{
			//are we at lowest, deepest level?
			if (this->boxWidth <= this->smallestChildBoxWidth)
			{
				bool bHasTriangle = false;
				for (int i = 0; i < this->vecTriangles.size(); i++)
				{
					//check if we already have this parent exact triangle
					if (vecTriangles[i].v1 == baseTriangle.v1 && vecTriangles[i].v2 == baseTriangle.v2 && vecTriangles[i].v3 == baseTriangle.v3)
					{
						bHasTriangle = true;
					}
				}
				if (!bHasTriangle)//if we don't have that base triangle add it to vector
					this->vecTriangles.push_back(baseTriangle);
			}
			else
			{

				glm::vec3 v1Floor(floor(v1.x / (this->boxWidth / 10.f))*(this->boxWidth / 10.f), floor(v1.y / (this->boxWidth / 10.f))*(this->boxWidth / 10.f), floor(v1.z / (this->boxWidth / 10.f))*(this->boxWidth / 10.f));
				int64_t idChildAABBv1 = this->CalculateIDFull(v1Floor, this->boxWidth / 10.0f);

				//do i have this child
				std::map<int64_t, CAABB*>::iterator itChildAABB = this->mapChildAABBs.find(idChildAABBv1);

				if (itChildAABB == this->mapChildAABBs.end())
				{
					CAABB* pChildAABB = new CAABB();
					pChildAABB->smallestChildBoxWidth = 100.f;
					pChildAABB->boxWidth = this->boxWidth / 10.f;
					pChildAABB->minXYZ = this->CalculateMinXYZFromPointAndWidth(v1, pChildAABB->boxWidth);
					pChildAABB->UpdateMaxFromMinAndWidth();
					pChildAABB->ID = pChildAABB->CalculateIDFull(pChildAABB->minXYZ, pChildAABB->boxWidth);
					this->mapChildAABBs[idChildAABBv1] = pChildAABB;

					//Pass the triangle down to the child AABB
					pChildAABB->AddChildAABBFromTriangle(vecTrisToTest[i], baseTriangle);
				}
				else
				{
					//this child exists
					itChildAABB->second->AddChildAABBFromTriangle(vecTrisToTest[i], baseTriangle);
				}

				//this->vecTriangles.push_back(triangle);
				//is there an AABB in my children


				//If it;s pointing to end(), then there isn't a child AABB

			}
		}

		glm::vec3 v2(vecTrisToTest[i].v2.x, vecTrisToTest[i].v2.y, vecTrisToTest[i].v2.z);
		int64_t v2ID;
		if (this->boxWidth == 10000)
		{
			float v2X;
			if (vecTrisToTest[i].v2.x < 0.f)
				v2X = ceil(vecTrisToTest[i].v2.x / this->boxWidth) * this->boxWidth;
			else
				v2X = floor(vecTrisToTest[i].v2.x / this->boxWidth) * this->boxWidth;

			float v2Y;
			if (vecTrisToTest[i].v2.y < 0.f)
				v2Y = ceil(vecTrisToTest[i].v2.y / this->boxWidth) * this->boxWidth;
			else
				v2Y = floor(vecTrisToTest[i].v2.y / this->boxWidth) * this->boxWidth;

			float v2Z;
			if (vecTrisToTest[i].v2.z < 0.f)
				v2Z = ceil(vecTrisToTest[i].v2.z / this->boxWidth) * this->boxWidth;
			else
				v2Z = floor(vecTrisToTest[i].v2.z / this->boxWidth) * this->boxWidth;

			v2ID = this->CalculateIDFull(glm::vec3(v2X, v2Y, v2Z), this->boxWidth);
		}
		else
		{
			float v2X;
			float v2Y;
			float v2Z;
			v2X = floor(vecTrisToTest[i].v2.x / this->boxWidth) * this->boxWidth;
			v2Y = floor(vecTrisToTest[i].v2.y / this->boxWidth) * this->boxWidth;
			v2Z = floor(vecTrisToTest[i].v2.z / this->boxWidth) * this->boxWidth;
			v2ID = this->CalculateIDFull(glm::vec3(v2X, v2Y, v2Z), this->boxWidth);
		}
		if (v2ID == this->ID)
		{
			//are we at lowest, deepest level?
			if (this->boxWidth <= this->smallestChildBoxWidth)
			{
				bool bHasTriangle = false;
				for (int i = 0; i < this->vecTriangles.size(); i++)
				{
					//check if we already have this exact triangle
					if (vecTriangles[i].v1 == baseTriangle.v1 && vecTriangles[i].v2 == baseTriangle.v2 && vecTriangles[i].v3 == baseTriangle.v3)
					{
						bHasTriangle = true;
					}
				}
				if (!bHasTriangle)//we dont have this base triangle, add it to vector
					this->vecTriangles.push_back(baseTriangle);
			}
			else
			{

				glm::vec3 v2Floor(floor(v2.x / (this->boxWidth / 10.f))*(this->boxWidth / 10.f), floor(v2.y / (this->boxWidth / 10.f))*(this->boxWidth / 10.f), floor(v2.z / (this->boxWidth / 10.f))*(this->boxWidth / 10.f));
				int64_t idChildAABBv2 = this->CalculateIDFull(v2Floor, this->boxWidth / 10.0f);

				//do i have this child
				std::map<int64_t, CAABB*>::iterator itChildAABB = this->mapChildAABBs.find(idChildAABBv2);

				if (itChildAABB == this->mapChildAABBs.end())
				{
					CAABB* pChildAABB = new CAABB();
					pChildAABB->smallestChildBoxWidth = 100.f;
					pChildAABB->boxWidth = this->boxWidth / 10.f;
					pChildAABB->minXYZ = this->CalculateMinXYZFromPointAndWidth(v2, pChildAABB->boxWidth);
					pChildAABB->UpdateMaxFromMinAndWidth();
					pChildAABB->ID = pChildAABB->CalculateIDFull(pChildAABB->minXYZ, pChildAABB->boxWidth);
					this->mapChildAABBs[idChildAABBv2] = pChildAABB;

					//Pass the small triangle down to the child AABB as well as the base larger triangle
					pChildAABB->AddChildAABBFromTriangle(vecTrisToTest[i], baseTriangle);
				}
				else
				{
					//this child exists
					itChildAABB->second->AddChildAABBFromTriangle(vecTrisToTest[i], baseTriangle);
				}

			}
		}

		glm::vec3 v3(vecTrisToTest[i].v3.x, vecTrisToTest[i].v3.y, vecTrisToTest[i].v3.z);
		int64_t v3ID;
		if (this->boxWidth == 10000)
		{
			float v3X;
			if (vecTrisToTest[i].v3.x < 0.f)
				v3X = ceil(vecTrisToTest[i].v3.x / this->boxWidth) * this->boxWidth;
			else
				v3X = floor(vecTrisToTest[i].v3.x / this->boxWidth) * this->boxWidth;

			float v3Y;
			if (vecTrisToTest[i].v3.y < 0.f)
				v3Y = ceil(vecTrisToTest[i].v3.y / this->boxWidth) * this->boxWidth;
			else
				v3Y = floor(vecTrisToTest[i].v3.y / this->boxWidth) * this->boxWidth;

			float v3Z;
			if (vecTrisToTest[i].v3.z < 0.f)
				v3Z = ceil(vecTrisToTest[i].v3.z / this->boxWidth) * this->boxWidth;
			else
				v3Z = floor(vecTrisToTest[i].v3.z / this->boxWidth) * this->boxWidth;

			v3ID = this->CalculateIDFull(glm::vec3(v3X, v3Y, v3Z), this->boxWidth);
		}
		else
		{
			float v3X;
			float v3Y;
			float v3Z;
			v3X = floor(vecTrisToTest[i].v3.x / this->boxWidth) * this->boxWidth;
			v3Y = floor(vecTrisToTest[i].v3.y / this->boxWidth) * this->boxWidth;
			v3Z = floor(vecTrisToTest[i].v3.z / this->boxWidth) * this->boxWidth;
			v3ID = this->CalculateIDFull(glm::vec3(v3X, v3Y, v3Z), this->boxWidth);
		}
		if (v3ID == this->ID)
		{
			//are we at lowest, deepest level?
			if (this->boxWidth <= this->smallestChildBoxWidth)
			{
				bool bHasTriangle = false;
				for (int i = 0; i < this->vecTriangles.size(); i++)
				{
					//check if we already have this exact triangle
					if (vecTriangles[i].v1 == baseTriangle.v1 && vecTriangles[i].v2 == baseTriangle.v2 && vecTriangles[i].v3 == baseTriangle.v3)
					{
						bHasTriangle = true;
					}
				}
				if (!bHasTriangle)	//we don't have this large triangle, add it to vector
					this->vecTriangles.push_back(baseTriangle);
			}
			else
			{

				glm::vec3 v3Floor(floor(v3.x / (this->boxWidth / 10.f))*(this->boxWidth / 10.f), floor(v3.y / (this->boxWidth / 10.f))*(this->boxWidth / 10.f), floor(v3.z / (this->boxWidth / 10.f))*(this->boxWidth / 10.f));
				int64_t idChildAABBv3 = this->CalculateIDFull(v3Floor, this->boxWidth / 10.0f);

				//do i have this child
				std::map<int64_t, CAABB*>::iterator itChildAABB = this->mapChildAABBs.find(idChildAABBv3);

				if (itChildAABB == this->mapChildAABBs.end())
				{
					CAABB* pChildAABB = new CAABB();
					pChildAABB->smallestChildBoxWidth = 100.f;
					pChildAABB->boxWidth = this->boxWidth / 10.f;
					pChildAABB->minXYZ = this->CalculateMinXYZFromPointAndWidth(v3, pChildAABB->boxWidth);
					pChildAABB->UpdateMaxFromMinAndWidth();
					pChildAABB->ID = pChildAABB->CalculateIDFull(pChildAABB->minXYZ, pChildAABB->boxWidth);
					this->mapChildAABBs[idChildAABBv3] = pChildAABB;

					//Pass the small triangle down to the child AABB to be tested, and pass the large triangle down to be added at the bottom
					pChildAABB->AddChildAABBFromTriangle(vecTrisToTest[i], baseTriangle);
				}
				else
				{
					//this child exists
					itChildAABB->second->AddChildAABBFromTriangle(vecTrisToTest[i], baseTriangle);
				}

			}
		}
	}
	
}

bool CAABB::getTriangles(glm::vec3 xyz, std::vector<sTriangle>& triangles)
{
	int64_t ID;
	if (this->boxWidth == 10000)
	{
		float v1X;
		if (xyz.x < 0.f)
			v1X = ceil(xyz.x / this->boxWidth) * this->boxWidth;
		else
			v1X = floor(xyz.x / this->boxWidth) * this->boxWidth;

		float v1Y;
		if (xyz.y < 0.f)
			v1Y = ceil(xyz.y / this->boxWidth) * this->boxWidth;
		else
			v1Y = floor(xyz.y / this->boxWidth) * this->boxWidth;

		float v1Z;
		if (xyz.z < 0.f)
			v1Z = ceil(xyz.z / this->boxWidth) * this->boxWidth;
		else
			v1Z = floor(xyz.z / this->boxWidth) * this->boxWidth;

		ID = this->CalculateIDFull(glm::vec3(v1X, v1Y, v1Z), this->boxWidth);
	}
	else
	{
		float v1X;
		float v1Y;
		float v1Z;
		v1X = floor(xyz.x / this->boxWidth) * this->boxWidth;
		v1Y = floor(xyz.y / this->boxWidth) * this->boxWidth;
		v1Z = floor(xyz.z / this->boxWidth) * this->boxWidth;
		ID = this->CalculateIDFull(glm::vec3(v1X, v1Y, v1Z), this->boxWidth);
	}
	if (ID == this->ID)
	{

		if (this->boxWidth == this->smallestChildBoxWidth)
		{
			triangles = this->vecTriangles;
			return true;

		}
		else
		{
			glm::vec3 xyzFloor(floor(xyz.x / (this->boxWidth / 10.f))*(this->boxWidth / 10.f), floor(xyz.y / (this->boxWidth / 10.f))*(this->boxWidth / 10.f), floor(xyz.z / (this->boxWidth / 10.f))*(this->boxWidth / 10.f));
			int64_t childID = this->CalculateIDFull(xyzFloor, this->boxWidth / 10.0f);

			std::map<int64_t, CAABB*>::iterator itChildAABB = this->mapChildAABBs.find(childID);

			if (itChildAABB == this->mapChildAABBs.end())
			{	//no child box at player location
				//therefore no triangles to collide with in that area
				return false;
			}
			else
			{
				//we do have a child with that ID
				//get triangles from that AABB
				itChildAABB->second->getTriangles(xyz, triangles);
			}
		}

	}
	
}