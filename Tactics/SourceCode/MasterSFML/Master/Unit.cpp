//Includes
#include "Unit.h"

//Namespace
using namespace std;

//Defines

//Const

//Prototypes

//Class Definition
//Constructor & Destructor
Unit::Unit()
{
}

Unit::Unit(mt::texPair& texture, mt::BinPathingStruct pathing, GridInfo startPos, UnitProperties unitProperties)
{
	coordinates_ = startPos;
	pathingInfo_ = pathing;
	textureName_ = (mt::TextureName::TextureName)texture.first.textureName;

	setUnitProperties(unitProperties);
	
	animation_.setDirection((mt::Direction::Direction)unitProperties_.get(mt::Properties::Facing));
	
	animation_.getAnimatedSprite().setTexture(texture.second);
	
	int spriteWidth  = texture.first.spriteWidth;
	int spriteHeight = texture.first.spriteHeight;

	//TODO: (0,0) is arbitrary. Should be changed to fit what we want to draw
	animation_.getAnimatedSprite().setTextureRect(sf::IntRect(0,0,spriteWidth,spriteHeight)); 

	//scaling, could depend on the object being drawn
	animation_.getAnimatedSprite().setScale(mt::UnitScaleX,mt::UnitScaleY);
	//centering on the bottom middle to be able to scale any amount and still have a fixed point from where the object "Raise"
	animation_.getAnimatedSprite().setOrigin(
		(float)spriteWidth/2, 
		(float)spriteHeight);

	//Position in the display
	sf::Vector2f pixelPosition = 
		mt::calculateObjectPixelPosition(
		coordinates_.getPosColumn(), 
		coordinates_.getPosRow());
	animation_.getAnimatedSprite().setPosition(pixelPosition);

	animation_.setFrameSize(sf::Vector2i(spriteWidth, spriteHeight));
	animation_.setNumFrame(3);
	animation_.setDuration(sf::seconds(0.5));

	setID(0);

	//Testing purpose
	animation_.setIsAnimated(true);
}

Unit::Unit(Unit& unit)
{
	//not copyable
	assert(false);
}

Unit::~Unit()
{
	cout << "~" << typeid(*this).name() << endl;
}

//Access Methods
short Unit::getUnitProperties(mt::Properties::Properties properties) const
{
	return unitProperties_.get(properties);
}

string Unit::getName() const
{
	return unitProperties_.getName();
}

UnitAnimation& Unit::getAnimation()
{
	return animation_;
}

sf::Sprite& Unit::getSprite()
{
	return animation_.getAnimatedSprite();
}

//Modifying methods
void Unit::setUnitProperties(const UnitProperties& unitProperties)
{
	unitProperties_ = unitProperties;
}

void Unit::setUnitProperties(mt::Properties::Properties properties, short value)
{
	unitProperties_.set(properties, value);
}

//Functions
void Unit::dealDamageTo(Unit* attackedUnit) const
{
	cout << "Attacking unit wdamage: \t" << unitProperties_.get(mt::Properties::wDamage) << endl;
	cout << "Attacking unit strenght: \t" << unitProperties_.get(mt::Properties::Strenght) << endl;
	int scaledDamage = mt::calculateDamage(attackedUnit->unitProperties_.get(mt::Properties::Armor), unitProperties_.get(mt::Properties::wDamage), unitProperties_.get(mt::Properties::Strenght));
	cout << "Final damage: \t" << scaledDamage << endl;
	cout << "Attacked unit armor: \t" << attackedUnit->unitProperties_.get(mt::Properties::Armor) << endl;
	cout << "Attacked unit hp before: \t" << attackedUnit->unitProperties_.get(mt::Properties::hp) << endl;
	int attackedHp = attackedUnit->unitProperties_.get(mt::Properties::hp);
	attackedUnit->unitProperties_.set(mt::Properties::hp,attackedHp - scaledDamage);
	cout << "Attacked unit hp after: \t" << attackedUnit->unitProperties_.get(mt::Properties::hp) << endl;
}

void Unit::updateAnimation(sf::Time dt)
{
	animation_.setDirection((mt::Direction::Direction)unitProperties_.get(mt::Properties::Facing));
	animation_.update(dt);
}

//Inherited Functions
void Unit::updateCurrent(sf::Time dt)
{
	updateAnimation(dt);
	if (unitProperties_.get(mt::Properties::hp) <= 0)
	{
	}
}

void Unit::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(animation_, states);
}

unsigned int Unit::getCategory() const
{
	unsigned int team = unitProperties_.get(mt::Properties::Team);
	switch (team)
	{
	case mt::Team::Neutral:
		return mt::Category::NeutralUnit;

	case mt::Team::Player1:
		return mt::Category::Player1Unit;

	case mt::Team::Player2:
		return mt::Category::Player2Unit;

	case mt::Team::Allied1:
		return mt::Category::Allied1Unit;

	case mt::Team::Allied2:
		return mt::Category::Allied2Unit;

	case mt::Team::Allied3:
		return mt::Category::Allied1Unit | mt::Category::Allied2Unit;

	case mt::Team::Enemy1:
		return mt::Category::Enemy1Unit;

	case mt::Team::Enemy2:
		return mt::Category::Enemy2Unit;

	case mt::Team::Enemy3:
		return mt::Category::Enemy1Unit | mt::Category::Enemy2Unit;

	default:
		return mt::Category::None;
	}
}

//Operator Overloads