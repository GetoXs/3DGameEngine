#ifndef GRAPH_SYS
#define GRAPH_SYS
#pragma once
#include "cSceneList.h"
#include "loadSceneXML.h"

//interpreter sygnalow maszyny grafiki
int graph_signal_interpreter(csig* signal);
//uruchamia pojedyncze przejscie kolejki mechaniki grafiki
int graph_run(unsigned long* counter);

//wzorzec projektowy Singleton
class graphSys
{
public:
	static graphSys &getI()
	{
		//Inicjalizacja statycznego obiektu.
		//Obiekt zostanie utworzony przy pierwszym wywo³aniu tej metody
		//i tylko wtedy nast¹pi inicjalizacja przy pomocy konstruktora.
		//Ka¿de nastêpne wywo³anie jedynie zwróci referencjê tego obiektu.
		static graphSys instance;
		return instance;
	}
	//uruchamia pojedyncze przejscie kolejki
	int go(unsigned long* counter);

	//przepisuje wskaznik obiektu do sceny
	unsigned addObjectScene(cObject* object);	
	//tworzy nowy obiekt przy pomocy fabryki obiektów
	unsigned addObjectScene(XML* param);
	//unsigned addObjectScene(const std::string type, std::vector<std::string>* param);	//pierwsza wersja
	//kasowanie obiektu
	bool delObject(unsigned idObject);

	//ustawienie sceny (tylko jesli jest pusta!)
	bool setScene(short type, const std::string name, float ambR=1.0f, float ambG=1.0f, float ambB=1.0f);
	cScene* getScene() {return scene;}
	//wyczyszczenie sceny i listy obiektow z nia
	void delScene();

	//inicjalizacja silnika grafiki
	void initializeEngine();
	//wylaczanie silnika grafiki (stan jak po wlaczeniu)
	void destroyEngine();
	//TODO: ustawia niebo do wyboru skybox i skydome
	//void setSky(XML* param);

	//inicjalizacja maszyny dygnalow i dodanie jej do glownej maszyny
	signal_machine* assign_signal_machine(main_signal_machine *main_machine);
	//interpreter sygnalow
	int graphSys::sigInterpreter(csig* signal);
	//friend int graph_signal_interpreter(csig* signal);
	signal_machine* getSignalMachine() { return sig_machine; }

	//TODO: dodac zarzadzanie grupami zasobow z poziomu sygnalow
	~graphSys(void);
protected:
	struct flagParam {
		flagParam():flag(false),param() {}
		void clear()
		{
			for(int i=0; i<param.size(); i++)
			{ delete param[i]; }
			flag=false;
		}
		~flagParam() { clear(); }
		operator bool() {return flag;}
		bool operator==(const bool check) { return check==flag; }
		flagParam& operator=(const bool& check) 
		{ 
			this->flag=check;
			return *this;
		}
		void setParam(std::vector<void*> &v)	
		{ 
			if(param.size()!=0)	clear();
			param = v;
		}
		bool flag;
		std::vector<void*> param;
	};
	flagParam _fExit;	//sekwencja wyjscia z programu
	flagParam _fStartInit;	//sekwencja zainicjalizowania sceny
	flagParam _fLoadXML;	//ladowanie obiektow z XMLa
	flagParam _fRenderFrame;	//sekwencja renderowania pojedynczej klatki
	flagParam _fInitEngine;	//inicjalizacja silnika grafiki
	flagParam _fCreateWindow;	//tworzy okno windowsa
	flagParam _fCameraSet;	//proces ustawienia odpowiedniej kamery (param)
	flagParam _fChangeBgColor;	//zmiana koloru tla
	void _fClear() 
	{	_fExit.clear();
		_fStartInit.clear();
		_fLoadXML.clear();
		_fRenderFrame.clear(); 
		_fInitEngine.clear();
		_fCreateWindow.clear();
		_fCameraSet.clear();
	}
	bool lockRun;
/*	pierwotna wersja tego wyzej
	struct graphFlags //flagi stanu maszyny grafiki
	{
		graphFlags(){clear();}
		bool fExit;	//sekwencja wyjscia z programu
		bool fStartInit;	//sekwencja zainicjalizowania sceny
		bool fLoadXML;	//ladowanie obiektow z XMLa
		bool fRenderFrame;	//sekwencja renderowania pojedynczej klatki
		bool fInitEngine;	//inicjalizacja silnika grafiki
		bool fCreateWindow;	//tworzy okno windowsa
		bool fCameraSet;	//proces ustawienia odpowiedniej kamery (param)
		bool fChangeBgColor;	//zmiana koloru tla
		void clear() { fChangeBgColor=fCameraSet=fExit=fStartInit=fLoadXML=fRenderFrame=fInitEngine=fCreateWindow=false; }
		void clearScene() {fStartInit=fLoadXML=fRenderFrame=false;}
	};
	graphFlags fl;	//flagi stanu maszyny grafiki

	//std::list<std::string> sig_param;
	std::list<std::vector<void*>> sig_param2;	//lista z lista parametrow dla kolejnych flag
	//std::string interpreterParam;	//parametry sygnalu z interpretera
*/
	
	loadSceneXML* XMLScene;
	cScene* scene;	//wskaznik na scene aktualnie wczytana
	Ogre::Root* oRoot;	//wskaznik na roota od ogre'a
	Ogre::RenderWindow* oWin;
	//maszyna sygnalow maszyny grafiki ;)
	signal_machine *sig_machine;
	//okresla co ktore przejscie kolejki ma byc generowana nowa klatka
	unsigned frameRate;

	graphSys(void);
};




#endif