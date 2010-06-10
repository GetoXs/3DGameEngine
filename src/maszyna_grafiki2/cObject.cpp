#include "cObject.h"

unsigned cObject::nextId = 1;
cObject::cObject(Ogre::SceneNode* SceneNode):id(nextId++),oSceneNode(SceneNode)
{
}

cObject::~cObject(void)
{
	//kasowanie noda
	oSceneNode=NULL;
}
