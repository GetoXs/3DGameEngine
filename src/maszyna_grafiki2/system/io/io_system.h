#ifndef _IO_SYS_
#define _IO_SYS_

#include "../system_queue.h"
/*
	System wejœcia/wyjœcia
*/


class io_mgr
/*
	Singleton wejœcia-wyjœcia
*/
{
public:
	io_mgr();
	~io_mgr();
	static io_mgr &get(){
		static io_mgr instance;
		return instance;
	};

	void run(long timer);			// kompatybilnoœæ z list¹ - funkcja sprawdzaj¹ca klawisz i reaguj¹ca sygna³em.
	

	signal_machine *getSigMach(){return sig_mach;};			// zwraca istniejaca maszyne sygnalowa
	signal_machine* assign_signal_machine(main_signal_machine *nowa);	// pod³¹cza maszynê sygna³ow¹ do jakiejœ g³ównej
	

	bool locked;					// czy maszyna ma nas³uchiwaæ? Domyœlnie nie.
	protected:
	signal_machine* sig_mach;		// maszyna sygna³owa
	char l_key;				// ostatnio wciœniêty klawisz
};

int io_signal_interpreter(csig *);	// interpreter sygna³ów widoczny z zewn¹trz
int io_run(unsigned long *timer); // zgodnoœc z kolejk¹
#endif