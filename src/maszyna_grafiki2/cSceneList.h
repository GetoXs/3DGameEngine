#ifndef CSCENE_LIST
#define CSCENE_LIST
#pragma once
#include "cSceneObjectList.h"
#include "cMovableObject.h"

class cScene :
	public cObject
{
public:
	cScene(Ogre::SceneManager* oSceneMgr);
	~cScene();
	virtual unsigned getId() { return id; }
	//przepisuje wskaznik do listy, zwraca id obiektu
	unsigned addObject(cObject *object);	
	//get scenemgr
	Ogre::SceneManager* getSceneMgr() {return oSceneMgr;}
	//kasowanie obiektu o podanym id
	bool delObject(unsigned idObject);
protected:
	//unsigned sid;
	//static unsigned nextSid;

	//TODO(kiedys): informacje o scenie w której dana scena sie znajduje, aby móc j¹ w prosty sposób wykasowaæ
	//unsigned idSceneUp;	//id sceny na ktorej znajduje sie dana scena

	//lista cObjektow
	cSceneObjectList objectList;
	//Ogre'owy Scene Manager
	Ogre::SceneManager* oSceneMgr;
};



//NIEUZYWANE
/*
class cSceneElem
{
public:
	cSceneElem();
	~cSceneElem();

	cScene *scene;
	cSceneElem *next;
};

class cSceneList
{
public:
	cSceneList();
	~cSceneList();
	unsigned addScene();
	unsigned addScene(cScene* scene);
	unsigned addObjectToScene(unsigned idScene, cObject* object);
protected:
	cSceneElem *head;
	cScene *render;
};

*/

#endif