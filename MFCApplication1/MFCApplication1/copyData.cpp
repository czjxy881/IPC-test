#include "stdafx.h"
#include "copyData.h"

CString name,content;
COPYDATASTRUCT cd; 
copyData::copyData(void)
{
		cd.dwData=0;
}
copyData::~copyData(void)
{
}
int flag=0;
BOOL CALLBACK find(HWND hwnd, LPARAM lParam)
{
	char s[200];
	GetWindowText(hwnd,s,200);
	if(s==name)
	{
		SendMessage(hwnd, WM_COPYDATA, 0, (LPARAM)(&cd));
		flag=1;
	}
	return 1;
}
int copyData::send(CString na,CString co)
{
	name=na;content=co;
	cd.cbData=content.GetLength()+1;
	cd.lpData=(void*)content.GetBuffer(cd.cbData);
	flag=0;
	EnumWindows(find,NULL);
	return flag;
}
