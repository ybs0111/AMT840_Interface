#pragma once

#include ".\\Ctrl\Grid\\GridCtrl.h"
#include ".\\Ctrl\\BtnST.h"
#include ".\\Ctrl\\GradientStatic.h"
// CDialogVnRConfig 대화 상자입니다.

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
	CDialogVnRConfig(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CDialogVnRConfig();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG_VNR_CONFIG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual BOOL DestroyWindow();
	afx_msg void OnStnClickedMsgPortData();
	afx_msg void OnBnClickedBtnExit();
	afx_msg void OnStnClickedMsgChanData();
};
