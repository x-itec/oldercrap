/*

Prozessforking-Klasse
(C) X-ITEC Boris Köster 2001

Benötigt
CbkError.cpp

*/


#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

const char* CbkFork_Copyright="X-ITEC C++ Multiprocess-Library. $Id: CbkFork.cpp,v 1.1.1.1 2001/06/15 03:11:08 BKoester Exp $";


class CbkFork
{

public:
enum EN_bkForkType{FT_UNKNOWN,FT_FORK};
enum EN_bkForkStatus{FS_UNKNOWN,FS_DAD,FS_SON,FS_ERROR};

EN_bkForkType   forktype;//muss gesetzt werden, sonst Abbruch
EN_bkForkStatus forkstatus;//z. B. ob man der Baba is oder Soon oder so
pid_t           pid;//Rückgabewert nach fork
int             waitstatus;//status nach Aufruf von waitpid(), siehe Makros zu ::waitpid()

//Konstruktor
   CbkFork();//kein Forktyp? Abbruch!
   CbkFork(EN_bkForkType ft);//so ists richtig

pid_t fork();
pid_t wait();
pid_t wait(pid_t p);

};



CbkFork::CbkFork(EN_bkForkType ft)
{
forktype=ft;
}

CbkFork::CbkFork()
{
//So nicht mein Freund
CbkError fehler;
fehler.ErrorSTL(CbkError::ERROR_sCORE,
                CbkError::ERROR_tMISSINGCONSTRUCTORPARAM,
                CbkError::ERROR_lWARNING,
                "Fork ohne Konstruktor aufgerufen, Konstruktor auf FORK gesetzt"
                );

                forktype=FT_FORK;
                fehler.DoThrow();//Rückmeldung an Hauptanwendung, Kontrolle erwünscht
}

//wartet auf einen spezifischen Prozess
pid_t CbkFork::wait(pid_t p)
{
return ::waitpid(p,&waitstatus,0);
}

pid_t CbkFork::wait()
{
return ::waitpid(pid,&waitstatus,0);
}

pid_t CbkFork::fork()
{
//TODO: VFork, PFork oder was da war
if(forktype==FT_FORK)
{
pid= ::fork();//systemcall
//weitere Infos, nur so
if(pid==-1){forkstatus=FS_ERROR;}
if(pid==0){forkstatus=FS_SON;}
if(pid>0){forkstatus=FS_DAD;}

}
return pid;
/*
Rückgabewerte: 0=bin im Kindprozess, -1=Fehler, <>0 bin im Elternprozess
*/
}