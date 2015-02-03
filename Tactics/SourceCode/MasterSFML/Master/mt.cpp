//Includes
#include "mt.h"

//Namespace

//Defines

//Const

//Prototypes
double inline __fastcall fastSqrt(double value);

//Functions
//returns -1 ifnegative ; 0 if==0 ; 1 ifpositive
int mt::sign(int value)
{
	if (value > 0) 
		return 1;
	else if (value < 0)
		return -1;
	else 
		return 0;
}

//returns the positive of value
int mt::abs(int value)
{
	if (value>=0)
		return value;
	return sign(value)*value;
}

//returns the highest of 2 value
int mt::max2(int value1, int value2)
{
	if (value1 > value2)
		return value1;
	else
		return value2;
}

//returns the highest of 3 value
int mt::max3(int value1, int value2, int value3)
{
	if (value1 > value2)
		if (value1 > value3)
			return value1;
		else
			return value3;
	else if (value2 > value3)
		return value2;
	else 
		return value3;
}

//returns sqrt of value
float mt::sqrt(float value)
{
	return (float)fastSqrt((double)value);
}

//returns an approximation of 1/sqrt of value
float mt::invsqrt(float value, int precision)
{
	const float threehalfs = 1.5F;

	float number = value;
	float x2 = number * 0.5F;
	float y  = number;
	long i  = * ( long * ) &y;                       // evil floating point bit level hacking
	i  = 0x5f3759df - ( i >> 1 );               // what the fuck?
	y  = * ( float * ) &i;
	y  = y * ( threehalfs - ( x2 * y * y ) );   // 1st iteration
	for ( int i_inc = 0 ; i_inc < precision ; ++i_inc)
	{
		y  = y * ( threehalfs - ( x2 * y * y ) );   // 2nd iteration, this can be removed
	}
	return y;
}//found on: en.wikipedia.org/wiki/Fast_inverse_square_root

//returns the scaled damage of an attack
int mt::calculateDamage(int armor, int weaponDamage, int strenght)
{
	float armorModifier = float(100 - mt::sign(armor)*mt::ArmorTable[mt::abs(armor)])/100;
	//damage algorithm is: (x-5)/2+sqrt(64*y)
	//damage algorithm is: (strenght-5)/2+sqrt(64*weaponDamage)
	float damageModofier = (float)((strenght-5)>>1) + (float)mt::sqrt((float)(weaponDamage<<6));
	return int(armorModifier*damageModofier);
}

//returns the 2 floats x,y of desired position, according to the tileset texture size
sf::Vector2f mt::calculatePixelPosition(int column, int row, float sizeX, float sizeY)
{
	//ifrow is impair, starts at x=0
	//ifrow is pair, starts at x=sizeX/2
	float xPos = sizeX/2*!(row&1)+column*sizeX; //64*column

	float yPos = (sizeY*0.375f+1)*row; //49*row, +1 is to make the hexes look better on the diagonal edges

	return sf::Vector2f(xPos, yPos);
}

//returns the pixel coordinates_ of the grid position according to the camera
sf::Vector2f mt::calculateObjectPixelPosition(int column, int row, float sizeX, float sizeY)
{
	sf::Vector2f pixelPosition = calculatePixelPosition(column, row, sizeX, sizeY);

	pixelPosition.x  += sizeX/2; //origin is in the middle, so add half the lenght to the position

	pixelPosition.y  += sizeY - 88 ; //88 magic number to adjust height of origin of sprite

	return pixelPosition;
}

//returns a random int from min to max, default 0 to 2. !MAX IS FIRST!
int mt::random(int max, int min)
{
	std::random_device randomEngine;
	std::uniform_int_distribution<int> distribution(min,max);
	int i = distribution(randomEngine);
	return i;
}

//returns a vector of textureName that can be use to assign to map tiles TODO
std::vector<std::vector<mt::TextureName::TextureName>> mt::generateTextureArray(int size)
{
	std::vector<std::vector<mt::TextureName::TextureName>> textVect;
	for ( int row = 0 ; row < size ; ++row)
	{

		for ( int column = 0 ; column < size ; ++column)
		{
			//TODO
		}
	}
	return textVect;
}

//fast sqrt
double inline __declspec(naked) __fastcall fastSqrt(double value)
{
	_asm fld qword ptr [esp+4]
	_asm fsqrt
	_asm ret 8
}//found on: www.codeproject.com/Articles/69941/Best-Square-Root-Method-mt-Function-Precisi