#pragma once

//Includes
#include "mt.h"
#include "UnitProperties.h"
#include "Object.h"
#include "GridInfo.h"
#include "Pathing.h"
#include "AnimatedUnit.h"

//Namespace
using namespace std;

//Defines

//Const

//Prototypes

//Class Prototypes

//Class Declaration
class Unit : public Entity, public AnimatedUnit
{
public:

	//Constructor & Destructor
	Unit();
	Unit(mt::texPair& texture, mt::BinPathingStruct pathing,
		GridInfo startPos = GridInfo(0,0),
		UnitProperties unitProperties = UnitProperties());
	Unit(Unit& unit);
	~Unit();
	
	//Access Methods
	short getUnitProperties(mt::Properties::Properties properties) const;
	string getName() const;
	//R-W access
	sf::Sprite& getSprite() override;
	UnitAnimation& getAnimation();
	
	//Modifying methods
	void setUnitProperties(const UnitProperties& unitProperties);
	void setUnitProperties(mt::Properties::Properties properties, short value);

	//Functions
	//attack mechanic, the calling unit attacks the unit given in parameters
	void dealDamageTo(Unit* attackedUnit) const;

	//Inherited Functions
	void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;
	
	void updateCurrent(sf::Time dt) override;

	unsigned int getCategory() const override;
	//Operator Overload

private:
	
	//Private Functions
	
	//update responsible of the animation
	void updateAnimation(sf::Time dt) override;

	//Private Attributes
	UnitProperties unitProperties_;
};