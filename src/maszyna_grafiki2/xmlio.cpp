#include "xmlio.h"
// ==========================================================

int cAttMgr::getNumOfAtt()
// zwraca ilosc argumentow
{
	cAttList *temp;
	if (att==NULL)
		return 0;
	temp = att;
	int iterator = 0;
	while (temp!=NULL)
	{
		temp = temp->next;
		iterator++;
	};
	return iterator;
};

// ==========================================================

int cAttMgr::getAtt(char *n)
// zwraca numer porzadkowy atrybutu o okreslonej nazwie
{
	cAttList *temp;
	if (att==NULL)
		return -1; // not found
	temp = att;
	int i=0;
	while(temp!=NULL)
	{
		if (strcmp(temp->current->getName(),n)==0)
			return i;
		temp = temp->next;
		i++;
	};
	return -1; // not found
};

// ==========================================================

void cAttMgr::delAtt(int i)
// usun atrybut o okreslonym numerze
{
	cAttList *temp;
	if (att==NULL)
		return; // nie mozna usunac atrybutu ktory nie istnieje
	if (i==0)
	{
		if (att->next==NULL)
		{
			delete att;
			att = NULL;
			return;
		};
		cAttList *temp2 = att->next;
		att->next=NULL;
		delete att;
		att = temp2;
		return;
	};

	temp = att;

	int iterator = 0;
	while (temp!=NULL)
	{
		if (iterator==i-1)
		{
			if (temp->next==NULL) return; // zabezpieczenie

			cAttList *temp2 = temp->next->next;
			temp->next->next=NULL;
			delete temp->next;
			temp->next = temp2;
			
			return;
		};
		temp = temp->next;
		iterator++;			
	};
	return;
};

// ==========================================================

char *cAttMgr::getNameOfAtt(int n)
// pobierz nazwe atrybutu o numerze n
{
	cAttList *temp;
	if (att==NULL)
		return 0;
	temp = att;
	int iterator = 0;
	while (temp!=NULL)
	{
		if (iterator==n)
			return temp->current->getName();
		temp = temp->next;
		iterator++;			
	};
	return 0;
};

// ==========================================================

char *cAttMgr::getValueOfAtt(int n)
// pobierz wartosc atrybutu o numerze n
{
	cAttList *temp;
	if (att==NULL)
		return 0;
	temp = att;
	int iterator = 0;
	while (temp!=NULL)
	{
		if (iterator==n)
			return temp->current->getValue();
		temp = temp->next;
		iterator++;			
	};
	return 0;
};

// ==========================================================

char *cAttMgr::getValueOfAtt(char* n)
// pobierz wartosc atrybutu o nazwie n, Mateusz
{
	cAttList *temp;
	if (att==NULL)
		return 0;
	temp = att;
	while (temp!=NULL)
	{
		if(strcmp(n, temp->current->getName())==0)
			return temp->current->getValue();
		temp = temp->next;	
	};
	return 0;
};

// ==========================================================

void cAttMgr::setNameOfAtt(int i,char *n)
// zmien nazwe atrybutu n
{
	cAttList *temp;
	if (att==NULL)
		return;
	temp = att;
	int iterator = 0;
	while (temp!=NULL)
	{
		if (iterator==i)
		{
			temp->current->setName(n);
			return;
		};
		temp = temp->next;
		iterator++;			
	};
	return;
};

// ==========================================================

void cAttMgr::setValueOfAtt(int i,char *n)
// zmien wartosc atrybutu n
{
	cAttList *temp;
	if (att==NULL)
		return;
	temp = att;
	int iterator = 0;
	while (temp!=NULL)
	{
		if (iterator==i)
		{
			temp->current->setValue(n);
			return;
		};
		temp = temp->next;
		iterator++;			
	};
	return;
};

// ==========================================================

void cAttMgr::addAtt(char *n,char *v)
// dodaje atrybut
{
	cAttList *temp;
	if (this->att==NULL)
	{
		this->att = new cAttList();
		this->att->current = new cAtt(n,v);
		return;
	}
	temp = this->att;
	while (temp->next!=NULL)
		temp = temp->next;
	temp ->next = new cAttList();
	temp->next->current = new cAtt(n,v);
	return;
	
};

