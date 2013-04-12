
// MFCApplication1Dlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "guandao.h"
#include "mailslot.h"
#include "copyData.h"
#include "niming.h"
#include "share.h"
// CMFCApplication1Dlg 对话框
class CMFCApplication1Dlg : public CDialogEx
{
// 构造
public:
	CMFCApplication1Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MFCAPPLICATION1_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

private:


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	virtual void OnOK();
public:
	mailslot mail;
	guandao guan;
	niming ni;
	copyData cc;
	share sh;
	afx_msg void OnBnClickedSend();
	CEdit Content_Text;
	afx_msg void OnBnClickedRecive();
	afx_msg void OnBnClickedRadio1();
	CEdit cip;
	afx_msg void OnBnClickedRadio2();
	CEdit cname;
	afx_msg void OnBnClickedbuild();
	afx_msg void OnBnClickedconnect();
	afx_msg void OnBnClickeddel();
	//afx_msg DWORD WINAPI read(LPVOID lpParameter);
	afx_msg BOOL OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct);
	afx_msg void OnBnClickedCheck1();
	CButton runc;
	afx_msg void OnBnClickedRadio3();
	CListBox chistroy;
	afx_msg void OnBnClickedButton1();
	afx_msg void dclick();
	afx_msg void OnBnClickedRadio4();
	CButton radio_niming;
	afx_msg void OnBnClickedRadio5();
//	afx_msg void OnOK();
	afx_msg BOOL PreTranslateMessage(MSG *p);
};
 DWORD WINAPI read(LPVOID lpParameter);

 