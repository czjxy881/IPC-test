#include "stdafx.h"
#include "niming.h"
#include <iostream>
using namespace std;
niming::niming(void)
{
}


niming::~niming(void)
{
}

int niming::build()
{
	SECURITY_ATTRIBUTES sa;
	sa.bInheritHandle=TRUE;
	sa.lpSecurityDescriptor=NULL;
	sa.nLength=sizeof(SECURITY_ATTRIBUTES);
	if(!CreatePipe(&hRead,&hWrite,&sa,0))
	{
		MessageBox(0,"´´½¨Ê§°Ü","error",0);
		return 0;
	}
	STARTUPINFO sui;
	ZeroMemory(&sui,sizeof(STARTUPINFO));
	sui.cb=sizeof(STARTUPINFO);
	sui.dwFlags=STARTF_USESTDHANDLES;
	sui.hStdInput=hRead;
	sui.hStdOutput=hWrite;
	sui.hStdError=GetStdHandle(STD_ERROR_HANDLE);
	PROCESS_INFORMATION ProcessInfo;
	if(CreateProcess("jxyprocess.exe",NULL,NULL,NULL,TRUE,0,NULL,NULL,&sui,&ProcessInfo))
		return 1;
	else return 0;
}

int niming::send(CString con)
{
	DWORD d;
	if(WriteFile(hWrite,con,con.GetLength()+1,&d,NULL))return 1;
	return 0;
}
CString niming::recv()
{
	DWORD dwRead;
	char ss[1024];
	if(ReadFile(hRead , ss ,1024,&dwRead,NULL))return ss;
	return "";
}
void niming::connect()
{
	hRead=GetStdHandle(STD_INPUT_HANDLE);
	hWrite=GetStdHandle(STD_OUTPUT_HANDLE);
	return;
}
int niming::have()
{
	bool s=cin.eof();
	DWORD d;
	int pid;
	char ss[1024];
	if(!s)
	{
		ReadFile(hRead , ss ,1024,&d,NULL);
		sscanf(ss,"pid-%d",&pid);
		if(pid==getpid())s=1;
		WriteFile(hWrite,ss,1024,&d,NULL);
	}
	return !s;
}