// ==========================================================

bool cAttMgr::isAtt(char *n)
// czy w bazie wystêpuje podany atrybut
{
	if (this->getAtt(n) == -1)
		return false;
	return true;
};

// ==========================================================

int XML::getNumOfChild()
{
	XMLlist *temp = children;
	if (children==NULL)
		return 0;
	int counter = 0;
	while (temp!=NULL)
	{
		temp = temp->next;
		counter++;
	};
	return counter;	
};

// ==========================================================

XML *XML::getChild(int i)
// zwraca dziecko o podanym numerze porzadkowym
{
	XMLlist *temp = children;
	if (children==NULL)
		return 0;
	if (i==0)
		return children->current;
	int counter = 0;
	while (temp!=NULL)
	{
		if (counter==i-1)
		{
			if (temp->next!=NULL)
				return temp->next->current;
			return 0;
		}
		temp = temp->next;
		counter++;
	};
	return 0;
};

// ==========================================================

XML *XML::getChild(char *n)
// podobnie, zwraca pierwsze dziecko o podanej nazwie
{
	XMLlist *temp = children;
	if (children==NULL)
		return 0;
	while (temp!=NULL)
	{
		if (strcmp(n,temp->current->getName()) == 0)
		{
			return temp->current;
		}
		temp = temp->next;
	};
	return 0;
};

// ==========================================================

int XML::getChildNum(char *n)
// zwraca ilosc dzieci o podanej nazwie
{
	XMLlist *temp = children;
	if (children==NULL)
		return 0;
	int counter = 0;
	while (temp!=NULL)
	{
		if (strcmp(n,temp->current->getName()) == 0)
		{
			counter++;
		}
		temp = temp->next;
	};
	return counter;
};

// ==========================================================

int XML::getChildID(char *n,int i=0)
// zwraca ID i-tego dziecka o podanej nazwie - wersja ex
{
	XMLlist *temp = children;
	if (children==NULL)
		return 0;
	int counter = 0;
	int num=0;
	while (temp!=NULL)
	{
		if (strcmp(n,temp->current->getName()) == 0)
		{
			if (counter==i)
				return num;
			counter++;
		}
		temp = temp->next;
		num++;
	};
	return counter;
};

// ==========================================================

XML *XML::addChild(char *n)
// dodaje dziecko o podanej nazwie a nastepnie zwraca wskaŸnik do niego
{
	XMLlist *temp = children;
	if (children==NULL)
	{
		children=new XMLlist();
		children->current=new XML(n);
		return children->current;
	};
	while(temp->next!=NULL)
	{
		temp = temp->next;
	};
	temp->next = new XMLlist();
	temp->next->current = new XML(n);
	return temp->next->current;
};

// ==========================================================

void XML::delChild(int n)
// usuwa dziecko o numerze n
{
	XMLlist *temp = children;
	if (children==NULL)
		return;
	if (n==0)
	{
		XMLlist *temp2 = children->next;
		children->next=NULL;
		delete children;
		children = temp2;
		return;
	}
	int counter = 0;
	while (temp!=NULL)
	{
		if (counter==n-1)
		{
			if (temp->next==NULL)
				return;
			XMLlist *temp2 = temp->next->next;
			temp->next->next=NULL;
			delete temp->next;
			temp->next = temp2;
			return;
		}
		temp = temp->next;
		counter++;
	};
	return;
};


