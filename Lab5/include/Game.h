#pragma once
#include "IEngineCore.h"
#include "InputHandler.h"
#include "GameObject.h"
#include "Camera.h"
#include "Scene.h"

class Game
{
public:
	Game();
	IEngineCore* m_engineInterfacePtr;

	InputHandler* m_inputHandler;
	
	Scene* m_currentScene;

	void update();
	void render();

	

private:
	
	GameObject m_playerBackground;
	GameObject m_playerCube;
	

	///Camera m_camera;
};


