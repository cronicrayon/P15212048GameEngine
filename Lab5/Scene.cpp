#include "Scene.h"
#include <fstream>
#include <sstream>

Scene::Scene()
{
	
}

void Scene::loadLevel(std::string levelFile)
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
}