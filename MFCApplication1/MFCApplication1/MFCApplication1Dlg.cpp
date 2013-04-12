
// MFCApplication1Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "MFCApplication1Dlg.h"
#include "afxdialogex.h"


#include <iostream>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
using namespace std;

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���
bool frun; 
BOOL fchild;
class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CMFCApplication1Dlg �Ի���



CMFCApplication1Dlg::CMFCApplication1Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMFCApplication1Dlg::IDD, pParent)
{
	guan=guandao();
	mail=mailslot();
	cc=copyData();
	ni=niming();
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT2, Content_Text);
	DDX_Control(pDX, IDC_EDIT3, cip);
	DDX_Control(pDX, IDC_EDIT1, cname);
	DDX_Control(pDX, IDC_CHECK1, runc);
	DDX_Control(pDX, IDC_LIST1, chistroy);
	DDX_Control(pDX, IDC_RADIO4, radio_niming);
}

void recmessage();
BEGIN_MESSAGE_MAP(CMFCApplication1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_Send, &CMFCApplication1Dlg::OnBnClickedSend)
	ON_BN_CLICKED(IDC_Recive, &CMFCApplication1Dlg::OnBnClickedRecive)
	ON_BN_CLICKED(IDC_RADIO1, &CMFCApplication1Dlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CMFCApplication1Dlg::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_build, &CMFCApplication1Dlg::OnBnClickedbuild)
	ON_BN_CLICKED(IDC_connect, &CMFCApplication1Dlg::OnBnClickedconnect)
	ON_BN_CLICKED(IDC_del, &CMFCApplication1Dlg::OnBnClickeddel)
	ON_BN_CLICKED(IDC_CHECK1, &CMFCApplication1Dlg::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_RADIO3, &CMFCApplication1Dlg::OnBnClickedRadio3)
	//ON_MESSAGE_VOID(WM_COPYDATA,recmessage)
	ON_WM_COPYDATA()
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCApplication1Dlg::OnBnClickedButton1)
	ON_LBN_DBLCLK(IDC_LIST1, &CMFCApplication1Dlg::dclick)
	ON_BN_CLICKED(IDC_RADIO4, &CMFCApplication1Dlg::OnBnClickedRadio4)
	ON_BN_CLICKED(IDC_RADIO5, &CMFCApplication1Dlg::OnBnClickedRadio5)
END_MESSAGE_MAP()


// CMFCApplication1Dlg ��Ϣ�������

