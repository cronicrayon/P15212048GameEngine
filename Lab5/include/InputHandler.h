#pragma once
#include <map>
#include "GameObject.h"
#include <vector>
#include "TransformComponent.h"


class InputCommand
{
public:
	virtual ~InputCommand() {}
	virtual void execute(PlayerCharacter& playerBackground) = 0;
	
};

class Move : public InputCommand
{
public :
	std::string message;
	Move(std::string m): message(m){}
	void execute(PlayerCharacter& m_playerCube) override
	{
		m_playerCube.OnMessage(message);
	}
	
};

//e.g. class RotateLeftCommand : public InputCommand
class RotateRight : public InputCommand
{
public:
	void execute(PlayerCharacter& m_player) override
	{
		m_player.OnMessage("rotateRight");
	}
};

class RotateLeft : public InputCommand
{
public:
	void execute(PlayerCharacter& m_playerCube) override
	{
		if (m_playerCube.getComponent<TransformComponent>())
			m_playerCube.getComponent<TransformComponent>()->roll(0.05f);
	}
};

class ScaleXUp : public InputCommand
{
public:
	void execute(PlayerCharacter& m_playerCube) override {
		if (m_playerCube.getComponent<TransformComponent>())
			m_playerCube.getComponent<TransformComponent>()->scaleUp(0.1f, 0.0f, 0.0f);
	}
};

class ScaleXDown : public InputCommand
{
public:
	void execute(PlayerCharacter& m_playerCube) override {
		if (m_playerCube.getComponent<TransformComponent>())
			m_playerCube.getComponent<TransformComponent>()->scaleUp(-0.1f, 0.0f, 0.0f);
	}
};

struct InputHandler
{	
	PlayerCharacter* m_playerCube;

	std::map<int, InputCommand*> m_controlMapping;

	InputHandler(PlayerCharacter* playerCube) : m_playerCube(playerCube)
	{
		// the idea will be to map the keys directly from a config file that can be loaded in
		// and changed on the fly
		m_controlMapping[(int)'F'] = new Move("SetCameraFirstPerson");
		m_controlMapping[(int)'T'] = new Move("SetCameraThirdPerson");
		m_controlMapping[(int)'S'] = new Move("movePlayerBackwards");
		m_controlMapping[(int)'A'] = new Move("movePlayerLeft");
		m_controlMapping[(int)'W'] = new Move("movePlayerForward");
		m_controlMapping[(int)'D'] = new Move("movePlayerRight");
		m_controlMapping[(int)'Q'] = new Move("rotateCameraLeft");
		m_controlMapping[(int)'E'] = new Move("rotateCameraRight");

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
