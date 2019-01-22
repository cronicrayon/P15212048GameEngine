#pragma once
#include "Model.h"
#include "Component.h"

class ModelComponent : public Component
{
public:


	ModelComponent(Model* aModel)
	{
		theModel = aModel;
	}

	void OnUpdate(float dt) override {}

	void OnMessage(const std::string m) override
	{
		// e.g.	if (m == "rotateLeft")

	}

	Model* getModel() 
	{ 
		return theModel;
	};

private:

	Model* theModel;
};