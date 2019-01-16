#pragma once
#include "GameObject.h"
#include "Model.h"
#include "TransformComponent.h"
#include "IEngineCore.h"
#include "json/json.h"

class Scene
{
public:
	Scene();
	int numElementsToRead;
	void loadLevel(std::string levelFile);
	GameObject* getGameObject(int tmp_numerator);
	void Render(IEngineCore *renderer);
	bool loadLevelJSON(std::string levelJSONFile);
private:
	std::vector<GameObject> v_playerCubes;
	//Model* theModel;
};