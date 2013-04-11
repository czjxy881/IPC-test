#include "stdafx.h"
#include "mailslot.h"


mailslot::mailslot(void)
{
	hmail=NULL;
}


mailslot::~mailslot(void)
{
	if(hmail)
		CloseHandle(hmail);
}
int mailslot::free()
{
	if(hmail)
	{
		CloseHandle(hmail);
		return 1;
	}
	return 0;
}

int mailslot::have()
{
	if(!hmail)return 0;
	DWORD cbMessage, cMessage;
    GetMailslotInfo(hmail,(LPDWORD) NULL, &cbMessage,&cMessage,0); 
	 if(cbMessage == MAILSLOT_NO_MESSAGE)
		 return 0;
	return 1;
}

int mailslot::create(CString name)
{
	MessageBox(0,"�ȴ����Ͷ�","ok",MB_ICONINFORMATION);
	//�����ʲ�
	hmail=CreateMailslot("\\\\.\\mailslot\\"+name,0,500,NULL);
	if(hmail==INVALID_HANDLE_VALUE||hmail==0)
	{
		MessageBox(0,"����ʧ��","����",MB_ICONERROR);
		hmail=0;
		return 0;
	}
	return 1;
}
CString mailslot::read()
{
	char content[200];
	DWORD dread;
	if(!ReadFile(hmail,content,200,&dread,NULL))
	{
		MessageBox(0,"��ȡʧ��","����",MB_ICONERROR);
		return "";
	}
	return content;
}
int mailslot::connect(CString server,CString name)
{
	hmail=CreateFile("\\\\"+server+"\\mailslot\\"+name,GENERIC_WRITE,FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
	if(hmail==INVALID_HANDLE_VALUE||hmail==0)
	{
		MessageBox(0,"��ʧ�ܣ�,��ȷ��Ŀ���ַ��׼������","����",MB_ICONERROR);
		hmail=0;
		return 0;
	}
	return 1;
}
int mailslot::send(CString content)
{
	DWORD dwrite;
	if(!WriteFile(hmail,content,content.GetLength()+1,&dwrite,NULL))
	{
		MessageBox(0,"д��ʧ��","����",MB_ICONERROR);
		return 0;
	}
	return 1;
}
