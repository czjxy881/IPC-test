#pragma once
class guandao
{
private:
	HANDLE hpipe;
	bool flag;
public:
	 guandao(void);
	 ~guandao(void);
	 int create(CString sever=".",CString name="MyPipe");
	 CString read();
	 int write(CString content);
	 int connect(CString sever=".",CString name="MyPipe");
	 int free();
	 int have();
};

