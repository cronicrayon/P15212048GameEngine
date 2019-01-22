#pragma once
#include "Component.h"
#include <unordered_map>
#include <typeindex>
#include "ModelComponent.h"
#include "CameraComponent.h"
#include "TransformComponent.h"

class GameObject : public Component
{
public:
	template <typename T>
	T* getComponent()
	{

		auto iter = m_components.find(typeid(T));

		if(iter != std::end(m_components))
		{
			// if found dynamic cast the component pointer and return it
			return dynamic_cast<T*>(iter->second);
		}
		
		// return null if we don't have a component of that type
		return nullptr;
		
	}

	template <typename T>
	void addComponent(T* comp)
	{
		// add the component to unoreder map with hash of its typeid
		m_components[typeid(T)] = comp;
	}
	
	void OnUpdate(float dt) override
	{
	}
	void OnMessage(const std::string m) override
	{
	}

private:
	std::unordered_map<std::type_index, Component*> m_components;
};

class StaticEnvirinmentObject : public GameObject
{
public:
	StaticEnvirinmentObject(Model* model)
	{
		addComponent(new TransformComponent);
		addComponent(new ModelComponent(model));
	}
	~StaticEnvirinmentObject()
	{

	}

	void OnUpdate(float dt) override
	{

	}

	void OnMessage(const std::string message) override
	{

	}
};

class PlayerCharacter : public GameObject
{
	enum class CameraViewState { FPCamera, TPCamera };

public:
	PlayerCharacter(Model* model)
	{
		addComponent(new TransformComponent);
		addComponent(new CameraComponent);
		addComponent(new ModelComponent(model));
	}
	~PlayerCharacter()
	{

	}
	
	// how to add model transform and camera components

	void OnUpdate(float dt) override
	{
		switch (m_cameraState)
		{
		case CameraViewState::FPCamera:
		{
			TransformComponent* transform = getComponent<TransformComponent>();

			getComponent<CameraComponent>()->m_position = -1.0f * transform->m_position;
			getComponent<CameraComponent>()->m_orientation = inverse(transform->m_orientation);

			break;
		}
		case CameraViewState::TPCamera:

			TransformComponent * transform = getComponent<TransformComponent>();

			glm::quat inverseOrinentation = inverse(transform->m_orientation);

			getComponent<CameraComponent>()->m_position = -1.0f*(transform->m_position + glm::vec3(0, 150, 500) * inverseOrinentation);

			getComponent<CameraComponent>()->m_orientation = inverseOrinentation;

			break;
		}
	}
	void OnMessage(const std::string m) override
	{
		if (m == "SetCameraFirstPerson")
		{
			m_cameraState = CameraViewState::FPCamera;
		}
		else if ("SetCameraThirdPerson")
		{
			m_cameraState = CameraViewState::TPCamera;
		}
		else if (m.compare(0, 12, "rotateCamera") == 0)
		{
			TransformComponent* transform = getComponent<TransformComponent>();
			float rotationValue;
			if (m == "rotateCameraLeft") rotationValue = -0.05f;
			else rotationValue = 0.05f;

			transform->yaw(rotationValue);
		}
		else if (m.compare(0, 10, "movePlayer") == 0)
		{
			glm::vec3 translationVector(0.0f, 0.0f, 0.0f);
			if (m == "movePlayerForward") translationVector.z = -1.0f;
			else if (m == "movePlayerBackwards") translationVector.z = 1.0f;
			else if (m == "movePlayerLeft") translationVector.x = -1.0f;
			else if (m == "movePlayerRight") translationVector.x = -1.0f;

			TransformComponent* transform = getComponent<TransformComponent>();
			transform->translate(translationVector * inverse(transform->m_orientation));
		}
		

		// access the camera component tooand link it to our position

	}

	CameraViewState m_cameraState;
};


