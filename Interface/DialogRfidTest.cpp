// DialogRfidTest.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Interface.h"
#include "DialogRfidTest.h"
#include "afxdialogex.h"
#include ".\\Ctrl\\Variable.h"
#include ".\\Ctrl\\PublicFunction.h"
#include ".\\Ctrl\\KeyBoard.h"

// CDialogRfidTest 대화 상자입니다.

IMPLEMENT_DYNAMIC(CDialogRfidTest, CDialog)

CDialogRfidTest::CDialogRfidTest(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogRfidTest::IDD, pParent)
{
	m_nChan = 1;
}

CDialogRfidTest::~CDialogRfidTest()
{
}

void CDialogRfidTest::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CUSTOM_TAG,				m_pGridTag);
	DDX_Control(pDX,	IDC_MSG_CHAN,				m_msgChan);
	DDX_Control(pDX,	IDC_MSG_CHAN_DATA,			m_msgChanData);
	DDX_Control(pDX,	IDC_BTN_EXIT,				m_btnExit);
	DDX_Control(pDX,	IDC_BTN_READ,				m_btnRead);
	DDX_Control(pDX,	IDC_BTN_WRITE,				m_btnWrite);
}


BEGIN_MESSAGE_MAP(CDialogRfidTest, CDialog)
	ON_NOTIFY(NM_CLICK, IDC_CUSTOM_TAG,	OnTagCellClick)
	ON_STN_CLICKED(IDC_MSG_CHAN_DATA, &CDialogRfidTest::OnStnClickedMsgChanData)
	ON_BN_CLICKED(IDC_BTN_READ, &CDialogRfidTest::OnBnClickedBtnRead)
	ON_BN_CLICKED(IDC_BTN_WRITE, &CDialogRfidTest::OnBnClickedBtnWrite)
	ON_BN_CLICKED(IDC_BTN_EXIT, &CDialogRfidTest::OnBnClickedBtnExit)
END_MESSAGE_MAP()


// CDialogRfidTest 메시지 처리기입니다.

BOOL CDialogRfidTest::Create(CWnd *pWnd)
{
	m_pWnd = pWnd;
	return CDialog::Create( CDialogRfidTest::IDD );
}

BOOL CDialogRfidTest::DestroyWindow()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	return CDialog::DestroyWindow();
}


