//Includes
#include "Map.h"

//Namespace
using namespace std;

//Defines
#define TODO
#define TileTextureNumber 3
//Const

//Prototypes
Map* Map::_instance = nullptr;

//Class Definition
//Constructor & Destructor
Map::Map(): 
	height_(20), 
	width_(35)
{
}

Map::Map(int width, int height, TextureLoader* textureHolder):
	height_(height), 
	width_(width),
	textureHolder_(textureHolder)
{	
	//allocating memory
	Hex::Create();
	map_ = new vector<vector<Hex>>(height_, vector<Hex>(width_,Hex()));
	assert(map_ != nullptr);

	//creating the hexes
	for ( int row = 0 ; row < height_ ; ++row)
	{
		for ( int column = 0 ; column < width_ ; ++column)
		{
			//Temporary Measure, random tile
			(*map_)[row][column].setTilesetType(mt::TilesetType(/*::Sand(*/mt::random(TileTextureNumber,1)));
			//setting up adjacent hexes
			getHex(column, row)->setGridInfo(column, row);
			getHex(column, row)->setAdjacent(this);
			
		}
	}
	//Setting up correct 3axis coordinates
	initGrid();

	setID(0);
	isContourActive_.toggle();
	isContourActive_.toggled = false;
}

Map::~Map()
{
	cout << "~" << typeid(*this).name() << endl;
	delete map_;
	map_ = nullptr;
	for (auto* object : mapEntities_)
	{
		object = nullptr;
	}
	_instance = nullptr;
	Hex::Erase();
}

void Map::Create(int width, int height, TextureLoader* textureHolder_)
{
	_instance = new Map(width, height, textureHolder_);
}

void Map::erase()
{
	delete _instance;
}

//Singleton specific
Map* Map::Instance()
{
	if (_instance == nullptr) 
	{ 
		_instance = new Map();
	}
	return _instance;
}

//Access Methods
const int Map::getHeight() const
{
	return height_;
}

const int Map::getWidth() const
{
	return width_;
}

vector<vector<Hex>>* Map::getMap() const
{
	return map_;
}

const list<Entity*>& Map::getMapEntities() const
{
	return mapEntities_;
}

sf::Sprite& Map::getSprite()
{
	throw runtime_error("Map::GetSprite");
}

//returns a Hex pointer to offset column/row ex:(9,9) will return (10th,10th) element
Hex* Map::getHex(int column, int row) const
{
	if (column < 0 || row < 0 || column >= width_ || row >= height_)
		return nullptr;
	return &(*map_)[row][column];
}
//returns a Hex reference to the matching GridInfo coordinates
Hex* Map::getHex(GridInfo coordinates) const
{
	if(coordinates.isDirty())
		return getHex(coordinates.getPosX(),coordinates.getPosY(),coordinates.getPosZ());
	return getHex(coordinates.getPosColumn(),coordinates.getPosRow());
}
//returns a pointer to Hex (posX,posY,posZ)
Hex* Map::getHex(int posX, int posY, int posZ) const
{
	if (posY > 0)
		return nullptr;
	int row = mt::abs(posY);
	Hex* temp = getHex(0, row);
	int column = 0;
	if (temp != nullptr)
		column = posX - getHex(0, row)->getGridInfo().getPosX();

	return getHex(column,row);
}

//Modifying methods

//Functions
void Map::updateCurrent(sf::Time dt)
{
	
}

void Map::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	const mt::texPair& tileset = textureHolder_->getPair(mt::TextureName::Tileset);
	sf::Sprite background(tileset.second);

	/*Long version, use if tileset is not 128x128
	float xScale = 128.0f / tileset.first.spriteWidth;
	float yScale = 64.0f / tileset.first.spriteHeight;
	background.setScale(xScale,yScale);*/
	//Short version
	background.setScale(1,0.5f);

	for ( int row = 0 ; row < height_ ; ++row)
	{
		for ( int column = 0 ; column < width_ ; ++column)
		{
			mt::TilesetType type = this->getHex(column,row)->getTilesetType();

			//Tileset Type Filter
			/*if (type== mt::TilesetType::Grass)
			type = mt::TilesetType::Grass;
			else if (type== mt::TilesetType::SmoothStone)
			type = mt::TilesetType::CrackStone;
			else if (type== mt::TilesetType::Dirt)
			type = mt::TilesetType::DeepDirt;
			else if (type== mt::TilesetType::SandStone)
			type = mt::TilesetType::MixedGrass;
			else if (type== mt::TilesetType::Sand)
			type = mt::TilesetType::Grass;
			else if (type== mt::TilesetType::Rock)
			type = mt::TilesetType::PaleDirt;*/

			int tilesPerRow = (int)(tileset.second.getSize().x / 128);

			background.setTextureRect(sf::IntRect(
				128 * ((int)type % tilesPerRow),
				128 * ((int)type / tilesPerRow),
				128,
				128));

			background.setPosition(mt::calculatePixelPosition(column, row));

			target.draw(background);
			if (isContourActive_())
			{
				background.setTextureRect(sf::IntRect(
					128 * ((int)mt::TilesetType::Contour % tilesPerRow),
					128 * ((int)mt::TilesetType::Contour / tilesPerRow),
					128,
					128)); 
				target.draw(background);
			}
		}
	}
}

