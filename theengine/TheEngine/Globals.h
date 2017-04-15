#ifndef _Globals_HG_
#define _Globals_HG_

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/vec3.hpp>

#include <vector>
#include "cShaderManager.h"
#include "cMeshTypeManager.h"
#include "cBasicTextureManager.h"
#include "cPlayer.h"
#include "cSceneGraph.h"
#include "cCamera.h"
#include "cAStarManager.h"

extern int64_t AABBID;

extern cShaderManager* g_pShaderManager;
extern cMeshTypeManager* g_pMeshManager;
extern cBasicTextureManager* g_pTextureManager;
extern cSceneGraph* g_pSceneGraph;
extern cAStarManager* g_pAStarManager;

extern bool g_bWin;

extern CAABB* g_pCollisionWorld;

extern cPlayer* g_pPlayer;
extern cCamera* g_pCamera;

extern std::vector<sTriangle> environTris;

extern GLFWwindow* g_window;

extern glm::vec3 lightPos;
extern float lightConstAtten;
extern float lightLinearAtten;
extern float lightQuadAtten;
extern glm::vec3 lightDiffuse;

extern glm::vec3 lightPos9;
extern float lightConstAtten9;
extern float lightLinearAtten9;
extern float lightQuadAtten9;


extern bool bDrawLightDebugSpheres;
extern bool bDrawLightDebugLocation;

extern GLint locID_matModel;		// 
extern GLint locID_matView;
extern GLint locID_matProj;

extern GLint UniformLoc_ID_objectColour;
extern GLint UniformLoc_ID_isWireframe;
extern GLint UniformLoc_ID_bUseDebugDiffuseNoLighting;

extern GLint UniformLoc_alpha;

extern GLint UniformLoc_texSamp2D_00;
extern GLint UniformLoc_texSamp2D_01;
extern GLint UniformLoc_texSamp2D_02;
extern GLint UniformLoc_texSamp2D_03;
extern GLint UniformLoc_bUseTextureAsDiffuse;
extern GLint UniformLoc_bUseLighting;
extern GLint UniformLoc_bUseAlphaMask;

extern GLint UniformLoc_bIsImposterBlackIsAlpha;


#endif