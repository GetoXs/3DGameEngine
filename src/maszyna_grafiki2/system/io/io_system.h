#ifndef _IO_SYS_
#define _IO_SYS_

#include "../system_queue.h"
/*
	System wej�cia/wyj�cia
*/


class io_mgr
/*
	Singleton wej�cia-wyj�cia
*/
{
public:
	io_mgr();
	~io_mgr();
	static io_mgr &get(){
		static io_mgr instance;
		return instance;
	};

	void run(long timer);			// kompatybilno�� z list� - funkcja sprawdzaj�ca klawisz i reaguj�ca sygna�em.
	

	signal_machine *getSigMach(){return sig_mach;};			// zwraca istniejaca maszyne sygnalowa
	signal_machine* assign_signal_machine(main_signal_machine *nowa);	// pod��cza maszyn� sygna�ow� do jakiej� g��wnej
	

	bool locked;					// czy maszyna ma nas�uchiwa�? Domy�lnie nie.
	protected:
	signal_machine* sig_mach;		// maszyna sygna�owa
	char l_key;				// ostatnio wci�ni�ty klawisz
};

int io_signal_interpreter(csig *);	// interpreter sygna��w widoczny z zewn�trz
int io_run(unsigned long *timer); // zgodno�c z kolejk�
#endif