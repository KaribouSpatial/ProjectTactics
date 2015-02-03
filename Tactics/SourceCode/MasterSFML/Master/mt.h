#pragma once
//Includes
#include "Enum.h"
#include <vector>
#include <utility>
#include <iostream>
#include <exception>
#include <string>
#include <random>           //random
#include <ctime>            //time
#include <functional> //function

#include <SFML/Graphics.hpp>//IntRect
#include <SFML/System.hpp>  //Vector2

//#include
//Namespace

//Defines
#define SUCCESS true
#define FAILURE false

//Const

//Prototypes

//Typedef

namespace mt
{

	//Constantes
	const float TileScaleX = 1.0f;
	const float TileScaleY = 0.5f;
	const float UnitScaleX = 03.0f;
	const float UnitScaleY = 03.0f;
	const float ObjectScaleX = 4.5f;
	const float ObjectScaleY = 4.4f;

	const float UnitPixel = 32.0f;
	const float ObjectPixel = 32.0f;
	const float TilePixel = 128.0f;

	const sf::Time SecondPerFrame = sf::seconds(1.0f/60.0f);

	const int TilesetTextureResolution = 128;
	const int UnitTextureNumber = mt::TextureName::Tex0;
	const int AllTextureNumber = mt::TextureName::TextureNumber;

	const short PathingNumber = mt::Pathing::passFlying+1;

	//has to be divided by 100 for a %
	const int ArmorTable[61] = {
		0,4,7,9,11,13,15,17,19,20,22,23,24,25,26,27,28,28,29,29,30,
		33,36,38,40,42,44,45,47,48,50,51,52,53,54,55,55,56,56,57,57,
		61,63,65,67,69,71,73,74,76,77,78,79,80,81,82,83,83,84,84,85};


	//returns negative = -1 ; ==0 = 0 ; positive = 1
	int sign(int value);
	//returns the positive of value
	int abs(int value);
	//returns the highest of 2 value
	int max2(int value1, int value2);
	//returns the highest of 2 value
	int max3(int value1, int value2, int value3);
	//returns sqrt of value
	float sqrt(float value);
	//returns 1/sqrt of value
	float invsqrt(float value, int precision = 0);
	//returns the scaled damage of an attack
	int calculateDamage(int armor, int weaponDamage, int strenght);
	//returns the 2 floats x,y of desired position, according to the tileset texture size
	sf::Vector2f calculatePixelPosition(int column, int row, float sizeX = 128.0f, float sizeY = 128.0f);
	//returns the pixel coordinates_ of the grid position according to the camera
	sf::Vector2f calculateObjectPixelPosition(int column, int row, float sizeX = 128.0f, float sizeY = 128.0f);
	//returns a random int from min to max, default 0 to 2. !MAX IS FIRST!
	int random(int max = 2, int min = 0);
	
	//returns a vector of textureName that can be use to assign to map tiles
	typedef std::vector<std::vector<TextureName::TextureName>> TextureArray;
	TextureArray generateTextureArray(int size);

	//Structures
	struct BinUnitStruct
	{
		BinUnitStruct() {
			for each (char& value in name)
				value = '\0';
			for each (short& value in properties)
				value = 0;
		}
		char name[20];
		short properties[Properties::PropertiesNumber];
	};

	struct BinPathingStruct
	{
		BinPathingStruct(bool isGround=0,bool isMagic=0,bool isFlying=0,
			bool passGround=1, bool passMagic=1, bool passFlying=1)
		{
			pathing[mt::Pathing::isGround] = isGround;
			pathing[mt::Pathing::isMagic] = isMagic;
			pathing[mt::Pathing::isFlying] = isFlying;
			pathing[mt::Pathing::passGround] = passGround;
			pathing[mt::Pathing::passMagic] = passMagic;
			pathing[mt::Pathing::passFlying] = passFlying;
		}
		bool operator[](mt::Pathing path) const
		{
			return pathing[path];
		}
		bool pathing[PathingNumber];
	};
	const BinPathingStruct stdGround(1,0,0,0,1,1);
	const BinPathingStruct stdFly(0,0,1,1,1,0);
	const BinPathingStruct stdEtherealGround(1,0,1,1,1,0);
	const BinPathingStruct stdEtherealFly(0,1,1,1,1,0);
	const BinPathingStruct stdPassable(0,0,0,1,1,1);

	struct Toggle{
		Toggle()
		{
			state = false;
			toggled = false;
		}
		void toggle()
		{
			state = !state;
			toggled = true;
		}
		bool operator()() const
		{
			return state;
		}
		/*****************************
		//State true: is activated
		//State false: is deactivated
		*****************************/
		bool toggled;
	private:
		bool state;
	};

	struct BinUnitProperties
	{
		char name[20];
		short properties[47];
	};

	struct BinImg{
		BinImg()
		{
			size=0;
			textureName=0;
			width=0;
			height=0;
			spriteWidth=0;
			spriteHeight=0;
		}
		unsigned int size;
		unsigned int textureName;
		unsigned short width;
		unsigned short height;
		unsigned short spriteWidth;
		unsigned short spriteHeight;
	};

	struct Key{
		unsigned long long first;
		unsigned long long second;
		unsigned long long third;
		unsigned long long last;
	};

	//typedef
	typedef std::pair<BinImg,sf::Uint8*> imgPair;
	typedef std::vector<imgPair> imgHolder;
	typedef std::pair<BinImg,sf::Texture> texPair ;
	typedef std::vector<texPair> texHolder;

}

