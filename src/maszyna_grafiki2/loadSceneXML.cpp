#include "loadSceneXML.h"
#include "graphSys.h"


loadSceneXML::loadSceneXML(void):loadedXML(NULL), initResourceGroupNum(0), loadStage(0)
{
}

loadSceneXML::~loadSceneXML(void)
{
	if(loadedXML!=NULL)
	{
		delete loadedXML;
		loadedXML=NULL;
	}
}
short loadSceneXML::nextLoadStage()
{
	if(loadStage==0)
	{
		clear();
		return -1;
	}
	if(loadStage==1)
	{
		if(addResourcesLoc()==false)
		{
			clear();
			return -1;
		}else	//lokalizacje dodane
		{
			loadStage = 2;
			return 1;
		}
	}
	if(loadStage==2)
	{
		int tmp = initNextResourceGroup();
		if(tmp==-1)
		{
			clear();
			return -1;
		}else if(tmp==1)	//koniec inicjalizacji grup
		{
			loadStage=3;
			return 1;
		}
		else	//ciag dalszy inicjalizacji grup
		{
			return 1;
		}
	}
	if(loadStage==3)
	{
		if(addObjects()==false)	//blad
		{
			clear();
			return -1;
		}else	//dodawanie zakonczone
		{
			clear();
			return 0;	//koniec
		}
	} else
		return -1;
}
void loadSceneXML::clear()
{
	loadStage=0;
	initResourceGroupNum=0;

	if(loadedXML!=NULL)
	{
		delete loadedXML;
		loadedXML=NULL;
	}
}
/*bool loadSceneXML::validSceneXML(const std::string fileName)
{
	XML* tmp;
	for(int i=0; i<loadedXML->getChild("resource")->getNumOfChild(); i++)
	{
		tmp = loadedXML->getChild("resource")->getChild(i);
		if (tmp->getNumOfAtt()!=2)
			return false;
		for(int j=0; j<tmp->getNumOfChild(); j++)
		{
			if(cObjectFactory::isExistObject(tmp->getChild(j)->getName(),tmp->getChild(j)->getNumOfAtt()))
				return false;
		}
	}
	//for(int i=0; i<loadedXML->getChild("scene")->getNumOfChild(); i++)
	//{

	//}
}*/
bool loadSceneXML::addResourcesLoc()
{
	if(loadedXML==NULL)
		return false;
	loadedXML->getChild("resource");
	std::string node;
	XML* tmp;
	for(int i=0; i<loadedXML->getChild("resource")->getNumOfChild(); i++)
	{
		tmp=loadedXML->getChild("resource")->getChild(i);
		if(tmp->getAtt("name")==-1 || tmp==NULL)
			return false;
		node=tmp->getValueOfAtt(tmp->getAtt("name"));	//pobranie nazwy ResourceGroup
		for(int j=0; j<tmp->getNumOfChild(); j++)
		{
			if(tmp->getChild(j)->getAtt("path")==-1)
				return false;
			//dodanie lokaliazji do Ogrea
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(tmp->getChild(j)->getValueOfAtt("path"),tmp->getChild(j)->getName(), node);
		}
	}
	return true;
}
short loadSceneXML::initNextResourceGroup()
{
	if(loadedXML==NULL)
		return -1;
	XML* tmp=loadedXML->getChild("resource")->getChild(initResourceGroupNum);
	if(tmp->getAtt("name")==-1 || tmp==NULL)
		return -1;
	//inicjalizacja danej grupy w Ogrze
	Ogre::ResourceGroupManager::getSingleton().initialiseResourceGroup(tmp->getValueOfAtt(tmp->getAtt("name")));
	
	//zwiekszenie licznika zainicjalizowanej grupy
	if(loadedXML->getChild("resource")->getNumOfChild() > initResourceGroupNum+1)
	{
		initResourceGroupNum++;
		return 0;	//kontynuacja
	}else
		return 1;
}
bool loadSceneXML::addObjects()
{
	if(loadedXML==NULL)
		return false;
	if(loadedXML->getChild("scene")==NULL 
		|| loadedXML->getChild("scene")->getAtt("type")==-1
		|| loadedXML->getChild("scene")->getAtt("name")==-1)
		return false;

	
	XML* tmp = loadedXML->getChild("scene");
	//ustawienie sceny
	if(graphSys::getI().setScene(
						atoi(tmp->getValueOfAtt("type")), 
						tmp->getValueOfAtt("type"))==false
		)
		return false;

	std::vector<std::string>* param = new std::vector<std::string>;
	for(int i=0; i<loadedXML->getChild("scene")->getNumOfChild(); i++)
	{
		tmp = loadedXML->getChild("scene")->getChild(i);
		if(tmp->getNumOfChild()!=0)
			return false;
		
		if(graphSys::getI().addObjectScene(tmp)==0)
			return false;

		/* Pierwsza wersja tego powyzej
		for(int j=1; j<tmp->getNumOfAtt(); j++)	//dodajemy atrybuty jako paramtery
		{
			param->push_back(tmp->getValueOfAtt(j));	//atrybuty dodawane sa na koniec listy, wazna jest kolejnosc!!!
		}
		//graphSys::getI().addObjectScene(cObjectFactory::createObject(tmp->getName(), param));	//przekazanie do fabryki tworzonego obiektu
		//lub:
		graphSys::getI().addObjectScene(tmp->getName(), param);
		*/
	}


	return true;
}
bool loadSceneXML::loadXML(std::string fileName)
{
	loadedXML = new XML;
	if (!loadedXML->loadFromFileBuf(fileName.c_str()))
		return false;
	loadStage = 1;
	return true;
}

/*	do ustawienia nieba
bool loadSceneXML::interpreteSky(XML* param)
{
	std::string tmp_str=param->getValueOfAtt("skyType");
	if(tmp_str=="SkyBox")
	{
		

	}else if(tmp_str=="SkyDome")
	{

	}else
	{
		//TODO: Exception
	}
		return false;
}*/