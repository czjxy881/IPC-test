#include "stdafx.h"
#include "guandao.h"

guandao::guandao(void)
{
	hpipe=NULL;
	flag=0;
}


guandao::~guandao(void)
{
	if(hpipe)
		CloseHandle(hpipe);
}

int guandao::free()
{
	CloseHandle(hpipe);
	hpipe=NULL;
	return 1;
}

int guandao::have()
{
	if(!hpipe)return 0;
	char 	 szOutput[1024+10];
	DWORD 	 cntReadedChar=0;
	long a=PeekNamedPipe(hpipe, szOutput, 1, &cntReadedChar, NULL, 0);
	if(szOutput[0] ==-52)
		 return 0;
	return 1;
}


int guandao::create(CString sever,CString name )
{
	hpipe=CreateNamedPipe("\\\\"+sever+"\\pipe\\"+name,PIPE_ACCESS_DUPLEX|FILE_FLAG_OVERLAPPED,0,1,1024,1024,500,NULL);
	if(hpipe==INVALID_HANDLE_VALUE)
	{
		MessageBox(NULL,"���������ܵ�"+name+"ʧ��","error",MB_ICONERROR);
		hpipe=NULL;
		return 0;
	}
	//���������˹����ö���
	HANDLE hevent;
	hevent=CreateEvent(NULL,true,false,NULL);
	if(!hevent)
	{
		MessageBox(NULL,"�����¼�����ʧ��","error",MB_ICONERROR);
		CloseHandle(hpipe);
		hpipe=NULL;
		return 0;
	}
	OVERLAPPED ovlap;
	ZeroMemory(&ovlap,sizeof(OVERLAPPED));
	ovlap.hEvent=hevent;
	MessageBox(NULL,"�ȴ��ͻ���","ok",MB_ICONINFORMATION);
	if(!ConnectNamedPipe(hpipe,&ovlap))
	{
		if(ERROR_IO_PENDING!=GetLastError())
		{
			MessageBox(NULL,"�ȴ��ͻ���ʧ��","error",MB_ICONERROR);
			CloseHandle(hpipe);
			CloseHandle(hevent);
			hpipe=NULL;
			return 0;
		}
	}
	if(WAIT_FAILED==WaitForSingleObject(hevent,INFINITE))
	{
			MessageBox(NULL,"�ȴ�����ʧ��","error",MB_ICONERROR);
			CloseHandle(hpipe);
			CloseHandle(hevent);
			hpipe=NULL;
			return 0;
	}
	CloseHandle(hevent);
	MessageBox(NULL,"�������","ok",MB_ICONINFORMATION);
	flag=1;
	return 1;
}
CString guandao::read()
{
	char s[200];
	DWORD d;
	if(!ReadFile(hpipe,s,200,&d,NULL))
	{
		MessageBox(NULL,"��ȡ����ʧ��","error",MB_ICONERROR);
		return "";
	}
	return s;
}
int guandao::write(CString content)
{
	DWORD d;
	if(!WriteFile(hpipe,content,content.GetLength()+1,&d,NULL))
	{
		MessageBox(NULL,"д������ʧ��","error",MB_ICONERROR);
		return 0;
	}
	return 1;
}
int guandao::connect(CString sever,CString name )
{
	if(flag)
	{
		MessageBox(NULL,"�Ѵ����ܵ�","error",MB_ICONERROR);
		return 0;
	}
	CString nn="\\\\"+sever+"\\pipe\\"+name;
	if(!WaitNamedPipe(nn,500))
	{
		MessageBox(NULL,"�޿��ùܵ�","error",MB_ICONERROR);
		return 0;
	}
	hpipe=CreateFile(nn,GENERIC_ALL,0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
	if(hpipe==INVALID_HANDLE_VALUE)
	{
		MessageBox(NULL,"���������ܵ�"+name+"ʧ��","error",MB_ICONERROR);
		hpipe=NULL;
		return 0;
	}
	//MessageBox(NULL,"�������","ok",MB_ICONINFORMATION);
	return 1;
}