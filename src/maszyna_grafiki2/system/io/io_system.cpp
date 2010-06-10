#include "io_system.h"
#include <conio.h>

io_mgr::io_mgr()
{
	locked = true;
	sig_mach = NULL;
	l_key = 0;
}

io_mgr::~io_mgr()
{
	if (sig_mach!=NULL)
		delete sig_mach;
}

void io_mgr::run(long timer)
{
	if (this->locked)
		return;
	if (kbhit())
	{
		char k = getch();
		if(l_key!=0)
		if (l_key!=k)		// jeœli zwolniono ostatnio wciœniêty klawisz
		{
			sig_mach->send(SIG_GRAPHMACHINE,SIG_KEYUP,new char(l_key),NULL);	//Mateusz
			
		}		
		else
			return; // jeœli nadal jest wciœniêty ten sam klawisz to nic nie rób

		// dla znaków specjalnych
		// zale¿nie od znaku nadaj inny sygna³
		switch (k)
		{
		default:
			// dla pozosta³ych po prostu nadaj sygna³ do maszyny grafiki z znakiem sygna³u jako parametrem
			l_key = k;
			sig_mach->send(SIG_GRAPHMACHINE,SIG_KEYDOWN,new char(l_key),NULL);	//Mateusz
			break;
		}
	}
}


int io_signal_interpreter(csig *sig)
{
	switch(sig->sid)
	{
	case SIG_INPUT_START:
		io_mgr::get().locked = false;
		break;
	case SIG_INPUT_STOP:
		io_mgr::get().locked = true;
		break;
	case SIG_FAKEKEY: // przekazuje argument dalej, jako wciœniêcie i zwolnienie klawisza

		io_mgr::get().getSigMach()->send(SIG_GRAPHMACHINE,SIG_KEYDOWN,sig->param);
		io_mgr::get().getSigMach()->send(SIG_GRAPHMACHINE,SIG_KEYUP,sig->param);
		break;
	default:
		break;
	}
	delete sig;
	return 0;
}

signal_machine* io_mgr::assign_signal_machine(main_signal_machine *nowa)
{
	int (*t)(csig*) = io_signal_interpreter;
	sig_mach = new signal_machine(SIG_INPUTMACHINE,nowa,t);
	return sig_mach;
};

int io_run(unsigned long *timer)
{
	io_mgr::get().run(*timer);
	*timer = 0;
	return 0;
};