// ===========================================================
void XML::saveToFileBuf(const char *filename, cBuf * file)
// zapisuje do pliku hierarhiê uznaj¹c¹ ten XML za rodzica, tryb=0 oznacza tworzenie od 0, 1 kontynuacjê
{
	//FILE *plik;
	int tryb;
	if(file==NULL)
	{
		tryb=0;
		file = new cBuf();
		file->open(filename, true);
		if (strcmp(this->name,"xml")!=0)
		{
			file->saveString("<xml childEl=\"1\" version=\"1.0\">\n");
			//fprintf(file,"<xml childEl=\"1\" version=\"1.0\">\n");
		}
	}else
	{
		tryb=1;
	}
	/*switch(tryb)
	{
	case 1:
		plik=fopen(filename,"a");break;
	default:
		plik=fopen(filename,"w");
		// wa¿ne, na pocz¹tku nowego pliku MUSI znaleœæ siê sekcja XML
		if (strcmp(this->name,"xml")!=0)
			fprintf(plik,"<xml childEl=\"1\" version=\"1.0\">\n");

		break;
	};*/

	file->saveString("<");
	file->saveString(name);
	//fprintf(plik,"<%s",name);
	// atrybuty
	file->saveString(" childEl=\"");
	file->saveString(this->getNumOfChild());
	file->saveString("\"");
	//fprintf(plik," childEl=\"%d\"",this->getNumOfChild());
	for (int i=0;i<this->getNumOfAtt();i++)
		if (strcmp(this->getNameOfAtt(i),"childEl")!=0)
		{
			file->saveString(" ");
			file->saveString(this->getNameOfAtt(i));
			file->saveString("=\"");
			file->saveString(this->getValueOfAtt(i));
			file->saveString("\"");
			//fprintf(plik," %s=\"%s\"",this->getNameOfAtt(i),this->getValueOfAtt(i));
		}
	if (this->getNumOfChild()==0)
	{
		file->saveString("/>\n");
		//fprintf(plik,"/>\n");
	}else
	{
		file->saveString(">\n");
		//fprintf(plik,">\n");
		//fclose(plik);
		for (int i=0;i<this->getNumOfChild();i++)
		{
			this->getChild(i)->saveToFileBuf(filename,file);
			//this->getChild(i)->saveToFile(filename,1);
		}
		//plik=fopen(filename,"a");
		file->saveString("</");
		file->saveString(this->getName());
		file->saveString(">\n");
		//fprintf(plik,"</%s>\n",this->getName());
	};
	if ((tryb==0))
	{
		if(strcmp(this->name,"xml")!=0)
		{
			file->saveString("</xml>");
			//fprintf(plik,"</xml>");
		}
		file->close();
	}
	//fclose(plik);
	
};

// ===========================================================
bool XML::loadFromFileBuf(const char *filename, cBuf * plik)
{

	if (plik==NULL)
	{
		plik = new cBuf;
		if(!plik->open(filename, false))
			return false;

		if (att!=NULL)delete att;	
		if (children!=NULL) delete this->children;
		att=NULL;
		children=NULL;
	};

	/*
	tryb=
		4 : zbieranie znakow z "wartosci atrybutu"
		3 : poszukiwanie rozpoczecia ciagu znakow "wartosci atrybutu"
		2 : zbieranie znakow z "nazwy atrybutu"
		1 : zbierniae znakow z "tagu"
		0 : poszukiwanie rozpoczecia ciagu znakow "tagu"
		10 : koniec tagu - sa dzieci ">"
		20 : koniec tagu bez dzieci "/>"
	*/
	unsigned short int tryb = 0;
	char c;
	bool koniec=false;
	char buf[50];
	char buf1[50];
	//char buf2[50];	
	buf[0]=0;
	//strcpy(buf,"");
	int pos=0;
	bool gotname=false;
	do
	{
		c = plik->getChar();//getc(plik);
		if (c==EOF)return false;
		buf[pos]=c;
		pos++;

		if ((tryb==4)&&(c=='"'))
			//zakonczenie wartosci trybu
		{
			tryb=1;
			buf[pos-1]='\0';
			this->addAtt(buf1,buf);
			pos=0;
			continue;
		};

		if ((tryb==3)&&(c=='"'))
			// rozpoczecie wartoci atrybutu
		{
			tryb=4;
			pos=0;
		};

		if ((tryb==3)&&(c==' '))
			// omijamy spacje
			pos--;

		if ((tryb==2)&&(c=='='))
			// poszukiwanie rozpoczecia wartoci atrybutu
		{
			buf[pos-1]='\0';
			strcpy(buf1,buf);
			pos=0;
			tryb=3;
		}

		if ((tryb==2)&&(c==' '))
			// omijamy spacje
			pos--;


		if ((tryb==1)&&(c==' '))
			// koniec nazwy, ale sa atrybuty
		{
			buf[pos-1]='\0';
			tryb=2;
			if (!gotname)
			this->setName(buf);
			gotname=true;
			//std::cout<<buf<<std::endl;
			pos=0;
		};
		
		if ((tryb==0)&&(c=='<'))
		{
			tryb=1;
			pos=0;
			buf[0]=0;
			//strcpy(buf,"");
		};
		if ((tryb==1)&&(c=='>'))
		// koniec ale sa dzieci
		{
			koniec=true;
			tryb=10;
		};

		if ((tryb==1)&&(c=='/'))
		// koniec
		{
			buf[pos]='\0';
			//this->setName(buf);
			pos = 0;
			buf[0]=0;
			//strcpy(buf,"");
			tryb=0;
			koniec=true;

			//getc(plik);
			tryb=20;
		};
	}while((c!=EOF)&&(!koniec));

	if (tryb==10)
	{
		// s¹ dzieci!
		int krok=0;
		if (this->isAtt("childEl"))
			krok = atoi(this->getValueOfAtt(this->getAtt("childEl")));
		if (krok>0)
		for (int i=0;i<krok;i++)
		{
			XML * a = this->addChild("test");
			a->loadFromFileBuf(filename, plik);
		};
	};
		do{ 
			c = plik->getChar();//getc(plik); 
		}while((c!='>')&&(c!=EOF));

		//getc(plik);	
	
	if (plik==NULL)
	{
		plik->close();//fclose(plik);
	}	
	return true;
};

