#pragma once

#include ".\\Ctrl\Grid\\GridCtrl.h"
#include ".\\Ctrl\\BtnST.h"
#include ".\\Ctrl\\GradientStatic.h"
// CDialogVnRView 대화 상자입니다.

class CDialogVnRView : public CDialog
{
	DECLARE_DYNAMIC(CDialogVnRView)

public:
	CGridCtrl			m_pGridVnR;

	CButtonST			m_btnExit;

	void				OnInitButton();
	void				OnInitLabel();
	void				OnInitGridVnR();
	void				OnDisplayVnR();

public:
	CDialogVnRView(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CDialogVnRView();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG_VNR_VIEW };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL DestroyWindow();
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedBtnExit();
};
