#ifndef _MAIN_SYS_
#define _MAIN_SYS_
/*
	G³ówny menager aplikacji
	- obsluga g³ównej maszyny sygna³owej i maszyny kolejek 

*/
//#include "system_queue.h"
//#include "../system_scriptusmgr.h"
#include "io/io_system.h"
#include "../graphSys.h"


class main_system
{
public:
	static main_system &get(){
		static main_system instance;
		return instance;
	};

	main_system();
	~main_system();

	void add_function_to_loop(unsigned int id,unsigned short int prior,int (*func)(unsigned long int*)); // dodaje funkcje do kolejki 
	inline main_signal_machine *getSignalMachine(){return main_sig_m;};	// funkcja przydatna do tworzenia nowych podmaszyn
	void add_signal_machine(signal_machine* sig) { main_loop->addSigMachine(sig); }

	void init();	// funkcje inicjuj¹ce poszczególne systemy
	void loop();	// uruchamia pêtle

protected:
	main_signal_machine *main_sig_m;
	process_queue *main_loop;
};

int sys_main_signal_machine_integration(unsigned long *timer);


#endif