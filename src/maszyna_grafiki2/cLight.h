#ifndef CLIGHT
#define CLIGHT
#pragma once
#include "cMovableObject.h"

class cLight:
	public cMovableObject
{
public:
	cLight(Ogre::Light* oLight);
	virtual ~cLight(void);
	virtual unsigned getId() { return id; }
protected:
};

#endif