#pragma once

#include "Model.h"
#include <iostream>
#include <unordered_map>


class ModelHandler
{
	// model list and load all
	//
	// or
	// inside json loader
	// when you read a model name
	// ask the handler if it is loaded already - if yes use Model*
	// else load it, add to the map and use this model*


public:


	ModelHandler()
	{
		addComponent("assets/models/duck/duck.dae", "duck");
		addComponent("assets/models/cube.obj", "cube");
		addComponent("assets/models/floor/floor.obj", "floor");
		addComponent("assets/models/foliage/Bush_A.obj", "Bush A");
		addComponent("assets/models/foliage/Flowers_Daisys.obj", "Flower Daisys");
		addComponent("assets/models/foliage/Flowers_Pink.obj", "Flower Pink");
		addComponent("assets/models/foliage/Flowers_Yellow.obj", "Flower Yellow");
		addComponent("assets/models/foliage/Grass_A.obj", "Grass A");
		addComponent("assets/models/foliage/Peebles.obj", "Peebles");
		addComponent("assets/models/foliage/Rock_A.obj", "Rock A");
		addComponent("assets/models/foliage/Tree_A.obj", "Tree A");
	}


	Model* getComponent(std::string name)
	{

		auto iter = m_models.find(name);

		if (iter != std::end(m_models))
		{
			// if found dynamic cast the component pointer and return it
			return (iter->second);
		}

		// return null if we don't have a component of that type
		return nullptr;

	}

	
	void addComponent(std::string fileName, std::string name)
	{
		// add the component to unoreder map with hash of its typeid
		m_models[name] = new Model(fileName);
	
		
	}

private:

	std::unordered_map<std::string, Model*> m_models;

};