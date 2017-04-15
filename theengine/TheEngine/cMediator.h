#include "iMediator.h"
#include <vector>
#include "iEntity.h"
#include "cPlayer.h"
#include "cEntityBuilder.h"

class cMediator : public iMediator
{
public:
	cMediator();
	virtual void spawnEnemy(int ID);
	virtual void createEntity(sEntityDesc* entityDesc);//, std::vector<unsigned int>* indices, std::vector<sMeshVertex>* vertices);
	virtual void setPlayer(cPlayer* player);
	virtual void getTargetPosition(glm::vec3& targetPosition, float distance);
	virtual void getPlayerPosition(glm::vec3 &playerPosition);
	virtual void getPlayerForward(glm::vec3& playerForward);


	std::vector<iEntity*> vec_spheres;
	
private:
	//std::vector<iPlant*> m_vec_pPlants;
	//std::vector<iEnemy*> m_vec_pEnemys;
	cEntityBuilder* m_pEntityBuilder;
	sMeshEntry m_curiousMesh;
	sMeshEntry m_angryMesh;
	std::vector<sMeshVertex> m_vertices;
	std::vector<unsigned int> m_indices;
	cPlayer* m_ThePlayer;

	static int m_EntityID;
	
	//iEntity* m_pFindEnemyByID(int ID);
	//void deleteEnemy(int ID);
};