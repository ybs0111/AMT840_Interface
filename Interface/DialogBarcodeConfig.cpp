// DialogBarcodeConfig.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Interface.h"
#include "DialogBarcodeConfig.h"
#include "afxdialogex.h"
#include ".\\Ctrl\\Variable.h"
#include ".\\Ctrl\\KeyBoard.h"
#include ".\\Ctrl\\PublicFunction.h"
// CDialogBarcodeConfig 대화 상자입니다.

IMPLEMENT_DYNAMIC(CDialogBarcodeConfig, CDialog)

CDialogBarcodeConfig::CDialogBarcodeConfig(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogBarcodeConfig::IDD, pParent)
{
	m_nBarcodeNum = 1;
}

CDialogBarcodeConfig::~CDialogBarcodeConfig()
{
}

void CDialogBarcodeConfig::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX,	IDC_MSG_PORT,				m_msgPort);
	DDX_Control(pDX,	IDC_MSG_BAUDRATE,			m_msgBaudRate);
	DDX_Control(pDX,	IDC_MSG_DATA,				m_msgData);
	DDX_Control(pDX,	IDC_MSG_STOP,				m_msgStop);
	DDX_Control(pDX,	IDC_MSG_PARITY,				m_msgParity);
	DDX_Control(pDX,	IDC_MSG_LAST,				m_msgLastChar);
	DDX_Control(pDX,	IDC_BTN_APPLY,				m_btnApply);
	DDX_Control(pDX,	IDC_BTN_EXIT,				m_btnExit);
	DDX_Control(pDX,	IDC_MSG_CUT_NUM,			m_msgCutCount);
	DDX_Control(pDX,	IDC_MSG_CUT_NUM_DATA,		m_msgCutCountData);
	DDX_Control(pDX,	IDC_MSG_BARCODE,			m_msgBarcode);
	DDX_Control(pDX,	IDC_MSG_BARCODE_DATA,		m_msgBarcodeData);
	DDX_Control(pDX,	IDC_MSG_TRIGGER,			m_msgTrigger);
	DDX_Control(pDX,	IDC_MSG_TRIGGER_DATA,		m_msgTriggerData);	
	DDX_Control(pDX,	IDC_COMBO_PORT,				m_cbPort);
	DDX_Control(pDX,	IDC_COMBO_BAUDRATE,			m_cbRate);
	DDX_Control(pDX,	IDC_COMBO_DATA,				m_cbData);
	DDX_Control(pDX,	IDC_COMBO_STOP,				m_cbStop);
	DDX_Control(pDX,	IDC_COMBO_PARITY,			m_cbParity);
	DDX_Radio(pDX,		IDC_RADIO3,					m_nEndR);
	DDX_Radio(pDX,		IDC_RADIO4,					m_nEndS);
}


BEGIN_MESSAGE_MAP(CDialogBarcodeConfig, CDialog)
	ON_BN_CLICKED(IDC_BTN_CHANGE, &CDialogBarcodeConfig::OnBnClickedBtnChange)
	ON_BN_CLICKED(IDC_BTN_APPLY, &CDialogBarcodeConfig::OnBnClickedBtnApply)
	ON_BN_CLICKED(IDC_BTN_EXIT, &CDialogBarcodeConfig::OnBnClickedBtnExit)
	ON_STN_CLICKED(IDC_MSG_BARCODE_DATA, &CDialogBarcodeConfig::OnStnClickedMsgBarcodeData)
	ON_STN_CLICKED(IDC_MSG_CUT_NUM_DATA, &CDialogBarcodeConfig::OnStnClickedMsgCutNumData)
	ON_STN_CLICKED(IDC_MSG_TRIGGER_DATA, &CDialogBarcodeConfig::OnStnClickedMsgTriggerData)
END_MESSAGE_MAP()

BOOL CDialogBarcodeConfig::Create()
{

	return CDialog::Create( CDialogBarcodeConfig::IDD );
}
// CDialogBarcodeConfig 메시지 처리기입니다.


