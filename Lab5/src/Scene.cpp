#include"Scene.h"
#include"Model.h"
#include"ModelComponent.h"
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

		v_sceneCubes.resize(numElementsToRead);
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

			if (i == 0)
			{
			
			v_playerCubes[i]->addComponent(new TransformComponent(pos, orient, scale));
		}

		v_sceneCubes[i]->addComponent(new TransformComponent(pos, orient, scale));

	}
	}
}


GameObject* Scene::getGameObject(int tmp_numerator)
{
	if (tmp_numerator <= v_sceneCubes.size() - 1)
	{
		return v_sceneCubes[tmp_numerator];
	}
}

StaticEnvironmentObject* Scene::getStaticObject(int tmp_numerator)
{
	if (tmp_numerator <= v_sceneCubes.size() - 1)
	{
		return v_sceneCubes[tmp_numerator];
	}
}

void Scene::Render(IEngineCore *renderer)
{
	for (StaticEnvironmentObject* go : v_sceneCubes)
	{

		Model* m = go->getComponent<ModelComponent>()->getModel();

		glm::mat4 modelMatrix = go->getComponent<TransformComponent>()->getModelMatrix();

		renderer->drawModel(m, modelMatrix);
	}

	for (PlayerCharacter* pc : v_playerCubes)
	{
		if ((pc->getComponent<ModelComponent>()->getModel()->getFirstPerson() == false))
		{
			Model* m = pc->getComponent<ModelComponent>()->getModel();

			glm::mat4 modelMatrix = pc->getComponent<TransformComponent>()->getModelMatrix();

			renderer->drawModel(m, modelMatrix);
		}
	}
}

bool Scene::loadLevelJSON(std::string levelJSONFile) 
{
	Model* mytestModel = new Model("assets/models/cube.obj");
	
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


	// oops these are all gameObjects - none of them are playerCharacters...
	v_sceneCubes.resize(gameObjects.size()-1);
	
	
	
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



		if (i == 0)
		{
			// this is the player

			PlayerCharacter* pc = new PlayerCharacter(modelMap.getComponent(gameObjects[i]["modelName"].asString()));

			v_playerCubes.push_back(pc);
		}
		else
		{
			//adding environment objects

			StaticEnvironmentObject* go = new StaticEnvironmentObject(modelMap.getComponent(gameObjects[i]["modelName"].asString()));
			
			v_sceneCubes[i - v_playerCubes.size()] = go;
			//v_sceneCubes[i - 1].addComponent(new TransformComponent(pos));
			//v_sceneCubes[i - 1].addComponent(new ModelComponent(mytestModel));

		}



		//const Json::Value orientNode = gameObjects[i]["orientation"];
	
		




	}

	// get player TODO
	
}

PlayerCharacter* Scene::getPlayer(int tmp_numerator)
{
	if (tmp_numerator <= v_playerCubes.size())
	{
		return v_playerCubes[tmp_numerator];
	}
	
}