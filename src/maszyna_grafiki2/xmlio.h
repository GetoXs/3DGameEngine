/*

		XMLio - XML input/output library 

		Automated Playground (c) Adrian Skupie� 2010
		Optimized by Mateusz Przybylek

		Nag��wek steruj�cy bibliotek� obs�ugi plik�w XML


		INFO:

		atrybuty zaczynaj� si� od indeksu 0, zwr�cenie indeksu -1 oznacza b��d
		nazwy nie mog� posiada� spacji, powinny by� unikalne w danej przestrzeni nazw, powielanie powoduje b��dy przy sprawdzaniu
		jest to uproszczona biblioteka, obs�uguje atrybuty i zagnie�dzenia, wymaga root'a o nazwie xml (lub sama go tworzy)
			przy zapisie/odczycie plikowym.
		wy��czona obs�uga danych
*/


// ===========================
#ifndef XMLIO
#define XMLIO
#include <iostream>
#include <fstream>
#define _BUF 3500
#pragma once

class cAtt
	// klasa atrybutu
{
public:
	cAtt(char *n,char *v){
							name = new char[strlen(n)+1]; strcpy(name,n);
							value = new char[strlen(v)+1]; strcpy(value,v);
							};
	~cAtt()	{
		delete [] name;
		delete [] value;
	};
	char*getName(){return name;};
	char*getValue(){return value;};
	void setName(char *n){
						delete [] name;
						name = new char[strlen(n)+1];
						strcpy(name,n);
						};
	void setValue(char *n){
						delete [] value;
						value = new char[strlen(n)+1];
						strcpy(value,n);
						};
protected:
	char *name;
	char *value;
};


// struktura listy atrybut�w z wbudowanym destruktorem
struct cAttList{
	cAttList(){current=NULL;next=NULL;};
	~cAttList(){if (current!=NULL)delete current; if (next!=NULL) delete next; next=NULL;current=NULL;};
	cAtt *current;
	cAttList *next;
};

// menager atrybut�w - sk�adowa obs�ugi atrybut�w klasy XML
class cAttMgr{
public:
	cAttMgr(){att=NULL;};
	~cAttMgr(){if (att!=NULL)delete att;};
	int getNumOfAtt();					// zwraca ilosc argumentow
	int getAtt(char *n);				// zwraca numer porzadkowy atrybutu o okreslonej nazwie
	void delAtt(int i);					// usun atrybut o okreslonym numerze
	char *getNameOfAtt(int n);			// pobierz nazwe atrybutu o numerze n
	char *getValueOfAtt(int n);			// pobierz wartosc atrybutu o numerze n
	char *getValueOfAtt(char* n);		// pobierz wartosc atrybutu o nazwie n, Mateusz
	void setNameOfAtt(int i,char *n);	// zmien nazwe atrybutu n
	void setValueOfAtt(int i,char *n);	// zmien wartosc atrybutu n
	void addAtt(char *n,char *v);		// dodaje atrybut
	bool isAtt(char *n);				// czy w bazie wyst�puje podany atrybut
protected:
	cAttList *att;						// lista atrybutow
};


// ===========================

class XML;
class cBuf;

struct XMLlist
{
	XMLlist(){current=NULL;next=NULL;};
	~XMLlist(){ if(current!=NULL) delete current; if (next!=NULL) delete next;};
	XML *current;
	XMLlist *next;
};

// klasa XML, uwaga - dzia�a rekurencyjnie!

class XML:public cAttMgr
{
public:
	XML(char *n){name = new char[strlen(n)+1]; strcpy(name,n); children=NULL;};
	XML(){name = new char[strlen("XML")+1]; strcpy(name,"XML"); children=NULL;};
	~XML(){delete [] name; if (children!=NULL) delete children;};
	char *getName(){return name;};
	void setName(char *n){delete [] name; name = new char[strlen(n)+1]; strcpy(name,n);};

	int getNumOfChild();
	XML *getChild(int i);			// zwraca dziecko o podanym numerze porzadkowym
	XML *getChild(char *n);			// podobnie, zwraca pierwsze dziecko o podanej nazwie
	//int getChildID(char *n);		// zwraca ID pierwszego dziecka o podanej nazwie
	int getChildNum(char *n);		// zwraca ilosc dzieci o podanej nazwie
	int getChildID(char *n,int i);// zwraca ID i-tego dziecka o podanej nazwie - wersja ex

	XML *addChild(char *n);			// dodaje dziecko o podanej nazwie a nastepnie zwraca wska�nik do niego
	void delChild(int n);			// usuwa dziecko o numerze n

	void saveToFileBuf(const char *filename, cBuf * plik = NULL); //jw. bufor pami�ciowy
	bool loadFromFileBuf(const char *filename, cBuf * plik = NULL); //jw. buforowane w pamieci


	void printf(); // przedstaw si�

protected:
	char *name;				// nazwa
	XMLlist *children;		// rekurencyjnie, dzieci :)

};


class cBuf
{
public:
	cBuf(): _handleMem(0), _countMem(0), _saveMode(false) { _buf[0]=0; };
	~cBuf() { _file.close(); } 

	bool open(const char *, bool saveMode=false);
	void close();	//zamyka plik i zapisuje reszte z bufora
	char getChar();
	int getHandleFile() { return (int)_file.tellg(); }
	int getHandleMem() { return _handleMem; }
	int getCountMem() { return _countMem; }
	void setPEOF();	//ustawia handler pliku na jego koniec
	void saveString(const char *);
	void saveString(const int);
	void flush();	//zapisuje reszte z bufora
private:
	char _buf[_BUF];
	std::fstream _file;
	
	bool _saveMode;
	int _handleMem;
	int _countMem;
};
#endif