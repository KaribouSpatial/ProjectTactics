#pragma once

//Includes
#include "mt.h"
#include "SceneNode.h"

#include <assert.h> //assert

//Namespace
using namespace std;

//Defines

//Const

//Prototypes

//Class Prototypes
class SceneNode;

//Class Declaration
class Command
{
public:
	typedef int ID;

	//Constructor
	Command(mt::Category::Type type = mt::Category::None, ID idd = 0)
	{
		category = type;
		id = idd;
	};

	//Destructor
	~Command(){};

	//Attributes
	function<void(SceneNode&, sf::Time)> action;

	template <typename GameObject, typename Function>
	function<void(SceneNode&, sf::Time)> derivedAction(Function fn)
	{
		return [=] (SceneNode& node, sf::Time dt)
		{
			// Check ifcast is safe
			assert(dynamic_cast<GameObject*>(&node) != nullptr);

			// Downcast node and invoke function on it
			fn(static_cast<GameObject&>(node), dt);
		};
	}
	
	unsigned int category;
	ID id;
};

/*
Command example;
example.category = mt::Category::ColorFiltre;
example.action = destroyOverlay.derivedAction<Unit>( 
[] (Unit& filtre, sf::Time)
{
//do something
});
World::Instance()->getCommandQueue().push(example);
*/