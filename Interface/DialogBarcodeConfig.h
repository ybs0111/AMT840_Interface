#pragma once

#include ".\\Ctrl\\XPGroupBox.h"
#include ".\\Ctrl\\BtnST.h"
#include ".\\Ctrl\\GradientStatic.h"
// CDialogBarcodeConfig 대화 상자입니다.

class CDialogBarcodeConfig : public CDialog
{
	DECLARE_DYNAMIC(CDialogBarcodeConfig)

public:
	int					m_nBarcode;
	int					m_nBarcodeNum;
	int					m_nCutCount;

	CString				m_strTrigger;

	CGradientStatic		m_msgPort;
	CGradientStatic		m_msgBaudRate;
	CGradientStatic		m_msgData;
	CGradientStatic		m_msgStop;
	CGradientStatic		m_msgParity;
	CGradientStatic		m_msgLastChar;
	CGradientStatic		m_msgLastCharData;
	CGradientStatic		m_msgCutCount;
	CGradientStatic		m_msgCutCountData;
	CGradientStatic		m_msgBarcode;
	CGradientStatic		m_msgBarcodeData;
	CGradientStatic		m_msgTrigger;
	CGradientStatic		m_msgTriggerData;

	CComboBox			m_cbPort;
	CComboBox			m_cbRate;
	CComboBox			m_cbData;
	CComboBox			m_cbStop;
	CComboBox			m_cbParity;

	CButtonST			m_btnExit;
	CButtonST			m_btnApply;

	void				OnInitButton();
	void				OnInitLabel();
	int					ConverterToData(int nMode, int nPos);
	int					ConverterToPos(int nMode, int Ndata);
	void				Display(int nBarcode);
	BOOL				Create();

public:
	CDialogBarcodeConfig(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CDialogBarcodeConfig();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG_BARCODE_CONFIG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnChange();
	afx_msg void OnBnClickedBtnApply();
	afx_msg void OnBnClickedBtnExit();

	int m_nEndR;
	int m_nEndS;
	virtual BOOL OnInitDialog();
	virtual BOOL DestroyWindow();
	afx_msg void OnStnClickedMsgBarcodeData();
	afx_msg void OnStnClickedMsgCutNumData();
	afx_msg void OnStnClickedMsgTriggerData();
};
