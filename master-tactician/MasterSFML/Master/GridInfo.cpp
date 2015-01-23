//Includes
#include "GridInfo.h"
#include "Map.h"

//Namespace
using namespace std;

//Defines

//Const

//Prototypes

//Class Definition
//Constructor & Destructor
GridInfo::GridInfo(int column, int row):
	posColumn_(column),
	posRow_(row),
	posX_(0), posY_(0),posZ_(0), isDirty_(false)
{
}

GridInfo::GridInfo(int x, int y, int z):
	posColumn_(0),
	posRow_(0),
	posX_(x), posY_(y),posZ_(z),
	isDirty_(false)
{
}

GridInfo::GridInfo(const GridInfo& coordinates_)
{
	posColumn_ = coordinates_.posColumn_;
	posRow_ = coordinates_.posRow_;
	posX_ = coordinates_.posX_;
	posY_ = coordinates_.posY_;
	posZ_ = coordinates_.posZ_;
	isDirty_ = coordinates_.isDirty_;
}

GridInfo::~GridInfo()
{
}

//Access Methods
int GridInfo::getPosColumn() const
{
	return posColumn_;
}

int GridInfo::getPosRow() const
{
	return posRow_;
}

int GridInfo::getPosX() const
{
	return posX_;
}

int GridInfo::getPosY() const
{
	return posY_;
}

int GridInfo::getPosZ() const
{
	return posZ_;
}

bool GridInfo::isDirty() const
{
	return isDirty_;
}

//Modifying Methods
void GridInfo::setPosColumn(int posColumn)
{
	posColumn_ = posColumn;
}

void GridInfo::setPosRow(int posRow)
{
	posRow_ = posRow;
}

void GridInfo::setPosX(int posX)
{
	posX_ = posX;
}

void GridInfo::setPosY(int posY)
{
	posY_ = posY;
}

void GridInfo::setPosZ(int posZ)
{
	posZ_ = posZ;
}

//Functions
GridInfo& GridInfo::move(mt::Direction::Direction direct)
{
	switch (direct)
	{
	case mt::Direction::TOP_RIGHT:
		++posY_;
		--posZ_;
		break;
	case mt::Direction::RIGHT:
		++posX_;
		--posZ_;
		break;
	case mt::Direction::BOT_RIGHT:
		++posX_;
		--posY_;
		break;
	case mt::Direction::BOT_LEFT:
		++posZ_;
		--posY_;
		break;
	case mt::Direction::LEFT:
		++posZ_;
		--posX_;
		break;
	case mt::Direction::TOP_LEFT:
		++posY_;
		--posX_;
		break;
	default:
		throw runtime_error("Direction out of bounds in GridInfo::move");
	}
	isDirty_ = true;
	return *this;
}

GridInfo GridInfo::refresh()
{
	if (isDirty_)
	{
		*this = Map::Instance()->getHex(posX_,posY_,posZ_)->getGridInfo();
		isDirty_ = false;
	}
	return *this;
}
//Private Functions

//Operator Overloads
//Operator== compares only position column/row
bool GridInfo::operator==(GridInfo gridInfos) const
{
	if (posColumn_ == gridInfos.posColumn_
		&& posRow_ == gridInfos.posRow_)
		return true;
	else
		return false;
}

GridInfo& GridInfo::operator=(const GridInfo& coord)
{
	posColumn_ = coord.posColumn_;
	posRow_ = coord.posRow_;
	posX_ = coord.posX_;
	posY_ = coord.posY_;
	posZ_ = coord.posZ_;
	isDirty_ = coord.isDirty_;
	return *this;
}
