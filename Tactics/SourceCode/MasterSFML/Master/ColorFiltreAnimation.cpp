//Includes
#include "ColorFiltreAnimation.h"

//Namespace
using namespace std;

//Defines

//Const

//Prototypes

//Class Definition
//Constructor & Destructor
ColorFiltreAnimation::ColorFiltreAnimation()
{
}
ColorFiltreAnimation::~ColorFiltreAnimation()
{
}

//Access Methods

//Modifying methods

//Functions
void ColorFiltreAnimation::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(animatedSprite_, states);
}

void ColorFiltreAnimation::update(sf::Time dt)
{
	if (isAnimated_)
	{
		sf::Color color = animatedSprite_.getColor();

		elapsedTime_ += dt;
		if (elapsedTime_ > duration_)
		{
			isTransparent_ =! isTransparent_;
			elapsedTime_ = sf::Time();
		}

		float percent = elapsedTime_.asSeconds()/duration_.asSeconds();
		if (isTransparent_)
			color.a = 115 + percent*140.0f;
		else
			color.a = 255 - percent*140.0f;

		animatedSprite_.setColor(sf::Color(
			color.r, 
			color.g, 
			color.b,
			color.a)); 
	}
}
//Operator Overloads