BOOL CDialogRfidTest::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	OnInitGridTag();
	OnInitLabel();
	OnInitButton();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CDialogRfidTest::OnInitGridTag()
{
	CString strTemp;
	int i, j;
	int nRow, nCol;
	
	m_pGridTag.SetFrameFocusCell(FALSE);
	m_pGridTag.SetTrackFocusCell(FALSE);
	m_pGridTag.EnableSelection(FALSE);

	m_pGridTag.SetGridLineColor(BLACK_C);
	m_pGridTag.SetGridLines(1);

	if (st_rfid_info.nTagNum < 0) nRow = 1; 
	else nRow = st_rfid_info.nTagNum + 1;

	nCol = 3;

	m_pGridTag.SetRowCount(nRow);
	m_pGridTag.SetColumnCount(nCol);

	m_pGridTag.SetFixedRowCount(0);
	m_pGridTag.SetFixedColumnCount(0);
	m_pGridTag.SetFixedBkColor(RGB(0,0,200));
	m_pGridTag.SetFixedBkColor(RGB(200,200,255));
	m_pGridTag.SetTextBkColor(RGB(150,150,200));

	for (i=0; i<nRow; i++) 
	{
		m_pGridTag.SetRowHeight(i, 30);

		for (j=0; j<nCol; j++) 
		{
			if (j == 0)
			{
				m_pGridTag.SetColumnWidth(j, 60);

				if (i > 0)
				{
					strTemp.Format(_T("%d"), i);

					m_pGridTag.SetItemBkColour(i, j, BLACK_L, YELLOW_C);
					m_pGridTag.SetItemFont(i, j, &clsFunc.OnLogFont(18));
					m_pGridTag.SetItemFormat(i, j, DT_CENTER|DT_VCENTER|DT_SINGLELINE);
					m_pGridTag.SetItemState(i, j, GVIS_READONLY);
					m_pGridTag.SetItemText(i, j, strTemp);

				}
			}
			else if (j == 1)
			{
				m_pGridTag.SetColumnWidth(j, 300);

				m_pGridTag.SetItemFont(i, j, &clsFunc.OnLogFont(18));
				m_pGridTag.SetItemText(i, j, st_rfid_info.strRfidTitle[i-1]);

				m_pGridTag.SetItemFormat(i, j, DT_CENTER|DT_VCENTER|DT_SINGLELINE);
				m_pGridTag.SetItemState(i, j, GVIS_READONLY);
				m_pGridTag.SetItemBkColour(i, j, WHITE_C, BLACK_C);
			}
			else
			{
				m_pGridTag.SetColumnWidth(j, 270);

				m_pGridTag.SetItemFont(i, j, &clsFunc.OnLogFont(18));
				
				m_pGridTag.SetItemFormat(i, j, DT_CENTER|DT_VCENTER|DT_SINGLELINE);
				m_pGridTag.SetItemState(i, j, GVIS_READONLY);
				m_pGridTag.SetItemBkColour(i, j, WHITE_C, BLACK_C);
			}
		}
	}

	m_pGridTag.SetItemBkColour(0, 0, BLACK_L, YELLOW_C);
	m_pGridTag.SetItemFont(0, 0, &clsFunc.OnLogFont(18));
	m_pGridTag.SetItemFormat(0, 0, DT_CENTER|DT_VCENTER|DT_SINGLELINE);
	m_pGridTag.SetItemState(0, 0, GVIS_READONLY);
	m_pGridTag.SetItemText(0, 0, _T("NO."));

	m_pGridTag.SetItemBkColour(0, 1, BLACK_L, YELLOW_C);
	m_pGridTag.SetItemFont(0, 1, &clsFunc.OnLogFont(18));
	m_pGridTag.SetItemFormat(0, 1, DT_CENTER|DT_VCENTER|DT_SINGLELINE);
	m_pGridTag.SetItemState(0, 1, GVIS_READONLY);
	m_pGridTag.SetItemText(0, 1, _T("NAME"));

	m_pGridTag.SetItemBkColour(0, 2, BLACK_L, YELLOW_C);
	m_pGridTag.SetItemFont(0, 2, &clsFunc.OnLogFont(18));
	m_pGridTag.SetItemFormat(0, 2, DT_CENTER|DT_VCENTER|DT_SINGLELINE);
	m_pGridTag.SetItemState(0, 2, GVIS_READONLY);
	m_pGridTag.SetItemText(0, 2, _T("DATA"));

	DataDisplay(m_nChan);
}

void CDialogRfidTest::DataDisplay(int nChan)
{
	int nRow;
	int i;

	if (nChan < 0 || nChan > 1) return;

	if (st_rfid_info.nTagNum < 0) return; 
	else nRow = st_rfid_info.nTagNum;

	for (i=0; i<nRow; i++) 
	{
		m_pGridTag.SetItemText(i + 1, 2, st_rfid_info.strRfidData[nChan][i]);
	}

	m_pGridTag.Invalidate(FALSE);
}

