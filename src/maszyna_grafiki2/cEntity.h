#ifndef CENTITY
#define CENTITY
#pragma once

#include "cMovableObject.h"
class cEntity :
	public cMovableObject
{
public:
	cEntity(Ogre::Entity* oEntity);
	virtual ~cEntity(void);
	virtual unsigned getId() { return id; }
protected:

};

#endif

