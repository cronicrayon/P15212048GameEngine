#pragma once
#include "GameObject.h"
#include "Model.h"
#include "ModelHandler.h"
#include "TransformComponent.h"
#include "IEngineCore.h"
#include "json/json.h"
#include "CameraComponent.h"

class Scene
{
public:
	Scene();
	int numElementsToRead;
	void loadLevel(std::string levelFile);
	GameObject* getGameObject(int tmp_numerator);
	void Render(IEngineCore *renderer);
	bool loadLevelJSON(std::string levelJSONFile);


	PlayerCharacter* getPlayer(int tmp_numerator); // todo
	StaticEnvironmentObject* getStaticObject(int tmp_numerator);
	ModelHandler modelMap;


private:
	//std::vector<GameObject> v_sceneCubes;
	std::vector<PlayerCharacter*> v_playerCubes;
	std::vector<StaticEnvironmentObject*>v_sceneCubes;
	//Model* theModel;
};