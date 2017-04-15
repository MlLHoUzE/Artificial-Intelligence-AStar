#include "Render.h"
#include "Globals.h"
#include <glm\vec3.hpp>
#include <glm\vec4.hpp>
#include <glm\mat4x4.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>



void SetUpTextureBindings(sRenderingInfo* pCurGO)
{

	// Get texture number
	std::string textureName = pCurGO->texture00Name;
	GLuint texture00Number = ::g_pTextureManager->getTextureIDFromName(textureName);
	//GLuint texture00Number = ::g_pTextureManager->getTextureIDFromName("trudeau_transparency_20140611.bmp");
	// Texture binding...
	GLuint texture00Unit = 0;		// Texture unit go from 0 to 79

	glActiveTexture(texture00Unit + GL_TEXTURE0);		// GL_TEXTURE0 = 33984
	glBindTexture(GL_TEXTURE_2D, texture00Number);
	//	glBindTextureUnit( texture00Unit, texture00Number );			// OpenGL 4.5+ only
	// Set texture unit in the shader, too
	glUniform1i(UniformLoc_texSamp2D_00, texture00Unit);
	glUniform1i(UniformLoc_bUseAlphaMask, FALSE);

	if (pCurGO->alphaTextureName != "")
	{
		GLuint texture01Number = ::g_pTextureManager->getTextureIDFromName(pCurGO->alphaTextureName);
		GLuint texture01Unit = 1;		// Texture unit go from 0 to 79
		glActiveTexture(texture01Unit + GL_TEXTURE0);		// GL_TEXTURE0 = 33984
		glBindTexture(GL_TEXTURE_2D, texture01Number);
		////	glBindTextureUnit( 1, texture01Number );			// OpenGL 4.5+ only
		//	// Set texture unit in the shader, too
		glUniform1i(UniformLoc_texSamp2D_01, texture01Unit);
		glUniform1i(UniformLoc_bUseAlphaMask, TRUE);
	}
	if(pCurGO->texture01Name != "")
	{
		GLuint textureNumber = ::g_pTextureManager->getTextureIDFromName(pCurGO->texture01Name);
		GLuint textureUnit = 2;		// Texture unit go from 0 to 79
		glActiveTexture(textureUnit + GL_TEXTURE0);		// GL_TEXTURE0 = 33984
		glBindTexture(GL_TEXTURE_2D, textureNumber);
		////	glBindTextureUnit( 1, texture01Number );			// OpenGL 4.5+ only
		//	// Set texture unit in the shader, too
		glUniform1i(UniformLoc_texSamp2D_02, textureUnit);
	}
	//{
	//	GLuint textureNumber = ::g_pTextureManager->getTextureIDFromName("FenceAlphaMask.bmp");
	//	GLuint textureUnit = 3;		// Texture unit go from 0 to 79
	//	glActiveTexture(textureUnit + GL_TEXTURE0);		// GL_TEXTURE0 = 33984
	//	glBindTexture(GL_TEXTURE_2D, textureNumber);
	//	////	glBindTextureUnit( 1, texture01Number );			// OpenGL 4.5+ only
	//	//	// Set texture unit in the shader, too
	//	glUniform1i(UniformLoc_texSamp2D_03, textureUnit);
	//}



	glUniform1i(UniformLoc_bUseTextureAsDiffuse, TRUE);		// 1

	return;
}

