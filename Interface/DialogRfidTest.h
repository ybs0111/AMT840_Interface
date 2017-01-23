#pragma once

#include ".\\Ctrl\Grid\\GridCtrl.h"
#include ".\\Ctrl\\BtnST.h"
#include ".\\Ctrl\\GradientStatic.h"
// CDialogRfidTest ��ȭ �����Դϴ�.

class CDialogRfidTest : public CDialog
{
	DECLARE_DYNAMIC(CDialogRfidTest)

public:
	int					m_nChan;

	CGradientStatic		m_msgChan;
	CGradientStatic		m_msgChanData;

	CGridCtrl			m_pGridTag;

	CButtonST			m_btnRead;
	CButtonST			m_btnWrite;
	CButtonST			m_btnExit;

	CWnd				*m_pWnd;

	void				OnInitButton();
	void				OnInitLabel();
	void				OnInitGridTag();
	void				DataDisplay(int nChan);
	BOOL				Create(CWnd	*pWnd);

public:
	CDialogRfidTest(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CDialogRfidTest();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG_RFID_TEST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL DestroyWindow();
	virtual BOOL OnInitDialog();
	afx_msg void OnTagCellClick(NMHDR *pNotifyStruct, LRESULT* pResult);
	afx_msg void OnStnClickedMsgChanData();
	afx_msg void OnBnClickedBtnRead();
	afx_msg void OnBnClickedBtnWrite();
	afx_msg void OnBnClickedBtnExit();
};
