#pragma once

#if 1 
//Includes
#include <fstream>          //filestream
#include <string>
#include <list>
#include <algorithm>
#include <iostream>
//SFML
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>

#endif

//Namespace
using namespace std;
//Const

//structs
struct binUnitStruct
{
	char name[20];
	short properties[47];
};

struct binImg{
	unsigned int size;
	unsigned int textureName;
	unsigned short width;
	unsigned short height;
	unsigned short spriteWidth;
	unsigned short spriteHeight;
};

struct key{
	unsigned long long first;
	unsigned long long second;
	unsigned long long third;
	unsigned long long last;
};

typedef list<string> slist;
typedef vector<string> svector;

string temp;
svector names;
svector keywords;

string filenames = "Characters\\";
slist curl;
ofstream::streamoff buffer = 0xADDEADDE;

ofstream::streamoff pos1;
ofstream::streamoff pos2;
int textureNumber;



bool setOfUnitStructures(ifstream& file, ofstream& bin);
bool setOfObjectStructures(ifstream& file, ofstream& bin);
bool setOfTilesetStructures(ifstream& file, ofstream& bin);
bool setOfUnitPropertiesStructures(ifstream& file, ofstream& bin);
void keyCheckerGen(ofstream& bin);

int main()
{
	sf::err().rdbuf(NULL);
	ifstream file("characters.txt", ios::in | ios::beg);
	if(file.fail())
		throw "file.open(characters.txt) failed";
	ofstream bin("..\\Data\\Master.mt", ios::binary | ios::out | ios::beg);
	if(bin.fail())
		throw "bin.open(..\\..\\Data\\Master.mt failed";
	try{

	setOfUnitStructures(file, bin);

	setOfObjectStructures(file, bin);

	setOfTilesetStructures(file, bin);

	setOfUnitPropertiesStructures(file, bin);

	keyCheckerGen(bin);
	}
	catch(string error)
	{
		std::cout << error;
	}
	
	std::cout << endl << "Binary file successfully sent to->\n D:\\Travaux\\SVN\\master-tactician\\Data\\Master.mt" << endl << endl;
	//system("pause");
	return EXIT_SUCCESS;
}


bool setOfUnitStructures(ifstream& file, ofstream& bin)
{
	bool bkeywords = false;
	while(true)
	{
		file >> temp;
		if(file.fail())
			break;
		if(temp == "keywords")
		{
			bkeywords=true;
			keywords.push_back("");
		}
		else
		{
		if(bkeywords)
			keywords.push_back(temp);
		else
			names.push_back(temp);
		}
	}
	file.clear();
	file.close();
	if(file.fail())
		throw "file.close()1 failed";

	const int resize = 11;
	
	bin.write((char*)&buffer,sizeof(int));
	if(bin.fail())
		throw "bin.write()1 failed";

	for(auto& name : names)
	{
		filenames.resize(resize);
		filenames += (name + "\\" + name);
		for(auto& keywords1 : keywords)
		{
			filenames.resize(resize+2*name.size()+1);
			filenames += keywords1;
			for(auto& keywords2 : keywords)
			{
				filenames.resize(resize+2*name.size()+1+keywords1.size());
				filenames += keywords2;
				for(auto& keywords3 : keywords)
				{
					filenames.resize(resize+2*name.size()+1+keywords1.size()+keywords2.size());
					filenames += keywords3 + ".png";
					sf::Image image;
					if(image.loadFromFile(filenames) &&
						find(curl.begin(), curl.end(), filenames) == curl.end())
					{
						binImg img;
						img.textureName = curl.size();
						curl.push_back(filenames);
						img.width = image.getSize().x;
						img.height = image.getSize().y;
						img.spriteWidth = 32;
						img.spriteHeight = 32;
						
						img.size = (int)img.width*(int)img.height*4;

						char* pixels = (char*)image.getPixelsPtr();


						bin.write((char*)&img, sizeof(binImg));

						if(bin.fail())
							throw "bin.write()2 failed";

						bin.write(pixels, img.size);

						if(bin.fail())
							throw "bin.write()3 failed";
					}
				}
			}
		}

	}
	pos1 = bin.tellp();
	bin.seekp(0,ios::beg);
	buffer = pos1;
	bin.write((char*)&buffer, sizeof(int));
	if(bin.fail())
		throw "bin.write()4 failed";
	bin.seekp(0, ios::end);
	std::cout << "Current directory contains " << curl.size() << " different images." << endl << endl;
	return EXIT_SUCCESS;

}

