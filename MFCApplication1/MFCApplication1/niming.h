#pragma once
class niming
{
private:
	HANDLE hRead,hWrite;
public:
	niming(void);
	~niming(void);
	int build();
	int send(CString content);
	CString recv();
	void connect();
	int have();
};