void CDialogBarcodeConfig::OnBnClickedBtnChange()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CDialogBarcodeConfig::OnBnClickedBtnApply()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int nData;

	CString strData;

	if (m_nBarcodeNum > 0 && m_nBarcodeNum < 6)
	{
		nData = m_cbPort.GetCurSel();
		st_serial_info[m_nBarcodeNum - 1].nSerialPort = ConverterToData(COM_PORT, nData);

		nData = m_cbRate.GetCurSel();
		st_serial_info[m_nBarcodeNum - 1].nSerialBaudrate = ConverterToData(COM_BAUDRATE, nData);

		nData = m_cbData.GetCurSel();
		st_serial_info[m_nBarcodeNum - 1].nSerialData = ConverterToData(COM_DATA, nData);

		nData = m_cbStop.GetCurSel();
		st_serial_info[m_nBarcodeNum - 1].nSerialStop = ConverterToData(COM_STOP, nData);

		nData = m_cbParity.GetCurSel();
		st_serial_info[m_nBarcodeNum - 1].nSerialParity = ConverterToData(COM_PARITY, nData);

		UpdateData(TRUE);
		st_serial_info[m_nBarcodeNum - 1].nDataSub = m_nCutCount;

		st_serial_info[m_nBarcodeNum - 1].byEnd[0]	= m_nEndS;
		st_serial_info[m_nBarcodeNum - 1].byEnd[1]	= m_nEndR;

		st_serial_info[m_nBarcodeNum - 1].strOn	= m_strTrigger;
	}
}


void CDialogBarcodeConfig::OnBnClickedBtnExit()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialog::OnOK();
}


BOOL CDialogBarcodeConfig::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	OnInitLabel();
	OnInitButton();

	Display(m_nBarcodeNum);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


BOOL CDialogBarcodeConfig::DestroyWindow()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	return CDialog::DestroyWindow();
}

void CDialogBarcodeConfig::Display(int nBarcode)
{
	int nNum;
	int nData;
	CString strTemp;

	if (nBarcode < 1) nNum = 0;
	else if (nBarcode > 5) nNum = 4;
	else nNum = nBarcode - 1;

	nData = ConverterToPos(COM_PORT, st_serial_info[nNum].nSerialPort);
	m_cbPort.SetCurSel(nData);

	nData = ConverterToPos(COM_BAUDRATE, st_serial_info[nNum].nSerialBaudrate);
	m_cbRate.SetCurSel(nData);

	nData = ConverterToPos(COM_DATA, st_serial_info[nNum].nSerialData);
	m_cbData.SetCurSel(nData);

	nData = ConverterToPos(COM_PARITY, st_serial_info[nNum].nSerialParity);
	m_cbParity.SetCurSel(nData);

	nData = ConverterToPos(COM_STOP, st_serial_info[nNum].nSerialStop);
	m_cbStop.SetCurSel(nData);

	m_nEndR			= st_serial_info[nNum].byEnd[1];
	m_nEndS			= st_serial_info[nNum].byEnd[0];

	m_nCutCount		= st_serial_info[nNum].nDataSub;
	strTemp.Format(_T("%d"), m_nCutCount);
	m_msgCutCountData.SetWindowText(strTemp);

	strTemp.Format(_T("%d"), nBarcode);
	m_msgBarcodeData.SetWindowText(strTemp);

	m_strTrigger	= st_serial_info[nNum].strOn;
	m_msgTriggerData.SetWindowText(m_strTrigger);

	UpdateData(FALSE);
}

