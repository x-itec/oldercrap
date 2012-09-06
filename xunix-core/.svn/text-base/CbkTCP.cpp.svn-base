/*

TCP/IP Basisklasse
------------------
(C) Boris Köster 2001. Alle Rechte reserviert. http://www.x-itec.de

$Id: CbkTCP.cpp,v 1.1.1.1 2001/06/15 03:11:08 BKoester Exp $

Achtung

readint / writeint sind UNTESTED
--------------------------------





Clientfunktionalität
Serverfunktionalität
Basisfunktionalität

Benötigt:
CbkFork

//C++ Gedanken
...using obsolete binding at
man hat eine For-Schleife mit (for int i=0,..) am laufen und nachdem
man sie verlassen hat, versucht man drauf zuzugreifen - geht natürlich net -)))


//Limitations
eine einzelne Zeile die mit writeline gesendet wird, darf derzeit
nicht größer als 8 kb sein (wäre auch verwunderlich, wenn sie größer wäre)


*/

#ifndef CbkTCP
#define CbkTCP

#include <sys/types.h>
#include <sys/param.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <libutil.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <ctype.h>

#include "CbkBase.cpp"


const char* CbkTCP_Copyright="X-ITEC high performance TCP/IP C++ Library. $Id: CbkTCP.cpp,v 1.1.1.1 2001/06/15 03:11:08 BKoester Exp $";



class CbkTCPBasic : public CbkBase
{
public:
//"Properties"
int tcpPort;//z.B. 80
int tcpIPv4;//wird nicht benutzt bisher
int tcpIPv6;//wird nicht benutzt bisher

char writeline_string[8*1024];//8kb Stringlänge


//TCP technisches
struct sockaddr_in adresse;
size_t adrlaenge;

//Systembezeichner für die Streams usw...
int fd_sock,fd_conn;

//Konstruktor
     CbkTCPBasic();

//An einen bestehenden fd_conn anschließen
void AttachFD(int fd);

//Serverfunktionen

void InitStreamSocket();
void BindSocket();
void ListenSocket();
int AcceptSocket();

//Client-Connect Routine
void ConnectSocket();


//IO Operationen

inline ssize_t write   (const char* text,size_t textlen);
inline ssize_t read    (char* text,size_t textlen);

inline ssize_t writeint(int zahl);
inline int     readint();

ssize_t readline(char* text,size_t maxlen);//liest eine Zeile ein bis maxchars oder Return
ssize_t writeline(const char* text);//schreibt den Inhalt einschl. \r\n, nur für Textzeilen
};


/*
An einen bestehenden FD connecten, um zu senden und zu empfangen
*/

ssize_t CbkTCPBasic::writeint(int zahl)
{
zahl= htonl(zahl);

return ::write(fd_conn,&zahl,sizeof(zahl));
}

int CbkTCPBasic::readint()
{
int x;
::read(fd_conn,&x,sizeof(&x));
return ntohl(x);

}


void CbkTCPBasic::AttachFD(int fd)
{
fd_conn=fd;
}

/*
Sendung einer Stringzeile, \r\n wird angefügt
*/

ssize_t CbkTCPBasic::writeline(const char* text)
{
dout(CbkBase::LM_CORE,"+CbkTCPBasic::writeline");
dout(CbkBase::LM_CORE,(const char*)text);

sprintf(writeline_string,"%s\r\n",text);
int laenge=strlen(writeline_string);//Abschluss durch \0 bei sprintf
dout(CbkBase::LM_CORE,"Weiterleitung an .write");
write(writeline_string,laenge);
dout(CbkBase::LM_CORE,"-CbkTCPBasic::writeline");
}

/*
Schreiben von x Bytes auf den Kanal
*/

ssize_t CbkTCPBasic::write(const char* text,size_t textlen)
{
return ::write(fd_conn,text,textlen);
//-1 = Fehler, sonst Anzahl der Bytes die geschrieben wurden
}


/*
Lesen von x Bytes
*/

ssize_t CbkTCPBasic::read(char* text,size_t textlen)
{
return ::read(fd_conn,text,textlen);
}

/*
Stringzeile lesen
*/

