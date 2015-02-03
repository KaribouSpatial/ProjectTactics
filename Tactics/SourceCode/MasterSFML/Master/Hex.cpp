//Includes
#include "Hex.h"

//Namespace
using namespace std;

//Defines

//Const

//Prototypes
array<GeneratorArea*,mt::TypeArea::nbTypeArea>* Hex::_areaGenerator = nullptr;

//Class Definition
//Constructor & Destructor
Hex::Hex()
{
	isBorder_ = false;
}

Hex::~Hex()
{
	adjacentHex_.clear();
	hexEntities_.clear();
}

//Access Methods
Hex* Hex::getAdjacentHex(mt::Direction::Direction direction) const
{
	return adjacentHex_[direction];
}

Hex* Hex::getAdjacentHex(int direction) const
{
	return adjacentHex_[direction];
}

mt::TilesetType Hex::getTilesetType() const
{
	return tilesetType_;
}

GridInfo Hex::getGridInfo() const
{
	return gridInfo_;
}

list<Entity*>* Hex::getEntities()
{
	return &hexEntities_;
}

//Modifying methods
void Hex::setTilesetType(mt::TilesetType tilesetType)
{
	tilesetType_ = tilesetType;
}

void Hex::setGridInfo(int posX, int posY, int posZ)
{
	gridInfo_.setPosX(posX);
	gridInfo_.setPosY(posY);
	gridInfo_.setPosZ(posZ);
}
void Hex::setGridInfo(int column, int row)
{
	gridInfo_.setPosColumn(column);
	gridInfo_.setPosRow(row);
}

//add an "Object&" to the Hex's "list<Object*> hexEntities_"
void Hex::modifyHexObject_add(Entity& newEntity)
{
	hexEntities_.push_front(&newEntity);
	(*hexEntities_.begin())->setCoordinates(gridInfo_);
}

//remove the pointed Object from the Hex's "list<Object*> hexEntities_", does nothing ifthe object is not found
void Hex::modifyHexObject_delete(Entity& deletedEntity)
{
	auto it = find(hexEntities_.begin(),hexEntities_.end(), &deletedEntity);
	if (it != hexEntities_.end())
		hexEntities_.erase(it);
}

//Functions
void Hex::Create()
{
	_areaGenerator = GeneratorAreaFactory::Instance()->createGenerators();

	GeneratorAreaFactory::Instance()->erase();
}

void Hex::Erase()
{
	for(auto generator: *_areaGenerator)
	{
		delete generator;
		generator = nullptr;
	}
	delete _areaGenerator;
}

bool Hex::isBorder() const
{
	return isBorder_;
}

bool Hex::isEmpty() const
{
	if (hexEntities_.size() == 0)
		return true;
	else
		return false;
}

int Hex::calculateDistance(const Hex* targetHex) const
{
	int value = mt::max3(
		mt::abs(targetHex->gridInfo_.getPosX() - gridInfo_.getPosX()),
		mt::abs(targetHex->gridInfo_.getPosY() - gridInfo_.getPosY()),
		mt::abs(targetHex->gridInfo_.getPosZ() - gridInfo_.getPosZ()));
	return value;
}

vector<Hex*> Hex::generateArea(GeneratorParameters param, mt::TypeArea::TypeArea type)
{
	return (*_areaGenerator)[type]->generateArea(this,param);
}

//setAdjacent Functions block
#if 1
//called once by the map to set up adjacentHex_
void Hex::setAdjacent(Map* map)
{
	setAdjacentHex_0(map);
	setAdjacentHex_1(map);
	setAdjacentHex_2(map);
	setAdjacentHex_3(map);
	setAdjacentHex_4(map);
	setAdjacentHex_5(map);
}

//Private Functions
void Hex::setAdjacentHex_0(Map* map)
{
	int column = gridInfo_.getPosColumn();
	int row = gridInfo_.getPosRow();

	assert(this == (map->getHex(column, row)));
	
	//setting adjacentHex_[0]
	if (row != 0)
	{
		//if (row is impair)
		if (row & 1)
		{
			adjacentHex_.push_back((map->getHex(column, row - 1)));
		}
		//row is pair
		else if (column != map->getWidth() - 1)
		{
			adjacentHex_.push_back(map->getHex(column + 1, row - 1));
		}
		//if (last hex on row) push null
		else
		{
			adjacentHex_.push_back(nullptr);
			isBorder_ = true;
		}
	}
	//if (first row) push null
	else
	{
		adjacentHex_.push_back(nullptr);
		isBorder_ = true;
	}
}

