//Includes
#include "GeneratorCircle.h"

//Namespace
using namespace std;

//Defines

//Const

//Prototypes

//Class Definition
GeneratorCircle::GeneratorCircle()
{
}

GeneratorCircle::~GeneratorCircle()
{
	cout << "~" << typeid(*this).name() << endl;
}

//Access Method

//Modifying method

//Function
GeneratorArea::Area GeneratorCircle::generateArea(Hex* center, GeneratorParameters param)
{
	return generateCircle(center, param);
}

GeneratorArea::Area GeneratorCircle::generateCircle(Hex* center, GeneratorParameters param)
{
	vector<Hex*> area;
	vector<GridInfo> proxyArea;

	GridInfo current = center->getGridInfo();
	GridInfo first = current;
	//GridInfo grid = current;

	int rayon = param.width_;

	using namespace mt::Direction;
	//placing the first
	for(int diago_inc = 0; diago_inc < rayon; ++diago_inc)
	{
		current.move(TOP_LEFT);
	}
	first = current;
	//for each row
	for(int row_inc = 0; row_inc < 2*rayon+1; ++row_inc)
	{
		//for each column
		for(int column_inc = 0; column_inc < 2*rayon+1 - mt::abs(rayon - row_inc); ++column_inc)
		{
			proxyArea.push_back(current);
			current.move(RIGHT);
		}
		if (row_inc < rayon)
			first.move(BOT_LEFT);
		else
			first.move(BOT_RIGHT);
		current = first;
	}
	for(auto grid: proxyArea)
	{
		Hex* hex = Map::Instance()->getHex(grid);
		if (hex != nullptr)
			area.push_back(hex);
	}

	return area;
}
//Operator Overload
