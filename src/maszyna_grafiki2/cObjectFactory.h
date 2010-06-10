#ifndef COBJECT_FACTORY
#define COBJECT_FACTORY
#pragma once
#include "cEntity.h"
#include "cLight.h"
#include "cCamera.h"

//const short _NumParamEntity=6;
//const short _NumParamCamera=4;

//Wzorzec Fabryka wytworcza
class cObjectFactory
{
public:
	//dodawanie obiektu w vektorze znajduja sie parametry danego obiektu (np. Mesh dla Entity, Typ swiatla dla Light)
	static cObject* createObject(XML* param)
	{
		cObject* obj=NULL;
		//czy dodawac scene node
		bool addSceneNode=false;
		std::string tmp_str(param->getName());
		if(tmp_str=="entity")
		{
			//sprawdzanie czy dany zasob istnieje (tylko w tym potrzebujacych zasobow)
			if(Ogre::ResourceGroupManager::getSingleton().resourceExists(param->getValueOfAtt("resGroup"), param->getValueOfAtt("mesh")))
			{
				//TODO: validacja entity, sprawdzenie czy parametry istnieja itd
				Ogre::Entity* ent = graphSys::getI().getScene()->getSceneMgr()->createEntity(param->getValueOfAtt("name"), param->getValueOfAtt("mesh"), param->getValueOfAtt("resGroup"));
				if(param->getAtt("shadowEnabled")!=-1)
					ent->setCastShadows((bool)param->getValueOfAtt("shadowEnabled"));
				obj = (cObject *)new cEntity(ent);
				//dodajemy SceneNode'a
				addSceneNode=true;
			}
		}
		else if(tmp_str=="light")
		{
			tmp_str.assign(param->getValueOfAtt("type"));
			if(tmp_str=="point"||tmp_str=="directional"||tmp_str=="spotlight")
			{
				Ogre::Light *light=graphSys::getI().getScene()->getSceneMgr()->createLight(param->getValueOfAtt("name"));
				if(tmp_str=="point")
				{
					light->setType(Ogre::Light::LT_POINT);
					addSceneNode=true;
				}else if(tmp_str=="directional")
				{
					light->setType(Ogre::Light::LT_DIRECTIONAL);

					//moze byc dodane przy SceneNode
					//light->setDirection(Vector3( 0, -1, 1 )); 
					addSceneNode=false;
				}else 
				{
					light->setType(Ogre::Light::LT_SPOTLIGHT);

					//moze byc dodane przy SceneNode
					//light->setDirection(-1, -1, 0);
				
					//wewnetrzny i zewnetrzny kat swiatla 
					light->setSpotlightRange(Ogre::Degree((float)atoi(param->getValueOfAtt("spotlightRangeInner"))), Ogre::Degree((float)atoi(param->getValueOfAtt("spotlightRangeOutter"))));
					addSceneNode=true;
				}
				//Ustawianie koloru rozproszenia
				//light->setDiffuseColour(1.0, 1.0, 0.5);
				//Ustawianie koloru lustrzanego odbicia
				//light->setSpecularColour(0, 0, 1.0);

				//dodac kamere, a do sceny id kamery aktywnej itd
				
				obj = (cObject*)new cLight(light);
			}
		}else if(tmp_str=="camera")
		{
			Ogre::Camera* cam= graphSys::getI().getScene()->getSceneMgr()->createCamera(param->getValueOfAtt("name"));
			cam->setNearClipDistance(atoi(param->getValueOfAtt("nearClipDistance")));
			cam->setFarClipDistance(atoi(param->getValueOfAtt("farClipDistance")));

			
			obj = (cObject*)new cCamera(cam);
			addSceneNode=true;
		}
		if(obj!=NULL && addSceneNode==true)
		{
			Ogre::SceneNode* node=NULL;
			//dodawanie pozycji
			if(param->getAtt("nodeParent")==-1)	//sprawdzamy czy jest dodatkowy parametr
			{
				//jesli nie ma dodajemy z domyslnym rodzicem (scena)
				node = graphSys::getI().getScene()->getSceneNode()
					->createChildSceneNode(param->getValueOfAtt("name"), Ogre::Vector3((float)atoi(param->getValueOfAtt("posX")), (float)atoi(param->getValueOfAtt("posY")), (float)atoi(param->getValueOfAtt("posZ"))));
			}else
			{
				try{
					node = graphSys::getI().getScene()->getSceneMgr()->getSceneNode(param->getValueOfAtt("nodeParent"));
					//->createChildSceneNode(param->getValueOfAtt("name"), Ogre::Vector3((float)atoi(param->getValueOfAtt("posX")), (float)atoi(param->getValueOfAtt("posY")), (float)atoi(param->getValueOfAtt("posZ"))));
				}catch(...){
					delete obj;
					obj=NULL;
					return obj;
				}
				node = node->createChildSceneNode(param->getValueOfAtt("name"), Ogre::Vector3((float)atoi(param->getValueOfAtt("posX")), (float)atoi(param->getValueOfAtt("posY")), (float)atoi(param->getValueOfAtt("posZ"))));
			}
			//dodawanie kierunku
			if(param->getAtt("dirX")!=-1||param->getAtt("dirX")!=-1||param->getAtt("dirX")!=-1)
			{
				node->setDirection(atof(param->getValueOfAtt("dirX")), atof(param->getValueOfAtt("dirY")), atof(param->getValueOfAtt("dirZ")));
			}
			node->attachObject(((cMovableObject*)obj)->getMovObj());
			obj->setSceneNode(node);
		}
		
		return obj;
	}
	/*	niedoszla walidacja
	static bool isExistObject(const std::string &type, const short numParam=-1)	//sprawdzanie czy taki obiekt moze zostac stowrozny (dodatkowo mozna sprawdzic czy posiada odpowiednia liczbe parametrow)
	{
		bool mode = false;	//czy sprawdzaæ liczbe paramterow (XML valid)
		if (numParam>=0)
			mode = true;
		if (type=="entity")
		{
			if(mode==true && numParam!=_NumParamEntity)
				return false;
		}else if(type=="camera")
		{
			if(mode==true && numParam!=_NumParamCamera)
				return false;
		}else
			return false;

		return true;
	}
	*/
};

#endif