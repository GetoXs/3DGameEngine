#include "graphSys.h"
#include "cObjectFactory.h"

//uruchamia pojedyncze przejscie kolejki mechaniki grafiki
int graph_run(unsigned long* counter)
{
	return graphSys::getI().go(counter);
}

int graph_signal_interpreter(csig* signal)
{
	return graphSys::getI().sigInterpreter(signal);
}

graphSys::graphSys(void):scene(NULL), oRoot(NULL), oWin(NULL), XMLScene(NULL), frameRate(1), sig_machine(NULL), lockRun(false)
{
}

graphSys::~graphSys(void)
{
	destroyEngine();
	if(sig_machine!=NULL)
		delete sig_machine;
}

int graphSys::sigInterpreter(csig* signal)
{
	switch(signal->sid)
	{
		/*sygnaly w ktorych parametr, okresla obiekt ktory modyfikuja musza byc obsluzone w interpreterze
			inaczej zostan¹ pominiete przy ich natloku
				np przesuniecia obiektow */
		
		case SIG_GRAPHSYS_INIT:
			_fInitEngine=true;
			break;
		case SIG_GRAPHSYS_WIN_CREATE:
			_fCreateWindow.setParam(signal->param);	//dodanie listy parametrow
			_fCreateWindow=true;
			break;
		case SIG_GRAPHSYS_SCENE_INIT:
			_fStartInit.setParam(signal->param);	//dodanie listy parametrow
			_fStartInit=true;
			break;
		case SIG_GRAPHSYS_SET_CAMERA:
			_fCameraSet.setParam(signal->param);	//dodanie listy parametrow
			_fCameraSet=true;
			break;
		case SIG_GRAPHSYS_BG_COLOR:
			_fChangeBgColor.setParam(signal->param);	//dodanie listy parametrow
			_fChangeBgColor=true;
			break;

		default:
			_fRenderFrame=true;
			break;
	}
	delete signal;	//kasowanie sygnalu
	return 0;
}

int graphSys::go(unsigned long* counter)
{
	if(lockRun==false)
	{
		if(_fInitEngine==true)	//inicjalizacja silnika (rzeczy niezalezne od sceny)
		{
			initializeEngine();

			_fInitEngine.clear();
		}
		//Ustawianie kamery oraz viewportu, id kamery brane z parametru sygnalu
		else if(_fCreateWindow==true)
		{
			//TODO: pozniej zmienic
			//_fCreateWindow.param.push_back(new std::string("Mechanika gry rlz!"));

			if(oRoot!=NULL)
			{
				oRoot->initialise(true, *(std::string*)(_fCreateWindow.param.front()));
				oWin = oRoot->getAutoCreatedWindow();
			}
			_fCreateWindow.clear();
		}
		//inicjalizacja sceny i XMLa z ktorego bedzie ona pobierana, 
		//sprawdzany warunek, czy aktualnie sceena nie jest ladowana
		else if(_fStartInit==true && _fLoadXML==false)	
		{
			//TODO: wywalic pozniej
			//_fStartInit.param.push_back(new std::string("scene1.xml"));

			delScene();
			XMLScene = new loadSceneXML;
			if(!XMLScene->loadXML(*(std::string*)_fStartInit.param.front()))	//blad przy otwieraniu pliku xml
			{
				delScene();
				//generuj error nie ustalo sie wczytac sceny
			}else
			{
				lockRun=true;		//zabolowany run() wykonuje sie wieloetapowe ladowanie sceny!!!
				//Before we initialize the resources, we should also set the default number of mipmaps that textures use. 
				Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);
				_fLoadXML=true;
			}
			//czyszczenie parametrow i ustawienie flagi na false
			_fStartInit.clear();
		}
		//TODO: rozdzielenie inicjalizacji grafiki i ladowania obiektow
		//trzeba sie zastanowic czy warto kasowac scene (jest w niej kamera i vp) co jest rownowazne z przeladowaniem mapy

		else if(_fCameraSet==true)
		{
			//TODO: zmienic jak bedzie interpreter ustawiony
			//_fCameraSet.param.push_back(new std::string("Cam1"));

			if(oWin!=NULL&&scene!=NULL)
			{
				oWin->removeAllViewports();
				oWin->addViewport(scene->getSceneMgr()->getCamera(*(std::string*)_fCameraSet.param.front()));			
			}
			_fCameraSet.clear();
		}
		else if(_fChangeBgColor==true)
		{
			//TODO:wywalic pozniej
			//_fChangeBgColor.param.push_back(new float(0.236));	//R
			//_fChangeBgColor.param.push_back(new float(0.222));	//G
			//_fChangeBgColor.param.push_back(new float(0.222));	//B

			if(oWin!=NULL)
				oWin->getViewport(0)->setBackgroundColour(Ogre::ColourValue(*(float*)_fChangeBgColor.param[0],*(float*)_fChangeBgColor.param[1],*(float*)_fChangeBgColor.param[2]));

			//czyszczenie listy void*
			_fChangeBgColor.clear();
		}else if(_fExit==true)
		{
			destroyEngine();
			return -1;

			//domyslnie renderujemy klatke (a przynamniej probojemy ;)
		}else
		{
			//TODO:przeskoczenie renderowania klatki (ograniczanie fps) 
			if((*counter)%frameRate==0)	
				if(oRoot->renderOneFrame())
				{
					Ogre::WindowEventUtilities::messagePump();
				}
				else
				{
					//koniec, listener zwrocil 0
					_fRenderFrame.clear();
				}
		}
	}else
	{
		if(_fLoadXML==true)	//kolejne etapy ladowania sceny oraz obiektow z pliku XML,
										//WIELOETAPOWE!
		{
			lockRun=false;
			/*try{
				short tryb=XMLScene->nextLoadStage();
			} catch(...){
				tryb=-1;
			}*/
			short tryb=XMLScene->nextLoadStage();	//do debugowania wersja tego powyzej
			if(tryb==1)	//ladowanie niezakonczone, cdn
			{
				lockRun=true;
			}else	if(tryb==0)	//ladowanie zakonczone
			{
				//unlock interpreter
				delete XMLScene;
				XMLScene=NULL;
				_fLoadXML.clear();

				//TODO: odblokuj runa
			}else if(tryb==-1)	//ladowanie przerwane blad
			{
				//TODO: odblokuj runa
				delScene();
				_fLoadXML.clear();
				//generuj error blad ladowania sceny z XML
			}
		}

	}


	return 0;
}
unsigned graphSys::addObjectScene(XML* param)
{
	if(scene==NULL)
		return 0;
	cObject *tmp = cObjectFactory::createObject(param);
	if(tmp==NULL)
		return 0;
	return scene->addObject(tmp);
}
unsigned graphSys::addObjectScene(cObject* object)
{
	if(scene==NULL || object==NULL)
		return 0;
	return scene->addObject(object);
}
bool graphSys::setScene(short type, const std::string name, float ambR, float ambG, float ambB)
{
	if(scene!=NULL || oRoot==NULL)
		return false;

	scene = new cScene(oRoot->createSceneManager(type, name));
	scene->getSceneMgr()->setAmbientLight(Ogre::ColourValue(ambR, ambG, ambB));
	
	return true;
}
void graphSys::delScene()
{
	if(oRoot==NULL)
		return;
	if(scene!=NULL)
	{
		oRoot->destroySceneManager(scene->getSceneMgr());
		delete scene;
		scene=NULL;
	}
	if(XMLScene!=NULL)
	{
		delete XMLScene;
		XMLScene=NULL;
	}
	//fl.clearScene();	niepotrzebne
}
bool graphSys::delObject(unsigned idObject)
{
	if(scene==NULL)
		return false;
	return scene->delObject(idObject);
}
void graphSys::initializeEngine()
{
	oRoot = new Ogre::Root;
	if (!oRoot->restoreConfig() && !oRoot->showConfigDialog())
    throw Ogre::Exception(52, "User canceled the config dialog!", "Application::setupRenderSystem()");

}
void graphSys::destroyEngine()
{
	if(oRoot==NULL)
		return;
	if(scene==NULL)
		return;
	this->delScene();
	delete oRoot;
	oRoot=NULL;
	frameRate=1;
	oWin=NULL;
}