int CDialogBarcodeConfig::ConverterToData(int mode, int pos)
{
	int Ret;

	switch(mode)
	{
		case COM_PORT:
			switch(pos)
			{
				case 0:
					Ret = 1;
					break;
				case 1:
					Ret = 2;
					break;
				case 2:
					Ret = 3;
					break;
				case 3:
					Ret = 4;
					break;
				case 4:
					Ret = 5;
					break;
				case 5:
					Ret = 6;
					break;
				case 6:
					Ret = 7;
					break;
				case 7:
					Ret = 8;
					break;
			}
			break;
		case COM_BAUDRATE:
			switch(pos)
			{
				case 0:
					Ret = 2400;
					break;
				case 1:
					Ret = 4800;
					break;
				case 2:
					Ret = 9600;
					break;
				case 3:
					Ret = 19200;
					break;
				case 4:
					Ret = 38400;
					break;
				case 5:
					Ret = 57600;
					break;
				case 6:
					Ret = 115200;
					break;
			}
			break;
		case COM_DATA:
			switch(pos)
			{
				case 0:
					Ret = 5;
					break;
				case 1:
					Ret = 6;
					break;
				case 2:
					Ret = 7;
					break;
				case 3:
					Ret = 8;
					break;
				}
				break;
			case COM_STOP:
				switch(pos)
				{
					case 0:
						Ret = ONESTOPBIT;
						break;
					case 1:
						Ret = TWOSTOPBITS;
						break;
				}
				break;
			case COM_PARITY:
				switch(pos)
				{
					case 0:
						Ret = EVENPARITY;  // Even
						break;
					case 1:
						Ret = ODDPARITY;  // Odd
						break;
					case 2:
						Ret = NOPARITY;  // None
						break;
			}
			break;
	}

	return Ret;
}

int CDialogBarcodeConfig::ConverterToPos(int mode, int data)
{
	int Ret = 0;

	switch(mode)
	{
		case COM_PORT:
			switch(data)
			{
				case 1:
					Ret = 0;
					break;
				case 2:
					Ret = 1;
					break;
				case 3:
					Ret = 2;
					break;
				case 4:
					Ret = 3;
					break;
				case 5:
					Ret = 4;
					break;
				case 6:
					Ret = 5;
					break;
				case 7:
					Ret = 6;
					break;
				case 8:
					Ret = 7;
					break;
			}
			break;
		case COM_BAUDRATE:
			switch(data)
			{
				case 2400:
					Ret = 0;
					break;
				case 4800:
					Ret = 1;
					break;
				case 9600:
					Ret = 2;
					break;
				case 19200:
					Ret = 3;
					break;
				case 38400:
					Ret = 4;
					break;
				case 57600:
					Ret = 5;
					break;
				case 115200:
					Ret = 6;
					break;
			}
			break;
		case COM_DATA:
			switch(data)
			{
				case 5:
					Ret = 0;
					break;
				case 6:
					Ret = 1;
					break;
				case 7:
					Ret = 2;
					break;
				case 8:
					Ret = 3;
					break;
			}
			break;
		case COM_STOP:
			switch(data)
			{
				case ONESTOPBIT:
					Ret = 0;
					break;
				case TWOSTOPBITS:
					Ret = 1;
					break;
			}
			break;
		case COM_PARITY:
			switch(data)
			{
				case EVENPARITY:
					Ret = 0;  // Even
					break;
				case ODDPARITY:
					Ret = 1;  // Odd
					break;
				case NOPARITY:
					Ret = 2;  // None
					break;
			}
			break;
	}

	return Ret;
}

void CDialogBarcodeConfig::OnStnClickedMsgBarcodeData()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int nKey = m_nBarcodeNum;

	KeyPadI(1, 5, &nKey);

	m_nBarcodeNum = nKey;

	Display(m_nBarcodeNum);
}

void CDialogBarcodeConfig::OnInitButton()
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

	m_btnApply.SetBitmaps(IDC_BTN_APPLY, IDB_BITMAP_APPLY_DN, WINDOW_DN, IDB_BITMAP_APPLY_UP, WINDOW_UP);
	m_btnApply.SetColor(CButtonST::BTNST_COLOR_BK_IN, WINDOW_DN);
	m_btnApply.SetColor(CButtonST::BTNST_COLOR_BK_OUT, WINDOW_UP);
	m_btnApply.SetColor(CButtonST::BTNST_COLOR_BK_FOCUS, WINDOW_UP);
	m_btnApply.SetColor(CButtonST::BTNST_COLOR_FG_IN, BLACK_C);
	m_btnApply.SetColor(CButtonST::BTNST_COLOR_FG_OUT, BLUE_C);
	m_btnApply.SetColor(CButtonST::BTNST_COLOR_FG_FOCUS, BLUE_C);
	m_btnApply.SetFont(clsFunc.m_pFont[3]);
	m_btnApply.SetTooltipText(_T("Data Apply"));
}

