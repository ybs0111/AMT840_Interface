// DialogRfidConfig.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Interface.h"
#include "DialogRfidConfig.h"
#include "afxdialogex.h"
#include ".\\Ctrl\\Variable.h"
#include ".\\Ctrl\\PublicFunction.h"
#include ".\\Ctrl\\KeyBoard.h"

// CDialogRfidConfig 대화 상자입니다.

IMPLEMENT_DYNAMIC(CDialogRfidConfig, CDialog)

CDialogRfidConfig::CDialogRfidConfig(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogRfidConfig::IDD, pParent)
{

}

CDialogRfidConfig::~CDialogRfidConfig()
{
}

void CDialogRfidConfig::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CUSTOM_TAG,				m_pGridTag);
	DDX_Control(pDX,	IDC_MSG_TAG,				m_msgTag);
	DDX_Control(pDX,	IDC_MSG_TAG_DATA,			m_msgTagData);
	DDX_Control(pDX,	IDC_MSG_IP,					m_msgIp);
	DDX_Control(pDX,	IDC_MSG_IP_DATA,			m_msgIpData);
	DDX_Control(pDX,	IDC_MSG_PORT,				m_msgPort);
	DDX_Control(pDX,	IDC_MSG_PORT_DATA,			m_msgPortData);
	DDX_Control(pDX,	IDC_BTN_EXIT,				m_btnExit);
}


BEGIN_MESSAGE_MAP(CDialogRfidConfig, CDialog)
	ON_BN_CLICKED(IDC_BTN_EXIT, &CDialogRfidConfig::OnBnClickedBtnExit)
	ON_NOTIFY(NM_CLICK, IDC_CUSTOM_TAG,	OnTagCellClick)
	ON_STN_CLICKED(IDC_MSG_TAG_DATA, &CDialogRfidConfig::OnStnClickedMsgTagData)
	ON_STN_CLICKED(IDC_MSG_IP_DATA, &CDialogRfidConfig::OnStnClickedMsgIpData)
	ON_STN_CLICKED(IDC_MSG_PORT_DATA, &CDialogRfidConfig::OnStnClickedMsgPortData)
END_MESSAGE_MAP()


// CDialogRfidConfig 메시지 처리기입니다.


BOOL CDialogRfidConfig::DestroyWindow()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	return CDialog::DestroyWindow();
}


BOOL CDialogRfidConfig::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	OnInitGridTag();
	OnInitLabel();
	OnInitButton();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CDialogRfidConfig::OnInitGridTag()
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

	nCol = 6;

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
				m_pGridTag.SetColumnWidth(j, 60);

				m_pGridTag.SetItemFont(i, j, &clsFunc.OnLogFont(18));
				m_pGridTag.SetItemFormat(i, j, DT_CENTER|DT_VCENTER|DT_SINGLELINE);
				m_pGridTag.SetItemState(i, j, GVIS_READONLY);
				if (st_rfid_info.nRfidTag[i - 1] == NO)
				{
					m_pGridTag.SetItemText(i, j, _T("N"));
					m_pGridTag.SetItemBkColour(i, j, GREEN_D, BLACK_C);
				}
				else
				{
					m_pGridTag.SetItemText(i, j, _T("Y"));
					m_pGridTag.SetItemBkColour(i, j, GREEN_C, BLACK_C);
				}
			}
			else if (j == 2)
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
				m_pGridTag.SetColumnWidth(j, 70);

				if (j == 3)
				{
					strTemp.Format(_T("%d"), st_rfid_info.nRfidPos[i - 1]);
				}
				else if (j == 4)
				{
					strTemp.Format(_T("%d"), st_rfid_info.nRfidPos[i - 1] + st_rfid_info.nRfidNum[i - 1] - 1);
				}
				else
				{
					strTemp.Format(_T("%d"), st_rfid_info.nRfidNum[i - 1]);
				}

				m_pGridTag.SetItemFormat(i, j, DT_CENTER|DT_VCENTER|DT_SINGLELINE);
				m_pGridTag.SetItemState(i, j, GVIS_READONLY);
				m_pGridTag.SetItemBkColour(i, j, WHITE_C, BLACK_C);
				m_pGridTag.SetItemText(i, j, strTemp);
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
	m_pGridTag.SetItemText(0, 1, _T("USED"));

	m_pGridTag.SetItemBkColour(0, 2, BLACK_L, YELLOW_C);
	m_pGridTag.SetItemFont(0, 2, &clsFunc.OnLogFont(18));
	m_pGridTag.SetItemFormat(0, 2, DT_CENTER|DT_VCENTER|DT_SINGLELINE);
	m_pGridTag.SetItemState(0, 2, GVIS_READONLY);
	m_pGridTag.SetItemText(0, 2, _T("NAME"));

	m_pGridTag.SetItemBkColour(0, 3, BLACK_L, YELLOW_C);
	m_pGridTag.SetItemFont(0, 3, &clsFunc.OnLogFont(18));
	m_pGridTag.SetItemFormat(0, 3, DT_CENTER|DT_VCENTER|DT_SINGLELINE);
	m_pGridTag.SetItemState(0, 3, GVIS_READONLY);
	m_pGridTag.SetItemText(0, 3, _T("START"));

	m_pGridTag.SetItemBkColour(0, 4, BLACK_L, YELLOW_C);
	m_pGridTag.SetItemFont(0, 4, &clsFunc.OnLogFont(18));
	m_pGridTag.SetItemFormat(0, 4, DT_CENTER|DT_VCENTER|DT_SINGLELINE);
	m_pGridTag.SetItemState(0, 4, GVIS_READONLY);
	m_pGridTag.SetItemText(0, 4, _T("END"));

	m_pGridTag.SetItemBkColour(0, 5, BLACK_L, YELLOW_C);
	m_pGridTag.SetItemFont(0, 5, &clsFunc.OnLogFont(18));
	m_pGridTag.SetItemFormat(0, 5, DT_CENTER|DT_VCENTER|DT_SINGLELINE);
	m_pGridTag.SetItemState(0, 5, GVIS_READONLY);
	m_pGridTag.SetItemText(0, 5, _T("LENGTH"));
}

