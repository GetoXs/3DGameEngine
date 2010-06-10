#include "cEntity.h"

cEntity::cEntity(Ogre::Entity* oEntity):cMovableObject((Ogre::MovableObject*)oEntity)
{
}

cEntity::~cEntity(void)
{
}
