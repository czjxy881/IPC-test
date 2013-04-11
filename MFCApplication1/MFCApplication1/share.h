#pragma once
class share
{
private:
	int now;
public:
	share(void);
	~share(void);
	int send(CString);
	CString read();
	int have();
};