void Hex::setAdjacentHex_1(Map* map)
{
	int column = gridInfo_.getPosColumn();
	int row = gridInfo_.getPosRow();

	assert(this == (map->getHex(column, row)));

	//setting adjacentHex_[1]
	if (column != map->getWidth() - 1)
	{
		adjacentHex_.push_back(map->getHex(column + 1, row));
	}
	//if (last hex on row) push null
	else
	{
		adjacentHex_.push_back(nullptr);
		isBorder_ = true;
	}
}

void Hex::setAdjacentHex_2(Map* map)
{
	int column = gridInfo_.getPosColumn();
	int row = gridInfo_.getPosRow();

	assert(this == (map->getHex(column, row)));
	
	//setting adjacentHex_[2]
	if (row != map->getHeight() - 1)
	{
		//if (row is impair)
		if (row & 1)
		{
			adjacentHex_.push_back(map->getHex(column, row + 1));
		}
		//row is pair
		else if (column != map->getWidth() - 1)
		{
			adjacentHex_.push_back(map->getHex(column + 1, row + 1));
		}
		//if (last hex on row) push null
		else
		{
			adjacentHex_.push_back(nullptr);
			isBorder_ = true;
		}
	}
	//if (last row) push null
	else
	{
		adjacentHex_.push_back(nullptr);
		isBorder_ = true;
	}
}

void Hex::setAdjacentHex_3(Map* map)
{
	int column = gridInfo_.getPosColumn();
	int row = gridInfo_.getPosRow();

	assert(this == (map->getHex(column, row)));
	
	//setting adjacentHex_[3]
	if (row != map->getHeight() - 1)
	{
		//if (row is impair)
		if (row & 1)
		{
			if (column != 0)
			{
				adjacentHex_.push_back(map->getHex(column - 1, row + 1));
			}
			//if (first column) push null
			else
			{
				adjacentHex_.push_back(nullptr);
				isBorder_ = true;
			}
		}
		//row is pair
		else 
		{
			adjacentHex_.push_back(map->getHex(column, row + 1));
		}
	}
	//if (last row) push null
	else
	{
		adjacentHex_.push_back(nullptr);
		isBorder_ = true;
	}
}

void Hex::setAdjacentHex_4(Map* map)
{
	int column = gridInfo_.getPosColumn();
	int row = gridInfo_.getPosRow();

	assert(this == (map->getHex(column, row)));
	
	//setting adjacentHex_[4]
	if (column != 0)
	{
		adjacentHex_.push_back(map->getHex(column - 1, row));
	}
	//if (first column) push null
	else 
	{
		adjacentHex_.push_back(nullptr);
		isBorder_ = true;
	}
}

void Hex::setAdjacentHex_5(Map* map)
{
	int column = gridInfo_.getPosColumn();
	int row = gridInfo_.getPosRow();

	assert(this == (map->getHex(column, row)));
	
	//setting adjacentHex_[5]
	if (row != 0)
	{
		//if (row is impair)
		if (row & 1)
		{
			if (column != 0)
			{
				adjacentHex_.push_back(map->getHex(column - 1, row - 1));
			}
			//if (first column) push null
			else
			{
				adjacentHex_.push_back(nullptr);
				isBorder_ = true;
			}
		}
		//row is pair
		else 
		{
			adjacentHex_.push_back(map->getHex(column, row - 1));
		}
	}
	//if (first row) push null
	else
	{
		adjacentHex_.push_back(nullptr);
		isBorder_ = true;
	}
}
#endif

//Operator Overloads
//returns true ifboth hexes have the same coordinates
bool Hex::operator==(Hex target) const
{
	if (this->gridInfo_ == target.gridInfo_)
		return true;
	else
		return false;
}


