//Includes
#include "Object.h"

//Namespace
using namespace std;

//Defines

//Const

//Prototypes

//Class Definition
//Constructor & Destructor
Object::Object()
{
}

Object::Object(mt::texPair& texture, mt::BinPathingStruct pathing, GridInfo startPos)
{
	coordinates_ = startPos;
	pathingInfo_ = pathing;
	textureName_ = (mt::TextureName::TextureName)texture.first.textureName;

	animation_.getAnimatedSprite().setTexture(texture.second);
	
	int spriteWidth  = texture.first.spriteWidth;
	int spriteHeight = texture.first.spriteHeight;

	//TODO: (0,0) is arbitrary. Should be changed to fit what we want to draw
	animation_.getAnimatedSprite().setTextureRect(sf::IntRect(0,0,spriteWidth,spriteHeight)); 

	//scaling, could depend on the object being drawn
	animation_.getAnimatedSprite().setScale(mt::ObjectScaleX,mt::ObjectScaleY);
	//centering on the bottom middle to be able to scale any amount and still have a fixed point from where the object "Raise"
	animation_.getAnimatedSprite().setOrigin(spriteWidth/2.0f, (float)spriteHeight);

	//Position in the display
	sf::Vector2f pixelPosition = 
		mt::calculateObjectPixelPosition(
		coordinates_.getPosColumn(), 
		coordinates_.getPosRow(), 
		//parameter sizeX and sizeY have to be width and height of tiles texture
		mt::TilePixel, mt::TilePixel);
	
	animation_.getAnimatedSprite().setPosition(pixelPosition);
	
	animation_.setFrameSize(sf::Vector2i(spriteWidth, spriteHeight));
	animation_.setNumFrame(12);
	animation_.setDuration(sf::seconds(36));

	setID(0);

	//Testing purpose
	animation_.setIsAnimated(true);
}

Object::Object(Object& object)
{
	//not copyable
	throw runtime_error("Illegal operation: Object::Object(Object& object)");
}

Object::~Object()
{
	cout << "~" << typeid(*this).name() << endl;
}

//Access Methods
sf::Sprite& Object::getSprite()
{
	return animation_.getAnimatedSprite();
}

//Modifying methods


//Functions
 void Object::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
 {
	 target.draw(animation_, states);
 }

 void Object::updateAnimation(sf::Time dt)
 {
	 animation_.update(dt);
 }

 void Object::updateCurrent(sf::Time dt)
 {
	 updateAnimation(dt);
 }
 unsigned int Object::getCategory() const
 {
	 return mt::Category::Object;
 }
//Operator Overloads