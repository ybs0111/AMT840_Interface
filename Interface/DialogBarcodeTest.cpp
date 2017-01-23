// DialogBarcodeTest.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Interface.h"
#include "DialogBarcodeTest.h"
#include "afxdialogex.h"
#include ".\\Ctrl\\Variable.h"
#include ".\\Ctrl\\KeyBoard.h"
#include ".\\Ctrl\\PublicFunction.h"


// CDialogBarcodeTest 대화 상자입니다.

IMPLEMENT_DYNAMIC(CDialogBarcodeTest, CDialogEx)

CDialogBarcodeTest::CDialogBarcodeTest(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDialogBarcodeTest::IDD, pParent)
{
	m_nBarcodeNum = 1;
}

CDialogBarcodeTest::~CDialogBarcodeTest()
{
}

void CDialogBarcodeTest::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX,	IDC_MSG_BARCODE,			m_msgBarcode);
	DDX_Control(pDX,	IDC_MSG_BARCODE_DATA,		m_msgBarcodeData);
	DDX_Control(pDX,	IDC_MSG_TRIGGER,			m_msgTrigger);
	DDX_Control(pDX,	IDC_MSG_TRIGGER_DATA,		m_msgTriggerData);
	DDX_Control(pDX,	IDC_BTN_TRIGGER,			m_btnTrigger);
	DDX_Control(pDX,	IDC_BTN_EXIT,				m_btnExit);
}


BEGIN_MESSAGE_MAP(CDialogBarcodeTest, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_TRIGGER, &CDialogBarcodeTest::OnBnClickedBtnTrigger)
	ON_BN_CLICKED(IDC_BTN_EXIT, &CDialogBarcodeTest::OnBnClickedBtnExit)
	ON_STN_CLICKED(IDC_MSG_BARCODE_DATA, &CDialogBarcodeTest::OnStnClickedMsgBarcodeData)
	ON_STN_CLICKED(IDC_MSG_TRIGGER_DATA, &CDialogBarcodeTest::OnStnClickedMsgTriggerData)
END_MESSAGE_MAP()


// CDialogBarcodeTest 메시지 처리기입니다.


BOOL CDialogBarcodeTest::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	OnInitButton();
	OnInitLabel();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

BOOL CDialogBarcodeTest::Create(CWnd *pWnd)
{
	m_pWnd = pWnd;
	return CDialog::Create( CDialogBarcodeTest::IDD );
}

BOOL CDialogBarcodeTest::DestroyWindow()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	return CDialogEx::DestroyWindow();
}


void CDialogBarcodeTest::OnBnClickedBtnTrigger()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int nNum;

	if (m_pWnd != NULL)
	{
		//if (m_nBarcodeNum < 1) nNum = 0;
		//else if (m_nBarcodeNum > 5) nNum = 4;
		//else nNum = m_nBarcodeNum - 1;

		nNum = m_nBarcodeNum - 1;
		if (nNum < 0) nNum = 0;
		else if (nNum > 4) nNum = 4;

		if (m_strTrigger != _T(""))
		{
			m_pWnd->SendMessage(WM_BARCODE_MSG_1 + nNum, BARCODE_TRIGGER_2, (LPARAM)&m_strTrigger);
		}
		else
		{
			m_pWnd->SendMessage(WM_BARCODE_MSG_1 + nNum, BARCODE_TRIGGER_1, 0);
		}
	}
}

CString	CDialogBarcodeTest::OnCharToString(char chData[], int nLength)
{
	CString strTmp;
	BSTR	buf;
	int		nCnt;

	nCnt	= MultiByteToWideChar(CP_ACP, 0, chData, nLength, NULL, NULL);
	buf		= SysAllocStringLen(NULL, nCnt);
	MultiByteToWideChar(CP_ACP, 0, chData, nLength, buf, nCnt);
	strTmp.Format(_T("%s"), buf);

	SysFreeString(buf);

	return strTmp;
}

