#pragma once

#include ".\\Ctrl\\XPGroupBox.h"
#include ".\\Ctrl\\BtnST.h"
#include ".\\Ctrl\\GradientStatic.h"
// CDialogBarcodeTest 대화 상자입니다.

class CDialogBarcodeTest : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogBarcodeTest)

public:
	CButtonST			m_btnExit;
	CButtonST			m_btnTrigger;

	CGradientStatic		m_msgBarcode;
	CGradientStatic		m_msgBarcodeData;
	CGradientStatic		m_msgTrigger;
	CGradientStatic		m_msgTriggerData;

	int					m_nBarcodeNum;

	CString				m_strTrigger;

	CWnd				*m_pWnd;

	void				OnInitButton();
	void				OnInitLabel();
	BOOL				Create(CWnd	*pWnd);
	CString				OnCharToString(char chData[], int nLength);
	void				OnStringToChar(CString strData, char chData[]);

public:
	CDialogBarcodeTest(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CDialogBarcodeTest();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG_BARCODE_TEST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual BOOL DestroyWindow();
	afx_msg void OnBnClickedBtnTrigger();
	afx_msg void OnBnClickedBtnExit();
	afx_msg void OnStnClickedMsgBarcodeData();
	afx_msg void OnStnClickedMsgTriggerData();
};
