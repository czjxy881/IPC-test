#pragma once
class copyData
{

public:
	copyData(void);
	~copyData(void);
	int findone(CString name,CString content);
	int send(CString name,CString content);
//	CString receive();
};
#define WM_COMM WM_USER+10

