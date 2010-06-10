#ifndef CCAMERA
#define CCAMERA
#pragma once
#include "cMovableObject.h"

class cCamera :
	public cMovableObject
{
public:
	cCamera(Ogre::Camera* cam);
	virtual unsigned getId() { return id; }
	virtual ~cCamera(void);
	
};

#endif