ssize_t CbkTCPBasic::readline(char* text,size_t maxlen)
{
int flag;
char zeichen[1];
char dzeichen[10];//nur für Debug

int i=0;

dout(CbkBase::LM_CORE,"+CbkTCPBasic::readline");

for (i=0;i<=maxlen;i++)
{
flag=::read(fd_conn,zeichen,1);//1 Zeichen

/*
wenn ein Javaprog einen String sendet, endet dieser mit
den beiden Hexacodes 0d:0a  (13/10)
*/


if (zeichen[0]==10)
{
dout(CbkBase::LM_CORE,"CbkTCPBasic::readline Break Return");
break;
}

if (flag==0)
{
dout(CbkBase::LM_CORE,"CbkTCPBasic::readline Break Datenstrom leer");
break;
}//EOF

if (flag<0)
{
dout(CbkBase::LM_CORE,"CbkTCPBasic::readline Break Error/Datenstrom wurde beendet");
break;
}//Fehler

text[i]=zeichen[0];//das letzte Zeichen wird auch auf 0 gesetzt soviel ich weiss
sprintf(dzeichen,":%02x:%c:",text[i],text[i]);
dout(CbkBase::LM_CORE,dzeichen);
//printf("%02x:",text[i]);
}
dout(CbkBase::LM_CORE,"-CbkTCPBasic::readline");
//printf ("%i\n",i);
if(i>2){i-1;}//Return-Zeichen abschneiden
text[i]=0;//Nullbyte setzen

}

//Konstruktor

CbkTCPBasic::CbkTCPBasic()
{
tcpPort=fd_sock=fd_conn=0;
adrlaenge=sizeof(sockaddr_in);//Default
}

void CbkTCPBasic::ConnectSocket()
{

if ( ::connect(fd_sock,(struct sockaddr *)&adresse,adrlaenge) ==-1 )
{puts("connect error");exit(1);}

}

//Wenn >=0 dann ist der Socket noch am leben, sonst abgekackt
//gibt einen fd_conn zurück
int CbkTCPBasic::AcceptSocket()
{
fd_conn=accept(fd_sock,(struct sockaddr *)&adresse,&adrlaenge);
/*
cout << "\nacceptsocket aufgerufen fuer fd_sock:";
cout << fd_sock;
cout << "result-fd: ";
cout << fd_conn;
cout << "\n";
cout << "errno";
cout << errno;
*/

return fd_conn;

}

void CbkTCPBasic::ListenSocket()
{
if (listen(fd_sock,5)){puts("listen error");exit(1);}
}


void CbkTCPBasic::BindSocket()
{
adresse.sin_family = AF_INET;
adresse.sin_port=htons(tcpPort);
//TODO: Wenn eine IP hinterlegt ist oder Domain, resolven, umwandeln, eintragen

//memset(&adresse.sin_addr,0,sizeof(adresse.sin_addr));

adresse.sin_addr.s_addr=htonl(INADDR_ANY); //testweise an alle IPs binden

if(bind(fd_sock,(struct sockaddr *) &adresse,sizeof(adresse))){puts("bind p");exit(1);}

}


void CbkTCPBasic::InitStreamSocket()
{
int i=1;//non-zero für enable

if( (fd_sock=socket(PF_INET,SOCK_STREAM,0)) <0 ){puts("socket-error");exit(1);}
setsockopt(fd_sock,SOL_SOCKET,SO_REUSEADDR,&i,sizeof(i));
}

// ----------------------------------------------------


class CbkTCPServer : public CbkTCPBasic
{
public:
int DoAccept();
};

int CbkTCPServer::DoAccept()
{
int fd;
dout(CbkBase::LM_CORE,"+CbkTCPServer::DoAccept()");
dout(CbkBase::LM_CORE,"initialisiere FORK");
CbkFork forkme(CbkFork::FT_FORK);
dout(CbkBase::LM_CORE,"InitStream,BindSocket,ListenSocket");
InitStreamSocket();BindSocket();ListenSocket();
dout(CbkBase::LM_CORE,"Gehe nun in AcceptSocket-Schleife");
while(1==1)
{
dout(CbkBase::LM_CORE,"CbkTCPServer::AcceptSocket start");
fd=AcceptSocket();//Blockierung bis eine Verbindung kommt
dout(CbkBase::LM_CORE,"CbkTCPServer::AcceptSocket accepted");

/*
cout << "accept socket auf ";
cout << fd;
*/

dout(CbkBase::LM_CORE,"CbkTCPServer::AcceptSocket fork");
forkme.fork();      //Subprozess erzeugen
dout(CbkBase::LM_CORE,"CbkTCPServer::AcceptSocket forked");

//Wenn wir der Sohn sind, Accept "beenden" damit der Client bedient werden kann

if (forkme.forkstatus==CbkFork::FS_SON)
{
dout(CbkBase::LM_CORE,"CbkTCPServer::AcceptSocket FS_SON FORK, break");
break;
}
if (forkme.forkstatus==CbkFork::FS_ERROR){break;};//TODO
if (forkme.forkstatus==CbkFork::FS_DAD){};//unspecified bisher
}
return fd;
}

// -------------------------------------------------------------------


class CbkTCPClient : public CbkTCPBasic
{
};

#endif