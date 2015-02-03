#pragma once

//Includes
#include <string>

//Namespace

//Defines

//Const

//Prototypes

//Class Prototypes

//Class Declaration
namespace mt
{
	namespace TextureName
	{
		enum TextureName
		{
			Angrosh0=0,
			Cellia0,
			Cellia1,
			Cellia2,
			Cellia3,
			Cellia4,
			Cellia5,
			Cellia6,
			Cellia7,
			Cellia8,
			Cellia9,
			Cellia10,
			Cellia11,
			Cellia12,
			Cellia13,
			Cellia14,
			Cellia15,
			Cellia16,
			Cellia17,
			Cellia18,
			Cellia19,
			Cellia20,
			Cellia21,
			Cellia22,
			Cellia23,
			Cellia24,
			Cellia25,
			Cellia26,
			Cellia27,
			Cellia28,
			Cellia29,
			Cellia30,
			Cellia31,
			Cellia32,
			Goblin,
			Orc,
			Zombie,
			Neydala_Naked,
			Ray0,
			Ray1,
			Ray2,
			Ray3,
			Ray4,
			Ray5,
			Ray6,
			Tex0,
			TreeStd,
			TreeApple,
			TreePixel,
			Overlays,
			Tileset,
			TextureNumber};
	}

	namespace Category
	{
		enum Type
		{
			None = 0,
			SceneNode = 1 << 0,
			Object = 1 << 1,
			Player1Unit = 1 << 2,
			Player2Unit = 1 << 3,
			Allied1Unit = 1 << 4,
			Allied2Unit = 1 << 5,
			Enemy1Unit = 1 << 6,
			Enemy2Unit = 1 << 7,
			NeutralUnit = 1 << 8,
			Selection = 1 << 9,
			ColorFiltre = 1 << 10,
			Map = 1 << 11
		};
		enum TypeCombo
		{
			AnyUnit = 0x1FC, //0x 0001 1111 1100
		};
	}

	namespace Team
	{
		enum Team
		{
			Neutral = 0,
			Player1,
			Player2,
			Allied1,
			Allied2,
			Allied3,
			Enemy1,
			Enemy2,
			Enemy3,
			TeamNumber
		}; 
	}

	namespace Overlay
	{
		enum Type
		{
			ColorFilter = 0,
			Selection
		};
		enum Color
		{
			Orange = 0,
			Blue,
			Purple,
			Green,
			Red,
			White,
			Black,
			Contour
		};
	}

	namespace StateEnum
	{
		enum StateEnum{
			Void = 0,
			Menu = 1 << 0,
			Option = 1 << 1,
			Pause = 1 << 2,
			FreeCamera = 1 << 3,
			Selecting = 1 << 4,
			UnitSelected = 1 << 5,
			UnitSelected_GroundSelected = 1 << 6,
			Tracing = 1 << 7
		};
	}

	namespace Properties
	{
		enum Properties 
		{hp=0,
		maxHp,
		Armor,
		wDamage,
		Initiative,
		movSpeed,
		Facing,
		Vision,
		Range,
		Level,
		xp,
		Strenght,
		Dexterity,
		Intuition,
		Willpower,
		Lifeforce,
		Team,
		any17,any18,any19,any20,any21,any22,any23,any24,any25,any26,
		any27,any28,any29,any30,any31,any32,any33,any34,any35,any36,any37,
		any38,any39,any40,any41,any42,any43,any44,any45,any46,
		PropertiesNumber}; 
	}

	namespace TypeArea{
		enum TypeArea
		{
			CordnerLine = 0,
			Circle,
			nbTypeArea
		};
	}

	namespace Direction
	{
		enum Direction
		{TOP_RIGHT=0, RIGHT, BOT_RIGHT, BOT_LEFT, LEFT, TOP_LEFT};
	}

	enum LoaderType{
		Characters=0, 
		Objects, 
		Tilesets, 
		Property};

	enum TilesetType
	{
		Grass=0,SmoothStone,Dirt,
		SandStone,Sand,Rock,PerfectWood,
		OldWood,DeepGrass,CrackStone,
		CrackDirt,DeepDirt,SandLines,
		MixedGrass,PaleDirt,Contour,
		TilesetTypeNumber
	};

	enum Pathing
	{
		isGround=0, 
		isMagic, 
		isFlying, 
		passGround, 
		passMagic, 
		passFlying
	};

	enum Unit
	{
		Recruit = 0,
		Archer, 
		Assassin, 
		Berseker, 
		Brute, 
		Cleric, 
		Elementalist, 
		Scout, 
		Spearman, 
		Swordman
	};
};