void DrawObject(iEntity* pCurEntity, glm::mat4 matModel, bool bUseLighting /*= true*/)
{
	pCurEntity->PreRender();
	sRenderingInfo renderingInfo;
	pCurEntity->GetRenderingInfo(renderingInfo);
	

	std::string meshModelName = renderingInfo.meshName;

	GLuint VAO_ID = 0;
	int numberOfIndices = 0;
	float unitScale = 1.0f;
	if (!::g_pMeshManager->LookUpMeshInfo(meshModelName,
		VAO_ID,
		numberOfIndices,
		unitScale))
	{	// Skip the rest of the for loop, but continue
		return;
	}

	//			glm::mat4x4 mvp(1.0f);		// Model, View, Projection matrix

	//			mat4x4_identity(m);
	//glm::mat4x4 matModel = glm::mat4x4(1.0f);


	// Pre-rotation
	// Translation
	// Post-rotation
	// Scale

	// Pre in that it's BEFORE the translation
	//matModel = glm::rotate(matModel, pCurEntity->pre_Rot_X, glm::vec3(1.0f, 0.0f, 0.0f));
	//matModel = glm::rotate(matModel, pCurEntity->pre_Rot_Y, glm::vec3(0.0f, 1.0f, 0.0f));
	//matModel = glm::rotate(matModel, pCurEntity->pre_Rot_Z, glm::vec3(0.0f, 0.0f, 1.0f));

	sPhysicsInfo physicsInfo;
	pCurEntity->GetPhysicsInfo(physicsInfo);
	matModel = glm::translate(matModel, physicsInfo.position);

	//// Pre in that it's AFTER the translation
	//matModel = glm::rotate(matModel, pCurEntity->post_Rot_X, glm::vec3(1.0f, 0.0f, 0.0f));
	//matModel = glm::rotate(matModel, pCurEntity->post_Rot_Y, glm::vec3(0.0f, 1.0f, 0.0f));
	//matModel = glm::rotate(matModel, pCurEntity->post_Rot_Z, glm::vec3(0.0f, 0.0f, 1.0f));

	//
	glm::mat4 matRotation(physicsInfo.orientation);
	matModel = matModel * matRotation;

	float actualScale = renderingInfo.scale;// *unitScale;

	matModel = glm::scale(matModel, glm::vec3(actualScale, actualScale, actualScale));

	//save the world matrix
	pCurEntity->SetWorldMatrix(matModel);
	if (!renderingInfo.bIsVisible)
	{
		// Don't draw it
		return;
	}

	if (renderingInfo.bIsWireframe)
	{	// Turn off backface culling
		// Enable "wireframe" polygon mode
		glPolygonMode(GL_FRONT_AND_BACK,	// GL_FRONT_AND_BACK is the only thing you can pass here
			GL_LINE);			// GL_POINT, GL_LINE, or GL_FILL
		glDisable(GL_CULL_FACE);
	}
	else
	{	// "Regular" rendering: 
		// Turn on backface culling
		// Turn polygon mode to solid (Fill)
		glCullFace(GL_BACK);		// GL_FRONT, GL_BACK, or GL_FRONT_AND_BACK
		glEnable(GL_CULL_FACE);
		glPolygonMode(GL_FRONT_AND_BACK,	// GL_FRONT_AND_BACK is the only thing you can pass here
			GL_FILL);			// GL_POINT, GL_LINE, or GL_FILL
	}

	SetUpTextureBindings(&renderingInfo);
	//	// Get texture number
	//	std::string textureName = pCurGO->texture00Name;
	//	GLuint textureNumber = ::g_pTextureManager->getTextureIDFromName(textureName);
	//	if ( textureNumber == 0 )
	//	{	// Texture number is INVALID
	//		//
	//		// TODO:  Pick the brick texture if we don't have one...
	//		textureNumber = ::g_pTextureManager->getTextureIDFromName("brickTexture_square_1024pixels.bmp");
	//	}
	//	else
	//	{	// Texture number is valid (i.e. found the texture)
	//		
	//		// Texture binding...
	//		GLuint textureUnit = 0;		// Texture unit go from 0 to 79
	//		glActiveTexture( textureUnit + GL_TEXTURE0 );
	////		glActiveTexture( 33984 );
	//
	//		glBindTexture( GL_TEXTURE_2D, textureNumber );
	//
	//		// Set texture unit in the shader, too
	//		glUniform1i( UniformLoc_texSamp2D_00, textureUnit );
	//
	//		glUniform1i( UniformLoc_bUseTextureAsDiffuse, TRUE );		// 1
	//	}


	if (renderingInfo.bIsImposter)
	{
		glUniform1i(UniformLoc_bIsImposterBlackIsAlpha, TRUE);
	}
	else
	{
		glUniform1i(UniformLoc_bIsImposterBlackIsAlpha, FALSE);
	}


	if (bUseLighting)
	{
		glUniform1i(UniformLoc_bUseLighting, TRUE);
	}
	else
	{
		glUniform1i(UniformLoc_bUseLighting, FALSE);
	}



	//			mat4x4_mul(mvp, p, m);
	// This is being calculated in the shader now...
	//			mvp = p * v * m;

	//			glUseProgram(program);
	::g_pShaderManager->useShaderProgram("phong");


	glUniformMatrix4fv(locID_matModel, 1, GL_FALSE,
		(const GLfloat*)glm::value_ptr(matModel));



	// Setting the uniform colours
	glUniform4f(UniformLoc_ID_objectColour,
		renderingInfo.color.r, renderingInfo.color.g, renderingInfo.color.b, 1.0f);
	if (renderingInfo.bIsWireframe)
	{
		glUniform1i(UniformLoc_ID_isWireframe, TRUE);		// 1
	}
	else
	{
		glUniform1i(UniformLoc_ID_isWireframe, FALSE);	// 0
	}

	if (renderingInfo.bUseDebugColors)
	{
		glUniform1i(UniformLoc_ID_bUseDebugDiffuseNoLighting, TRUE);		// 1
	}
	else
	{
		glUniform1i(UniformLoc_ID_bUseDebugDiffuseNoLighting, FALSE);	// 0
	}

	//glDrawArrays(GL_TRIANGLES, 0, 3);
	//glDrawArrays(GL_TRIANGLES, 0, numberofVerts);

	// Drawing indirectly from the index buffer

	// "turns on" transparency
	glEnable(GL_BLEND);		// Enables "blending"
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Set transparency for all objects in scene

	///	glUniform1f( UniformLoc_alpha, 0.0f );
	glUniform1f(UniformLoc_alpha, renderingInfo.color.a);



	glBindVertexArray(VAO_ID);
	glDrawElements(GL_TRIANGLES,
		numberOfIndices,
		GL_UNSIGNED_INT,	// Each index is how big?? 
		(GLvoid*)0);		// Starting point in buffer
	glBindVertexArray(0);

	return;
}

