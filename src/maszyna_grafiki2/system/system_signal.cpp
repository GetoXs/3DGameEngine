#include "system_signal.h"

signal_machine::signal_machine(unsigned short int newsmid, main_signal_machine *glowna,int (*in)(csig*))
{
	this->smid = newsmid;
	this->mainMachine = glowna;
	this->interpreter = in;
	this->signals.clear();
	this->locked=false;
	glowna->addMachine(this);
}
/* pierwsza wersja
int signal_machine::send(int odb,int sid,char att[255])
{
	csig *temp = new csig(odb,this->smid,sid,att);
	this->mainMachine->addSig(temp);
	return 0;
}*/
int signal_machine::send(int odb,int sid, ...)
{
	va_list arg_list;
	va_start(arg_list, sid);
	
	std::vector<void*> new_param;	//nowa lista parametrow
	void* tmp=va_arg(arg_list, void*);
	while(tmp!=NULL)
	{
		new_param.push_back(tmp);	//dodawanie parametrow
		tmp = va_arg(arg_list, void*);
	}
	csig *temp = new csig(odb,this->smid,sid,new_param);	//stworzenie sygnalu
	this->mainMachine->addSig(temp);	//przeslanie sygnalu
	return 0;
}
int signal_machine::send(int odb,int sid, std::vector<void*>param)
{
	csig *temp = new csig(odb,this->smid,sid,param);	//stworzenie sygnalu
	this->mainMachine->addSig(temp);	//przeslanie sygnalu
	return 0;
}


int signal_machine::receiveS(csig *t)
{
	this->signals.push_back(t);
	return 0;
}


csig *signal_machine::getSignal()
{
	if (this->signals.size()>0)
	{
		csig *t =  this->signals.front();
		this->signals.pop_front();
		return t;
	}

	return NULL;
}

main_signal_machine::main_signal_machine(unsigned int newsmid)
{
	this->smid = newsmid;
	this->signals.clear();
	this->machines.clear();
}

void main_signal_machine::addSig(csig *t)
{
	this->signals.push_back(t);
}

void main_signal_machine::addMachine(signal_machine *x)
{
	this->machines.push_back(x);
}

bool main_signal_machine::isExisting(unsigned int a)
{
	
	for (int i=0;i<this->machines.size();i++)
	{
		if (this->machines[i]->getsmid() == a)
			return true;
	}
	return false;
}


signal_machine *main_signal_machine::find(unsigned int a)
{
	
	for (int i=0;i<this->machines.size();i++)
	{
		if (this->machines[i]->getsmid() == a)
			return this->machines[i];
	}
	return NULL;
}


void main_signal_machine::sendMessages(int a)
{
	// ta funkcja rozsy³a wszystkie otrzymane komunikaty interpretuj¹c jednoczeœnie w³asne
	for (int i=0;i<signals.size();i++)
	{
		csig *temp = signals[i];
		//std::cout <<"WYSY£AM sygna³ [nadawca,odbiorca,sig,wiad] "<<temp->nadawca<<" "<<temp->odbiorca<<" "<<temp->sid<<" "<<temp->comm<<std::endl;

		if (temp->odbiorca==this->smid)
		{
			// w³asny interpreter sygna³ów
			switch (temp->sid)
			{
			case SIG_CLOSEAPP:
				// zamkniêcie aplikacji
				break;
			case SIG_LOCKAPP:
				break;
			default:
				break;
			}
		}
		else

		if (isExisting(temp->odbiorca))
			find(temp->odbiorca)->receiveS(temp); // przekazanie sygna³u do celu
	}
	signals.clear();
}

void signal_machine::run(bool all)
{	
if (all)
{
	while (signals.size()>0)
		interpreter(getSignal());
}		// uruchomienie interpretacji sygna³u, zuzywa wszystkie sygna³y na raz!
else
	interpreter(getSignal());
};

int main_signal_machine::runInterpreters(bool all)
{
	int i=0;
	for(; i<machines.size(); i++)
	{
		machines[i]->run(all);
	}
	return i;
}