//Includes
#include "SelectionFiltre.h"

//Namespace
using namespace std;

//Defines

//Const

//Prototypes

//Class Definition
SelectionFiltre::SelectionFiltre()
{
}

SelectionFiltre::SelectionFiltre(sf::Texture& texture, GridInfo pos)
{
	setCoordinates(pos);

	animation_.getAnimatedSprite().setTexture(texture);
	animation_.getAnimatedSprite().setTextureRect(sf::IntRect(
		mt::Overlay::Color::White*mt::TilePixel,
		mt::Overlay::Type::Selection*mt::TilePixel,
		mt::TilePixel,mt::TilePixel));
	
	sf::Vector2f pixelPosition = mt::calculatePixelPosition(getObjectCoordinates().getPosColumn(),getObjectCoordinates().getPosRow());
	animation_.getAnimatedSprite().setPosition(pixelPosition);

	animation_.getAnimatedSprite().setColor(sf::Color(255,255,255,255));

	animation_.setFrameSize(sf::Vector2i(mt::TilePixel,mt::TilePixel));
	animation_.getAnimatedSprite().setScale(1.0f,0.495f);

	animation_.setNumFrame(3);
	animation_.setDuration(sf::seconds(1.5f));
}

SelectionFiltre::~SelectionFiltre()
{
	cout << "~" << typeid(*this).name() << endl;
}

//Access Method

//Modifying method
void SelectionFiltre::setColor(mt::Overlay::Color color, mt::Overlay::Type type)
{
	animation_.getAnimatedSprite().setTextureRect(sf::IntRect(color*(const int)mt::TilePixel, type*(const int)mt::TilePixel, (const int)mt::TilePixel, (const int)mt::TilePixel));
}

//Function
unsigned int SelectionFiltre::getCategory() const
{
	return mt::Category::Selection;
}
//Operator Overload