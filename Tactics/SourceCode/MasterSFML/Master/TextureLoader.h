#pragma once

//Includes
#include "mt.h"
#include "DataLoader.h"

#include <list>
#include <iostream>         //cout+cin
#include <assert.h>

#include <SFML/Graphics.hpp>

//Namespace
using namespace std;

//Defines

//Const

//Prototypes

//Typedefs


//Class Prototypes

//Class Declaration
class TextureLoader
{
public:

	//Constructor & Destructor
	TextureLoader(DataLoader* loadedData);
	~TextureLoader();

	//Access Methods
	//returns a const reference to the texture
	sf::Texture& getTexture(mt::TextureName::TextureName textureName);

	mt::texPair& getPair(mt::TextureName::TextureName textureName);

	//Modifying methods
	//returns SUCCESS ifload is successful. otherwise returns FAILURE
	bool loadTexture(mt::TextureName::TextureName textureName);

	//loads all textures, true ifsuccessful
	bool loadAll();

	//returns SUCCESS ifunload is successful. otherwise returns FAILURE
	bool unloadTexture(mt::TextureName::TextureName textureName);
	//Functions
	//returns ifthe textureName texture is already loaded.
	bool isLoaded(mt::TextureName::TextureName textureName) const;

	//Operator Overload
	//returns a const reference to the infos of the texture
	const mt::BinImg& operator[](mt::TextureName::TextureName textureName);

private:

	//Private Functions

	//Private Attributes
	DataLoader* loadedData_;
	mt::texHolder textures_;

	class FunctorLoadTexture
	{
	public:

		//Constructor & Destructor
		FunctorLoadTexture()
		{};
		FunctorLoadTexture(const mt::TextureName::TextureName textureName)
		{
			name_ = textureName;
		};
		~FunctorLoadTexture()
		{
		};
		//Access Methods

		//Modifying methods

		//Functions

		//Operator Overload
		template<class A>
		bool operator()(const A pair) const
		{
			if (name_ == pair.first.textureName)
				return true;
			return false;
		};

	private:

		//Private Functions

		//Private Attributes
		mt::TextureName::TextureName name_;
	};

};

