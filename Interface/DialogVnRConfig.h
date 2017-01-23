#pragma once

#include ".\\Ctrl\Grid\\GridCtrl.h"
#include ".\\Ctrl\\BtnST.h"
#include ".\\Ctrl\\GradientStatic.h"
// CDialogVnRConfig ��ȭ �����Դϴ�.

class CDialogVnRConfig : public CDialog
{
	DECLARE_DYNAMIC(CDialogVnRConfig)

public:
	CGradientStatic		m_msgPort;
	CGradientStatic		m_msgPortData;

	CGradientStatic		m_msgChan;
	CGradientStatic		m_msgChanData;

	CButtonST			m_btnExit;

	void				OnInitButton();
	void				OnInitLabel();

public:
	CDialogVnRConfig(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CDialogVnRConfig();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG_VNR_CONFIG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual BOOL DestroyWindow();
	afx_msg void OnStnClickedMsgPortData();
	afx_msg void OnBnClickedBtnExit();
	afx_msg void OnStnClickedMsgChanData();
};
