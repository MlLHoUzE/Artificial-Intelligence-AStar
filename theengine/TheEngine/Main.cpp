#include <stdio.h>
#include <stdlib.h>

#include <iostream>
#include "Globals.h"
//GLM STUFF
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

#include "cShaderManager.h"


#include "cPlayer.h"
#include "cMediator.h"
#include "CAABB.h"
#include "JsonHelp.h"
#include "Utilities.h"


#include "sEntityDesc.h"

#include "Input.h"


#include <time.h>

//#include "global.h"

//#include "LoadMesh.h"
//#include "LoadTexture.h"
//#include "Update.h"
//#include "iMediator.h"
//#include "cMediator.h"
//#include "JsonHelp.h"


void CollisionStep(float deltaTime);

static int WORLDSIZE = 5000;

std::vector<iEntity*> g_vec_pSpheres;

static void error_callback(int error, const char* description)
{
	fprintf(stderr, "Error: %s\n", description);
}

int main(void)
{
	//GLFWwindow* g_window;
	srand(time(NULL));
	glfwSetErrorCallback(error_callback);

	if (!glfwInit())
		exit(EXIT_FAILURE);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	g_window = glfwCreateWindow(1200, 800, "The Engine", NULL, NULL);
	if (!g_window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	std::string jsonFileName = "Scene.json";
	Json::Value json;
	std::string errs;

	if (!JsonHelp::Load(jsonFileName, json, errs))
	{
		std::cout << "couldn't load JSON file." << std::endl;
		std::cout << errs << std::endl;
	}

	glfwMakeContextCurrent(g_window);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	glfwSwapInterval(1);

	::g_pShaderManager = new cShaderManager();

	cShaderManager::cShader verShader;
	cShaderManager::cShader fragShader;

	verShader.fileName = "phongVert.glsl";
	fragShader.fileName = "phongFrag.glsl";
	::g_pShaderManager->setBasePath("assets//shaders//");
	if (!::g_pShaderManager->createProgramFromFile("phong", verShader, fragShader))
	{
		std::cout << ::g_pShaderManager->getLastError() << std::endl;
		std::cout.flush();

		return -1;
	}
	GLuint shaderProgramID = ::g_pShaderManager->getIDFromFriendlyName("phong");

	::g_pMeshManager = new cMeshTypeManager();
	::g_pMeshManager->SetBaseFilePath("assets//models//");
	::g_pMeshManager->ScaleEverythingToBoundingBoxOnLoad(true, 1.0f);

	//TODO: Load files here
	//::g_pMeshManager->LoadPlyFileIntoGLBuffer
	//done in mediator
	::g_pTextureManager = new cBasicTextureManager();
	::g_pTextureManager->SetBasePath("Assets//textures//");
	//TODO: Load Textures
	if (!::g_pTextureManager->Create2DTextureFromBMPFile("bear_texture.bmp", true))
	{
		std::cout << "WARNING: Didn't load texture" << std::endl;
	}
	if (!::g_pTextureManager->Create2DTextureFromBMPFile("deer_texture.bmp", true))
	{
		std::cout << "WARNING: Didn't load texture" << std::endl;
	}
	if (!::g_pTextureManager->Create2DTextureFromBMPFile("boar_texture.bmp", true))
	{
		std::cout << "WARNING: Didn't load texture" << std::endl;
	}
	if (!::g_pTextureManager->Create2DTextureFromBMPFile("grass_texture.bmp", true))
	{
		std::cout << "WARNING: Didn't load texture" << std::endl;
	}
	if (!::g_pTextureManager->Create2DTextureFromBMPFile("dirt_texture.bmp", true))
	{
		std::cout << "WARNING: Didn't load texture" << std::endl;
	}
	if (!::g_pTextureManager->Create2DTextureFromBMPFile("brick_texture.bmp", true))
	{
		std::cout << "WARNING: Didn't load texture" << std::endl;
	}
	if (!::g_pTextureManager->Create2DTextureFromBMPFile("FenceActual.bmp", true))
	{
		std::cout << "WARNING: Didn't load texture" << std::endl;
	}
	if (!::g_pTextureManager->Create2DTextureFromBMPFile("FenceAlphaMask.bmp", true))
	{
		std::cout << "WARNING: Didn't load texture" << std::endl;
	}
	if (!::g_pTextureManager->Create2DTextureFromBMPFile("metal.bmp", true))
	{
		std::cout << "WARNING: Didn't load texture" << std::endl;
	}
	if (!::g_pTextureManager->Create2DTextureFromBMPFile("gold.bmp", true))
	{
		std::cout << "WARNING: Didn't load texture" << std::endl;
	}
	if (!::g_pTextureManager->Create2DTextureFromBMPFile("rusty.bmp", true))
	{
		std::cout << "WARNING: Didn't load texture" << std::endl;
	}
	if (!::g_pTextureManager->Create2DTextureFromBMPFile("graffiti.bmp", true))
	{
		std::cout << "WARNING: Didn't load texture" << std::endl;
	}
	//create the SceneGraph
	g_pSceneGraph = cSceneGraph::getInstance();
	g_pAStarManager = cAStarManager::GetInstance();

	
	
	g_pMeshManager->ScaleEverythingToBoundingBoxOnLoad(false, 1.f);
	g_pMeshManager->LoadPlyFileIntoGLBuffer(shaderProgramID, "cubex10.ply", true, false);
	g_pMeshManager->LoadPlyFileIntoGLBuffer(shaderProgramID, "lamp.ply", false, false);
	g_pPlayer = cPlayer::getInstance();
	/*g_pMeshManager->LoadPlyFileIntoGLBuffer(shaderProgramID, "Utah_Teapot.ply");
	sRenderingInfo renderingInfo;
	renderingInfo.meshName = "Utah_Teapot.ply";
	renderingInfo.texture00Name = "brickTexture_square_1024pixels.bmp";
	renderingInfo.bIsImposter = false;
	renderingInfo.bIsVisible = true;
	renderingInfo.bIsWireframe = false;
	renderingInfo.bUseDebugColors = false;
	renderingInfo.color = (glm::vec4(1.f, 1.f, 1.f, 1.f));
	renderingInfo.scale = 7.f;
	g_pPlayer->SetRenderingInfo(renderingInfo);*/
	if (!JsonHelp::Set(json["Player"], *g_pPlayer))
	{
		std::cout << "Couldn't Load the Player" << std::endl;
	}


	{
		unsigned int testVAO;
		int testNumIndices;
		float testUnitScale;
		sRenderingInfo renderingInfo;
		g_pPlayer->GetRenderingInfo(renderingInfo);
		if (!g_pMeshManager->LookUpMeshInfo(renderingInfo.meshName, testVAO, testNumIndices, testUnitScale))//check if this mesh has already been loaded
		{
			//if it hasn't been loaded
			g_pMeshManager->ScaleEverythingToBoundingBoxOnLoad(false, 1.f);
			g_pMeshManager->LoadPlyFileIntoGLBuffer(shaderProgramID, renderingInfo.meshName, false, true);
			g_pMeshManager->ScaleEverythingToBoundingBoxOnLoad(true, 1.f);
		}
	}

	//g_pPlayer->Init();
	g_pSceneGraph->addSceneNode(g_pPlayer);
	std::vector<glm::vec3> map = loadMap("Map.bmp");
	CreateScene(map);
	//create camera
	g_pCamera = new cCamera();
	if (!JsonHelp::Set(json["Camera"], *g_pCamera))
	{
		std::cout << "Couldn't load the camera" << std::endl;
	}
	//g_pCamera->SetOffset(glm::vec3(0.f, 15.f, -15.f));
	g_pSceneGraph->addSceneNode(g_pCamera);

	cMediator* pMediator = new cMediator();
	pMediator->setPlayer(g_pPlayer);

	sEntityDesc entityDesc;
	if (!JsonHelp::Set(json["Entity"], entityDesc))
	{
		std::cout << "Couldnt load entity" << std::endl;
	}
	
	pMediator->createEntity(&entityDesc);
	if (!JsonHelp::Set(json["Entity2"], entityDesc))
	{
		std::cout << "Couldnt load entity" << std::endl;
	}

	pMediator->createEntity(&entityDesc);

	/*if (!JsonHelp::Set(json["Entity3"], entityDesc))
	{
		std::cout << "Couldnt load entity" << std::endl;
	}

	pMediator->createEntity(&entityDesc);

	if (!JsonHelp::Set(json["Entity4"], entityDesc))
	{
		std::cout << "Couldnt load entity" << std::endl;
	}

	pMediator->createEntity(&entityDesc);

	if (!JsonHelp::Set(json["Entity5"], entityDesc))
	{
		std::cout << "Couldnt load entity" << std::endl;
	}

	pMediator->createEntity(&entityDesc);

	if (!JsonHelp::Set(json["Entity6"], entityDesc))
	{
		std::cout << "Couldnt load entity" << std::endl;
	}

	pMediator->createEntity(&entityDesc);

	if (!JsonHelp::Set(json["Entity7"], entityDesc))
	{
		std::cout << "Couldnt load entity" << std::endl;
	}

	pMediator->createEntity(&entityDesc);

	if (!JsonHelp::Set(json["Entity8"], entityDesc))
	{
		std::cout << "Couldnt load entity" << std::endl;
	}

	pMediator->createEntity(&entityDesc);
	if (!JsonHelp::Set(json["Entity9"], entityDesc))
	{
		std::cout << "Couldnt load entity" << std::endl;
	}

	pMediator->createEntity(&entityDesc);
	if (!JsonHelp::Set(json["Entity10"], entityDesc))
	{
		std::cout << "Couldnt load entity" << std::endl;
	}

	pMediator->createEntity(&entityDesc);
	if (!JsonHelp::Set(json["Entity11"], entityDesc))
	{
		std::cout << "Couldnt load entity" << std::endl;
	}

	pMediator->createEntity(&entityDesc);*/

	
	sEntityDesc groundDesc;
	groundDesc.meshName = "ground.ply";
	//groundDesc.meshName = "cube.ply";
	g_pMeshManager->ScaleEverythingToBoundingBoxOnLoad(false, 1.f);
	g_pMeshManager->LoadPlyFileIntoGLBuffer(shaderProgramID, groundDesc.meshName, true, false);
	g_pMeshManager->ScaleEverythingToBoundingBoxOnLoad(true, 1.f);
	groundDesc.texture00Name = "grass_texture.bmp";
	groundDesc.position = glm::vec3(0.f, 0.f, 0.f);
	groundDesc.scale = 1;
	groundDesc.typeOfEntity = "Ground";
	groundDesc.color = glm::vec4(1.f, 1.f, 0.f, 1.f);

	pMediator->createEntity(&groundDesc);

	{
		//front left
		sEntityDesc debugDesc;
		//debugDesc.meshName = "Cube_Unit_CornerAtOrigin_N.ply";
		debugDesc.meshName = "Sphere.ply";
		g_pMeshManager->LoadPlyFileIntoGLBuffer(shaderProgramID, debugDesc.meshName, false, false);
		debugDesc.position = glm::vec3(/*0.f, 0.f, 0.f*/0.25f, 1.7f, 0.0f);
		debugDesc.scale = 3.f;
		debugDesc.typeOfEntity = "DebugAABB";
		debugDesc.color = glm::vec4(1.f, 1.f, 1.f, 1.f);
		

		pMediator->createEntity(&debugDesc);

		////front right
		//debugDesc.meshName = "Cube_Unit_CornerAtOrigin_N.ply";
		//debugDesc.meshName = "Sphere.ply";
		//debugDesc.position = glm::vec3(-2.8f, -1.f, 2.2f);
		//debugDesc.scale = 2.f;
		//debugDesc.typeOfEntity = "DebugAABB";
		//debugDesc.color = glm::vec4(1.f, 1.f, 1.f, 1.f);

		//pMediator->createEntity(&debugDesc);

		////back left
		//debugDesc.meshName = "Cube_Unit_CornerAtOrigin_N.ply";
		//debugDesc.meshName = "Sphere.ply";
		//debugDesc.position = glm::vec3(2.8f, -1.f, -4.5f);
		//debugDesc.scale = 2.f;
		//debugDesc.typeOfEntity = "DebugAABB";
		//debugDesc.color = glm::vec4(1.f, 1.f, 1.f, 1.f);

		//pMediator->createEntity(&debugDesc);

		////back right
		//debugDesc.meshName = "Cube_Unit_CornerAtOrigin_N.ply";
		//debugDesc.meshName = "Sphere.ply";
		//debugDesc.position = glm::vec3(-2.8f, -1.f, -4.5f);
		//debugDesc.scale = 2.f;
		//debugDesc.typeOfEntity = "DebugAABB";
		//debugDesc.color = glm::vec4(1.f, 1.f, 1.f, 1.f);

		//pMediator->createEntity(&debugDesc);

		////nose
		//debugDesc.meshName = "Cube_Unit_CornerAtOrigin_N.ply";
		//debugDesc.meshName = "Sphere.ply";
		//debugDesc.position = glm::vec3(0.f, 0.f, 5.2f);
		//debugDesc.scale = 4.f;
		//debugDesc.typeOfEntity = "DebugAABB";
		//debugDesc.color = glm::vec4(1.f, 1.f, 1.f, 1.f);

		//pMediator->createEntity(&debugDesc);

		////back
		//debugDesc.meshName = "Cube_Unit_CornerAtOrigin_N.ply";
		//debugDesc.meshName = "Sphere.ply";
		//debugDesc.position = glm::vec3(0.f, 0.f, -8.f);
		//debugDesc.scale = 5.f;
		//debugDesc.typeOfEntity = "DebugAABB";
		//debugDesc.color = glm::vec4(1.f, 1.f, 1.f, 1.f);

		//pMediator->createEntity(&debugDesc);
	}
	//std::vector<sTriangle> vecEnvironment;
	//g_pMeshManager->GetEnvironmentalTriangles(vecEnvironment);

	g_vec_pSpheres = pMediator->vec_spheres;
	g_pCollisionWorld = new CAABB();
	//world is around 5000 units
	g_pCollisionWorld->boxWidth = 10000.f;
	g_pCollisionWorld->minXYZ.x = -5000.f;
	g_pCollisionWorld->minXYZ.y = -5000.f;
	g_pCollisionWorld->minXYZ.z = -5000.f;
	g_pCollisionWorld->UpdateMaxFromMinAndWidth();
	g_pCollisionWorld->smallestChildBoxWidth = 100.f;
	//g_pCollisionWorld->ID =	g_pCollisionWorld->CalculateIDFull(g_pCollisionWorld->minXYZ);
	//child : 1000
	//grandchildren: 100
	//great grandchildren: 10

	//for each triangle in model
	/*{
	sTriangle test;
	g_pCollisionWorld->AddChildAABBFromTriangle(test, g_pCollisionWorld->boxWidth);
	}*/
	for (int i = 0; i < environTris.size(); i++)
	{
		g_pCollisionWorld->AddChildAABBFromTriangle(environTris[i], environTris[i]);
	}
	

	GLint locID_lightPosition = -1;
	GLint locID_lightDiffuse = -1;
	GLint locID_lightAttenuation = -1;

	GLint locID_lightPosition9 = -1;
	GLint locID_lightDiffuse9 = -1;
	GLint locID_lightAttenuation9 = -1;

	locID_matModel = glGetUniformLocation(shaderProgramID, "matModel");
	locID_matView = glGetUniformLocation(shaderProgramID, "matView");
	locID_matProj = glGetUniformLocation(shaderProgramID, "matProj");

	locID_lightPosition = glGetUniformLocation(shaderProgramID, "theLights[0].position");
	locID_lightDiffuse = glGetUniformLocation(shaderProgramID, "theLights[0].diffuse");
	locID_lightAttenuation = glGetUniformLocation(shaderProgramID, "theLights[0].attenuation");

	locID_lightPosition9 = glGetUniformLocation(shaderProgramID, "theLights[8].position");
	locID_lightDiffuse9 = glGetUniformLocation(shaderProgramID, "theLights[8].diffuse");
	locID_lightAttenuation9 = glGetUniformLocation(shaderProgramID, "theLights[8].attenuation");

	UniformLoc_ID_objectColour = glGetUniformLocation(shaderProgramID, "objectColour");
	UniformLoc_ID_isWireframe = glGetUniformLocation(shaderProgramID, "isWireframe");
	UniformLoc_ID_bUseDebugDiffuseNoLighting = glGetUniformLocation(shaderProgramID, "bUseDebugDiffuseNoLighting");


	UniformLoc_alpha = glGetUniformLocation(shaderProgramID, "alpha");

	UniformLoc_texSamp2D_00 = glGetUniformLocation(shaderProgramID, "texSamp2D_00");
	UniformLoc_texSamp2D_01 = glGetUniformLocation(shaderProgramID, "texSamp2D_01");
	UniformLoc_texSamp2D_02 = glGetUniformLocation(shaderProgramID, "texSamp2D_02");
	UniformLoc_texSamp2D_03 = glGetUniformLocation(shaderProgramID, "texSamp2D_03");

	UniformLoc_bUseTextureAsDiffuse = glGetUniformLocation(shaderProgramID, "bUseTextureAsDiffuse");
	UniformLoc_bUseLighting = glGetUniformLocation(shaderProgramID, "bUseLighting");

	UniformLoc_bIsImposterBlackIsAlpha = glGetUniformLocation(shaderProgramID, "bIsImposterBlackIsAlpha");
	UniformLoc_bUseAlphaMask = glGetUniformLocation(shaderProgramID, "bUseAlphaMask");

	glEnable(GL_DEPTH_TEST);
	double lastTime = glfwGetTime();
	std::stringstream ssTitle;

	while (!glfwWindowShouldClose(g_window))
	{
		float ratio;
		int width, height;
		glm::mat4 matProjection;

		glfwGetFramebufferSize(g_window, &width, &height);
		ratio = width / (float)height;

		glViewport(0, 0, width, height);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::mat4 matView(1.0f);

		g_pCamera->GetProjectionMatrix(matProjection);
		//matProjection = glm::perspective(0.6f, ratio, 0.01f, 10000.0f);
		g_pCamera->GetViewMatrix(matView);

		glm::vec4 eye;
		g_pCamera->GetEyePosition(eye);
		//pass this to shader?

		static const float MAXDELTATIME = 0.1f;
		float deltaTime = static_cast<float>(glfwGetTime() - lastTime);
		lastTime = glfwGetTime();
		if (deltaTime > MAXDELTATIME)
		{
			deltaTime = MAXDELTATIME;
		}

		//update everything in the scene graph
		g_pSceneGraph->updateObjects(g_pSceneGraph->getRoot(), deltaTime);
		CollisionStep(deltaTime);
		bool pressF = nInput::IsKeyPressed::F();
		bool pressG = nInput::IsKeyPressed::G();
		bool pressC = nInput::IsKeyPressed::C();
		bool pressV = nInput::IsKeyPressed::V();
		if (pressF)
		{
			g_pSceneGraph->setWireframe(true, g_pSceneGraph->getRoot());
		}
		if (pressG)
		{
			g_pSceneGraph->setWireframe(false, g_pSceneGraph->getRoot());
		}
		if (pressC)
		{
			g_pSceneGraph->setUseLighting(true, g_pSceneGraph->getRoot());
		}
		if (pressV)
		{
			g_pSceneGraph->setUseLighting(false, g_pSceneGraph->getRoot());
		}


		

		glUniformMatrix4fv(locID_matProj, 1, GL_FALSE,
			(const GLfloat*)glm::value_ptr(matProjection));

		// This is set once at the start of the "scene" draw.
		glUniformMatrix4fv(locID_matView, 1, GL_FALSE,
			(const GLfloat*)glm::value_ptr(matView));

		glUniform4f(locID_lightPosition, lightPos.x, lightPos.y, lightPos.z, 1.0f);
		//glUniform4f(locID_lightDiffuse, 1.0, 1.0f, 1.0f, 1.0f);
		glUniform4f(locID_lightDiffuse, lightDiffuse.x, lightDiffuse.y, lightDiffuse.z, 1.0f);
		glUniform4f(locID_lightAttenuation, ::lightConstAtten, ::lightLinearAtten, ::lightQuadAtten, 1.0f);

		glUniform4f(locID_lightPosition9, lightPos9.x, lightPos9.y, lightPos9.z, 1.0f);
		//glUniform4f(locID_lightDiffuse, 1.0, 1.0f, 1.0f, 1.0f);
		glUniform4f(locID_lightDiffuse9, 1.0f, 1.0f, 1.0f, 1.0f);
		glUniform4f(locID_lightAttenuation9, ::lightConstAtten9, ::lightLinearAtten9, ::lightQuadAtten9, 1.0f);

		//draw sceneGraph
		g_pSceneGraph->draw(g_pSceneGraph->getRoot());

		glm::vec3 playerPos;
		g_pPlayer->GetNextPosition(playerPos, 0.f);
		glm::vec3 playerPosID;
		if (playerPos.x < 0)
			playerPosID.x = ceil(playerPos.x / 100) * 100;
		else
			playerPosID.x = floor(playerPos.x / 100) * 100;

		if (playerPos.y < 0)
			playerPosID.y = ceil(playerPos.y / 100) * 100;
		else
			playerPosID.y = floor(playerPos.y / 100) * 100;

		if (playerPos.z < 0)
			playerPosID.z = ceil(playerPos.z / 100) * 100;
		else
			playerPosID.z = floor(playerPos.z / 100) * 100;
		AABBID = g_pCollisionWorld->CalculateIDFull(playerPosID, 100.f);

		ssTitle.str(std::string());
		ssTitle << "X: " << playerPos.x << " Y: " << playerPos.y << " Z: " << playerPos.z << " AABBID: " << AABBID;
		glfwSetWindowTitle(g_window, ssTitle.str().c_str());

		std::vector<sTriangle> collidingTris;
		g_pCollisionWorld->getTriangles(playerPos, collidingTris);

		if (g_bWin)
		{
			srand(time(NULL));

			if (!JsonHelp::Set(json["Player"], *g_pPlayer))
			{
				std::cout << "Couldn't Load the Player" << std::endl;
			}


			{
				unsigned int testVAO;
				int testNumIndices;
				float testUnitScale;
				sRenderingInfo renderingInfo;
				g_pPlayer->GetRenderingInfo(renderingInfo);
				if (!g_pMeshManager->LookUpMeshInfo(renderingInfo.meshName, testVAO, testNumIndices, testUnitScale))//check if this mesh has already been loaded
				{
					//if it hasn't been loaded
					g_pMeshManager->ScaleEverythingToBoundingBoxOnLoad(false, 1.f);
					g_pMeshManager->LoadPlyFileIntoGLBuffer(shaderProgramID, renderingInfo.meshName, false, true);
					g_pMeshManager->ScaleEverythingToBoundingBoxOnLoad(true, 1.f);
				}
			}
			sPhysicsInfo playerPhysics;
			g_pPlayer->GetPhysicsInfo(playerPhysics);
			playerPhysics.velocity = glm::vec3(0.f);
			g_pPlayer->SetPhysicsInfo(playerPhysics);
			ResetScene(map);

			g_pCamera = new cCamera();
			if (!JsonHelp::Set(json["Camera"], *g_pCamera))
			{
				std::cout << "Couldn't load the camera" << std::endl;
			}
			//g_pCamera->SetOffset(glm::vec3(0.f, 15.f, -15.f));
			g_pSceneGraph->addSceneNode(g_pCamera);

			cMediator* pMediator = new cMediator();
			pMediator->setPlayer(g_pPlayer);

			sEntityDesc entityDesc;
			if (!JsonHelp::Set(json["Entity"], entityDesc))
			{
				std::cout << "Couldnt load entity" << std::endl;
			}

			pMediator->createEntity(&entityDesc);
			if (!JsonHelp::Set(json["Entity2"], entityDesc))
			{
				std::cout << "Couldnt load entity" << std::endl;
			}

			pMediator->createEntity(&entityDesc);

			sEntityDesc debugDesc;
			//debugDesc.meshName = "Cube_Unit_CornerAtOrigin_N.ply";
			debugDesc.meshName = "Sphere.ply";
			g_pMeshManager->LoadPlyFileIntoGLBuffer(shaderProgramID, debugDesc.meshName, false, false);
			debugDesc.position = glm::vec3(/*0.f, 0.f, 0.f*/0.25f, 1.7f, 0.0f);
			debugDesc.scale = 3.f;
			debugDesc.typeOfEntity = "DebugAABB";
			debugDesc.color = glm::vec4(1.f, 1.f, 1.f, 1.f);


			pMediator->createEntity(&debugDesc);

			g_bWin = false;

		}
		//check collisions between playertris and colliding tris
		glfwSwapBuffers(g_window);

		glfwPollEvents();
	}
	delete ::g_pMeshManager;
	delete ::g_pCamera;
	delete ::g_pPlayer;
//	delete ::g_pSceneGraph;
	delete ::g_pShaderManager;
	delete ::g_pTextureManager;

	glfwDestroyWindow(g_window);
	glfwTerminate();
	exit(EXIT_SUCCESS);

	system("pause");
	return 0;
}

void CollisionStep(float deltaTime)
{
	//get tris to check
	glm::vec3 playerPos;
	g_pPlayer->GetNextPosition(playerPos, 0);

	std::vector<sTriangle> vecTris;
	g_pCollisionWorld->getTriangles(playerPos, vecTris);

	// Brute force narrow phase detection
	
	for (int ballIndex = 0; ballIndex != ::g_vec_pSpheres.capacity(); ballIndex++)
	{
		if (g_vec_pSpheres.size() == 0)
		{
			break;
		}
		iEntity* pBall = ::g_vec_pSpheres[ballIndex];

		sRenderingInfo renderingIn;
		pBall->GetRenderingInfo(renderingIn);
		sRenderingInfo renderingOut;
		renderingOut = renderingIn;
		renderingOut.color = glm::vec4(1.f, 1.f, 1.f, 1.f);
		pBall->SetRenderingInfo(renderingOut);
		// Go through all the triangles, checking for collisions
		for (int triIndex = 0; triIndex != vecTris.size(); triIndex++)
		{
			sPhysicsInfo ballPhysicsInfo;
			pBall->GetPhysicsInfo(ballPhysicsInfo);

			sRenderingInfo ballRender;
			pBall->GetRenderingInfo(ballRender);

			glm::mat4 ballTrans;
			pBall->GetWorldMatrix(ballTrans);
			glm::vec3 ballCentre = ballTrans[3];

			glm::vec3 closestPoint = ClosestPtPointTriangle(ballCentre,
				vecTris[triIndex].v1,
				vecTris[triIndex].v2,
				vecTris[triIndex].v3);
			// Is this closer than the radius of the ball?? 
			if (glm::distance(ballCentre, closestPoint) < ballRender.scale/2)
			{
				//sRenderingInfo renderingOut;
				renderingOut.color = glm::vec4(1.f, 0.f, 0.f, 1.f);
				pBall->SetRenderingInfo(renderingOut);
				//there was a collision DO SOMETHING

				float penetration = abs(glm::distance(ballCentre, closestPoint) - ballRender.scale / 2);

				std::cout << "COLLISION" << std::endl;

				glm::vec3 normal;
				g_pMeshManager->getTriangleNormal(vecTris, triIndex, normal);
				normal * 1.f;

				sPhysicsInfo physicsInfoOut;
				sPhysicsInfo PhysicsInfoIn;

				g_pPlayer->GetPhysicsInfo(PhysicsInfoIn);

				glm::vec3 responseVelocity = glm::reflect(PhysicsInfoIn.velocity, normal);

				physicsInfoOut = PhysicsInfoIn;
				physicsInfoOut.velocity = responseVelocity;
				physicsInfoOut.position = PhysicsInfoIn.lastPosition + responseVelocity*penetration;
				physicsInfoOut.acceleration = glm::vec3(0.f);
				g_pPlayer->SetPhysicsInfo(physicsInfoOut);
				g_pPlayer->Update(deltaTime);
				//cContact curContact;
				//curContact.contactXYZ = closestPoint;
				//curContact.normal = normal;
				//curContact.sphereID = pBall->getID();
				//curContact.collisionType = cContact::WITH_TRIANGLE;
				//createHitMarker(closestPoint);
				//deleteSphereByID(pBall->getID());

				//::g_vec_Contacts.push_back(curContact);

				//// Set the ground collision fade to something
				//pBall->groundCollisionFadeCounter = 1.0f;
			}


		}
	}// for ( int ballIndex = 0...


	return;
}
