//Includes
#include "Entity.h"

//Namespace
using namespace std;

//Defines

//Const

//Prototypes

//Class Definition
//Constructor & Destructor
Entity::Entity()
{
}

Entity::~Entity()
{
}

//Access Methods
const GridInfo Entity::getObjectCoordinates() const
{
	return coordinates_;
}

mt::TextureName::TextureName Entity::getTextureName() const
{
	return textureName_;
}

//Modifying methods
void Entity::setCoordinates(const GridInfo newCoordinates)
{
	coordinates_ = newCoordinates;
}

void Entity::setPathingInfo(mt::BinPathingStruct pathing)
{
	pathingInfo_ = pathing;
}

//Functions

//Operator Overloads
