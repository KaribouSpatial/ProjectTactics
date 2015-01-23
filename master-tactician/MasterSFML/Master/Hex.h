#pragma once

//Includes
#include "mt.h"
#include "Object.h"
#include "Map.h"
#include "GeneratorArea.h"
#include "GeneratorParameters.h"
#include "GeneratorAreaFactory.h"

#include <list>
#include <array>
#include <assert.h>

//Namespace
using namespace std;

//Defines

//Const

//Prototypes

//Class Prototypes
class Map;
class GeneratorArea;

//Class Declaration
class Hex
{
public:
	//Constructor & Destructor
	Hex();
	~Hex();

	//Access Methods
	Hex* getAdjacentHex(mt::Direction::Direction direction) const;
	Hex* getAdjacentHex(int direction) const;
	mt::TilesetType getTilesetType() const;
	GridInfo getGridInfo() const;
	//R-W Access
	list<Entity*>* getEntities();

	//Modifying methods
	void setTilesetType(mt::TilesetType tilesetType);
	void setGridInfo(int posX, int posY, int posZ);
	void setGridInfo(int column, int row);
	//add an "Object&" to the Hex's "list<Object*> hexEntities_"
	void modifyHexObject_add(Entity& newEntity);
	//remove the pointed Object from the Hex's "list<Object*> hexEntities_", does nothing ifthe object is not found
	void modifyHexObject_delete(Entity& deletedEntity);

	///Functions
	//create the generators
	static void Create();
	//destroy the generators
	static void Erase();
	//returns true if the hex is on a border
	bool isBorder() const;
	//returns: true ifthe hexEntities_* list is empty
	bool isEmpty() const;
	//returns shortest distance between hex and target hex
	int calculateDistance(const Hex* targetHex) const;
	//generates a vector of hexes
	vector<Hex*> generateArea(GeneratorParameters param, mt::TypeArea::TypeArea type);
	//called once for each hex by the map to set up adjacentHex_
	void setAdjacent(Map* map);

	//Operator Overload
	//returns true ifboth hexes have the same coordinates
	bool operator==(Hex target) const;

private:

	//Private Functions
	void setAdjacentHex_0(Map* map);
	void setAdjacentHex_1(Map* map);
	void setAdjacentHex_2(Map* map);
	void setAdjacentHex_3(Map* map);
	void setAdjacentHex_4(Map* map);
	void setAdjacentHex_5(Map* map);

	//Private Attributes
	bool isBorder_;
	vector<Hex*> adjacentHex_;
	mt::TilesetType tilesetType_;
	list<Entity*> hexEntities_;
	GridInfo gridInfo_;
	static array<GeneratorArea*,mt::TypeArea::nbTypeArea>* _areaGenerator;
};