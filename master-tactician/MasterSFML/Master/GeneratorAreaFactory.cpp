//Includes
#include "GeneratorAreaFactory.h"

#include "GeneratorCornerLine.h"
#include "GeneratorCircle.h"

//Namespace
using namespace std;

//Defines

//Const

//Prototypes
GeneratorAreaFactory* GeneratorAreaFactory::_instance = nullptr;

//Class Definition
GeneratorAreaFactory::GeneratorAreaFactory()
{
}

GeneratorAreaFactory::~GeneratorAreaFactory()
{
	_instance = nullptr;
	cout << "~" << typeid(*this).name() << endl;
}

void GeneratorAreaFactory::erase()
{
	delete _instance;
}

//Singleton specific
GeneratorAreaFactory* GeneratorAreaFactory::Instance()
{
	if (_instance == nullptr) 
	{ 
		_instance = new GeneratorAreaFactory();
	}
	return _instance;
}

//Access Method

//Modifying method

//Function

array<GeneratorArea*,mt::TypeArea::nbTypeArea>* GeneratorAreaFactory::createGenerators()
{
	array<GeneratorArea*,mt::TypeArea::nbTypeArea>* generators = new array<GeneratorArea*,mt::TypeArea::nbTypeArea>;
	(*generators)[mt::TypeArea::CordnerLine] = new GeneratorCornerLine();
	(*generators)[mt::TypeArea::Circle] = new GeneratorCircle();
	return generators;
}
//Operator Overload