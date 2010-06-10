#ifndef CSCENE_OBJECTS
#define CSCENE_OBJECTS
#pragma once
#include "cObject.h"

class cSceneObjectElem
{
public:
	cSceneObjectElem();
	~cSceneObjectElem();
	cObject* object;
	cSceneObjectElem* next;
};
class cSceneObjectList
{
public:
	cSceneObjectList(void);
	~cSceneObjectList(void);
	//przepisuje wskaznik do obiektu na poczatek listy
	unsigned addObject(cObject* object);	
	//Liczba elementow
	unsigned getCount() {return count;}
	//kasuje elementy listy
	void clearList();
	//kasowanie obiektu z listy
	bool delObject(unsigned idObject);
	//czy istnieje obiekt o takim id
	bool isId(unsigned idObject);
	//pobiera obiekt, NULL jesli nie ma
	cObject* getObject(unsigned idObject);
protected:
	//liczba elementow w liscie
	unsigned count;	
	cSceneObjectElem* head;
};

#endif
