#pragma once

#include ".\\Ctrl\\XPGroupBox.h"
#include ".\\Ctrl\\BtnST.h"
#include ".\\Ctrl\\GradientStatic.h"
// CDialogBarcodeConfig ��ȭ �����Դϴ�.

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
	CDialogBarcodeConfig(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CDialogBarcodeConfig();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG_BARCODE_CONFIG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

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
