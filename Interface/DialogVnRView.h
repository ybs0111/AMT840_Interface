#pragma once

#include ".\\Ctrl\Grid\\GridCtrl.h"
#include ".\\Ctrl\\BtnST.h"
#include ".\\Ctrl\\GradientStatic.h"
// CDialogVnRView ��ȭ �����Դϴ�.

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
	CDialogVnRView(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CDialogVnRView();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG_VNR_VIEW };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL DestroyWindow();
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedBtnExit();
};
