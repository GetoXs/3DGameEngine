#ifndef _SIG_SYS_
#define _SIG_SYS_
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <deque>
#include <cstdarg>
#include "system_signal_names.h"

struct csig;
class signal_machine;
class main_signal_machine;


struct csig
{
	unsigned short int odbiorca;	// id odbiorcy
	unsigned short int nadawca;		// id nadawcy
	//char comm[255];					// parametry sygna�u
	std::vector<void*> param;	// nowe parametry sygnalu2
	int sid;						// signal-id
	csig():param(),odbiorca(0),nadawca(0),sid(0) {};	// wersja nieu�ywana
	csig(int o,int n,int s):param(),nadawca(n),odbiorca(o),sid(s){};	// wersja bez argument�w
	csig(int o,int n,int s, std::vector<void*> p):param(p),nadawca(n),odbiorca(o),sid(s){};	//wersja z kopiowanie argumentow
	csig(int o,int n,int s, ...):param(),nadawca(n),odbiorca(o),sid(s)	//wersja z ustawianiem arg, Mateusz
	{
		va_list param_list;
		va_start(param_list, s);
		void* tmp=va_arg(param_list, void*);
		while(tmp!=NULL)
		{
			param.push_back(tmp);
			tmp = va_arg(param_list, void*);
		}
	}
};


class signal_machine
{
public:
	signal_machine(unsigned short int newsmid, main_signal_machine *glowna,int (*in)(csig*)); // konstruktor przyjmuj�ce ID nowej maszyny jako parametr,maszyne glowna oraz funkcje interpretera
	/*Wysyla sygnal do innej maszyny
		WAZNE:	Przyjmuje parametry void* !!!
						liste parametrow zakonczyc NULL'em !!!
		np: send(SIG_MAINMACHINE, SIG_GRAPHMACHINE, new float(4.12), new int(5), NULL); */
	int send(int odb,int sid, ...);
	/*Wysyla sygnal do innej maszyny
		WAZNE:	Nie nalezy kasowac parametrow listy (nie mozna delete param[i];) mozna wyczyscic (param.clear(); lub delete param;)	*/
	int send(int odb,int sid, std::vector<void*>param);	
	int (*interpreter)(csig *t);			// wska�nik na funkcj� interpretera
												// UWAGA ! funkcja ta powinna zwalnia� miejsce w pami�ci zajmowane przez odebrany sygna�!
												// UWAGA NA NULL ! 

	int receiveS(csig *t);						// funkcja przyjmuj�ca sygna�, nie wywo�ywa� r�cznie!!
	unsigned int getsmid(){return smid;};		// zwracanie ID maszyny
	bool isLocked(){return locked;};
	void lock(){locked=true;};
	void unlock(){locked=false;};
	void run(bool all);							// uruchamia interpreter. TRUE = wszystkie sygna�y, false =jeden
	
protected:
	int smid;			// id maszyny sygna��w
	bool locked;		// blokada maszyny
	std::deque<csig*>signals;
	csig *getSignal();		// pobranie sygna�u celem interpretacji
	main_signal_machine *mainMachine;	// maszyna rozdysponywujaca sygnaly
};

class main_signal_machine
// maszyna rozdysponowujaca sygna�y
{
public:

	main_signal_machine(unsigned int newsmid);
	void addSig(csig *t);						// dodawanie sygna�u do rozdysponowania
	void sendMessages(int a);					// rozsy�anie wiadomo�ci po maszynach, kompatybilna z listami zdarze�
	void addMachine(signal_machine *x);			// dodaje maszyn� sygna��w
	int runInterpreters(bool all);	//uruchamia interpretery maszyn sygnalow
protected:
	std::vector<signal_machine *> machines;
	std::deque<csig*> signals;
	unsigned int smid;
	bool isExisting(unsigned int a);			// czy podana maszyna jest pod��czona?
	signal_machine *find(unsigned int a);		// odnajd� i zwr�� wska�nik na maszyn�
};

#endif