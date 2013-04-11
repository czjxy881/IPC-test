#include "stdafx.h"
#include "share.h"
#pragma data_seg("have_jxy")
char m[2000]="";
#pragma data_seg()
#pragma comment(linker,"/SECTION:have_jxy,RWS")

share::share(void)
{
	 now=0;
}


share::~share(void)
{
}

CString last="";
int share::send(CString content)
{
	strncpy_s(m,(LPCTSTR)content,sizeof(m));
	return 1;
}
CString share::read()
{
	CString s(m);
	if(last==s)return "";
	last=s;
	return s;
}

int share::have()
{
	return last!=CString(m);
}
