// DialogVnRView.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Interface.h"
#include "DialogVnRView.h"
#include "afxdialogex.h"
#include ".\\Ctrl\\Variable.h"
#include ".\\Ctrl\\PublicFunction.h"

#define TM_VNR				100
// CDialogVnRView ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CDialogVnRView, CDialog)

CDialogVnRView::CDialogVnRView(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogVnRView::IDD, pParent)
{

}

CDialogVnRView::~CDialogVnRView()
{
}

void CDialogVnRView::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CUSTOM_VNR,			m_pGridVnR);
	DDX_Control(pDX, IDC_BTN_EXIT,				m_btnExit);
}


BEGIN_MESSAGE_MAP(CDialogVnRView, CDialog)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BTN_EXIT, &CDialogVnRView::OnBnClickedBtnExit)
END_MESSAGE_MAP()


// CDialogVnRView �޽��� ó�����Դϴ�.


BOOL CDialogVnRView::DestroyWindow()
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	KillTimer(TM_VNR);

	return CDialog::DestroyWindow();
}


BOOL CDialogVnRView::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	OnInitButton();
	OnInitLabel();
	OnInitGridVnR();

	SetTimer(TM_VNR, 500, NULL);
	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void CDialogVnRView::OnInitButton()
{
	m_btnExit.SetBitmaps(IDC_BTN_EXIT, IDB_BITMAP_EXIT_DN, WINDOW_DN, IDB_BITMAP_EXIT_UP, WINDOW_UP);
	m_btnExit.SetColor(CButtonST::BTNST_COLOR_BK_IN, WINDOW_DN);
	m_btnExit.SetColor(CButtonST::BTNST_COLOR_BK_OUT, WINDOW_UP);
	m_btnExit.SetColor(CButtonST::BTNST_COLOR_BK_FOCUS, WINDOW_UP);
	m_btnExit.SetColor(CButtonST::BTNST_COLOR_FG_IN, BLACK_C);
	m_btnExit.SetColor(CButtonST::BTNST_COLOR_FG_OUT, BLUE_C);
	m_btnExit.SetColor(CButtonST::BTNST_COLOR_FG_FOCUS, BLUE_C);
	m_btnExit.SetFont(clsFunc.m_pFont[3]);
	m_btnExit.SetTooltipText(_T("Exit"));
}

void CDialogVnRView::OnInitLabel()
{
}

void CDialogVnRView::OnInitGridVnR()
{
	CString strTemp;
	int i, j;
	int nRow, nCol;
	
	m_pGridVnR.SetFrameFocusCell(FALSE);
	m_pGridVnR.SetTrackFocusCell(FALSE);
	m_pGridVnR.EnableSelection(FALSE);

	m_pGridVnR.SetGridLineColor(BLACK_C);
	m_pGridVnR.SetGridLines(1);

	if (st_VnR_info.nChan < 0) nRow = 1; 
	else nRow = st_VnR_info.nChan + 1;

	nCol = 3;

	m_pGridVnR.SetRowCount(nRow);
	m_pGridVnR.SetColumnCount(nCol);

	m_pGridVnR.SetFixedRowCount(1);
	m_pGridVnR.SetFixedColumnCount(1);
	m_pGridVnR.SetFixedBkColor(RGB(0,0,200));
	m_pGridVnR.SetFixedBkColor(RGB(200,200,255));
	m_pGridVnR.SetTextBkColor(RGB(150,150,200));

	for (i=0; i<nRow; i++) 
	{
		m_pGridVnR.SetRowHeight(i, 30);

		for (j=0; j<nCol; j++) 
		{
			if (j == 0)
			{
				m_pGridVnR.SetColumnWidth(j, 90);

				if (i > 0)
				{
					strTemp.Format(_T("%d"), i);

					m_pGridVnR.SetItemBkColour(i, j, BLACK_L, YELLOW_C);
					m_pGridVnR.SetItemFont(i, j, &clsFunc.OnLogFont(18));
					m_pGridVnR.SetItemFormat(i, j, DT_CENTER|DT_VCENTER|DT_SINGLELINE);
					m_pGridVnR.SetItemState(i, j, GVIS_READONLY);
					m_pGridVnR.SetItemText(i, j, strTemp);

				}
			}
			else
			{
				m_pGridVnR.SetColumnWidth(j, 280);

				m_pGridVnR.SetItemFont(i, j, &clsFunc.OnLogFont(18));
				
				m_pGridVnR.SetItemFormat(i, j, DT_CENTER|DT_VCENTER|DT_SINGLELINE);
				m_pGridVnR.SetItemState(i, j, GVIS_READONLY);
				m_pGridVnR.SetItemBkColour(i, j, WHITE_C, BLACK_C);
			}
		}
	}

	m_pGridVnR.SetItemBkColour(0, 0, BLACK_L, YELLOW_C);
	m_pGridVnR.SetItemFont(0, 0, &clsFunc.OnLogFont(18));
	m_pGridVnR.SetItemFormat(0, 0, DT_CENTER|DT_VCENTER|DT_SINGLELINE);
	m_pGridVnR.SetItemState(0, 0, GVIS_READONLY);
	m_pGridVnR.SetItemText(0, 0, _T("Chan"));

	m_pGridVnR.SetItemBkColour(0, 1, BLACK_L, YELLOW_C);
	m_pGridVnR.SetItemFont(0, 1, &clsFunc.OnLogFont(18));
	m_pGridVnR.SetItemFormat(0, 1, DT_CENTER|DT_VCENTER|DT_SINGLELINE);
	m_pGridVnR.SetItemState(0, 1, GVIS_READONLY);
	m_pGridVnR.SetItemText(0, 1, _T("Volt"));

	m_pGridVnR.SetItemBkColour(0, 2, BLACK_L, YELLOW_C);
	m_pGridVnR.SetItemFont(0, 2, &clsFunc.OnLogFont(18));
	m_pGridVnR.SetItemFormat(0, 2, DT_CENTER|DT_VCENTER|DT_SINGLELINE);
	m_pGridVnR.SetItemState(0, 2, GVIS_READONLY);
	m_pGridVnR.SetItemText(0, 2, _T("Resistance"));

	OnDisplayVnR();
}

void CDialogVnRView::OnDisplayVnR()
{
	int i;

	CString strTemp;

	for (i=0; i<st_VnR_info.nChan; i++) 
	{
		strTemp.Format(_T("%.3f"), st_VnR_info.dVolt[i]);
		m_pGridVnR.SetItemText(i + 1, 1, strTemp);

		strTemp.Format(_T("%.3f"), st_VnR_info.dResistance[i]);
		m_pGridVnR.SetItemText(i + 1, 2, strTemp);
	}
	m_pGridVnR.Invalidate(FALSE);
}


void CDialogVnRView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	OnDisplayVnR();

	CDialog::OnTimer(nIDEvent);
}


void CDialogVnRView::OnBnClickedBtnExit()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CDialog::OnOK();
}