void CDialogRfidConfig::OnBnClickedBtnExit()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialog::OnOK();
}

void CDialogRfidConfig::OnInitButton()
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

void CDialogRfidConfig::OnInitLabel()
{
	CString strTemp;

	m_msgTag.SetFont(clsFunc.m_pFont[5]);
	m_msgTag.SetWindowText(_T("RFID Tag Num"));
	m_msgTag.SetCenterText();
	m_msgTag.SetColor(WHITE_C);
	m_msgTag.SetGradientColor(ORANGE_C);
	m_msgTag.SetTextColor(BLACK_C);

	strTemp.Format(_T("%d"), st_rfid_info.nTagNum);
	m_msgTagData.SetFont(clsFunc.m_pFont[5]);
	m_msgTagData.SetWindowText(strTemp);
	m_msgTagData.SetCenterText();
	m_msgTagData.SetColor(WHITE_C);
	m_msgTagData.SetGradientColor(WHITE_C);
	m_msgTagData.SetTextColor(BLACK_C);

	m_msgIp.SetFont(clsFunc.m_pFont[5]);
	m_msgIp.SetWindowText(_T("IP Address"));
	m_msgIp.SetCenterText();
	m_msgIp.SetColor(WHITE_C);
	m_msgIp.SetGradientColor(ORANGE_C);
	m_msgIp.SetTextColor(BLACK_C);

	m_msgIpData.SetFont(clsFunc.m_pFont[5]);
	m_msgIpData.SetWindowText(st_client_info.strIp);
	m_msgIpData.SetCenterText();
	m_msgIpData.SetColor(WHITE_C);
	m_msgIpData.SetGradientColor(WHITE_C);
	m_msgIpData.SetTextColor(BLACK_C);

	m_msgPort.SetFont(clsFunc.m_pFont[5]);
	m_msgPort.SetWindowText(_T("Port"));
	m_msgPort.SetCenterText();
	m_msgPort.SetColor(WHITE_C);
	m_msgPort.SetGradientColor(ORANGE_C);
	m_msgPort.SetTextColor(BLACK_C);

	strTemp.Format(_T("%d"), st_client_info.nPort);
	m_msgPortData.SetFont(clsFunc.m_pFont[5]);
	m_msgPortData.SetWindowText(strTemp);
	m_msgPortData.SetCenterText();
	m_msgPortData.SetColor(WHITE_C);
	m_msgPortData.SetGradientColor(WHITE_C);
	m_msgPortData.SetTextColor(BLACK_C);
}

