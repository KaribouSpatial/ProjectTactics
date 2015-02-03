#pragma once

//Includes
#include "mt.h"
#include "SceneNode.h"
#include "Pathing.h"
#include "GridInfo.h"

//Namespace
using namespace std;

//Defines

//Const

//Prototypes

//Class Prototypes

//Class Declaration
class Entity : public SceneNode
{
public:

	//Constructor & Destructor
	Entity();
	virtual ~Entity() = 0;
	//Access Method
	//R-only access
	virtual const GridInfo getObjectCoordinates() const;
	virtual mt::TextureName::TextureName getTextureName() const;
	//R-W access
	virtual sf::Sprite& getSprite() = 0;

	//Modifying method
	virtual void setCoordinates(const GridInfo newCoordinates);

	virtual void setPathingInfo(mt::BinPathingStruct pathing);

	//Functions
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override = 0;

	virtual void updateCurrent(sf::Time dt) override = 0;

	virtual unsigned int getCategory() const override = 0;
	//Operator Overload

protected:

	//protected Function

	//protected Attribute
	mt::TextureName::TextureName textureName_;
	GridInfo coordinates_;
	Pathing pathingInfo_;
};