void DrawObject(cPlayer* pCurPlayer, glm::mat4 matModel, bool bUseLighting /*= true*/)
{
	pCurPlayer->PreRender();
	sRenderingInfo renderingInfo;
	pCurPlayer->GetRenderingInfo(renderingInfo);
	
	
	std::string meshModelName = renderingInfo.meshName;

	GLuint VAO_ID = 0;
	int numberOfIndices = 0;
	float unitScale = 1.0f;
	if (!::g_pMeshManager->LookUpMeshInfo(meshModelName,
		VAO_ID,
		numberOfIndices,
		unitScale))
	{	// Skip the rest of the for loop, but continue
		return;
	}

	//			glm::mat4x4 mvp(1.0f);		// Model, View, Projection matrix

	//			mat4x4_identity(m);
	//matModel = renderingInfo.modelMatrix;


	// Pre-rotation
	// Translation
	// Post-rotation
	// Scale

	// Pre in that it's BEFORE the translation
	//matModel = glm::rotate(matModel, pCurPlayer->pre_Rot_X, glm::vec3(1.0f, 0.0f, 0.0f));
	//matModel = glm::rotate(matModel, pCurPlayer->pre_Rot_Y, glm::vec3(0.0f, 1.0f, 0.0f));
	//matModel = glm::rotate(matModel, pCurPlayer->pre_Rot_Z, glm::vec3(0.0f, 0.0f, 1.0f));
	sPhysicsInfo physicsInfo;
	pCurPlayer->GetPhysicsInfo(physicsInfo);

	matModel = glm::translate(matModel, physicsInfo.position);

	//// Pre in that it's AFTER the translation
	//matModel = glm::rotate(matModel, pCurPlayer->post_Rot_X, glm::vec3(1.0f, 0.0f, 0.0f));
	//matModel = glm::rotate(matModel, pCurPlayer->post_Rot_Y, glm::vec3(0.0f, 1.0f, 0.0f));
	//matModel = glm::rotate(matModel, pCurPlayer->post_Rot_Z, glm::vec3(0.0f, 0.0f, 1.0f));
	glm::mat4 matRotation(physicsInfo.orientation);
	matModel = matModel * matRotation;
	

	//
	float actualScale = renderingInfo.scale;// *unitScale;

	matModel = glm::scale(matModel, glm::vec3(actualScale, actualScale, actualScale));

	//save object world transform
	pCurPlayer->SetWorldMatrix(matModel);

	if (!renderingInfo.bIsVisible)
	{
		// Don't draw it

		return;
	}

	if (renderingInfo.bIsWireframe)
	{	// Turn off backface culling
		// Enable "wireframe" polygon mode
		glPolygonMode(GL_FRONT_AND_BACK,	// GL_FRONT_AND_BACK is the only thing you can pass here
			GL_LINE);			// GL_POINT, GL_LINE, or GL_FILL
		glDisable(GL_CULL_FACE);
	}
	else
	{	// "Regular" rendering: 
		// Turn on backface culling
		// Turn polygon mode to solid (Fill)
		glCullFace(GL_BACK);		// GL_FRONT, GL_BACK, or GL_FRONT_AND_BACK
		glEnable(GL_CULL_FACE);
		glPolygonMode(GL_FRONT_AND_BACK,	// GL_FRONT_AND_BACK is the only thing you can pass here
			GL_FILL);			// GL_POINT, GL_LINE, or GL_FILL
	}

	SetUpTextureBindings(&renderingInfo);
	//	// Get texture number
	//	std::string textureName = pCurGO->texture00Name;
	//	GLuint textureNumber = ::g_pTextureManager->getTextureIDFromName(textureName);
	//	if ( textureNumber == 0 )
	//	{	// Texture number is INVALID
	//		//
	//		// TODO:  Pick the brick texture if we don't have one...
	//		textureNumber = ::g_pTextureManager->getTextureIDFromName("brickTexture_square_1024pixels.bmp");
	//	}
	//	else
	//	{	// Texture number is valid (i.e. found the texture)
	//		
	//		// Texture binding...
	//		GLuint textureUnit = 0;		// Texture unit go from 0 to 79
	//		glActiveTexture( textureUnit + GL_TEXTURE0 );
	////		glActiveTexture( 33984 );
	//
	//		glBindTexture( GL_TEXTURE_2D, textureNumber );
	//
	//		// Set texture unit in the shader, too
	//		glUniform1i( UniformLoc_texSamp2D_00, textureUnit );
	//
	//		glUniform1i( UniformLoc_bUseTextureAsDiffuse, TRUE );		// 1
	//	}


	if (bUseLighting)
	{
		glUniform1i(UniformLoc_bUseLighting, TRUE);
	}
	else
	{
		glUniform1i(UniformLoc_bUseLighting, FALSE);
	}



	//			mat4x4_mul(mvp, p, m);
	// This is being calculated in the shader now...
	//			mvp = p * v * m;

	//			glUseProgram(program);
	::g_pShaderManager->useShaderProgram("phong");


	glUniformMatrix4fv(locID_matModel, 1, GL_FALSE,
		(const GLfloat*)glm::value_ptr(matModel));



	// Setting the uniform colours
	glUniform4f(UniformLoc_ID_objectColour,
		renderingInfo.color.r, renderingInfo.color.g, renderingInfo.color.b, 1.0f);
	if (renderingInfo.bIsWireframe)
	{
		glUniform1i(UniformLoc_ID_isWireframe, TRUE);		// 1
	}
	else
	{
		glUniform1i(UniformLoc_ID_isWireframe, FALSE);	// 0
	}

	if (renderingInfo.bUseDebugColors)
	{
		glUniform1i(UniformLoc_ID_bUseDebugDiffuseNoLighting, TRUE);		// 1
	}
	else
	{
		glUniform1i(UniformLoc_ID_bUseDebugDiffuseNoLighting, FALSE);	// 0
	}

	//glDrawArrays(GL_TRIANGLES, 0, 3);
	//glDrawArrays(GL_TRIANGLES, 0, numberofVerts);

	// Drawing indirectly from the index buffer

	// "turns on" transparency
	glEnable(GL_BLEND);		// Enables "blending"
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Set transparency for all objects in scene

	///	glUniform1f( UniformLoc_alpha, 0.0f );
	glUniform1f(UniformLoc_alpha, renderingInfo.color.a);



	glBindVertexArray(VAO_ID);
	glDrawElements(GL_TRIANGLES,
		numberOfIndices,
		GL_UNSIGNED_INT,	// Each index is how big?? 
		(GLvoid*)0);		// Starting point in buffer
	glBindVertexArray(0);

	return;
}