void CDialogRfidConfig::OnTagCellClick(NMHDR *pNotifyStruct, LRESULT* pResult)
{
	int nRow, nCol;
	int nNum;
	int nKey;
	int i;

	CString strTemp;

	NM_GRIDVIEW* pItem	= (NM_GRIDVIEW*) pNotifyStruct;

	nRow				= pItem->iRow;
	nCol				= pItem->iColumn;

	if (nRow == 0 || nCol == 0) return;

	nNum = nRow - 1;
	if (nCol == 1)
	{
		if (nRow > 1) return;

		if (st_rfid_info.nRfidTag[nNum] == NO)
		{
			st_rfid_info.nRfidTag[nNum] = YES;
			m_pGridTag.SetItemText(nRow, nCol, _T("Y"));
			m_pGridTag.SetItemBkColour(nRow, nCol, GREEN_C, BLACK_C);
		}
		else
		{
			st_rfid_info.nRfidTag[nNum] = NO;
			m_pGridTag.SetItemText(nRow, nCol, _T("N"));
			m_pGridTag.SetItemBkColour(nRow, nCol, GREEN_D, BLACK_C);
		}
	}
	else if (nCol == 2)
	{
		strTemp = st_rfid_info.strRfidTitle[nNum];

		KeyBoard(&strTemp);

		st_rfid_info.strRfidTitle[nNum] = strTemp;
		m_pGridTag.SetItemText(nRow, nCol, strTemp);
	}
	else if (nCol == 3)
	{
		nKey = st_rfid_info.nRfidPos[nNum];

		KeyPadI(0, 200, &nKey);
		st_rfid_info.nRfidPos[nNum] = nKey;

		strTemp.Format(_T("%d"), nKey);
		m_pGridTag.SetItemText(nRow, nCol, strTemp);

		strTemp.Format(_T("%d"), st_rfid_info.nRfidPos[nNum] + st_rfid_info.nRfidNum[nNum] - 1);
		m_pGridTag.SetItemText(nRow, 4, strTemp);

		for (i=nNum + 1; i<st_rfid_info.nTagNum; i++)
		{
			st_rfid_info.nRfidPos[i] = (st_rfid_info.nRfidPos[i - 1] + st_rfid_info.nRfidNum[i - 1]);

			strTemp.Format(_T("%d"), st_rfid_info.nRfidPos[i]);
			m_pGridTag.SetItemText(i + 1, 3, strTemp);

			strTemp.Format(_T("%d"), st_rfid_info.nRfidPos[i] + st_rfid_info.nRfidNum[i] - 1);
			m_pGridTag.SetItemText(i + 1, 4, strTemp);
		}
	}
	else if (nCol == 4)
	{
		nKey = st_rfid_info.nRfidPos[nNum] + st_rfid_info.nRfidNum[nNum];

		KeyPadI(0, 200, &nKey);
		st_rfid_info.nRfidNum[nNum] = nKey - st_rfid_info.nRfidPos[nNum];

		strTemp.Format(_T("%d"), nKey);
		m_pGridTag.SetItemText(nRow, nCol, strTemp);

		strTemp.Format(_T("%d"), st_rfid_info.nRfidNum[nNum]);
		m_pGridTag.SetItemText(nRow, 5, strTemp);

		for (i=nNum + 1; i<st_rfid_info.nTagNum; i++)
		{
			st_rfid_info.nRfidPos[i] = (st_rfid_info.nRfidPos[i - 1] + st_rfid_info.nRfidNum[i - 1]);

			strTemp.Format(_T("%d"), st_rfid_info.nRfidPos[i]);
			m_pGridTag.SetItemText(i + 1, 3, strTemp);

			strTemp.Format(_T("%d"), st_rfid_info.nRfidPos[i] + st_rfid_info.nRfidNum[i] - 1);
			m_pGridTag.SetItemText(i + 1, 4, strTemp);
		}
	}
	else if (nCol == 5)
	{
		nKey = st_rfid_info.nRfidNum[nNum];

		KeyPadI(1, 100, &nKey);
		st_rfid_info.nRfidNum[nNum] = nKey;

		strTemp.Format(_T("%d"), nKey);
		m_pGridTag.SetItemText(nRow, nCol, strTemp);

		strTemp.Format(_T("%d"), st_rfid_info.nRfidPos[nNum] + st_rfid_info.nRfidNum[nNum] - 1);
		m_pGridTag.SetItemText(nRow, 4, strTemp);

		for (i=nNum + 1; i<st_rfid_info.nTagNum; i++)
		{
			st_rfid_info.nRfidPos[i] = (st_rfid_info.nRfidPos[i - 1] + st_rfid_info.nRfidNum[i - 1]);

			strTemp.Format(_T("%d"), st_rfid_info.nRfidPos[i]);
			m_pGridTag.SetItemText(i + 1, 3, strTemp);

			strTemp.Format(_T("%d"), st_rfid_info.nRfidPos[i] + st_rfid_info.nRfidNum[i] - 1);
			m_pGridTag.SetItemText(i + 1, 4, strTemp);
		}
	}

	m_pGridTag.Invalidate(FALSE);
}

void CDialogRfidConfig::OnStnClickedMsgTagData()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString strTemp;

	int nKey = st_rfid_info.nTagNum;

	KeyPadI(1, 50, &nKey);

	st_rfid_info.nTagNum = nKey;
	strTemp.Format(_T("%d"), st_rfid_info.nTagNum);
	m_msgTagData.SetWindowText(strTemp);

	OnInitGridTag();
}


void CDialogRfidConfig::OnStnClickedMsgIpData()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString strData;

	strData = st_client_info.strIp;

	KeyBoard(&strData);

	st_client_info.strIp = strData;
	m_msgIpData.SetWindowText(strData);
}


void CDialogRfidConfig::OnStnClickedMsgPortData()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString strData;

	int nKey;

	nKey = st_client_info.nPort;

	KeyPadI(1, 100000, &nKey);

	st_client_info.nPort = nKey;

	strData.Format(_T("%d"), nKey);
	m_msgPortData.SetWindowText(strData);
}
