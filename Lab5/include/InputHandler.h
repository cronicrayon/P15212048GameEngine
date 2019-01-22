#pragma once
#include <map>
#include "GameObject.h"
#include <vector>
#include "TransformComponent.h"


class InputCommand
{
public:
	virtual ~InputCommand() {}
	virtual void execute(GameObject& playerBackground) = 0;
};


//e.g. class RotateLeftCommand : public InputCommand
class RotateRight : public InputCommand
{
public:
	void execute(GameObject& m_player) override
	{
		m_player.OnMessage("rotateRight");
	}
};

class RotateLeft : public InputCommand
{
public:
	void execute(GameObject& m_playerCube) override
	{
		if (m_playerCube.getComponent<TransformComponent>())
			m_playerCube.getComponent<TransformComponent>()->roll(0.05f);
	}
};

class ScaleXUp : public InputCommand
{
public:
	void execute(GameObject& m_playerCube) override {
		if (m_playerCube.getComponent<TransformComponent>())
			m_playerCube.getComponent<TransformComponent>()->scaleUp(0.1f, 0.0f, 0.0f);
	}
};

class ScaleXDown : public InputCommand
{
public:
	void execute(GameObject& m_playerCube) override {
		if (m_playerCube.getComponent<TransformComponent>())
			m_playerCube.getComponent<TransformComponent>()->scaleUp(-0.1f, 0.0f, 0.0f);
	}
};

struct InputHandler
{	
	GameObject* m_playerCube;

	std::map<int, InputCommand*> m_controlMapping;

	InputHandler(GameObject* playerCube) : m_playerCube(playerCube)
	{
		// the idea will be to map the keys directly from a config file that can be loaded in
		// and changed on the fly
		m_controlMapping[(int)'A'] = new RotateLeft;
		m_controlMapping[(int)'Z'] = new ScaleXDown;
		m_controlMapping[(int)'S'] = new RotateRight;
		m_controlMapping[(int)'X'] = new ScaleXUp;
	}

	void handleInputs(const std::vector<bool>& keyBuffer)
	{
		for(const auto& mapEntry : m_controlMapping)
		{
			if(keyBuffer[mapEntry.first])
			{
				mapEntry.second->execute(*m_playerCube);
			}
		}

	}
};
