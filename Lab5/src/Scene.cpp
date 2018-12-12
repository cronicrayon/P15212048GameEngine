#include"Scene.h"
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


GameObject* Scene::getGameObject(int tmp_numerator)
{
	if (tmp_numerator <= v_playerCubes.size() - 1)
	{
		return &v_playerCubes[tmp_numerator];
	}
}

void Scene::Render(IEngineCore *renderer)
{
	for (GameObject go : v_playerCubes)
	{
		renderer->drawCube(go.getComponent<TransformComponent>()->getModelMatrix());
	}

}

bool Scene::loadLevelJSON(std::string levelJSONFile) 
{
	std::fstream jsonData;
	Json::Value root;
	Json::Reader reader;

	jsonData.open(levelJSONFile.c_str());
	//check for errors
	if (!reader.parse(jsonData, root))
	{
		std::cout << "Failed to parse data from" << levelJSONFile << reader.getFormattedErrorMessages();
		return false;
	}
	const Json::Value gameObjects = root["GameObjects"];
	//size() tells us how large the array is
	v_playerCubes.resize(gameObjects.size());
	for (int i = 0; i < gameObjects.size(); i++)
	{
		//get string
		std::cout << gameObjects[i]["name"].asString() << " loaded\n";
		float x, y, z;
		//get the position node

		const Json::Value posNode = gameObjects[i]["position"];

		x = posNode[0].asFloat();
		y = posNode[1].asFloat();
		z = posNode[2].asFloat();

		glm::vec3 pos(x, y, z);

		//const Json::Value orientNode = gameObjects[i]["orientation"];
	
		v_playerCubes[i].addComponent(new TransformComponent(pos));

	}
}