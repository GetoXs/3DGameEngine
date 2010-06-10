#include "cMovableObject.h"

cMovableObject::cMovableObject(Ogre::MovableObject* MovObj):oMovObj(MovObj), cObject(MovObj->getParentSceneNode())
{
}

cMovableObject::~cMovableObject(void)
{
	oMovObj = NULL;
}