void CDialogRfidTest::OnInitButton()
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

	m_btnRead.SetBitmaps(IDC_BTN_READ, IDB_BITMAP_READ_DN, WINDOW_DN, IDB_BITMAP_READ_UP, WINDOW_UP);
	m_btnRead.SetColor(CButtonST::BTNST_COLOR_BK_IN, WINDOW_DN);
	m_btnRead.SetColor(CButtonST::BTNST_COLOR_BK_OUT, WINDOW_UP);
	m_btnRead.SetColor(CButtonST::BTNST_COLOR_BK_FOCUS, WINDOW_UP);
	m_btnRead.SetColor(CButtonST::BTNST_COLOR_FG_IN, BLACK_C);
	m_btnRead.SetColor(CButtonST::BTNST_COLOR_FG_OUT, BLUE_C);
	m_btnRead.SetColor(CButtonST::BTNST_COLOR_FG_FOCUS, BLUE_C);
	m_btnRead.SetFont(clsFunc.m_pFont[3]);
	m_btnRead.SetTooltipText(_T("RFID Tag Read"));

	m_btnWrite.SetBitmaps(IDC_BTN_WRITE, IDB_BITMAP_WRITE_DN, WINDOW_DN, IDB_BITMAP_WRITE_UP, WINDOW_UP);
	m_btnWrite.SetColor(CButtonST::BTNST_COLOR_BK_IN, WINDOW_DN);
	m_btnWrite.SetColor(CButtonST::BTNST_COLOR_BK_OUT, WINDOW_UP);
	m_btnWrite.SetColor(CButtonST::BTNST_COLOR_BK_FOCUS, WINDOW_UP);
	m_btnWrite.SetColor(CButtonST::BTNST_COLOR_FG_IN, BLACK_C);
	m_btnWrite.SetColor(CButtonST::BTNST_COLOR_FG_OUT, BLUE_C);
	m_btnWrite.SetColor(CButtonST::BTNST_COLOR_FG_FOCUS, BLUE_C);
	m_btnWrite.SetFont(clsFunc.m_pFont[3]);
	m_btnWrite.SetTooltipText(_T("RFID Tag Write"));
}

void CDialogRfidTest::OnInitLabel()
{
	CString strTemp;

	m_msgChan.SetFont(clsFunc.m_pFont[5]);
	m_msgChan.SetWindowText(_T("Chan"));
	m_msgChan.SetCenterText();
	m_msgChan.SetColor(WHITE_C);
	m_msgChan.SetGradientColor(ORANGE_C);
	m_msgChan.SetTextColor(BLACK_C);

	strTemp.Format(_T("%d"), m_nChan);
	m_msgChanData.SetFont(clsFunc.m_pFont[5]);
	m_msgChanData.SetWindowText(strTemp);
	m_msgChanData.SetCenterText();
	m_msgChanData.SetColor(WHITE_C);
	m_msgChanData.SetGradientColor(WHITE_C);
	m_msgChanData.SetTextColor(BLACK_C);
}

void CDialogRfidTest::OnTagCellClick(NMHDR *pNotifyStruct, LRESULT* pResult)
{
	int nRow, nCol;
	int nNum;

	CString strTemp;

	NM_GRIDVIEW* pItem	= (NM_GRIDVIEW*) pNotifyStruct;

	nRow				= pItem->iRow;
	nCol				= pItem->iColumn;

	if (nRow == 0 || nCol == 0) return;

	nNum = nRow - 1;

	if (nCol == 2)
	{
		strTemp = st_rfid_info.strRfidData[m_nChan-1][nNum];

		KeyBoard(&strTemp);

		st_rfid_info.strRfidData[m_nChan-1][nNum] = strTemp;
		m_pGridTag.SetItemText(nRow, nCol, strTemp);
	}
	
	m_pGridTag.Invalidate(FALSE);
}

void CDialogRfidTest::OnStnClickedMsgChanData()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString strTemp;

	int nKey = m_nChan;

	KeyPadI(1, 2, &nKey);

	m_nChan = nKey;
	strTemp.Format(_T("%d"), m_nChan);
	m_msgChanData.SetWindowText(strTemp);
}


void CDialogRfidTest::OnBnClickedBtnRead()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_pWnd != NULL)
	{
		m_pWnd->SendMessage(WM_RFID_MSG, RFID_READ, m_nChan);
	}
}


void CDialogRfidTest::OnBnClickedBtnWrite()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_pWnd != NULL)
	{
		m_pWnd->SendMessage(WM_RFID_MSG, RFID_WRITE, m_nChan);
	}
}


void CDialogRfidTest::OnBnClickedBtnExit()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_pWnd != NULL)
	{
		m_pWnd->SendMessage(WM_RFID_MSG, RFID_DELETE, 0);
	}
}
