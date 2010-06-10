/*
	PLIK NAZW MASZYN I SPECYFICZNYCH SYGNA£ÓW
*/ 

#define SIG_MAINMACHINE 0
#define SIG_GRAPHMACHINE 1
#define SIG_SCRIPTMACHINE 2
#define SIG_INPUTMACHINE 3


#define SIG_CLOSEAPP 1001 /* zamkniecie aplikacji */
#define SIG_LOCKAPP 1002 /* oczekiwanie na sygna³ powrotu sterowania */

// sygnaly maszyny grafiki

/*inicjalizuje silnik */
#define SIG_GRAPHSYS_INIT	5001				
/*tworzy okno jako parametr przyjmuje tytul okna
	@param: string titleWindow */
#define SIG_GRAPHSYS_WIN_CREATE 5002
/*laduje scene jako parametr przyjmuje nazwe pliku .xml sceny do wczytania
	@param: string fileName */
#define SIG_GRAPHSYS_SCENE_INIT	5003
/*ustawia kamere jako parametr przyjmuje nazwe kamery do wczytania (nazwa z pliku xml)
	@param: string camName */
#define SIG_GRAPHSYS_SET_CAMERA 5004
/*ustawia kolor tla sceny
	@param: float R, float G, float B */
#define SIG_GRAPHSYS_BG_COLOR 5005

// sygnaly jezyka skryptowego

#define SIG_SCRIPTUS_LOCK 2001		/* zablokuj wywolanie skryptow */
#define SIG_SCRIPTUS_UNLOCK 2002	/* odblokuj wywolanie skryptow */
#define SIG_SCRIPTUS_RUNSCRIPT 2003 /* powoduje uruchomienie skryptu o ID przeslanym jako parametr */

// sygna³y menagera wejscia

#define SIG_INPUT_START 3001	/* w³¹cza nas³uch wejœcia z klawiatury */
#define SIG_INPUT_STOP 3002		/* wy³¹cza nas³uch z klawiatury */
#define SIG_KEYDOWN 3003		/* wysy³a jako argument kod wciœniêtego klawisza */
#define SIG_KEYUP 3004			/* wysy³a informacjê, ¿e klawisz o podanym ID nie jest ju¿ wciœniêty */
#define SIG_FAKEKEY 3005		/* nadaje "fa³szywy" znak klawisza, funkcja sterowania klawiatur¹ */