#pragma once

#include ".\\Ctrl\Grid\\GridCtrl.h"
#include ".\\Ctrl\\BtnST.h"
#include ".\\Ctrl\\GradientStatic.h"
// CDialogRfidConfig ��ȭ �����Դϴ�.

class CDialogRfidConfig : public CDialog
{
	DECLARE_DYNAMIC(CDialogRfidConfig)

public:
	CGradientStatic		m_msgTag;
	CGradientStatic		m_msgTagData;
	CGradientStatic		m_msgIp;
	CGradientStatic		m_msgIpData;
	CGradientStatic		m_msgPort;
	CGradientStatic		m_msgPortData;

	CGridCtrl			m_pGridTag;

	CButtonST			m_btnExit;

	void				OnInitButton();
	void				OnInitLabel();
	void				OnInitGridTag();
public:
	CDialogRfidConfig(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CDialogRfidConfig();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG_RFID_CONFIG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL DestroyWindow();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnExit();
	afx_msg void OnTagCellClick(NMHDR *pNotifyStruct, LRESULT* pResult);
	afx_msg void OnStnClickedMsgTagData();
	afx_msg void OnStnClickedMsgIpData();
	afx_msg void OnStnClickedMsgPortData();
};