void CDialogBarcodeTest::OnStringToChar(CString strData, char chData[])
{
	int nCnt;
	wchar_t *chBuf;

	chBuf = strData.GetBuffer(strData.GetLength());
	nCnt  = WideCharToMultiByte(CP_ACP, 0, chBuf, -1, NULL, 0, NULL, NULL);
	WideCharToMultiByte(CP_ACP, 0, chBuf, -1, chData, nCnt, 0, 0);
}

void CDialogBarcodeTest::OnBnClickedBtnExit()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_pWnd != NULL)
	{
		m_pWnd->SendMessage(WM_BARCODE_MSG_1, BARCODE_DELETE, 0);
	}
}


void CDialogBarcodeTest::OnStnClickedMsgBarcodeData()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString strTemp;

	int nKey = m_nBarcodeNum;

	KeyPadI(1, 5, &nKey);

	m_nBarcodeNum = nKey;
	strTemp.Format(_T("%d"), m_nBarcodeNum);
	m_msgBarcodeData.SetWindowText(strTemp);
}


void CDialogBarcodeTest::OnStnClickedMsgTriggerData()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	CString strData = m_strTrigger;

	KeyBoard(&strData);

	m_strTrigger = strData;
	m_msgTriggerData.SetWindowText(m_strTrigger);
}

void CDialogBarcodeTest::OnInitButton()
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

	m_btnTrigger.SetBitmaps(IDC_BTN_TRIGGER, IDB_BITMAP_TRIGGER_DN, WINDOW_DN, IDB_BITMAP_TRIGGER_UP, WINDOW_UP);
	m_btnTrigger.SetColor(CButtonST::BTNST_COLOR_BK_IN, WINDOW_DN);
	m_btnTrigger.SetColor(CButtonST::BTNST_COLOR_BK_OUT, WINDOW_UP);
	m_btnTrigger.SetColor(CButtonST::BTNST_COLOR_BK_FOCUS, WINDOW_UP);
	m_btnTrigger.SetColor(CButtonST::BTNST_COLOR_FG_IN, BLACK_C);
	m_btnTrigger.SetColor(CButtonST::BTNST_COLOR_FG_OUT, BLUE_C);
	m_btnTrigger.SetColor(CButtonST::BTNST_COLOR_FG_FOCUS, BLUE_C);
	m_btnTrigger.SetFont(clsFunc.m_pFont[3]);
	m_btnTrigger.SetTooltipText(_T("Trigger"));
}

void CDialogBarcodeTest::OnInitLabel()
{
	m_msgTrigger.SetFont(clsFunc.m_pFont[5]);
	m_msgTrigger.SetWindowText(_T("Trigger"));
	m_msgTrigger.SetCenterText();
	m_msgTrigger.SetColor(WHITE_C);
	m_msgTrigger.SetGradientColor(ORANGE_C);
	m_msgTrigger.SetTextColor(BLACK_C);

	m_msgTriggerData.SetFont(clsFunc.m_pFont[5]);
	m_msgTriggerData.SetWindowText(_T("-"));
	m_msgTriggerData.SetCenterText();
	m_msgTriggerData.SetColor(WHITE_C);
	m_msgTriggerData.SetGradientColor(WHITE_C);
	m_msgTriggerData.SetTextColor(BLACK_C);

	m_msgBarcode.SetFont(clsFunc.m_pFont[5]);
	m_msgBarcode.SetWindowText(_T("Barcode"));
	m_msgBarcode.SetCenterText();
	m_msgBarcode.SetColor(WHITE_C);
	m_msgBarcode.SetGradientColor(ORANGE_C);
	m_msgBarcode.SetTextColor(BLACK_C);

	m_msgBarcodeData.SetFont(clsFunc.m_pFont[5]);
	m_msgBarcodeData.SetWindowText(_T("1"));
	m_msgBarcodeData.SetCenterText();
	m_msgBarcodeData.SetColor(WHITE_C);
	m_msgBarcodeData.SetGradientColor(WHITE_C);
	m_msgBarcodeData.SetTextColor(BLACK_C);
}
