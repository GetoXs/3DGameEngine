/*
	Kolejka systemu
	v0.1
*/
#ifndef _SYS_QUEUE_
#define _SYS_QUEUE_

#include "system_signal.h"




// podstawowa klasa funkcji

struct basic_func
{
	int (*function)(unsigned long*);			// funkcja wskazywana
	unsigned short int prior;					// priorytet 0 - najwyższy
	unsigned int ID;						// nazwa funkcji
	unsigned long timer;						// timer - który raz wywołujemy funkcję
												//		   FUNKCJE POWINNY ZADBAC O RESETOWANIE!
	// konstruktory
	basic_func(unsigned int id,int i,int (*w)(unsigned long *)):timer(0){prior = i;function = w;ID = id;};
	//basic_func(int i,int (*w)(unsigned long*)):timer(0){prior = i;function = w;ID = sys::func::mainIDLE;};
	//basic_func(int i):timer(0){prior = i;function = NULLfunc;ID = sys::func::mainIDLE;};
	//basic_func():timer(0){prior=1000;function=NULLfunc;ID = sys::func::mainIDLE;};

	// funkcje obsługi
	int run(){timer++; return function(&timer);};	

};


// kolejka procesów

class process_queue
{
public:
	// konstruktory i destruktory
	process_queue();
	~process_queue();

	void sort();						// sortowanie względem priorytetów 

	int run(unsigned long *tim);		// wykonuje 1 pętle kolejki, kompatybilne z zagnieżdzeniami kolejek procesów
	bool end(){return en;};				// czy powinniśmy już zakończyć?

	void set_end_state(bool a){en=a;};	// zmienia stan zmiennej odpowiedzialnej za koniec

	void add(unsigned int id,unsigned short int prior,int (*func)(unsigned long int*)); // dodaje funkcje
	void del(unsigned int id);			// usuwa funkcję o podanym ID
	
	unsigned int size(){return process.size();};

	void addSigMachine(signal_machine *sig);
	void addSigMachine(main_signal_machine *sig);
	main_signal_machine *getMainMachine(){return mainsigmach;};
	signal_machine *getSigMachine(){return sigmach;};
protected:
	std::vector<basic_func*> process;	
	bool en;							// zmienna odpowiedzialna za wyjście z kolejki
	int dodano_maszyne;				// czy zintegrowano maszynę stanów? 0-nie, 1-zwykłą, 2-główną
	signal_machine *sigmach;			// maszyna stanów
	main_signal_machine *mainsigmach;	// główna maszyna stanów
};




// kolejka systemu - singleton kolejki procesów

class system_queue:public process_queue
{
public:
	static system_queue &get()
	{
		static system_queue instance;
		return instance;
	};
};

#endif