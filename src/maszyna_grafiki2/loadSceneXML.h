#ifndef LOAD_SCENE_XML
#define LOAD_SCENE_XML
#pragma once
#include "xmlio.h"

class loadSceneXML
{
public:
	loadSceneXML(void);
	~loadSceneXML(void);
	bool loadXML(std::string fileName);	//zaladowanie pliku XML do pamieci
	short nextLoadStage();	//odpalenie kolejnego etapu
	void clear();	//czyszczenie
	//bool validSceneXML(const std::string fileName);
	//TODO: do ustawiania nieba
	//bool loadSceneXML::interpreteSky(XML* param)
	
private:
	bool addResourcesLoc();
	short initNextResourceGroup();
	bool addObjects();

	int loadStage;
	int initResourceGroupNum;
	XML* loadedXML;
};

#endif