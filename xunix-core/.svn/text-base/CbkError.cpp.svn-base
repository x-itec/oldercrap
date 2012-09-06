/*
#include <stdio.h>
#include <iostream.h>
#include <fstream.h>
#include <iomanip>
#include <strstream>
#include <string>
*/

/*
#include "ext/md5/md5.cc"
*/

//-------------------------------------------------------
// Das hier gehoert alles zu CbkError
// die Klasse wird geworfen bei Exceptions in meinen Klassen

/*

Anleitung
---------
verwendet: CbkBase.cpp

Mit dieser Klasse erzeugt man Error-Exceptions immer vom gleichen Typ.


Praxisbeispiel 1:
-----------------
CbkError fehler;
fehler.ErrorSTL(CbkError::ERROR_sCORE,
                CbkError::ERROR_tMISSINGCONSTRUCTORPARAM,
                CbkError::ERROR_lWARNING,
                "Fork ohne Konstruktor aufgerufen, Konstruktor auf FORK gesetzt"
                );
                fehler.DoThrow();//Rückmeldung an Hauptanwendung, Kontrolle erwünscht

Errorsektionen: ERROR_sCORE ERROR_sCLASS ERROR_sAPP

Errorypen:

ERROR_tPARAMETER,       //Parameter nicht zu gebrauchen in einer Funktion,
ERROR_tMISSINGCONSTRUCTORPARAM,//eine Klasse braucht einen Parameter im Konstruktor!
ERROR_tMEMORY,          //nicht genug Speicher
ERROR_tFILEOUTPUT,        //Datei kann nicht geschrieben werden
ERROR_tFILEINPUT,        //Datei kann nicht gelesen/gefunden werden
ERROR_tSEMINIT,          //Semaphore kann nicht initialisiert werden

ERROR_tERRORLEVEL,       //Errorlevel kann nicht geändert werden weil schon Critical

Errorlevel:

ERROR_lCRITICAL, //Prog-Abbruch wenn keine Loesung
ERROR_lWARNING,  //ein wichtiger Hinweis, Modul entscheidete selbst eine Lösung
ERROR_lNOTICE   //Eine Sache die man wissen sollte


*/


#ifndef cbkerror
#define cbkerror

#include "CbkBase.cpp"


const char* CbkError_Copyright="X-ITEC C++ Error-Handling. $Id: CbkError.cpp,v 1.1.1.1 2001/06/15 03:11:08 BKoester Exp $";



class CbkError  : public CbkBase
{

public:

char* errorString;
char* errorKennung;


enum EbkError
{
//Fehlerkategorie/Fehlerbereich intern

ERROR_UNDEF,//nicht spezifiziert

//dieses Element hier ist keinem Thema zugewiesen
//von daher sollte es nicht benutzt werden im Moment
ERROR_CRITICAL,//kritische Fehler, allgemeingueltig

//errorsection

ERROR_sCORE,//Fehler gemeldet durch Core-Code
ERROR_sCLASS, // Class-Code, der den Core-Code benutzt
ERROR_sAPP,  // Anwendung, die den Class-Code benutzt

//errortype Fehlerart
ERROR_tPARAMETER,       //Parameter nicht zu gebrauchen in einer Funktion,
ERROR_tMISSINGCONSTRUCTORPARAM,//eine Klasse braucht einen Parameter im Konstruktor!
ERROR_tMEMORY,          //nicht genug Speicher
ERROR_tFILEOUTPUT,        //Datei kann nicht geschrieben werden
ERROR_tFILEINPUT,        //Datei kann nicht gelesen/gefunden werden
ERROR_tSEMINIT,          //Semaphore kann nicht initialisiert werden
ERROR_tSEMOP,            //Semaphore Modusänderung schiefgelaufen
ERROR_tSHMEM,            //Fehler bei der Benutzung von Shared Memory

ERROR_tERRORLEVEL,       //errorlevel Variable kann nicht überschrieben werden

//errorlevel Variable

ERROR_lCRITICAL, //Prog-Abbruch wenn keine Loesung
ERROR_lWARNING,  //ein wichtiger Hinweis, Modul entscheidete selbst eine Lösung
ERROR_lNOTICE   //Eine Sache die man wissen sollte
/*
Wenn ein Fehler positiv behandelt wurde, muss der ErrorLevel wieder auf 0
gesetzt werden, ausser er war CRITICAL, dann bleibt der Errorlevel.

*/
};//enum

private:

//UbkFehlerDetails info;
static EbkError errorlevel;//enums mit ERROR_l
EbkError errortype;//enums mit ERROR_t
EbkError errorsection;//enums mit ERROR_s

static void ErrorLevel(EbkError error);//setzt nur ErrorLevel ohne Check
//aus Geschwindigkeitsgruenden sinnvoll

//diese Routinen werden nur von der Public Routine Error(Esect sector) aufgerufen
inline static EbkError ErrorLevel();
inline  EbkError ErrorType();
inline  EbkError ErrorSection();

//Log ausgeben
void Log();


public:

//Konstruktor

CbkError();

enum Esect{SECT_LEVEL, SECT_TYPE, SECT_SECTION, SECT_RESET};

void Error(EbkError error,Esect sector);

//ruft 3x Error auf fuer jede einzelne Kategorie
void ErrorSTL(EbkError es, EbkError et, EbkError el);//3 Zustaende auf einmal
void ErrorSTL(EbkError es, EbkError et, EbkError el,char* text);//Klartextfehlermeldg.

//kennung=Klassenname-Fehlerkürzel, sprachunabhängig, wird intern in md5 umgerechnet
//und soll später als Fehlerinformation in einer Doku verwendet werden können
void ErrorSTL(EbkError es, EbkError et, EbkError el,char* text,char* kennung);



inline EbkError Error(Esect sector);

//Exception auslösen
void DoThrow();

};
//Static Definition / Methoden

