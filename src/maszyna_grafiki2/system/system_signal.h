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
	//char comm[255];					// parametry sygna³u
	std::vector<void*> param;	// nowe parametry sygnalu2
	int sid;						// signal-id
	csig():param(),odbiorca(0),nadawca(0),sid(0) {};	// wersja nieu¿ywana
	csig(int o,int n,int s):param(),nadawca(n),odbiorca(o),sid(s){};	// wersja bez argumentów
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
	signal_machine(unsigned short int newsmid, main_signal_machine *glowna,int (*in)(csig*)); // konstruktor przyjmuj¹ce ID nowej maszyny jako parametr,maszyne glowna oraz funkcje interpretera
	/*Wysyla sygnal do innej maszyny
		WAZNE:	Przyjmuje parametry void* !!!
						liste parametrow zakonczyc NULL'em !!!
		np: send(SIG_MAINMACHINE, SIG_GRAPHMACHINE, new float(4.12), new int(5), NULL); */
	int send(int odb,int sid, ...);
	/*Wysyla sygnal do innej maszyny
		WAZNE:	Nie nalezy kasowac parametrow listy (nie mozna delete param[i];) mozna wyczyscic (param.clear(); lub delete param;)	*/
	int send(int odb,int sid, std::vector<void*>param);	
	int (*interpreter)(csig *t);			// wskaŸnik na funkcjê interpretera
												// UWAGA ! funkcja ta powinna zwalniaæ miejsce w pamiêci zajmowane przez odebrany sygna³!
												// UWAGA NA NULL ! 

	int receiveS(csig *t);						// funkcja przyjmuj¹ca sygna³, nie wywo³ywaæ rêcznie!!
	unsigned int getsmid(){return smid;};		// zwracanie ID maszyny
	bool isLocked(){return locked;};
	void lock(){locked=true;};
	void unlock(){locked=false;};
	void run(bool all);							// uruchamia interpreter. TRUE = wszystkie sygna³y, false =jeden
	
protected:
	int smid;			// id maszyny sygna³ów
	bool locked;		// blokada maszyny
	std::deque<csig*>signals;
	csig *getSignal();		// pobranie sygna³u celem interpretacji
	main_signal_machine *mainMachine;	// maszyna rozdysponywujaca sygnaly
};

class main_signal_machine
// maszyna rozdysponowujaca sygna³y
{
public:

	main_signal_machine(unsigned int newsmid);
	void addSig(csig *t);						// dodawanie sygna³u do rozdysponowania
	void sendMessages(int a);					// rozsy³anie wiadomoœci po maszynach, kompatybilna z listami zdarzeñ
	void addMachine(signal_machine *x);			// dodaje maszynê sygna³ów
	int runInterpreters(bool all);	//uruchamia interpretery maszyn sygnalow
protected:
	std::vector<signal_machine *> machines;
	std::deque<csig*> signals;
	unsigned int smid;
	bool isExisting(unsigned int a);			// czy podana maszyna jest pod³¹czona?
	signal_machine *find(unsigned int a);		// odnajdŸ i zwróæ wskaŸnik na maszynê
};

#endif