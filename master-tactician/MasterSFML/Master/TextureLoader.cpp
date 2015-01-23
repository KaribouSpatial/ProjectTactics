//Includes
#include "TextureLoader.h"

#include <SFML/Graphics.hpp>

//Namespace
using namespace std;

//Defines

//Macro


//Const

//Prototypes

//Functors


//Class Definition
//Constructor & Destructor
TextureLoader::TextureLoader(DataLoader* loadedData)
{
	loadedData_ = loadedData;
	textures_.resize(mt::AllTextureNumber,mt::texPair(/*mt::BinImg(),sf::Texture()*/));
}

TextureLoader::~TextureLoader()
{
	for (int textureNumber_inc = 0; textureNumber_inc < mt::TextureName::TextureNumber; ++textureNumber_inc)
	{
		unloadTexture((mt::TextureName::TextureName)textureNumber_inc);
	}
	cout << "~" << typeid(*this).name() << endl;
}

//Access Methods
sf::Texture& TextureLoader::getTexture(mt::TextureName::TextureName textureName)
{
	if (!isLoaded(textureName))
		loadTexture(textureName);
	return textures_[textureName].second;
}

mt::texPair& TextureLoader::getPair(mt::TextureName::TextureName textureName)
{
	if (!isLoaded(textureName))
		loadTexture(textureName);
	return textures_[textureName];
}

//Modifying methods
bool TextureLoader::loadTexture(mt::TextureName::TextureName textureName)
{
	assert(!isLoaded(textureName));
	FunctorLoadTexture pairCompare(textureName);
	auto imgIt = find_if (loadedData_->getCharacterHolder().begin(), loadedData_->getCharacterHolder().end(), pairCompare);

	if ( imgIt == loadedData_->getCharacterHolder().end())
	{
		imgIt = find_if (loadedData_->getObjectHolder().begin(), loadedData_->getObjectHolder().end(), pairCompare);
		if (imgIt == loadedData_->getObjectHolder().end())
			imgIt = find_if (loadedData_->getTilesetHolder().begin(), loadedData_->getTilesetHolder().end(), pairCompare);
	}
	textures_[textureName].first = imgIt->first;
	textures_[textureName].second.create(imgIt->first.width,imgIt->first.height);
	textures_[textureName].second.update(imgIt->second);
	textures_[textureName].second.setSmooth(false);
	cout << "Adding new texture to the map, of type: " << textureName << endl;

	return SUCCESS;
}

bool TextureLoader::loadAll()
{
	for (int textureNumber_inc = 0; textureNumber_inc < mt::AllTextureNumber; ++textureNumber_inc)
	{
		if (!loadTexture(mt::TextureName::TextureName(textureNumber_inc)))
			return FAILURE;
	}
	return SUCCESS;
}

bool TextureLoader::unloadTexture(mt::TextureName::TextureName textureName)
{
	assert(isLoaded(textureName));

	textures_[textureName] = mt::texPair(/*mt::BinImg(),sf::Texture()*/);

	return SUCCESS;
}
//Functions
bool TextureLoader::isLoaded(mt::TextureName::TextureName textureName) const
{
	if (textures_[textureName].first.size == 0)
		return false;
	return true;

}
//Operator Overloads
const mt::BinImg& TextureLoader::operator[](mt::TextureName::TextureName textureName)
{
	if (!isLoaded(textureName))
		loadTexture(textureName);
	return textures_[textureName].first;
}