void XML::printf()
{
	using namespace std;
	cout<<"===== "<<name<<" ======"<<endl;
	cout<<"= mam "<<this->getNumOfAtt()<<" atrybutów"<<endl;
	cout<<"= mam "<<this->getNumOfChild()<<" dzieci"<<endl;
	for (int i=0;i<getNumOfAtt();i++)
		cout<<"= At["<<i<<"]->    "<<this->getNameOfAtt(i)<<" : "<<this->getValueOfAtt(i)<<endl;
	cout<<"= MOJE DZIECI: "<<endl;
	for(int i=0;i<this->getNumOfChild();i++)
	{
		cout<<"=== Dziecko "<<i<<endl;
		this->getChild(i)->printf();
		cout<<endl<<"== koniec dziecka "<<i<<endl;
	};
};

bool cBuf::open(const char * name, bool saveMode)
{
	if (name!=NULL)
	{
		_file.close();
		this->_saveMode=saveMode;
		int mode;
		if(saveMode==true)
			mode=std::fstream::out|std::fstream::trunc;
		else
			mode=std::fstream::in;
		_file.open(name, mode);
		if (_file.rdstate()==0)
			return true;
		else
			return false;
	}else
		return false;
}
char cBuf::getChar()
{
	if(_countMem == _handleMem)
	{
		
		if(!_file.eof())
		{
			//int oldHandleFile=file.tellg();
			_file.read(_buf, _BUF);
			_countMem = _file.gcount();
			_handleMem = 0;
			/* modul dla getline
			if(!file.eof())
			{
				int countMemOld = file.gcount();
				for(; buf[countMemOld]!=10 && countMemOld!=0; countMemOld--)
				{}
				countMem = countMemOld;
				file.seekg(oldHandleFile+countMemOld); 
			}
			*/
		}else
		{
			return EOF;
		}
	}
	return _buf[_handleMem++];
}
void cBuf::close()
{
	if(_file!=NULL && _saveMode==true)
		flush();
	_file.close();
}

void cBuf::saveString(const int l)
{
	char *tmp = new char[_MAX_INT_DIG];
	_itoa(l, tmp, 10);
	saveString(tmp);
	delete [] tmp;
}
void cBuf::saveString(const char * str)
{
	if(_file!=NULL&&_saveMode==true)
	{
		if(_handleMem+strlen(str)>=_BUF)
		{
			this->flush();
			_handleMem=0;
		}
		strcpy(_buf+_handleMem, str);
		_handleMem+=strlen(str);
	}
}
inline void cBuf::flush()
{
	if (_file!=NULL&&_saveMode==true) 
	{
		//_file<<_buf;
		_file.write(_buf, _handleMem);
		_file.flush();
	}
}