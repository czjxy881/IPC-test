#pragma once
class mailslot
{
private:
	HANDLE hmail;
public:
	mailslot(void);
	~mailslot(void);
	int send(CString content);
	CString read();
	int connect(CString server,CString name);
	int create(CString name);
	int free();
	int have();

};

