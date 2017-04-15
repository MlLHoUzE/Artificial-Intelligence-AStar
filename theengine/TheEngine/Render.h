#ifndef _Render_HG_
#define _Render_HG_
#include  "iEntity.h"
#include "cPlayer.h"

void DrawObject(iEntity* pCurEntity, glm::mat4 matModel, bool bUseLighting = true);

void DrawObject(cPlayer* pCurPlayer, glm::mat4 matModel, bool bUseLighting = true);


#endif