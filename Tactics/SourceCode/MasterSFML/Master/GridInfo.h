#pragma once

//Includes
#include "mt.h"

#include <iostream>

//Namespace
using namespace std;

//Defines

//Const

//Prototypes

//Class Prototypes

//Class Declaration
class GridInfo
{
public:
	GridInfo(int column = 1, int row = 1);
	GridInfo(int x, int y, int z);
	GridInfo(const GridInfo& coordinates_);
	virtual ~GridInfo();

	//Access Methods
	int getPosColumn() const;
	int getPosRow() const;
	int getPosX() const;
	int getPosY() const;
	int getPosZ() const;
	bool isDirty() const;

	//Modifying Methods
	void setPosColumn(int posColumn);
	void setPosRow(int posRow);
	void setPosX(int posX);
	void setPosY(int posY);
	void setPosZ(int posZ);
	
	//Function
	//using move corrupts the 2axis infos, use refresh() to fix it
	GridInfo& move(mt::Direction::Direction direct);
	//restores the 2axis coordinates according to the current 3axis coordinates
	GridInfo refresh();

	//operator overload
	//Operator== compares only position column/row
	bool operator==(GridInfo gridInfos) const;
	//Operator= copies all values
	GridInfo& operator=(const GridInfo& coord);

protected:
	//Protected
	int posColumn_;
	int posRow_;
	int posX_;
	int posY_;
	int posZ_;

private:
	bool isDirty_;
};

