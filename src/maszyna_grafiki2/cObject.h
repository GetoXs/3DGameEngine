#ifndef COBJECT
#define COBJECT
#pragma once
#include <cstddef>
#include <string>
#include <vector>
#include <deque>
#include "Ogre.h"
#include "system\system_queue.h"

//klasa abstrakcyjna
class cObject
{
public:
	cObject(Ogre::SceneNode* SceneNode);
	virtual ~cObject(void);
	virtual unsigned getId()=0;	// {return id;}
	static unsigned getNextId() {return nextId;}
	//Pobranie Ogrowego SceneNode'a
	Ogre::SceneNode* getSceneNode() {return oSceneNode; }
	//zmiana/ustawienie SceneNode'a
	void setSceneNode(Ogre::SceneNode* newSN) { oSceneNode=newSN; }
	


protected:
	unsigned id;
	static unsigned nextId;
	
	//Ogre'owy SceneNode
	Ogre::SceneNode* oSceneNode;
};

#endif