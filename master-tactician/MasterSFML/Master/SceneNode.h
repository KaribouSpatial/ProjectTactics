#pragma once

//Includes
#include "GridInfo.h"
#include "mt.h"
#include "Command.h"

#include <memory> //unique_ptr
#include <vector> //vector
#include <assert.h> //assert
#include <algorithm> //find_if

#include <SFML/Graphics.hpp>

//Namespace
using namespace std;

//Defines

//Const

//Prototypes

//Class Prototypes
class Command;

//Class Declaration
class SceneNode : public sf::Drawable, private sf::NonCopyable
{
public:
	//typdef
	typedef unique_ptr<SceneNode> Ptr;
	typedef int ID;

	//Constructor
	SceneNode();
	SceneNode(SceneNode& sceneNode);
	//Destructor
	virtual ~SceneNode();

	//Access Method
	//R-only Access
	virtual const GridInfo getObjectCoordinates() const;
	virtual mt::TextureName::TextureName getTextureName() const;
	ID getID() const;
	virtual unsigned int getCategory() const;

	//R-W Access
	vector<Ptr>& getChildren();

	//Modifying method
	void setID(ID id);

	//Add a child to the node
	void attachChild(Ptr child);
	//Use only to attach singletons
	void attachChild(SceneNode* child);

	//Remove a child from the node, retuns the removed child
	Ptr detachChild(const SceneNode& node);

	//Function
	void draw(sf::RenderTarget& target, sf::RenderStates states) const final;

	void update(sf::Time dt);

	void onCommand(const Command& command, sf::Time dt);

	//careful with this
	void suicide();

	//Operator Overload
	virtual bool operator==(SceneNode node);


private:
	//Private Function
	virtual void updateCurrent(sf::Time dt);
	virtual void drawCurrent(sf::RenderTarget& target,sf::RenderStates states) const;
	void updateChildren(sf::Time dt);


	//Private Attribute
	vector<Ptr> children_;
	SceneNode* parent_;
	ID id_;
};


