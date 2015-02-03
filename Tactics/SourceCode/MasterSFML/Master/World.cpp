//Includes
#include "World.h"

//Namespace
using namespace std;

//Defines

//Const

//Prototypes
World* World::_instance = nullptr;

//Class Definition
//Constructor
World::World()
{
}

World::World(sf::RenderWindow* window, DataLoader* loadedData, TextureLoader* textureHolder):
	window_(window),
	loadedData_(loadedData),
	textureHolder_(textureHolder),
	idNumber_(0)
{
	sceneGraph_.setID(0);
	buildScene();
}

 //Destructor
World::~World()
{
	cout << "~" << typeid(*this).name() << endl;
	_instance = nullptr;
}

//Singleton specific
World* World::Instance()
{
	if (_instance == nullptr) 
	{ 
		_instance = new World();
	}
	return _instance;
}

void World::erase()
{
	delete _instance;
}

void World::Create(sf::RenderWindow* window, DataLoader* loadedData, TextureLoader* textureHolder)
{
	_instance = new World(window, loadedData, textureHolder);
}

//Access Methods
CommandQueue& World::getCommandQueue()
{
	return commandQueue_;
}

SceneNode::ID& World::getIdNumber()
{
	return idNumber_;
}

//Modifying methods

//Functions
void World::update(sf::Time dt)
{
	while (!commandQueue_.isEmpty())
		sceneGraph_.onCommand(commandQueue_.pop(), dt);

	sceneGraph_.update(dt);
}

void World::draw()
{
	window_->setView(*MyView::Instance());

	window_->draw(sceneGraph_);
}

void World::buildScene()
{
	for (std::size_t i = 0; i < LayerCount; ++i)
	{
		SceneNode::Ptr layer(new SceneNode());
		layer->setID(++idNumber_);
		sceneLayers_[i] = layer.get();
		sceneGraph_.attachChild(std::move(layer));
	}
	Map::Create(MAP_SIZE_X, MAP_SIZE_Y, textureHolder_);
	Map::Instance()->setID(++idNumber_);
	sceneLayers_[BackgroundL]->attachChild(Map::Instance());

	Selection::create(textureHolder_->getTexture(mt::TextureName::Overlays));
	sceneLayers_[SelectionL]->attachChild(SceneNode::Ptr(Selection::Instance()->getCursor()));

	/********************************
	*Facultatif
	*Adding objects for test purposes
	*********************************/
	createUnit(6,5);
	createUnit(2,6);
	createUnit(1,5);

	createObject(1,6);
	createObject(4,6);
	createObject(5,5);
	//*/
	/********************************
	//Add random objects
	for (int i = 0; i < 75; ++i)
	{
		createObject(); 
	}
	for (int i = 0; i < 15; ++i)
	{
		createUnit();
	}
	//*/
}

void World::createUnit()
{
	int x = 0, y = 0, times = 0;
	do{
		x = mt::random(Map::Instance()->getWidth() - 1);
		y = mt::random(Map::Instance()->getHeight() - 1);
	}while ((Map::Instance()->getHex(x,y)->getEntities()->size() != 0 && ++times < 200) || Map::Instance()->getHex(x,y)->isBorder());

	createUnit(x,y);
}

void World::createUnit(int column, int row)
{
	++idNumber_;
	unique_ptr<Unit> anyUnit(new Unit(
		textureHolder_->getPair(mt::TextureName::TextureName(mt::random(mt::UnitTextureNumber))),
		mt::stdGround, 
		GridInfo(column,row),
		loadedData_->getUnitPropertiesHolder()[mt::Unit::Recruit]));
	anyUnit->setID(idNumber_);
	Map::Instance()->modifyMapObject_add(*anyUnit.get());
	sceneLayers_[UnitL]->attachChild(move(anyUnit));
	sortLayer(UnitL);
}

void World::createObject()
{
	int x = 0, y = 0;
	do{
		x = mt::random(Map::Instance()->getWidth() - 1);
		y = mt::random(Map::Instance()->getHeight() - 1);
	}while (Map::Instance()->getHex(x,y)->getEntities()->size() != 0);

	createObject(x,y);
}

void World::createObject(int column, int row)
{
	++idNumber_;
	unique_ptr<Object> anyObject(new Object(
		textureHolder_->getPair(mt::TextureName::TextureName(mt::TextureName::TreeStd+mt::random(1))),
		mt::stdGround, 
		GridInfo(column,row)));
	anyObject->setID(idNumber_);
	Map::Instance()->modifyMapObject_add(*anyObject.get());
	sceneLayers_[UnitL]->attachChild(move(anyObject));
	sortLayer(UnitL);
}

void World::makeOverlay(vector<Hex*> hexes, mt::Overlay::Color color)
{
	++idNumber_;
	for(auto hex: hexes)
	{
		unique_ptr<ColorFiltre> anyFiltre(new ColorFiltre(textureHolder_->getTexture(mt::TextureName::Overlays),
			hex->getGridInfo()));
		anyFiltre.get()->setID(idNumber_);
		anyFiltre.get()->setColor(color);
		anyFiltre.get()->setPathingInfo(mt::BinPathingStruct());

		sf::Vector2f pixelPosition = 
			mt::calculatePixelPosition(
			hex->getGridInfo().getPosColumn(),
			hex->getGridInfo().getPosRow());
		anyFiltre.get()->getSprite().setPosition(pixelPosition);
		//dont need overlays represented in hex entity vector
		//Map::Instance()->modifyMapObject_add(*anyFiltre.get());
		sceneLayers_[OverlaysL]->attachChild(move(anyFiltre));
	}
}

void World::eraseLayer(Layer layer)
{
	sceneLayers_[layer]->getChildren().clear();
}


void World::sortLayer(Layer layer)
{
	sort(sceneLayers_[layer]->getChildren().begin(), sceneLayers_[layer]->getChildren().end(), 
		[] (const unique_ptr<SceneNode>& firstObject, const unique_ptr<SceneNode>& secondObject) -> bool
	{
		int firstRow = firstObject->getObjectCoordinates().getPosRow();
		int firstColumn = firstObject->getObjectCoordinates().getPosColumn();
		int secondRow = secondObject->getObjectCoordinates().getPosRow();
		int secondColumn = secondObject->getObjectCoordinates().getPosColumn();

		if (firstRow > secondRow)
			return false;
		if (firstRow < secondRow)
			return true;
		if (firstColumn > secondColumn)
			return true;
		else
			return false;
	});
}


//Operator Overloads
