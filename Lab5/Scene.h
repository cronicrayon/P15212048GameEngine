#pragma once
#include "GameObject.h"
#include "TransformComponent.h"

class Scene
{
public:
	Scene();
	void loadLevel(std::string levelFile);
private:
	int numElementsToRead;
	std::vector<GameObject> v_playerCubes;
};