BOOL CMFCApplication1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}
	HANDLE m=GetStdHandle(STD_INPUT_HANDLE);//�ж��ǲ������ɵ��ӽ���
	fchild=(m!=0);
	if(fchild)//����Ǿ��Զ�ѡ��4ģʽ
	{
		radio_niming.SetCheck(4);
		OnBnClickedRadio4();
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CMFCApplication1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMFCApplication1Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CMFCApplication1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

int now=0;
void CMFCApplication1Dlg::OnBnClickedSend()
{
	CString content,name;
	Content_Text.GetWindowTextA(content);
	int t=0;
	int s=_getpid();
	char pid[100];
	_itoa_s(s,pid,10);
	SYSTEMTIME tt;
	GetLocalTime(&tt);
	wsprintf(pid+strlen(pid)," %02d:%02d",tt.wHour,tt.wMinute);
	content="pid-"+CString(pid)+" :"+content;
	switch (now)
	{
		case 1:
			t=mail.send(content);
			break;
		case 2:
			t=guan.write(content);
			break;
		case 3:
			cip.GetWindowTextA(name);
			t=cc.send(name,content);
			break;
		case 4:
			t=ni.send(content);
			break;
		case 5:
			t=sh.send(content);
			break;
		default:
			MessageBox("��ѡ�����ͣ�","����",MB_ICONERROR);
			return;
	}
	if(!t)return;
	chistroy.InsertString(-1,"send "+content);
	Content_Text.SetWindowTextA("");
}
//�س�������
void CMFCApplication1Dlg::OnOK()
{
	OnBnClickedSend();
}

void CMFCApplication1Dlg::OnBnClickedRecive()
{
	CString content;
	switch (now)
	{
		case 1:
			content=mail.read();break;
		case 2:
			content=guan.read();break;
		case 4:
			content=ni.recv();break;
		case 5:
			content=sh.read();break;
		default:
			MessageBox("��ѡ�����ͣ�","����",MB_ICONERROR);
			return;
	}
	if(content!="")chistroy.InsertString(-1,"Recv "+content);

}


//������ʱ������Ϣ�����ⴰ����Ϊͬ�������ܲ�����Ϣ
DWORD WINAPI read(LPVOID lpParameter)
{
	CMFCApplication1Dlg *p=(CMFCApplication1Dlg*)lpParameter;
	while(frun)
	{
		int hh=0;
		while(!hh)
		{
			if(!frun)return 0;
			Sleep(1000);
			if(now<3&&!(p->GetDlgItem(IDC_del)->IsWindowEnabled()))continue;
			switch (now)
			{
			case 1:  hh=p->mail.have();break;
			case 2: hh=p->guan.have();break;
			case 4: hh=p->ni.have();break;
			case 5: hh=p->sh.have();break;
			default:
			break;
			}
		}
	p->OnBnClickedRecive();
	}
	return 0;
}
//�Զ�������Ϣ
void CMFCApplication1Dlg::OnBnClickedCheck1()
{
	frun=!frun;
	if(frun)CreateThread(NULL,0,read,this,0,NULL);
}

//���������
void CMFCApplication1Dlg::OnBnClickedbuild()
{
	CString serve,name;
	cip.GetWindowTextA(serve);
	cname.GetWindowTextA(name);
	int t=0;
	switch (now)
	{
	case 1:
		t=mail.create(name);
		break;
	case 2:
		t=guan.create(serve,name);break;
	case 3:
		this->SetWindowTextA(name);break;
	case 4:
		t=ni.build();
		break;
	default:
		break;
	}
	if(t)
	{
		GetDlgItem(IDC_build)->EnableWindow(FALSE);
		GetDlgItem(IDC_connect)->EnableWindow(FALSE);
		GetDlgItem(IDC_del)->EnableWindow(TRUE);
		if(now==1)GetDlgItem(IDC_Send)->EnableWindow(FALSE);
	}
}
//�������Ͷ�
void CMFCApplication1Dlg::OnBnClickedconnect()
{
	CString serve,name;
	cip.GetWindowTextA(serve);
	cname.GetWindowTextA(name);
	int t=0;
	switch (now)
	{
	case 1:
		t=mail.connect(serve,name);break;
	case 2:
		t=guan.connect(serve,name);break;
	default:
		ni.connect();
		t=1;
		break;
	}
	if(t)
	{
		GetDlgItem(IDC_connect)->EnableWindow(FALSE);
		GetDlgItem(IDC_build)->EnableWindow(FALSE);
		GetDlgItem(IDC_del)->EnableWindow(TRUE);
		if(now==1)GetDlgItem(IDC_Recive)->EnableWindow(FALSE);
	}
}
//�Ͽ�����
void CMFCApplication1Dlg::OnBnClickeddel()
{
	int t;
	switch (now)
	{
	case 1:
		t=mail.free();break;
	case 2:
		t=guan.free();break;
	default:
		break;
	}
	if(t)
	{
		GetDlgItem(IDC_build)->EnableWindow(TRUE);
		GetDlgItem(IDC_connect)->EnableWindow(TRUE);
		GetDlgItem(IDC_del)->EnableWindow(FALSE);
		GetDlgItem(IDC_Recive)->EnableWindow(TRUE);
		GetDlgItem(IDC_Send)->EnableWindow(TRUE);
	}
}


//������Ϣ����
BOOL CMFCApplication1Dlg::OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct)
{
	if (now==3&&pCopyDataStruct != NULL)
	{
		LPCTSTR pszText = (LPCTSTR)(pCopyDataStruct->lpData);
		DWORD dwLength = (DWORD)(pCopyDataStruct->cbData);
		TCHAR szRecvText[1024] = {0};
		memcpy(szRecvText, pszText, dwLength);
		chistroy.InsertString(-1,"Recv "+CString(szRecvText));
	}
	return CDialog::OnCopyData(pWnd, pCopyDataStruct);
}

//��ʷ��¼���
void CMFCApplication1Dlg::OnBnClickedButton1()
{
	chistroy.ResetContent();
}

//˫�������Ϣ
void CMFCApplication1Dlg::dclick()
{
	CString c,s;
	int nItem = chistroy.GetCurSel();;
	chistroy.GetText(nItem,s);
    Content_Text.GetWindowTextA(c);
	s=s.Right(s.GetLength()-1-s.ReverseFind(':'));
    Content_Text.SetWindowTextA(c+s);
   
}