signal_machine* graphSys::assign_signal_machine(main_signal_machine *main_machine)
{
	if(sig_machine==NULL){
		sig_machine = new signal_machine(SIG_GRAPHMACHINE,main_machine,graph_signal_interpreter);
		return sig_machine;
	}
	return NULL;
}



/* Ladowanie sceny po czesci
int graphSys::loadPartSceneXML()
{
	if(_loadObjectCount!=0 && _loadSceneXML==NULL)
		_loadObjectCount=0;
	if(_loadSceneXML==NULL)
	{
		if(_loadObjectCount!=0 || _loadNameXML==NULL || scene!=NULL)
		{
			delete _loadNameXML;
			_loadNameXML=NULL;
			return -1;
		}

		_loadSceneXML = new XML();	//ladowanie nowego XMLa
		if(!_loadSceneXML->loadFromFileBuf(_loadNameXML->c_str()))
		{
			delete _loadSceneXML;
			_loadSceneXML=NULL;
			delete _loadNameXML;
			_loadNameXML=NULL;
			return -1;
		}else
		{
			delete _loadNameXML;
			_loadNameXML=NULL;
		}
	}

	XML* sceneXML = _loadSceneXML->getChild("scene");
	if (sceneXML==NULL)
	{
		delete scene;
		delete _loadNameXML;
		_loadNameXML=NULL;
		delete _loadSceneXML;
		return -1;
	}
	if(scene==NULL)
	{
		scene = new cScene();
		//TODO: dolaczyc SceneMgr
	}
	unsigned maxCount = sceneXML->getNumOfChild();

	unsigned i;
	std::vector<std::string>* param = new std::vector<std::string>;
	for(i=_loadObjectCount; i<LOAD_PER_FRAME+_loadObjectCount && i<=maxCount; i++)
	{
		for(int j=0; j<sceneXML->getChild(i)->getNumOfAtt(); j++)
		{
			param->push_back(sceneXML->getChild(i)->getValueOfAtt(j));
		}
		cObjectFactory::createObject(sceneXML->getChild(i)->getName(), param);
		param->clear();
		//scene->addObject();
		std::cout<<i<<std::endl;
		//dodawanie elementu
	}
	if(i>=maxCount)
	{
		delete sceneXML;
		delete _loadSceneXML;
		_loadSceneXML = NULL;
		_loadObjectCount=0;
		return 1;	//koniec
	} else
	{
		_loadObjectCount = i;	//aktualizacja licznika zaladowanych obj
		return 0;	//cdn.
	}
} */