bool setOfObjectStructures(ifstream& file, ofstream& bin)
{
	buffer = 0xADDEADDE;

	bin.write((char*)&buffer, sizeof(int));
	if(bin.fail())
		throw "bin.write()5 failed";

	textureNumber = curl.size();

	file.open("objects.txt", ios::in | ios::beg);
	if(file.fail())
		throw "file.open(objects.txt) failed";

	while (true)
	{
		file >> temp;
		if(file.fail())
			break;
		sf::Image image;
		filenames = "Objects\\" + temp + ".png";
		image.loadFromFile(filenames);
		binImg img;

		img.textureName = textureNumber;
		textureNumber++;

		img.width = image.getSize().x;
		img.height = image.getSize().y;
		img.spriteWidth = 32;
		img.spriteHeight = 32;

		img.size = (int)img.width*(int)img.height*4;

		char* pixels = (char*)image.getPixelsPtr();

		bin.write((char*)&img, sizeof(binImg));
		if(bin.fail())
			throw "bin.write()6 failed";

		bin.write(pixels, img.size);
		if(bin.fail())
			throw "bin.write()7 failed";
	}
	file.clear();
	file.close();
	if(file.fail())
		throw "file.close()2 failed";

	pos2 = bin.tellp();
	bin.seekp(pos1, ios::beg);
	buffer = pos2;
	bin.write((char*)&buffer, sizeof(int));
	if(bin.fail())
		throw "bin.write()8 failed";

	bin.seekp(0, ios::end);
	ofstream::streamoff yolo;
	yolo = bin.tellp();
	std::cout << "Now at " << textureNumber << " different images." << endl << endl;

	return EXIT_SUCCESS;
}

bool setOfTilesetStructures(ifstream& file, ofstream& bin)
{
	buffer = 0xADDEADDE;
	bin.write((char*)&buffer, sizeof(int));
	if(bin.fail())
		throw "bin.write()9 failed";

	file.open("tileset.txt", ios::in | ios::beg);
	if(file.fail())
		throw "file.open(tileset.txt) failed";

	if(file.fail())
		return EXIT_FAILURE;

	while (true)
	{
		file >> temp;
		if(file.fail())
			break;
		sf::Image image;
		filenames = "Tileset\\" + temp + ".png";
		image.loadFromFile(filenames);
		binImg img;

		img.textureName = textureNumber;
		textureNumber++;

		img.width = image.getSize().x;
		img.height = image.getSize().y;
		img.spriteWidth = 128;
		img.spriteHeight = 128;

		img.size = (int)img.width*(int)img.height*4;

		char* pixels = (char*)image.getPixelsPtr();

		bin.write((char*)&img, sizeof(binImg));
		if(bin.fail())
			throw "bin.write()10 failed";

		bin.write(pixels, img.size);
		if(bin.fail())
			throw "bin.write()11 failed";
	}
	file.clear();
	file.close();
	if(file.fail())
		throw "file.close()3 failed";

	pos1 = bin.tellp();
	bin.seekp(pos2, ios::beg);
	buffer = pos1;
	bin.write((char*)&buffer, sizeof(int));
	if(bin.fail())
		throw "bin.write()12 failed";

	bin.seekp(0, ios::end);

	std::cout << "Now at " << textureNumber << " different images." << endl << endl;

	return EXIT_SUCCESS;

}

bool setOfUnitPropertiesStructures(ifstream& file, ofstream& bin)
{
	buffer = 0xADDEADDE;
	bin.write((char*)&buffer, sizeof(int));
	if(bin.fail())
		throw "bin.write()13 failed";

	file.open("unit.txt", ios::beg | ios::in);
	if(file.fail())
		throw "file.open(unit.txt) failed";

	binUnitStruct unit;
	string unitName;

	while(true)
	{
		file >> unitName;
		if (file.fail()){
			file.clear();
			file.ignore(20,'\n');
			break;
		}
		unitName.resize(20);
		for(int i = 0; i < 20; ++i)
		{
			unit.name[i] = unitName[i];
		}
		for(int i = 0; i < 47; ++i)
		{
		file >> unit.properties[i];
		}

		bin.write((char*)&unit, sizeof(binUnitStruct));
		if(bin.fail())
			throw "bin.write()14 failed";
	}
	pos2 = bin.tellp();
	bin.seekp(pos1, ios::beg);
	buffer = pos2;
	bin.write((char*)&buffer, sizeof(int));
	if(bin.fail())
		throw "bin.write()15 failed";
	bin.seekp(0, ios::end);

	
	return EXIT_SUCCESS;
}

void keyCheckerGen(ofstream& bin)
{
	ifstream rbin("..\\Data\\Master.mt", ios::binary | ios::in | ios::beg);
	if(rbin.fail())
		throw "rbin.open(..\\Data\\Master.mt) failed";
	
	key keyChecker;
	keyChecker.last = 0xF4D32A31C96B14CD;
	keyChecker.first = keyChecker.last /2;
	keyChecker.second = keyChecker.last ^ keyChecker.first + keyChecker.last;
	keyChecker.third = keyChecker.second*keyChecker.second | keyChecker.first;


	long long red;
	while(true)
	{
		rbin.read((char*)&red,sizeof(long long));
		if(rbin.fail())
			break;
		if(!red == 0)
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

	ofstream newfile("..\\Data\\Key.mt", ios::binary| ios::out | ios::beg);

	if(bin.fail())
		throw "newfile.open(..\\Data\\Ket.mt) failed";
	
	newfile.write((char*)&keyChecker,sizeof(key));

	bin.close();
	newfile.close();
	if(bin.fail() || newfile.fail())
		throw "final close() fail";
}