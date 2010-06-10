#include "sys_mgr.h"


main_system::main_system()
{
	//glowna maszyna sygnalow
	this->main_sig_m = new main_signal_machine(SIG_MAINMACHINE);
	main_loop = new system_queue();
	main_loop->addSigMachine(main_sig_m);
	//main_loop->add(0,1,sys_main_signal_machine_integration);
	
	// pod³¹czamy maszyny sygna³owe i g³ówne funkcje
	//scriptus::get().assign_signal_machine(this->main_sig_m);
	io_mgr::get().assign_signal_machine(this->main_sig_m);
	main_loop->add(5,10,io_run);

	graphSys::getI().assign_signal_machine(this->main_sig_m);
	main_loop->add(5,10,graph_run);
}

main_system::~main_system()
{
	delete main_sig_m;
	delete main_loop;
};



int sys_main_signal_machine_integration(unsigned long *timer)
{
	main_system::get().getSignalMachine()->sendMessages(*timer);
	*timer = 0;
	return 0;
}

void main_system::add_function_to_loop(unsigned int id,unsigned short int prior,int (*func)(unsigned long int*))
{
	main_loop->add(id,prior,func);
}
void sleep(unsigned int miliseconds)
{
	clock_t goal = miliseconds + clock();
	while (goal > clock());
}

void main_system::loop()	// uruchamia pêtle
{
	//wysylka sygnalow
	this->main_sig_m->sendMessages(0);
	//interpretacja sygnalow oraz uruchomienie zarejestrowanych funkcji
	this->main_loop->run(0);
	sleep(10);
}