void CDialogBarcodeConfig::OnInitLabel()
{
	m_msgPort.SetFont(clsFunc.m_pFont[5]);
	m_msgPort.SetWindowText(_T("Port"));
	m_msgPort.SetCenterText();
	m_msgPort.SetColor(WHITE_C);
	m_msgPort.SetGradientColor(ORANGE_C);
	m_msgPort.SetTextColor(BLACK_C);

	m_msgBaudRate.SetFont(clsFunc.m_pFont[5]);
	m_msgBaudRate.SetWindowText(_T("BaudRate"));
	m_msgBaudRate.SetCenterText();
	m_msgBaudRate.SetColor(WHITE_C);
	m_msgBaudRate.SetGradientColor(ORANGE_C);
	m_msgBaudRate.SetTextColor(BLACK_C);

	m_msgData.SetFont(clsFunc.m_pFont[5]);
	m_msgData.SetWindowText(_T("Data"));
	m_msgData.SetCenterText();
	m_msgData.SetColor(WHITE_C);
	m_msgData.SetGradientColor(ORANGE_C);
	m_msgData.SetTextColor(BLACK_C);

	m_msgStop.SetFont(clsFunc.m_pFont[5]);
	m_msgStop.SetWindowText(_T("Stop"));
	m_msgStop.SetCenterText();
	m_msgStop.SetColor(WHITE_C);
	m_msgStop.SetGradientColor(ORANGE_C);
	m_msgStop.SetTextColor(BLACK_C);

	m_msgParity.SetFont(clsFunc.m_pFont[5]);
	m_msgParity.SetWindowText(_T("Parity"));
	m_msgParity.SetCenterText();
	m_msgParity.SetColor(WHITE_C);
	m_msgParity.SetGradientColor(ORANGE_C);
	m_msgParity.SetTextColor(BLACK_C);

	m_msgLastChar.SetFont(clsFunc.m_pFont[5]);
	m_msgLastChar.SetWindowText(_T("Last Char"));
	m_msgLastChar.SetCenterText();
	m_msgLastChar.SetColor(WHITE_C);
	m_msgLastChar.SetGradientColor(ORANGE_C);
	m_msgLastChar.SetTextColor(BLACK_C);
/*
	m_msgLastCharData.SetFont(clsFunc.m_pFont[5]);
	m_msgLastCharData.SetWindowText(_T("-"));
	m_msgLastCharData.SetCenterText();
	m_msgLastCharData.SetColor(WHITE_C);
	m_msgLastCharData.SetGradientColor(WHITE_C);
	m_msgLastCharData.SetTextColor(BLACK_C);
*/
	m_msgCutCount.SetFont(clsFunc.m_pFont[5]);
	m_msgCutCount.SetWindowText(_T("Cut Count"));
	m_msgCutCount.SetCenterText();
	m_msgCutCount.SetColor(WHITE_C);
	m_msgCutCount.SetGradientColor(ORANGE_C);
	m_msgCutCount.SetTextColor(BLACK_C);

	m_msgCutCountData.SetFont(clsFunc.m_pFont[5]);
	m_msgCutCountData.SetWindowText(_T("-"));
	m_msgCutCountData.SetCenterText();
	m_msgCutCountData.SetColor(WHITE_C);
	m_msgCutCountData.SetGradientColor(WHITE_C);
	m_msgCutCountData.SetTextColor(BLACK_C);

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

void CDialogBarcodeConfig::OnStnClickedMsgCutNumData()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString strTemp;

	int nKey = m_nCutCount;

	KeyPadI(0, 5, &nKey);

	m_nCutCount = nKey;
	strTemp.Format(_T("%d"), m_nCutCount);
	m_msgCutCountData.SetWindowText(strTemp);
}


void CDialogBarcodeConfig::OnStnClickedMsgTriggerData()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString strData = m_strTrigger;

	KeyBoard(&strData);

	m_strTrigger = strData;
	m_msgTriggerData.SetWindowText(m_strTrigger);
}
