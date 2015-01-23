//Includes
#include "ColorFiltre.h"

//Namespace
using namespace std;

//Defines

//Const

//Prototypes

//Class Definition
ColorFiltre::ColorFiltre()
{
}

ColorFiltre::ColorFiltre(sf::Texture& texture, GridInfo pos)
{
	setCoordinates(pos);

	animation_.getAnimatedSprite().setTexture(texture);
	animation_.getAnimatedSprite().setTextureRect(sf::IntRect(
		mt::Overlay::Color::White*mt::TilePixel,
		mt::Overlay::Type::ColorFilter*mt::TilePixel,
		(const int)mt::TilePixel,(const int)mt::TilePixel));
	
	sf::Vector2f pixelPosition = mt::calculatePixelPosition(getObjectCoordinates().getPosColumn(),getObjectCoordinates().getPosRow());
	animation_.getAnimatedSprite().setPosition(pixelPosition);

	animation_.getAnimatedSprite().setColor(sf::Color(255,255,255,150));

	animation_.setFrameSize(sf::Vector2i(mt::TilePixel,mt::TilePixel));
	animation_.setIsAnimated(false);
	animation_.getAnimatedSprite().setScale(1.0f,0.495f);
}

ColorFiltre::~ColorFiltre()
{
}

//Access Method

//Modifying method
void ColorFiltre::setColor(mt::Overlay::Color color, mt::Overlay::Type type)
{
	animation_.getAnimatedSprite().setTextureRect(sf::IntRect(color*(const int)mt::TilePixel, type*(const int)mt::TilePixel, (const int)mt::TilePixel, (const int)mt::TilePixel));
	if(color == mt::Overlay::Contour)
		animation_.getAnimatedSprite().setColor(sf::Color(255,255,255,255));
	else
		animation_.getAnimatedSprite().setColor(sf::Color(255,255,255,150));
}

//Function
unsigned int ColorFiltre::getCategory() const
{
	return mt::Category::ColorFiltre;
}

//Operator Overload