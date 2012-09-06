/*

CbkSharedMemory

(C) Boris Köster 2001
Alle Rechte reserviert.
http://www.x-itec.de

*/

#ifndef cbkshmem
#define cbkshmem

#include <signal.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/stat.h>

#include "CbkBase.cpp"
#include "CbkError.cpp"

const char* CbkShmem_Copyright="X-ITEC Shared-Memory C++ Library. $Id: CbkShmem.cpp,v 1.1.1.1 2001/06/15 03:11:08 BKoester Exp $";

class CbkShmem : public CbkBase
{

private:
int   shmem_reqid;
char* shmem_req;


public:
int shmem_id;

void getmem(int numbytes);
int releasemem();

CbkShmem(int id,int memsize);
~CbkShmem();
};

void CbkShmem::getmem(int numbytes)
{
int flags;

if(DebugFlag()>0)
{
char hinweis[100];
sprintf(hinweis,"CbkShmem::getmem Numbytes=%i",numbytes);
dout(CbkBase::LM_CORE,hinweis);

}

flags=S_IRWXU|S_IRWXG|S_IRWXO|IPC_CREAT|IPC_EXCL;
if(shmem_id==0){flags=flags|IPC_PRIVATE;}

if( (shmem_reqid=shmget(shmem_id,numbytes,flags))==-1)
 {
 CbkError fehler;
 char fstring[100];
 sprintf(fstring,"SHMEM get problem. errno=%i",errno);
 fehler.ErrorSTL(CbkError::ERROR_sCORE,
                CbkError::ERROR_tSHMEM,
                CbkError::ERROR_lCRITICAL,
                fstring
                );
                fehler.DoThrow();
 }

(void *)shmem_req=shmat(shmem_reqid,0,0);

if(shmem_req==(void *)-1)
{
 CbkError fehler;
 char fstring[100];
 sprintf(fstring,"SHMEM attach problem. errno=%i",errno);
 fehler.ErrorSTL(CbkError::ERROR_sCORE,
                CbkError::ERROR_tSHMEM,
                CbkError::ERROR_lCRITICAL,
                fstring
                );
                fehler.DoThrow();
 }



}



CbkShmem::CbkShmem(int id, int memsize)
{
shmem_id=id;

}

int CbkShmem::releasemem()
{
return shmctl(shmem_reqid,IPC_RMID,NULL);
}

CbkShmem::~CbkShmem()
{
dout(CbkBase::LM_CORE,"Destruktor CbkShmem");
releasemem();
}


#endif