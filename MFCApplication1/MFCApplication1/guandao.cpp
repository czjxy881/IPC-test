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
		MessageBox(NULL,"创建命名管道"+name+"失败","error",MB_ICONERROR);
		hpipe=NULL;
		return 0;
	}
	//创建匿名人工重置对象
	HANDLE hevent;
	hevent=CreateEvent(NULL,true,false,NULL);
	if(!hevent)
	{
		MessageBox(NULL,"创建事件对象失败","error",MB_ICONERROR);
		CloseHandle(hpipe);
		hpipe=NULL;
		return 0;
	}
	OVERLAPPED ovlap;
	ZeroMemory(&ovlap,sizeof(OVERLAPPED));
	ovlap.hEvent=hevent;
	MessageBox(NULL,"等待客户端","ok",MB_ICONINFORMATION);
	if(!ConnectNamedPipe(hpipe,&ovlap))
	{
		if(ERROR_IO_PENDING!=GetLastError())
		{
			MessageBox(NULL,"等待客户端失败","error",MB_ICONERROR);
			CloseHandle(hpipe);
			CloseHandle(hevent);
			hpipe=NULL;
			return 0;
		}
	}
	if(WAIT_FAILED==WaitForSingleObject(hevent,INFINITE))
	{
			MessageBox(NULL,"等待对象失败","error",MB_ICONERROR);
			CloseHandle(hpipe);
			CloseHandle(hevent);
			hpipe=NULL;
			return 0;
	}
	CloseHandle(hevent);
	MessageBox(NULL,"创建完成","ok",MB_ICONINFORMATION);
	flag=1;
	return 1;
}
CString guandao::read()
{
	char s[200];
	DWORD d;
	if(!ReadFile(hpipe,s,200,&d,NULL))
	{
		MessageBox(NULL,"读取数据失败","error",MB_ICONERROR);
		return "";
	}
	return s;
}
int guandao::write(CString content)
{
	DWORD d;
	if(!WriteFile(hpipe,content,content.GetLength()+1,&d,NULL))
	{
		MessageBox(NULL,"写入数据失败","error",MB_ICONERROR);
		return 0;
	}
	return 1;
}
int guandao::connect(CString sever,CString name )
{
	if(flag)
	{
		MessageBox(NULL,"已创建管道","error",MB_ICONERROR);
		return 0;
	}
	CString nn="\\\\"+sever+"\\pipe\\"+name;
	if(!WaitNamedPipe(nn,500))
	{
		MessageBox(NULL,"无可用管道","error",MB_ICONERROR);
		return 0;
	}
	hpipe=CreateFile(nn,GENERIC_ALL,0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
	if(hpipe==INVALID_HANDLE_VALUE)
	{
		MessageBox(NULL,"链接命名管道"+name+"失败","error",MB_ICONERROR);
		hpipe=NULL;
		return 0;
	}
	//MessageBox(NULL,"链接完成","ok",MB_ICONINFORMATION);
	return 1;
}