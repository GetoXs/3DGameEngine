#ifndef CMOVABLE_OBJECT
#define CMOVABLE_OBJECT
#pragma once
#include "cObject.h"

//klasa abstrakcyjna
class cMovableObject :
	public cObject
{
public:
	cMovableObject(Ogre::MovableObject* MovObj);
	virtual ~cMovableObject(void);
	Ogre::MovableObject* getMovObj() { return oMovObj; }
protected:
	//wskaznik na ogrowy MovableObj na danej scenie
	Ogre::MovableObject* oMovObj;
};

#endif
