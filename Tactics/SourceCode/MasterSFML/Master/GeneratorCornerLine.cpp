//Includes
#include "GeneratorCornerLine.h"

//Namespace
using namespace std;

//Defines

//Const

//Prototypes

//Class Definition
GeneratorCornerLine::GeneratorCornerLine()
{
}

GeneratorCornerLine::~GeneratorCornerLine()
{
	cout << "~" << typeid(*this).name() << endl;
}

//Access Method

//Modifying method

//Function
GeneratorArea::Area GeneratorCornerLine::generateArea(Hex* center, GeneratorParameters param)
{
	return generateCornerLine(center, param);
}

GeneratorArea::Area GeneratorCornerLine::generateCornerLine(Hex* center, GeneratorParameters param)
{
	vector<Hex*> area;
	Hex* current = center;
	Hex* previous = nullptr;
	Hex* temp = nullptr;

	unsigned direction = param.direction_;
	unsigned direction_inc;
	if (direction == 5)
		direction_inc = 0;
	else
		direction_inc = direction + 1;

	//we consider only width[2,3], otherwise, its considered width=2
	switch (param.width_)
	{
	case 3:
		previous = temp = current;
		for(unsigned i_inc = 0; i_inc < param.lenght_; ++i_inc)
		{
			if (temp != nullptr)
			{
				previous = temp->getAdjacentHex(direction);
				if (previous != nullptr)
					area.push_back(previous);

				current = temp->getAdjacentHex(direction_inc);
				if (current != nullptr)
					area.push_back(current); 
			}
			else 
			{
				if (current != nullptr)
				{
					current = current->getAdjacentHex(direction);
					if (current != nullptr)
						area.push_back(current);
				}
				if (previous != nullptr)
				{
					previous = previous->getAdjacentHex(direction_inc);
					if (previous != nullptr)
						area.push_back(previous);
				}
			}
			temp = nullptr;

			if(++i_inc >= param.lenght_)
				break;

			if (previous != nullptr)
			{
				temp = previous->getAdjacentHex(direction_inc);
				previous = previous->getAdjacentHex(direction);
				if (previous != nullptr)
						area.push_back(previous);
			}
			if (current != nullptr)
			{
				if (temp == nullptr)
					temp = current->getAdjacentHex(direction);
				current = current->getAdjacentHex(direction_inc);
				if (current != nullptr)
					area.push_back(current);
			}
			if (temp != nullptr)
				area.push_back(temp);
		}
		break;

		//for any other width, we consider width=2
	default:
		for(unsigned i_inc = 0; i_inc < param.lenght_; ++i_inc)
		{
			previous = current->getAdjacentHex(direction);
			if (previous != nullptr)
				area.push_back(previous);

			current = current->getAdjacentHex(direction_inc);
			if (current != nullptr)
				area.push_back(current);
			else
				break;

			if(++i_inc >= param.lenght_ || previous == nullptr)
				break;

			current = current->getAdjacentHex(direction);
			if (current != nullptr)
				area.push_back(current);
			else
				break;
		}
		break;
	}
	return area;
}
//Operator Overload
