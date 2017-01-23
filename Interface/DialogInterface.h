#pragma once


// CDialogInterface ��ȭ �����Դϴ�.
#include ".\\Ctrl\\TrayIcon.h"
// CDialogMain ��ȭ �����Դϴ�.
#include ".\\Ctrl\\Comm.h"
#include ".\\Ctrl\\XPGroupBox.h"
//#include ".\\Ctrl\\BtnST.h"
#include ".\\Ctrl\\GradientStatic.h"
#include ".\\Ctrl\\ColorListBox.h"		// Į�� ����Ʈ �ڽ� Ŭ����
#include ".\\Ctrl\\ClientSocket.h"
#include ".\\Ctrl\\ServerSocket.h"
#include ".\\Ctrl\\PublicFunction.h"
#include ".\\Ctrl\\BtnST.h"

class CDialogBarcodeTest;
class CDialogRfidTest;

class CDialogInterface : public CDialog
{
	DECLARE_DYNAMIC(CDialogInterface)
public:
	CServerSocket		*m_pVnRS;

	void				VnRConfigLoad();
	void				VnRConfigSave();
	void				VnRReadData(int nChan, double *dVolt, double *dResistance);
	void				VnRCreate();
	void				VnRDelete();
public:
	CClientSocket		*m_pRfidC;
	
	void				RfidTagInfo(int nItem, int nStart, int nNum, int nWriteYesNo);
	void				RfidReadData(int nChan, int nItem, CString *strMsg);
	void				RfidReadAllData(int nChan, CString *strMsg);
	void				RfidLastErrorMsg(CString *strMsg);
	void				RfidReadTag(int nChan);
	void				RfidWriteData(int nChan, int nItem, CString strMsg);
	void				RfidWriteAllData(int nChan, CString *strMsg);
	void				RfidConfigSave();
	void				RfidConfigLoad();
	void				RfidCreate();
	void				RfidDelete();

public:
	// barcode ����
	CComm				*m_pCom[5];

	HANDLE				m_thrHandle;
	BOOL				m_bThread;

	void				BarcodeConfigSave();
	void				BarcodeConfigLoad();
	void				BarcodeLastErrorMsg(CString *strMsg);
	int					BarcodeCreate(int nBarcode);
	void				BarcodeDelete(int nBarcode);
	void				BarcodeReadData(int nBarcode);
	void				BarcodeReadData(int nBarcode, CString strTrigger);
	void				Communication_1();
	void				Communication_2();
	void				Communication_3();
	void				Communication_4();
	void				Communication_5();
public:
	CWnd				*m_pWnd;
	
	CDialogBarcodeTest	*m_pBarcode;
	CDialogRfidTest		*m_pRfid;

	CTrayIcon			m_TrayIcon; 

	DWORD				m_dwWaitTime[5][3];
	int					m_nWaitTimeStep[5];

	long				m_lNormalWaitTime[3];

	CString				m_strOldMsg;
	CString				m_strRfidLastError;
	CString				m_strBarcodeLastError;

	CButtonST			m_btnHide;

	CColorListBox		m_listData;

	CXPGroupBox			m_groupInfo;

	void				OnInitGroupBox();
	void				OnInitLabel();
	void				OnInitButton();
	void				OnInitDigit();
	BOOL				Create(CWnd	*pWnd);
	CString				OnCharToString(char chData[], int nLength);
	void				OnStringToChar(CString strData, char chData[]);
	void				OnListNormalMsgDisplay(CString strMsg);

public:
	CDialogInterface(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CDialogInterface();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG_INTERFACE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual BOOL DestroyWindow();

	afx_msg LONG OnTrayNotification(UINT wParam, LONG lParam);
	afx_msg void OnView();
	afx_msg void OnBnClickedBtnHide();
	afx_msg void OnInterfaceBarcodeConfig();
	afx_msg void OnInterfaceBarcodeTest();
	afx_msg void OnInterfaceRfconfig();
	afx_msg void OnInterfaceRftest();
	afx_msg LRESULT	BarcodeMessage1(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT	BarcodeMessage2(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT	BarcodeMessage3(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT	BarcodeMessage4(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT	BarcodeMessage5(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT	RfidMessage(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT	ClientRfidMessage(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT ServerVnRMessage(WPARAM wParam, LPARAM lParam);
	afx_msg void OnInterfaceVnrConfig();
	afx_msg void OnInterfaceVnrView();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
