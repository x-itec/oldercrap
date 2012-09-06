/*

CbkBase

Basisklasse für alle anderen Klassen

$Id: CbkBase.cpp,v 1.1.1.1 2001/06/15 03:11:08 BKoester Exp $


(C) Boris Köster 2001
Alle Rechte reserviert.

*/

#ifndef cbkbase
#define cbkbase

#include <stdio.h>


class CbkBase
{

private:
static int debugflag;


public:

enum EN_DEBUGTYPE {LM_NONE,LM_CORE,LM_CLASS,LM_APP};
EN_DEBUGTYPE      logmode;//was soll dargestellt werden? SetLogMode() benutzen

//Debugging-Ausgaberoutinen!

inline void dout(const char* text);//logge diesen Text, egal welcher Debugmode
inline void dout(int zahl);
inline void dout(EN_DEBUGTYPE mymode,const char* text);//spezifisches Logging

inline static int  DebugFlag();
inline static void DebugFlag(int flag);
inline void SetLogMode(EN_DEBUGTYPE modus);//Debug-Modus setzen

};


int CbkBase::debugflag;

void CbkBase::SetLogMode(EN_DEBUGTYPE modus){logmode=modus;}

void CbkBase::dout(EN_DEBUGTYPE mymode,const char* text){if (mymode==logmode){dout(text);}}

void CbkBase::dout(const char* text)
{
 if(DebugFlag()>0)
 {
 cout << "\n DEBUG: ";
 cout << text;
 cout <<"\n";

 fflush(stdout);
 }
}
void CbkBase::dout(int zahl)   {cout << zahl;}

int  CbkBase::DebugFlag()
{
return debugflag;
}
void CbkBase::DebugFlag(int flag)
{
debugflag=flag;
}

#endif
