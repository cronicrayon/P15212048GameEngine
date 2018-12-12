#pragma once
#include "Model.h"
#include "Component.h"

class ModelComponent : public Component
{
public :

	ModelComponent();
	void OnUpdate(float dt) override {}

	void OnMessage(const std::string m) override
	{
		// e.g.	if (m == "rotateLeft")

	}

	Model* theModel;
};