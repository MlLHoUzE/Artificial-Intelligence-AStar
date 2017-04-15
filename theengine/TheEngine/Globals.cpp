#include "Globals.h"

int64_t AABBID = 0;

cShaderManager* g_pShaderManager = 0;
cMeshTypeManager* g_pMeshManager = 0;
cBasicTextureManager* g_pTextureManager = 0;
cSceneGraph* g_pSceneGraph = 0;
cAStarManager* g_pAStarManager = 0;

CAABB* g_pCollisionWorld = 0;

cPlayer* g_pPlayer = 0;
cCamera* g_pCamera = 0;

bool g_bWin = false;
std::vector<sTriangle> environTris;

GLFWwindow* g_window = 0;

glm::vec3 lightPos(9.f, 15.f, 16.f);		// I just picked these values after moving the light around until it looked "nice"
float lightConstAtten = 0.0f;
float lightLinearAtten = 0.001;
float lightQuadAtten = 0.00111786f;
glm::vec3 lightDiffuse(1.f, 0.8f, 0.f);

glm::vec3 lightPos9(0.f, 50.f, 0.f);		// I just picked these values after moving the light around until it looked "nice"
float lightConstAtten9 = 0.0f;
float lightLinearAtten9 = 0.001;
float lightQuadAtten9 = 0.000111786f;


bool bDrawLightDebugSpheres = false;
bool bDrawLightDebugLocation = true;

GLint locID_matModel = -1;		// 
GLint locID_matView = -1;
GLint locID_matProj = -1;

GLint UniformLoc_ID_objectColour = -1;
GLint UniformLoc_ID_isWireframe = -1;
GLint UniformLoc_ID_bUseDebugDiffuseNoLighting = -1;

GLint UniformLoc_alpha = -1;

GLint UniformLoc_texSamp2D_00 = -1;
GLint UniformLoc_texSamp2D_01 = -1;
GLint UniformLoc_texSamp2D_02 = -1;
GLint UniformLoc_texSamp2D_03 = -1;

GLint UniformLoc_bUseTextureAsDiffuse = -1;
GLint UniformLoc_bUseLighting = -1;

GLint UniformLoc_bIsImposterBlackIsAlpha = -1;
GLint UniformLoc_bUseAlphaMask = -1;