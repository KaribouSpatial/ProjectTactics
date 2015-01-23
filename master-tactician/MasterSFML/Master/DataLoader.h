#pragma once

//Includes
#include "mt.h"
#include "UnitProperties.h"

#include <fstream>
#include <iostream>
#include <vector>

#include <SFML\System.hpp>

//Namespace
using namespace std;

//Defines

//Const

//Prototypes

//Struct

//Typedefs
namespace mt
{
	typedef	std::vector<UnitProperties> unitPropertiesHolder;
}

//Class Declaration
class DataLoader
{
public:

	//Constructor & Destructor

	//Constructor
	DataLoader();

	~DataLoader();
	//Access Methods
	const mt::imgHolder& getCharacterHolder() const;
	const mt::imgHolder& getObjectHolder() const;
	const mt::imgHolder& getTilesetHolder() const;
	const mt::unitPropertiesHolder& getUnitPropertiesHolder() const;

	//Modifying Methods
	void setCharacterHolder(mt::imgHolder characterHolder);
	void setObjectHolder(mt::imgHolder objectHolder);
	void setTilesetHolder(mt::imgHolder tilesetHolder);
	void setUnitPropertiesHolder(mt::unitPropertiesHolder unitPropertiesHolder);

	//Functions
	//loads the Master.mt into the data vectors
	void loadAll(); 
	


	//Operator Overload

private:

	//Private Functions
	/******************************
	//Throws string ifthe Master.mt or Key.mt 
	//file could not be opened. Set the ready 
	//attribute to false ifthe files are corrupted 
	//and true ifthey are ready to be used.
	******************************/
	bool ready();
	/*********************
	//The function is called by the funtion loadAll()
	//once to load the ressources into memory
	**********************/
	mt::imgHolder loadImg(mt::LoaderType type);
	/*********************
	//The function is called by the funtion loadAll()
	//once to load the ressources into memory
	**********************/
	mt::unitPropertiesHolder loadUnitProperties();
	/*********************************************
	//The function is called by the load functions
	//to position the cursor in the right area.
	//THE POSITION OF THE CURSOR IS NOT MODIFIED
	*********************************************/
	ifstream::streampos newPosition(mt::LoaderType type);

	//Private Attributes
	ifstream* master;

	mt::imgHolder characterHolder_;
	mt::imgHolder objectHolder_;
	mt::imgHolder tilesetHolder_;
	mt::unitPropertiesHolder unitPropertiesHolder_;
};
