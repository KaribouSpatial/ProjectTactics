//Includes
#include "SceneNode.h"

//Namespace
using namespace std;

//Defines

//Const

//Prototypes

//Class Definition
//Constructor & Destructor
SceneNode::SceneNode()
{
}

SceneNode::SceneNode(SceneNode& sceneNode)
{
	//non-copyable
	assert(false);
}

SceneNode::~SceneNode()
{
}

//Access Methods
const GridInfo SceneNode::getObjectCoordinates() const
{
	throw runtime_error("SceneNode call to getObjectCoordinates");
}

mt::TextureName::TextureName SceneNode::getTextureName() const
{
	throw runtime_error("SceneNode call to getTextureName");
}

SceneNode::ID SceneNode::getID() const
{
	return id_;
}

vector<SceneNode::Ptr>& SceneNode::getChildren()
{
	return children_;
}
//Modifying methods
void SceneNode::setID(ID id)
{
	id_ = id;
}

void SceneNode::attachChild(Ptr child)
{
	child->parent_ = this;
	children_.push_back(std::move(child));
}

void SceneNode::attachChild(SceneNode* child)
{
	child->parent_ = this;
	children_.push_back(Ptr(child));
}

SceneNode::Ptr SceneNode::detachChild(const SceneNode& node)
{
	auto found = find_if(children_.begin(), children_.end(),
		[&] (Ptr& p) -> bool 
	{
		return p.get() == &node; 
	});

	if (found == children_.end())
		return nullptr;

	Ptr result = move(*found);
	result->parent_ = nullptr;
	children_.erase(found);
	return result;
}
//Functions
void SceneNode::draw(sf::RenderTarget& target,sf::RenderStates states) const
{
	drawCurrent(target, states);

	for (const auto& child : children_)
	{
		child->draw(target, states);
	}
}

void SceneNode::drawCurrent(sf::RenderTarget& target,sf::RenderStates states) const
{
}

void SceneNode::update(sf::Time dt)
{
	RETRY_UPDATE:
	try{
	updateChildren(dt);
	}catch(...){
		goto RETRY_UPDATE;
	}
	updateCurrent(dt);
}

void SceneNode::updateCurrent(sf::Time dt)
{
}

void SceneNode::updateChildren(sf::Time dt)
{
	for(auto& child: children_)
		child->update(dt);
}

unsigned int SceneNode::getCategory() const
{
	return mt::Category::SceneNode;
}

void SceneNode::onCommand(const Command& command, sf::Time dt)
{//this seems very dangerous...
	RETRY_ONCOMMAND:
	try{
	for(Ptr& child: children_)
		child->onCommand(command, dt);
	}catch(...){
		goto RETRY_ONCOMMAND;
	}

	if ((command.category != 0 && command.category & getCategory()) || (command.id != 0 && command.id == getID()))
		command.action(*this, dt);
}
void SceneNode::suicide()
{
	parent_->detachChild(*this);
}
//Operator Overloads
bool SceneNode::operator==(SceneNode node)
{
	if (id_ == node.id_)
		return true;
	else return false;
}