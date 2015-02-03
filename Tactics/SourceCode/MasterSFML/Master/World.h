#pragma once

//Includes
#include "Unit.h"
#include "mt.h"
#include "SceneNode.h"
#include "TextureLoader.h"
#include "Map.h"
#include "Selection.h"
#include "MyView.h"
#include "Object.h"
#include "ColorFiltre.h"
#include "DataLoader.h"
#include "CommandQueue.h"
#include "Player.h"

#include <algorithm> //sort
#include <array> //array
#include <iostream> //cin+cout

#include <SFML/Graphics.hpp>

//Namespace
using namespace std;

//Defines
#define MAP_SIZE_X 20 //>=16 for fullscreen
#define MAP_SIZE_Y 30 //>=23 for fullscreen


//Const

//Prototypes

//Class Prototypes

//Class Declaration
class World: private sf::NonCopyable
{
public:
	enum Layer
	{
		BackgroundL = 0,
		OverlaysL,
		SelectionL,
		GridL,
		UnitL,
		overUnitL,
		ObjectL,
		overObjectL,
		LayerCount
	};
	
	//Singleton specific
	static World* Instance();
	static void Create(sf::RenderWindow* window, 
		DataLoader* loadedData, 
		TextureLoader* textureHolder
		);
	void erase();

	//Destructor
	~World();

	//Access Method
	//R-only access
	//R-W access
	CommandQueue& World::getCommandQueue();
	SceneNode::ID& getIdNumber();

	//Modifying method

	//Function
	void update(sf::Time dt);

	void draw();

	void createUnit();
	void createUnit(int column, int row);

	void createObject();
	void createObject(int column, int row);

	void makeOverlay(vector<Hex*> hexes, mt::Overlay::Color color);

	void eraseLayer(Layer layer);
	void sortLayer(Layer layer);
	
	//Operator Overload

protected: 
	//Constructor
	World();
	World(sf::RenderWindow* window, 
		DataLoader* loadedData, 
		TextureLoader* textureHolder
		);

private:

	//Private Function
	//builds the SceneNodes
	void buildScene();

	//Private Attribute
	sf::RenderWindow* window_;

	DataLoader* loadedData_;
	TextureLoader* textureHolder_;

	SceneNode sceneGraph_;
	array<SceneNode*, LayerCount> sceneLayers_;

	CommandQueue commandQueue_;

	SceneNode::ID idNumber_;
	
	//Singleton specific
	static World* _instance; 
};
