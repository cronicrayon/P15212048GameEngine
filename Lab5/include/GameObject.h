#pragma once
#include "Component.h"
#include <unordered_map>
#include <typeindex>
#include "ModelComponent.h"
#include "CameraComponent.h"
#include "TransformComponent.h"
#include <iostream>

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

class StaticEnvironmentObject : public GameObject
{
public:
	StaticEnvironmentObject(Model* model)
	{
		addComponent(new TransformComponent);
		addComponent(new ModelComponent(model));
	}
	~StaticEnvironmentObject()
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

		TransformComponent* transform = getComponent<TransformComponent>();

		glm::vec3 pos = transform->m_position;

		glm::quat orient = transform->m_orientation;

		// access the camera component too and link it to our position

		CameraComponent* camera = getComponent<CameraComponent>();

		//m_cameraState = CameraViewState::FPCamera;awdaewsd

		glm::vec3 relativePosition = glm::vec3(0, 0.4, 1);



		pos += orient * relativePosition;

		camera->setPosition(pos);
		camera->setOrientation(orient);


		// set camera from model
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
			//TransformComponent* transform = getComponent<TransformComponent>();

			//getComponent<CameraComponent>()->m_position = -1.0f * transform->m_position;
			//getComponent<CameraComponent>()->m_orientation = inverse(transform->m_orientation);

			break;
		}
		case CameraViewState::TPCamera:

			//TransformComponent* transform = getComponent<TransformComponent>();

			//glm::quat inverseOrinentation = inverse(transform->m_orientation);

			//getComponent<CameraComponent>()->m_position = -1.0f*(transform->m_position + glm::vec3(0, 150, 500) * inverseOrinentation);

			//getComponent<CameraComponent>()->m_orientation = inverseOrinentation;

			break;
		}
	}
	void OnMessage(const std::string m) override
	{
		if (m == "SetCameraFirstPerson")
		{
			//getComponent<ModelComponent>()->getModel()->setFirstPerson(true);
			m_cameraState = CameraViewState::FPCamera;
			cout << "first person set" << endl;
		}
		
		if (m == "SetCameraThirdPerson")
		{
			//getComponent<ModelComponent>()->getModel()->setFirstPerson(false);
			m_cameraState = CameraViewState::TPCamera;
			cout << "third person set" << endl;
		}
		else if (m.compare(0, 12, "rotateCamera") == 0)
		{
			TransformComponent* transform = getComponent<TransformComponent>();
			float rotationValue;
			if (m == "rotateCameraLeft") {
				rotationValue = -0.025f;
				cout << "camera left" << endl;
			}
			else {
				rotationValue = 0.025f;
				cout << "camera right" << endl;
			}

			transform->yaw(rotationValue);
		}
		glm::vec3 translationVector(0.0f, 0.0f, 0.0f);
		if (m == "movePlayerForward") {
			translationVector.z = -0.25f;
			cout << "forward fire" << endl;
		}
		else if (m == "movePlayerBackwards") {
			translationVector.z = 0.25f;
			cout << "backwards fire" << endl;
		}
		else if (m == "movePlayerLeft") {
			translationVector.x = -0.25f;
			cout << "left fire" << endl;
		}
		else if (m == "movePlayerRight") {
			translationVector.x = 0.25f;
			cout << "right fire" << endl;
		}

		TransformComponent* transform = getComponent<TransformComponent>();
		transform->translate(translationVector * transform->m_orientation);
		
		// move pos to camera

		glm::vec3 pos = transform->m_position;

		glm::quat orient = transform->m_orientation;

		// access the camera component too and link it to our position

		CameraComponent* camera = getComponent<CameraComponent>();

		//m_cameraState = CameraViewState::FPCamera;awdaewsd

		glm::vec3 relativePosition = glm::vec3(0, 0.4, 1);



		pos += orient * relativePosition;

		camera->setPosition(pos);
		camera->setOrientation(orient);


	}

	CameraViewState m_cameraState;
};