CbkError::EbkError CbkError::errorlevel;

CbkError::EbkError CbkError::ErrorLevel()
{
return errorlevel;
}

CbkError::EbkError CbkError::ErrorType()
{
return errortype;
}
CbkError::EbkError CbkError::ErrorSection()
{
return errorsection;
}

void CbkError::ErrorLevel(EbkError error)
{
errorlevel=error;
}

//Konstruktor
CbkError::CbkError()
{
Error(ERROR_UNDEF,SECT_RESET);//Alle Variablen zurücksetzen

}

void CbkError::Error(EbkError error,Esect sector)
{
bool flag=false;//true verbietet das Setzen des Errorlevels


//Sektor der jeweiligen Sektion pruefen
if(sector==SECT_LEVEL)
{
if(error==ERROR_lCRITICAL)flag=true;
}
if(sector==SECT_TYPE)
{
}
if(sector==SECT_SECTION)
{
//hier gibt es noch nichts zu tun
}
if(sector==SECT_RESET)
{
// zurücksetzen, nur errorlevel wird nicht zurückgesetzt
}

if(!flag)
{
  //TODO!
  if(sector==SECT_LEVEL){errorlevel=error;}
  if(sector==SECT_TYPE){errortype=error;}
  if(sector==SECT_SECTION){errorsection=error;}
  if(sector==SECT_RESET)
  {
     // errorlevel=ERROR_UNDEF;
     errortype=ERROR_UNDEF;
     errorsection=ERROR_UNDEF;
     errorString=NULL;//Klartext-Fehlermeldungszeiger auf NULL
     errorKennung=NULL;
  }


}
else
{
//Hinweis, dass Errorlevel nicht gesetzt werden kann
//weil der Errorlevel Critical ist (ist nur informativ)
errortype=ERROR_tERRORLEVEL;
}//else

}//fu

CbkError::EbkError CbkError::Error(Esect sector)
{
if(sector==SECT_LEVEL)return ErrorLevel();
if(sector==SECT_TYPE)return ErrorType();
if(sector==SECT_SECTION)return ErrorSection();
}

void CbkError::ErrorSTL(EbkError es, EbkError et, EbkError el)
{
Error(es,SECT_SECTION);
Error(et,SECT_TYPE);
Error(el,SECT_LEVEL);
}

//Gibt Informationen auf Screen+Logfile aus
//Logfile ist TODO
void CbkError::Log()
{
char logsub[255];//müsste reichen

string logbuch;
sprintf(logsub, "\nEXCEPTION Errorlevel: %d-%d-%d \n%s\n", errorsection, errortype, errorlevel,errorString);

cout << logsub;
dout(logsub);//auf jeden Fall wenn Debugmode an ist, mitloggen

//todo: Systemlogging
//todo: md5 Kennung ausgeben


}

void CbkError::ErrorSTL(EbkError es, EbkError et, EbkError el,char* text)
{
errorString=text;//Adresse zuweisen
ErrorSTL(es,et,el);//Fehlerwerte setzen
}

void CbkError::ErrorSTL(EbkError es, EbkError et, EbkError el,char* text,char* kennung)
{
ErrorSTL(es,et,el);//Fehlerwerte setzen
errorString=text;
errorKennung=kennung;

}

void CbkError::DoThrow()
{
//TODO: Fehler loggen
Log();
//wir sind so frei und geben bis dahin einen  Fehlertext aus

throw this;
}

#endif