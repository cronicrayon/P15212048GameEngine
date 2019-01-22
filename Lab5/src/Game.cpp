#include "Game.h"
#include "TransformComponent.h"
#include "ColourComponent.h"
#include <fstream>
#include <sstream>

Game::Game()
{
	m_currentScene = new Scene();
	m_currentScene->loadLevelJSON("Assets/Levels/myCubeLevel.json");
	//loadLevel("assets/Levels/myCubeLevel.txt");
	m_engineInterfacePtr = nullptr;
	m_inputHandler = new InputHandler(m_currentScene->getGameObject(0));

	m_playerBackground.addComponent(new RedComponent);
	m_playerBackground.addComponent(new GreenComponent);
	m_playerBackground.addComponent(new BlueComponent);

	m_playerCube.addComponent(new TransformComponent);
	
	// move the cube
	TransformComponent* temp = m_playerCube.getComponent<TransformComponent>();
	temp->translate(0, 0, -5);
}

void Game::update()
{
	
}

void Game::render()
{
	float redValue = 0, greenValue = 0, blueValue = 0;
	if(m_playerBackground.getComponent<RedComponent>())
		redValue = m_playerBackground.getComponent<RedComponent>()->m_colourValue;
	if (m_playerBackground.getComponent<GreenComponent>())
		greenValue = m_playerBackground.getComponent<GreenComponent>()->m_colourValue;
	if (m_playerBackground.getComponent<BlueComponent>())
		blueValue = m_playerBackground.getComponent<BlueComponent>()->m_colourValue;
	
	// e.g. pass object details to the engine to render the next frame
	m_engineInterfacePtr->renderColouredBackground(redValue, greenValue, blueValue);

	// update the camera (probably don't need to do this each frame)

	// find the player

	// ask the scene for the player

	// ask the player for his camera component

	m_engineInterfacePtr->setCamera(m_currentScene->getPlayer->getComponent<CameraComponent>());

	// draw the cube
	//m_engineInterfacePtr->drawCube(m_playerCube.getComponent<TransformComponent>()->getModelMatrix());

	m_currentScene->Render(m_engineInterfacePtr);
}

/*void Game::loadLevel(std::string levelFile)
{
	std::stringstream ss;
	std::string s;
	

	std::ifstream myInputFile;




	myInputFile.open(levelFile, std::ios_base::in);

	if (myInputFile.is_open())
	{
		std::getline(myInputFile, s);
		ss.str(s);
		ss.ignore(17);
		ss >> numElementsToRead;

		v_playerCubes.resize(numElementsToRead);
		ss.clear();

		for (int i = 0; i < numElementsToRead; i++)
		{
			getline(myInputFile, s);
			getline(myInputFile, s);
			ss.clear();
			ss.str(s);


			float x;
			float y;
			float z;

			ss >> x;
			ss >> y;
			ss >> z;

			glm::vec3 pos = glm::vec3(x, y, z);

			getline(myInputFile, s);
			ss.clear();
			ss.str(s);

			float w;

			ss >> w;
			ss >> x;
			ss >> y;
			ss >> z;

			glm::quat orient = glm::quat(w, x, y, z);

			getline(myInputFile, s);
			ss.clear();
			ss.str(s);

			ss >> x;
			ss >> y;
			ss >> z;

			glm::vec3 scale = glm::vec3(x, y, z);

			v_playerCubes[i].addComponent(new TransformComponent(pos, orient, scale));
		}
	}
}*/

