
/*

CbkSemaphore

Semaphore-Handling

(C) Boris Köster 2001
Alle Rechte reserviert.
http://www.x-itec.de

Dieses Modul verwendet
CbkBase
CbkError

Dieses Modul verwendet Exceptions

$Id: CbkSemaphore.cpp,v 1.1.1.1 2001/06/15 03:11:08 BKoester Exp $

Dokumentation
-------------

Diese Klasse erzeugt Semaphoren für gesicherte Bereiche. Ein einmal reservierter Key, der nicht durch den Destruktor aufgrund eines STRG-C freigegeben werden kann, kann nicht noch einmal benutzt werden. Bei einem Core-Dump wird noch der Destruktor aufgerufen.

Wird im Konstruktor der Key 0 benutzt, wird ein IPC_Private Key erzeugt, der bei jedem Aufruf des Programms anders ist, sich natürlich während der Anwendung selbst nicht verändert, außer innerhalb einer lokalen Prozedur, wo dann natürlich durch einen Konstruktor ein neues IPC_Private Element angelegt wird.

Möchte man also ein IPC_Private Element benutzen aus Sicherheitsgründen, dies prozessübergreifend benutzen dann wäre eine globale Definition nicht verkehrt.

Anwendungsbeispiel:

CbkSemaphore sema(0);//0=private key erzeugen
sema.P();//Geschützten Bereich betreten
sema.V();//Semaphore verlassen

Das ist alles. Sobald der geschützte Bereich betreten wurde, kann er von
anderen (Sub)Prozessen nicht betreten werden, wenn sie zum Beispiel geforked sind weil sie auf die gleichen Daten zugreifen.

Wenn man ein Programm zweimal startet und die gleiche ID im Konstruktor aquiriert wird, kommt es zu einer Exception. Von daher sind diese Private-Keys mit denen man so nichts zu tun hat, schon sehr sinnvoll um dieses "Problem" zu umgehen, wenn es nicht komplett systemweit zu beachten ist!


*/

#include <signal.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/stat.h>

#include "CbkBase.cpp"
#include "CbkError.cpp"

const char* CbkSemaphore_Copyright="X-ITEC Semaphore C++ Library. $Id: CbkSemaphore.cpp,v 1.1.1.1 2001/06/15 03:11:08 BKoester Exp $";


class CbkSemaphore : public CbkBase
{
public:
int sem_key;//Key, Zahl die gesetzt werden muss, = Bereich
//Konstruktor
CbkSemaphore (int id);
~CbkSemaphore();

//pasar/verlasse
inline void P();
inline void V();


private:
int semid;//interne ID für den Key
struct sembuf sem;


//pasar/verlasse Basisroutine
void pv(int operation);

};

void CbkSemaphore::P()
{
dout(CbkBase::LM_CORE,"Sem-P");
pv(-1);
}
void CbkSemaphore::V()
{
dout(CbkBase::LM_CORE,"Sem-V");
pv(1);
}

void CbkSemaphore::pv(int operation)
{
sem.sem_num=0;
sem.sem_op=operation;sem.sem_flg=SEM_UNDO;

if(semop(semid,&sem,1)==-1)
{
CbkError fehler;
char fstring[100];
sprintf(fstring,"Semaphore-Status semop Problem. errno=%i",errno);

fehler.ErrorSTL(CbkError::ERROR_sCORE,
                CbkError::ERROR_tSEMOP,
                CbkError::ERROR_lCRITICAL,
                fstring
                );
                fehler.DoThrow();
}
}

CbkSemaphore::~CbkSemaphore()
{
dout(CbkBase::LM_CORE,"Semaphore Destruktor");
semctl(semid,IPC_RMID,0);
}

CbkSemaphore::CbkSemaphore (int id)
{
sem_key=id;
int shmflags=S_IRWXU|S_IRWXG|S_IRWXO|IPC_CREAT|IPC_EXCL;
if(id==0)
{
shmflags=shmflags|IPC_PRIVATE;//individuellen Key anlegen wenn id=0, sehr gut!
}
dout(CbkBase::LM_CORE,"Init sema start ");

if( (semid=semget(sem_key,1,shmflags))==-1 )
{
CbkError fehler;
char fstring[100];
sprintf(fstring,"Semaphore kann nicht initialisiert werden (semget). errno=%i",errno);

fehler.ErrorSTL(CbkError::ERROR_sCORE,
                CbkError::ERROR_tSEMINIT,
                CbkError::ERROR_lCRITICAL,
                fstring
                );
                fehler.DoThrow();
}

if(semctl(semid,0,SETVAL,1)==-1)
{
CbkError fehler;
fehler.ErrorSTL(CbkError::ERROR_sCORE,
                CbkError::ERROR_tSEMINIT,
                CbkError::ERROR_lCRITICAL,
                "Semaphore Init semctl Fehler"
                );
                fehler.DoThrow();
}


dout(CbkBase::LM_CORE,"Init sema end");
}

