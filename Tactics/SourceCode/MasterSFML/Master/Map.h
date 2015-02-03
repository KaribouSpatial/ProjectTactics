#pragma once

//Includes
#include "mt.h"
#include "TextureLoader.h"
#include "Object.h"
#include "GridInfo.h"
#include "Hex.h"
#include "Entity.h"

#include <algorithm>
#include <vector>
#include <list>

#include <SFML/Graphics.hpp>

//Namespace
using namespace std;

//Defines

//Const

//Prototypes

//Class Prototypes
class Hex;

//Class Declaration
class Map: public SceneNode
{
public:
	//Singleton specific
	static Map* Instance();
	static void Create(int width, int height, TextureLoader* textureHolder_);
	void erase();
	
	//Destructor
	~Map();

	//Access Methods
	const int getHeight() const;
	const int getWidth() const;
	vector<vector<Hex>>* getMap() const;
	const list<Entity*>& getMapEntities() const;
	sf::Sprite& getSprite();
	//returns a Hex pointer to offset column/row ex:(9,9) will return (10th,10th) element
	Hex* getHex(int column, int row) const;
	//returns a Hex pointer to offset column/row
	Hex* getHex(GridInfo coordinates_) const;
	//returns a Hex pointer to offset posX/posY/posZ
	Hex* getHex(int posX, int posY, int posZ) const;

	//Modifying methods

	//Functions
	//Generic update function
	void updateCurrent(sf::Time dt) override;
	//Generic draw function
	void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;

	//toggle the contour view of the tiles
	void toggleContour();
	
	//add an element to the list "mapEntities_", object will be added automatically to the proper Hex's list.
	//WARNING, USE NEW IF THE ADDED OBJECT IS CONSTRUCTED IN THE PARAMETER SECTION ie: ...->modifyMapObject_add(*new Unit())
	void modifyMapObject_add(Entity& addedEntity);

	//move the object to its new location following a direction vector, changes to containing hexes are made each step, pathing must be checked before calling this function
	void modifyMapObject_move(Entity& movedEntity, vector<const mt::Direction::Direction> direction);

	//move the object to its new location in one step, pathing must be checked before calling this function
	void modifyMapObject_move(Entity& movedEntity, GridInfo targetLocation);

	//delete the object from the grid
	void modifyMapObject_delete(Entity& deletedEntity);

	unsigned int getCategory() const override;

	//Operator Overload

	//Public Attributes
	const int height_;
	const int width_;

protected:
	//Constructor
	Map();
	Map(int width, int height, TextureLoader* textureHolder_);

private:

	//Private Functions
	//called once to set up the 3d tri-axis grid indexes of the hexes
	void initGrid();

	//Private Attributes
	mt::Toggle isContourActive_;
	vector<vector<Hex>>* map_;
	list<Entity*> mapEntities_;

	TextureLoader* textureHolder_;

	//Singleton specific
	static Map* _instance; 
};