void Map::toggleContour()
{
	isContourActive_.toggle();
	//generateBackground();
}

//add an element to the list "mapEntities_", object will be added automatically to the proper Hex's list.
//WARNING, USE NEW IF THE ADDED OBJECT IS CONSTRUCTED IN THE PARAMETER SECTION ie: ...->modifyMapObject_add(*new Unit())
void Map::modifyMapObject_add(Entity& addedEntity)
{
	//add addedObject to mapObjects ifit is not contained already
	if (find(mapEntities_.begin(), mapEntities_.end(), &addedEntity) == mapEntities_.end())
		mapEntities_.push_front(&addedEntity);

	//add the object to the Hex
	this->getHex(addedEntity.getObjectCoordinates())->modifyHexObject_add(addedEntity);
}

//move the object to its new location following a direction vector, changes to containing hexes are made each step, 
//pathing must be checked before calling this function
void Map::modifyMapObject_move(Entity& movedEntity, const vector<const mt::Direction::Direction> direction)
{
	Hex* currentHex = this->getHex(movedEntity.getObjectCoordinates());
	for ( unsigned moves_inc = 0 ; moves_inc < direction.size() ; ++moves_inc)
	{
		//movedObject is removed from the Hex's list
		currentHex->modifyHexObject_delete(movedEntity);

		//movedObject's coordinates are modified
		movedEntity.setCoordinates(currentHex->getAdjacentHex(direction[moves_inc])->getGridInfo());

		//movedObject is added to the proper Hex's list
		modifyMapObject_add(movedEntity);

		//set the new currentHex to follow the movement
		currentHex = currentHex->getAdjacentHex(direction[moves_inc]);
		assert(&movedEntity == *currentHex->getEntities()->begin());
	}
}

//move the object to its new location in one step, pathing must be checked before calling this function
void Map::modifyMapObject_move(Entity& movedEntity, GridInfo targetLocation)
{
	Hex* currentHex = this->getHex(movedEntity.getObjectCoordinates());
	//movedObject is removed from the Hex's list
	currentHex->modifyHexObject_delete(movedEntity);
	//movedObject's coordinates are modified
	movedEntity.setCoordinates(this->getHex(targetLocation)->getGridInfo());
	//movedObject is added to the proper Hex's list
	modifyMapObject_add(movedEntity);
	//set the new currentHex to follow the movement
	currentHex = this->getHex(targetLocation);
	assert(&movedEntity == *currentHex->getEntities()->begin());
}

//delete the object from the grid
void Map::modifyMapObject_delete(Entity& deletedEntity)
{
	this->getHex(deletedEntity.getObjectCoordinates())->modifyHexObject_delete(deletedEntity);
}

unsigned int Map::getCategory() const
{
	return mt::Category::Map;
}

//initiate the 3-axis grid within the map
void Map::initGrid()
{
	int posX = 0;
	int posY = 0;
	int posZ = 0;
	Hex* currentHex = nullptr;

	for ( int column = 0 ; column < width_ ; ++column )
	{
		currentHex = this->getHex(column, 0);
		if (column != 0)
		{
			posX = column;
			posY = 0;
			posZ = -posX;
		}
		for ( int row = 0 ; row < height_ ; ++row )
		{
			if ( !(row & 1) ) //ifrow is pair
			{
				currentHex->setGridInfo(posX, posY, posZ);
				assert((currentHex->getGridInfo().getPosX() + currentHex->getGridInfo().getPosY() + currentHex->getGridInfo().getPosZ()) == 0);
				currentHex = currentHex->getAdjacentHex(mt::Direction::BOT_LEFT);
				//posX dosn't change
				--posY;
				++posZ;
			}
			else //ifrow is impair
			{
				currentHex->setGridInfo(posX, posY, posZ);
				assert((currentHex->getGridInfo().getPosX() + currentHex->getGridInfo().getPosY() + currentHex->getGridInfo().getPosZ()) == 0);
				currentHex = currentHex->getAdjacentHex(mt::Direction::BOT_RIGHT);
				++posX;
				--posY;
				//posZ dosn't change
			}
		}
	}
}

//Operator Overload
