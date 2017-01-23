// DialogVnRConfig.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Interface.h"
#include "DialogVnRConfig.h"
#include "afxdialogex.h"
#include ".\\Ctrl\\Variable.h"
#include ".\\Ctrl\\KeyBoard.h"
#include ".\\Ctrl\\PublicFunction.h"

// CDialogVnRConfig 대화 상자입니다.

IMPLEMENT_DYNAMIC(CDialogVnRConfig, CDialog)

CDialogVnRConfig::CDialogVnRConfig(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogVnRConfig::IDD, pParent)
{

}

CDialogVnRConfig::~CDialogVnRConfig()
{
}

void CDialogVnRConfig::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX,	IDC_MSG_PORT,				m_msgPort);
	DDX_Control(pDX,	IDC_MSG_PORT_DATA,			m_msgPortData);
	DDX_Control(pDX,	IDC_MSG_CHAN,				m_msgChan);
	DDX_Control(pDX,	IDC_MSG_CHAN_DATA,			m_msgChanData);
	DDX_Control(pDX,	IDC_BTN_EXIT,				m_btnExit);
}


BEGIN_MESSAGE_MAP(CDialogVnRConfig, CDialog)
	ON_STN_CLICKED(IDC_MSG_PORT_DATA, &CDialogVnRConfig::OnStnClickedMsgPortData)
	ON_BN_CLICKED(IDC_BTN_EXIT, &CDialogVnRConfig::OnBnClickedBtnExit)
	ON_STN_CLICKED(IDC_MSG_CHAN_DATA, &CDialogVnRConfig::OnStnClickedMsgChanData)
END_MESSAGE_MAP()


// CDialogVnRConfig 메시지 처리기입니다.


BOOL CDialogVnRConfig::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	OnInitButton();
	OnInitLabel();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


BOOL CDialogVnRConfig::DestroyWindow()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	return CDialog::DestroyWindow();
}


void CDialogVnRConfig::OnStnClickedMsgPortData()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString strData;

	int nKey;

	nKey = st_server_info.nPort;

	KeyPadI(1, 100000, &nKey);

	st_server_info.nPort = nKey;

	strData.Format(_T("%d"), nKey);
	m_msgPortData.SetWindowText(strData);

}

void CDialogVnRConfig::OnInitButton()
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

void CDialogVnRConfig::OnInitLabel()
{
	CString strTemp;

	m_msgPort.SetFont(clsFunc.m_pFont[8]); 
	m_msgPort.SetWindowText(_T("Port"));
	m_msgPort.SetCenterText();
	m_msgPort.SetColor(WHITE_C);
	m_msgPort.SetGradientColor(ORANGE_C);
	m_msgPort.SetTextColor(BLACK_C);

	strTemp.Format(_T("%d"), st_server_info.nPort);
	m_msgPortData.SetFont(clsFunc.m_pFont[8]);
	m_msgPortData.SetWindowText(strTemp);
	m_msgPortData.SetCenterText();
	m_msgPortData.SetColor(WHITE_C);
	m_msgPortData.SetGradientColor(WHITE_C);
	m_msgPortData.SetTextColor(BLACK_C);

	m_msgChan.SetFont(clsFunc.m_pFont[8]);
	m_msgChan.SetWindowText(_T("Chan Count"));
	m_msgChan.SetCenterText();
	m_msgChan.SetColor(WHITE_C);
	m_msgChan.SetGradientColor(ORANGE_C);
	m_msgChan.SetTextColor(BLACK_C);

	strTemp.Format(_T("%d"), st_VnR_info.nChan);
	m_msgChanData.SetFont(clsFunc.m_pFont[8]);
	m_msgChanData.SetWindowText(strTemp);
	m_msgChanData.SetCenterText();
	m_msgChanData.SetColor(WHITE_C);
	m_msgChanData.SetGradientColor(WHITE_C);
	m_msgChanData.SetTextColor(BLACK_C);
}

void CDialogVnRConfig::OnBnClickedBtnExit()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialog::OnOK();
}


void CDialogVnRConfig::OnStnClickedMsgChanData()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString strData;

	int nKey;

	nKey = st_VnR_info.nChan;

	KeyPadI(1, 10, &nKey);

	st_VnR_info.nChan = nKey;

	strData.Format(_T("%d"), nKey);
	m_msgChanData.SetWindowText(strData);
}
