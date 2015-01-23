//Includes
#include "DataLoader.h"

//Namespace
using namespace std;

//Defines

//Const

//Prototypes

//Class Definition
//Constructor & Destructor
DataLoader::DataLoader()
{
	master = new ifstream;
	master->open("Data/Master.mt", ios::binary | ios::in | ios::beg);
	if (master->fail())
		throw runtime_error("Data\\Master.mt could not be found");
}

DataLoader::~DataLoader()
{
	if (master->is_open())
		master->close();
	for(auto& value : characterHolder_)
	{
		delete[] value.second;
	}
	for(auto& value : objectHolder_)
	{
		delete[] value.second;
	}
	for(auto& value : tilesetHolder_)
	{
		delete[] value.second;
	}
	delete master;
	cout << "~" << typeid(*this).name() << endl;
}

//Access Methods
const mt::imgHolder& DataLoader::getCharacterHolder() const
{
	return characterHolder_;
}

const mt::imgHolder& DataLoader::getObjectHolder() const
{
	return objectHolder_;
}

const mt::imgHolder& DataLoader::getTilesetHolder() const
{
	return tilesetHolder_;
}

const mt::unitPropertiesHolder& DataLoader::getUnitPropertiesHolder() const
{
	return unitPropertiesHolder_;
}

//Modifying Methods
void DataLoader::setCharacterHolder(mt::imgHolder characterHolder)
{
	characterHolder_ = characterHolder;
}

void DataLoader::setObjectHolder(mt::imgHolder objectHolder)
{
	objectHolder_ = objectHolder;
}

void DataLoader::setTilesetHolder(mt::imgHolder tilesetHolder)
{
	tilesetHolder_ = tilesetHolder;
}

void DataLoader::setUnitPropertiesHolder(mt::unitPropertiesHolder unitPropertiesHolder)
{
	unitPropertiesHolder_ = unitPropertiesHolder;
}

//Functions
bool DataLoader::ready()
{

	mt::Key keyChecker;
	keyChecker.last = 0xF4D32A31C96B14CD;
	keyChecker.first = keyChecker.last /2;
	keyChecker.second = keyChecker.last ^ keyChecker.first + keyChecker.last;
	keyChecker.third = keyChecker.second*keyChecker.second | keyChecker.first;


	while(true)
	{
		long long red;
		master->read((char*)&red,sizeof(long long));
		if (master->fail())
			break;
		if (!red == 0)
		{
			keyChecker.first *= red;
			keyChecker.second *= red|keyChecker.third;
			keyChecker.third |= red*red;
			keyChecker.last ^= red*keyChecker.first;
		}
		keyChecker.first ^= (keyChecker.first*keyChecker.second+0xC720F739ACBE3512);
		keyChecker.second ^= (keyChecker.second*keyChecker.first+0xF4D32A31C96B14CD);
		keyChecker.last ^= (keyChecker.third*!keyChecker.second+0xBCADEDF1337DEADB);
		keyChecker.third *= !(keyChecker.third) + 0x00D02A01C90B10CD;
	}

	master->clear();
	ifstream KeyLoad("Data\\Key.mt", ios::binary| ios::in | ios::beg);
	if (master->fail())
		throw runtime_error("Data\\Key.mt could not be found");
	mt::Key KeyLoaded;
	KeyLoad.read((char*)&KeyLoaded,sizeof(mt::Key));
	if (master->fail())
		throw runtime_error("Data\\Key.mt is corrupted,\nreinstall or get an official version.");

	if (!(KeyLoaded.first == keyChecker.first &&
		KeyLoaded.second == keyChecker.second &&
		KeyLoaded.third == keyChecker.third &&
		KeyLoaded.last == keyChecker.last))
		throw runtime_error("Source file Master.mt or Key.mt is corrupted,\nreinstall or get an official version.");
	else return SUCCESS;
}

void DataLoader::loadAll()
{
	if (ready())
	{
		characterHolder_ = loadImg(mt::LoaderType::Characters);
		objectHolder_ = loadImg(mt::LoaderType::Objects);
		tilesetHolder_ = loadImg(mt::LoaderType::Tilesets);
		unitPropertiesHolder_ = loadUnitProperties();
	}
}

//Operator Overloads

//Private functions
mt::imgHolder DataLoader::loadImg(mt::LoaderType type)
{
	mt::imgHolder returnValue;
	master->seekg(newPosition(type), ios::beg);
	int maximum = (int)master->tellg();
	master->read((char*)&maximum, sizeof(int));
	do{
		mt::BinImg currentImg;
		master->read((char*)&currentImg, sizeof(mt::BinImg));
		sf::Uint8* currentPixels = new sf::Uint8[currentImg.size];
		for (unsigned i_inc= 0; i_inc < currentImg.size; ++i_inc)
		{
			master->read((char*)&currentPixels[i_inc], sizeof(char));
		}

		returnValue.push_back(mt::imgPair(currentImg,currentPixels));
	}while((int)master->tellg() != maximum);
	return returnValue;
}

mt::unitPropertiesHolder DataLoader::loadUnitProperties()
{
	mt::unitPropertiesHolder returnValue;
	master->seekg(newPosition(mt::LoaderType::Property), ios::beg);
	int maximum = (int)master->tellg();
	master->read((char*)&maximum, sizeof(int));
	do{
		mt::BinUnitProperties currentProperties;
		master->read((char*)&currentProperties, sizeof(mt::BinUnitProperties));
		returnValue.push_back(currentProperties);

	}while((int)master->tellg() != maximum);

	return returnValue;
}

ifstream::streampos DataLoader::newPosition(mt::LoaderType type)
{
	ifstream::streampos saveCursor = master->tellg();
	master->seekg(0,ios::beg);
	for(int i_inc = 0; i_inc < type; ++i_inc)
	{
		int moveSize;
		master->read((char*)&moveSize, sizeof(int));
		master->seekg(moveSize, ios::beg);
	}
	ifstream::streampos returnValue = master->tellg();
	master->seekg(saveCursor, ios::beg);
	master->clear();
	return returnValue;
}