//ѡ���ʲ�
void CMFCApplication1Dlg::OnBnClickedRadio1()
{
	now=1;
	GetDlgItem(IDC_STATIC)->SetWindowTextA("����Ŀ����:(*Ϊȫ��,.Ϊ����)");
	GetDlgItem(IDC_STATICp)->SetWindowTextA("�ʲ���:");
	cip.ShowWindow(SW_SHOW);
	cip.SetWindowTextA("*");
	cname.ShowWindow(SW_SHOW);
	cname.SetWindowTextA("MyMail");
	GetDlgItem(IDC_build)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_build)->SetWindowTextA("�������ն�");
	GetDlgItem(IDC_connect)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_connect)->SetWindowTextA("�������Ͷ�");
	GetDlgItem(IDC_del)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_del)->SetWindowTextA("�Ͽ�����");
	GetDlgItem(IDC_Recive)->ShowWindow(SW_SHOW);
	runc.ShowWindow(SW_SHOW);
	frun=0;
	runc.SetCheck(false);
}
//ѡ��ܵ�
void CMFCApplication1Dlg::OnBnClickedRadio2()
{
	now=2;
	GetDlgItem(IDC_STATIC)->SetWindowTextA("Ŀ����:(.Ϊ����)");
	GetDlgItem(IDC_STATICp)->SetWindowTextA("�ܵ���:");
	cip.ShowWindow(SW_SHOW);
	cip.SetWindowTextA(".");
	cname.ShowWindow(SW_SHOW);
	cname.SetWindowTextA("MyPipe");
	GetDlgItem(IDC_build)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_build)->SetWindowTextA("�����ܵ�");
	GetDlgItem(IDC_connect)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_connect)->SetWindowTextA("���ӹܵ�");
	GetDlgItem(IDC_del)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_del)->SetWindowTextA("�Ͽ�����");
	GetDlgItem(IDC_Recive)->ShowWindow(SW_SHOW);
	runc.ShowWindow(SW_SHOW);
	frun=0;
	runc.SetCheck(false);
}
//ѡ����Ϣ����
void CMFCApplication1Dlg::OnBnClickedRadio3()
{
	now=3;
	GetDlgItem(IDC_STATIC)->SetWindowTextA("Ŀ�������:");
	GetDlgItem(IDC_STATICp)->SetWindowTextA("�����ڱ���:");
	cip.ShowWindow(SW_SHOW);
	cip.SetWindowTextA("����ͨ��");
	cname.ShowWindow(SW_SHOW);
	cname.SetWindowTextA("����ͨ��");
	GetDlgItem(IDC_build)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_build)->SetWindowTextA("�޸ı����ڱ���");
	GetDlgItem(IDC_connect)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_del)->ShowWindow(SW_HIDE);
	runc.ShowWindow(SW_HIDE);
	GetDlgItem(IDC_Recive)->ShowWindow(SW_HIDE);
	frun=0;
}

//�����ܵ�
void CMFCApplication1Dlg::OnBnClickedRadio4()
{
	now=4;
	GetDlgItem(IDC_STATIC)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATICp)->ShowWindow(SW_HIDE);
	cip.ShowWindow(SW_HIDE);
	cname.ShowWindow(SW_HIDE);
	if(fchild)
	{
		GetDlgItem(IDC_build)->ShowWindow(SW_HIDE);
		ni.connect();
	}
	else
	{
		GetDlgItem(IDC_build)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_build)->SetWindowTextA("�����ӽ���");
	}
	GetDlgItem(IDC_connect)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_del)->ShowWindow(SW_HIDE);
	runc.ShowWindow(SW_HIDE);
	GetDlgItem(IDC_Recive)->ShowWindow(SW_SHOW);
	runc.ShowWindow(SW_SHOW);
	frun=0;
	runc.SetCheck(false);
}

//������Ϣ
void CMFCApplication1Dlg::OnBnClickedRadio5()
{
	now=5;
	sh=share();
	GetDlgItem(IDC_STATIC)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATICp)->ShowWindow(SW_HIDE);
	cip.ShowWindow(SW_HIDE);
	cname.ShowWindow(SW_HIDE);
	GetDlgItem(IDC_build)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_connect)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_del)->ShowWindow(SW_HIDE);
	runc.ShowWindow(SW_HIDE);
	GetDlgItem(IDC_Recive)->ShowWindow(SW_SHOW);
	runc.ShowWindow(SW_SHOW);
	frun=0;
	runc.SetCheck(false);
}
