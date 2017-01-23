// DialogInterface.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Interface.h"
#include "DialogInterface.h"
#include "afxdialogex.h"
#include ".\\Ctrl\\Variable.h"
#include ".\\Ctrl\\Comm.h"
#include "DialogBarcodeConfig.h"
#include "DialogBarcodeTest.h"
#include "DialogRfidConfig.h"
#include "DialogRfidTest.h"
#include "DialogVnRConfig.h"
#include "DialogVnRView.h"
#include "ClientRfid.h"
#include "VnRCtrl.h"
// CDialogInterface 대화 상자입니다.

//tagSERIAL_INFO  st_serial_info[5];
//tagRFID_INFO	st_rfid_info;

IMPLEMENT_DYNAMIC(CDialogInterface, CDialog)

//UINT CommunicationMessage(LPVOID lParam);
//UINT CommunicationMessage_2(LPVOID lParam);
//UINT CommunicationMessage_3(LPVOID lParam);
//UINT CommunicationMessage_4(LPVOID lParam);
//UINT CommunicationMessage_5(LPVOID lParam);
#define TM_COM1			100
#define TM_COM2			200
#define TM_COM3			300
#define TM_COM4			400
#define TM_COM5			500

CDialogInterface::CDialogInterface(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogInterface::IDD, pParent)
{
	int i;
	for (i=0; i<5; i++)
	{
		m_pCom[i] = NULL;
	}

	m_pBarcode	= NULL;
	m_pRfid		= NULL;

	m_pRfidC	= NULL;
	m_pVnRS		= NULL;

	m_bThread	= false;
}

CDialogInterface::~CDialogInterface()
{
	
}

void CDialogInterface::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_DATA,				m_listData);
	DDX_Control(pDX, IDC_GROUP_MAIN_INFO,		m_groupInfo);
	DDX_Control(pDX, IDC_BTN_HIDE,				m_btnHide);
}


BEGIN_MESSAGE_MAP(CDialogInterface, CDialog)
	ON_MESSAGE(WM_ICON_NOTIFY,					OnTrayNotification)
	ON_COMMAND(ID_VIEW,							&CDialogInterface::OnView)
	ON_BN_CLICKED(IDC_BTN_HIDE,					&CDialogInterface::OnBnClickedBtnHide)
	ON_COMMAND(ID_INTERFACE_BARCODE_CONFIG,		&CDialogInterface::OnInterfaceBarcodeConfig)
	ON_COMMAND(ID_INTERFACE_BARCODE_TEST,		&CDialogInterface::OnInterfaceBarcodeTest)
	ON_COMMAND(ID_INTERFACE_RFID_CONFIG,		&CDialogInterface::OnInterfaceRfconfig)
	ON_COMMAND(ID_INTERFACE_RFID_TEST,			&CDialogInterface::OnInterfaceRftest)
	ON_MESSAGE(WM_BARCODE_MSG_1,				BarcodeMessage1)
	ON_MESSAGE(WM_BARCODE_MSG_2,				BarcodeMessage2)
	ON_MESSAGE(WM_BARCODE_MSG_3,				BarcodeMessage3)
	ON_MESSAGE(WM_BARCODE_MSG_4,				BarcodeMessage4)
	ON_MESSAGE(WM_BARCODE_MSG_5,				BarcodeMessage5)
	ON_MESSAGE(WM_RFID_MSG,						RfidMessage)
	ON_MESSAGE(WM_CLIENT_MSG,					ClientRfidMessage)
	ON_MESSAGE(WM_SERVER_MSG,					ServerVnRMessage)
	ON_COMMAND(ID_INTERFACE_VNR_CONFIG, &CDialogInterface::OnInterfaceVnrConfig)
	ON_COMMAND(ID_INTERFACE_VNR_VIEW, &CDialogInterface::OnInterfaceVnrView)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CDialogInterface 메시지 처리기입니다.

BOOL CDialogInterface::Create(CWnd *pWnd)
{
	m_pWnd = pWnd;
	return CDialog::Create( CDialogInterface::IDD );
}

void CDialogInterface::BarcodeConfigSave()
{
	CString strSaveFile = _T("C:\\Interface\\Hardware.TXT");
	CString strTemp;
	CString strHead;

	int i;

	for (i=0; i<5; i++)
	{
		strHead.Format(_T("COM_PORT_%02d"), i);
		strTemp.Format(_T("%d"), st_serial_info[i].nSerialPort);
		:: WritePrivateProfileString(_T("BARCODE"), strHead, LPCTSTR(strTemp), strSaveFile);

		strHead.Format(_T("COM_BAUD_%02d"), i);
		strTemp.Format(_T("%d"), st_serial_info[i].nSerialBaudrate);
		:: WritePrivateProfileString(_T("BARCODE"), strHead, LPCTSTR(strTemp), strSaveFile);

		strHead.Format(_T("COM_DATA_%02d"), i);
		strTemp.Format(_T("%d"), st_serial_info[i].nSerialData);
		:: WritePrivateProfileString(_T("BARCODE"), strHead, LPCTSTR(strTemp), strSaveFile);

		strHead.Format(_T("COM_STOP_%02d"), i);
		strTemp.Format(_T("%d"), st_serial_info[i].nSerialStop);
		:: WritePrivateProfileString(_T("BARCODE"), strHead, LPCTSTR(strTemp), strSaveFile);

		strHead.Format(_T("COM_PARITY_%02d"), i);
		strTemp.Format(_T("%d"), st_serial_info[i].nSerialParity);
		:: WritePrivateProfileString(_T("BARCODE"), strHead, LPCTSTR(strTemp), strSaveFile);

		strHead.Format(_T("COM_SUB_%02d"), i);
		strTemp.Format(_T("%d"), st_serial_info[i].nDataSub);
		:: WritePrivateProfileString(_T("BARCODE"), strHead, LPCTSTR(strTemp), strSaveFile);

		strHead.Format(_T("COM_END_%02d_S"), i);
		strTemp.Format(_T("%d"), st_serial_info[i].byEnd[0]);
		:: WritePrivateProfileString(_T("BARCODE"), strHead, LPCTSTR(strTemp), strSaveFile);

		strHead.Format(_T("COM_END_%02d_R"), i);
		strTemp.Format(_T("%d"), st_serial_info[i].byEnd[1]);
		:: WritePrivateProfileString(_T("BARCODE"), strHead, LPCTSTR(strTemp), strSaveFile);

		strHead.Format(_T("COM_TRIGGER_%02d"), i);
		:: WritePrivateProfileString(_T("BARCODE"), strHead, LPCTSTR(st_serial_info[i].strOn), strSaveFile);
	}
}

void CDialogInterface::RfidConfigSave()
{
	CString strSaveFile = _T("C:\\Interface\\Hardware.TXT");
	CString strTemp;
	CString strHead;

	int i;

	//////////////////////////////////////////////////////////////////////////////////////////////////////
	:: WritePrivateProfileString(_T("RFID"), _T("IP"), LPCTSTR(st_client_info.strIp), strSaveFile);

	strTemp.Format(_T("%d"), st_client_info.nPort);
	:: WritePrivateProfileString(_T("RFID"), _T("PORT"), LPCTSTR(strTemp), strSaveFile);

	strTemp.Format(_T("%d"), st_rfid_info.nCh);
	:: WritePrivateProfileString(_T("RFID"), _T("CHANNEL"), LPCTSTR(strTemp), strSaveFile);

	strTemp.Format(_T("%d"), st_rfid_info.nTagNum);
	:: WritePrivateProfileString(_T("RFID"), _T("TAGNUM"), LPCTSTR(strTemp), strSaveFile);

	for (i=0; i<st_rfid_info.nTagNum; i++)
	{
		strHead.Format(_T("POS_%02d"), i);
		strTemp.Format(_T("%d"), st_rfid_info.nRfidPos[i]);
		:: WritePrivateProfileString(_T("RFID"), strHead, LPCTSTR(strTemp), strSaveFile);

		strHead.Format(_T("LENGTH_%02d"), i);
		strTemp.Format(_T("%d"), st_rfid_info.nRfidNum[i]);
		:: WritePrivateProfileString(_T("RFID"), strHead, LPCTSTR(strTemp), strSaveFile);

		strHead.Format(_T("TAG_%02d"), i);
		strTemp.Format(_T("%d"), st_rfid_info.nRfidTag[i]);
		:: WritePrivateProfileString(_T("RFID"), strHead, LPCTSTR(strTemp), strSaveFile);

		strHead.Format(_T("TITLE_%02d"), i);
		strTemp.Format(_T("%s"), st_rfid_info.strRfidTitle[i]);
		:: WritePrivateProfileString(_T("RFID"), strHead, LPCTSTR(strTemp), strSaveFile);
	}
}

void CDialogInterface::BarcodeConfigLoad()
{
	CString strLoadFile = _T("C:\\Interface\\Hardware.TXT");
	CString strTemp;
	CString strHead;

	int i;

	TCHAR chData[50];

	for (i=0; i<5; i++)
	{
		strHead.Format(_T("COM_PORT_%02d"), i);
		GetPrivateProfileString(_T("BARCODE"), strHead, _T(""), chData, sizeof(chData), strLoadFile);
		strTemp.Format(_T("%s"), chData);
		st_serial_info[i].nSerialPort = _wtoi(strTemp);

		strHead.Format(_T("COM_BAUD_%02d"), i);
		GetPrivateProfileString(_T("BARCODE"), strHead, _T(""), chData, sizeof(chData), strLoadFile);
		strTemp.Format(_T("%s"), chData);
		st_serial_info[i].nSerialBaudrate = _wtoi(strTemp);

		strHead.Format(_T("COM_DATA_%02d"), i);
		GetPrivateProfileString(_T("BARCODE"), strHead, _T(""), chData, sizeof(chData), strLoadFile);
		strTemp.Format(_T("%s"), chData);
		st_serial_info[i].nSerialData = _wtoi(strTemp);

		strHead.Format(_T("COM_STOP_%02d"), i);
		GetPrivateProfileString(_T("BARCODE"), strHead, _T(""), chData, sizeof(chData), strLoadFile);
		strTemp.Format(_T("%s"), chData);
		st_serial_info[i].nSerialStop = _wtoi(strTemp);

		strHead.Format(_T("COM_PARITY_%02d"), i);
		GetPrivateProfileString(_T("BARCODE"), strHead, _T(""), chData, sizeof(chData), strLoadFile);
		strTemp.Format(_T("%s"), chData);
		st_serial_info[i].nSerialParity = _wtoi(strTemp);

		strHead.Format(_T("COM_SUB_%02d"), i);
		GetPrivateProfileString(_T("BARCODE"), strHead, _T(""), chData, sizeof(chData), strLoadFile);
		strTemp.Format(_T("%s"), chData);
		st_serial_info[i].nDataSub = _wtoi(strTemp);

		strHead.Format(_T("COM_END_%02d_S"), i);
		GetPrivateProfileString(_T("BARCODE"), strHead, _T(""), chData, sizeof(chData), strLoadFile);
		strTemp.Format(_T("%s"), chData);
		st_serial_info[i].byEnd[0] = _wtoi(strTemp);

		strHead.Format(_T("COM_END_%02d_R"), i);
		GetPrivateProfileString(_T("BARCODE"), strHead, _T(""), chData, sizeof(chData), strLoadFile);
		strTemp.Format(_T("%s"), chData);
		st_serial_info[i].byEnd[1] = _wtoi(strTemp);

		strHead.Format(_T("COM_TRIGGER_%02d"), i);
		GetPrivateProfileString(_T("BARCODE"), strHead, _T(""), chData, sizeof(chData), strLoadFile);
		st_serial_info[i].strOn = (LPCTSTR)chData;
	}
}

void CDialogInterface::RfidConfigLoad()
{
	CString strLoadFile = _T("C:\\Interface\\Hardware.TXT");
	CString strTemp;
	CString strHead;

	int i;

	TCHAR chData[50];
	
	GetPrivateProfileString(_T("RFID"), _T("IP"), _T("192.168.0.101"), chData, sizeof(chData), strLoadFile);
	st_client_info.strIp = (LPCTSTR)chData;

	GetPrivateProfileString(_T("RFID"), _T("PORT"), _T("1470"), chData, sizeof(chData), strLoadFile);
	strTemp.Format(_T("%s"), chData);
	st_client_info.nPort = _wtoi(strTemp);

	GetPrivateProfileString(_T("RFID"), _T("CHANNEL"), _T("0"), chData, sizeof(chData), strLoadFile);
	strTemp.Format(_T("%s"), chData);
	st_rfid_info.nCh = _wtoi(strTemp);

	GetPrivateProfileString(_T("RFID"), _T("TAGNUM"), _T("17"), chData, sizeof(chData), strLoadFile);
	strTemp.Format(_T("%s"), chData);
	st_rfid_info.nTagNum = _wtoi(strTemp);

	for (i=0; i<st_rfid_info.nTagNum; i++)
	{
		strHead.Format(_T("POS_%02d"), i);
		GetPrivateProfileString(_T("RFID"), strHead, _T("0"), chData, sizeof(chData), strLoadFile);
		strTemp.Format(_T("%s"), chData);
		st_rfid_info.nRfidPos[i] = _wtoi(strTemp);

		strHead.Format(_T("LENGTH_%02d"), i);
		GetPrivateProfileString(_T("RFID"), strHead, _T("1"), chData, sizeof(chData), strLoadFile);
		strTemp.Format(_T("%s"), chData);
		st_rfid_info.nRfidNum[i] = _wtoi(strTemp);

		strHead.Format(_T("TAG_%02d"), i);
		GetPrivateProfileString(_T("RFID"), strHead, _T("0"), chData, sizeof(chData), strLoadFile);
		strTemp.Format(_T("%s"), chData);
		st_rfid_info.nRfidTag[i] = _wtoi(strTemp);

		strHead.Format(_T("TITLE_%02d"), i);
		GetPrivateProfileString(_T("RFID"), strHead, _T(""), chData, sizeof(chData), strLoadFile);
		st_rfid_info.strRfidTitle[i] = (LPCTSTR)chData;
	}
}

BOOL CDialogInterface::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	if (!m_TrayIcon.Create(this, 
				           WM_ICON_NOTIFY, 
						   _T("Barcode Interface Program"), 
					       NULL, 
						   IDR_MENU))
		return -1;
	
	// 아이콘 설정
	// 아이콘 아이디에 자신의 아이콘을 넣으세요...
	m_TrayIcon.SetIcon(IDI_ICON2);

	BarcodeConfigLoad();
	RfidConfigLoad();

	OnInitGroupBox();
	OnInitLabel();
	OnInitButton();
	OnInitDigit();

	if (m_bThread == false)
	{
		m_bThread	= true;
		m_thrHandle = AfxBeginThread(CommunicationMessage, this);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


BOOL CDialogInterface::DestroyWindow()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	int i;

	BarcodeConfigSave();
	RfidConfigSave();

	for (i=0; i<5; i++)
	{
		if (m_pCom[i] != NULL)
		{
			switch (i)
			{
				case 0:
					KillTimer(TM_COM1);
					break;

				case 1:
					KillTimer(TM_COM2);
					break;

				case 2:
					KillTimer(TM_COM3);
					break;

				case 3:
					KillTimer(TM_COM4);
					break;

				case 4:
					KillTimer(TM_COM5);
					break;
			}
			m_pCom[i]->CloseConnection();
			delete m_pCom[i];
			m_pCom[i] = NULL;
		}
	}

	if (m_pBarcode != NULL)
	{
		m_pBarcode->DestroyWindow();
		delete m_pBarcode;
		m_pBarcode = NULL;
	}

	if (m_pRfid != NULL)
	{
		m_pRfid->DestroyWindow();
		delete m_pRfid;
		m_pRfid = NULL;
	}

	if (m_pRfidC != NULL)
	{
		clsRfid.Close();
		
		delete m_pRfidC;
		m_pRfidC = NULL;
	}

	if (m_pVnRS != NULL)
	{
		delete m_pVnRS;
		m_pVnRS = NULL;
	}

	return CDialog::DestroyWindow();
}

LRESULT CDialogInterface::OnTrayNotification(WPARAM wParam, LPARAM lParam)
{
	return m_TrayIcon.OnTrayNotification(wParam, lParam);
}

void CDialogInterface::OnInitGroupBox()
{
	m_groupInfo.SetFont(clsFunc.OnLogFont(16));
	m_groupInfo.SetCatptionTextColor(BLUE_C);
	m_groupInfo.SetBorderColor(ORANGE_C);
	m_groupInfo.SetFontBold(TRUE);
	m_groupInfo.SetBackgroundColor(WINDOW_UP);
}

void CDialogInterface::OnInitLabel()
{
}

void CDialogInterface::OnInitButton()
{
	m_btnHide.SetBitmaps(IDC_BTN_HIDE, IDB_BITMAP_HIDE_DN, WINDOW_DN, IDB_BITMAP_HIDE_UP, WINDOW_UP);
	m_btnHide.SetColor(CButtonST::BTNST_COLOR_BK_IN, WINDOW_DN);
	m_btnHide.SetColor(CButtonST::BTNST_COLOR_BK_OUT, WINDOW_UP);
	m_btnHide.SetColor(CButtonST::BTNST_COLOR_BK_FOCUS, WINDOW_UP);
	m_btnHide.SetColor(CButtonST::BTNST_COLOR_FG_IN, BLACK_C);
	m_btnHide.SetColor(CButtonST::BTNST_COLOR_FG_OUT, BLUE_C);
	m_btnHide.SetColor(CButtonST::BTNST_COLOR_FG_FOCUS, BLUE_C);
	m_btnHide.SetFont(clsFunc.m_pFont[3]);
	m_btnHide.SetTooltipText(_T("Program Hide"));
}

void CDialogInterface::OnInitDigit()
{
}

void CDialogInterface::OnView()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	ShowWindow(SW_SHOW);
}

CString	CDialogInterface::OnCharToString(char chData[], int nLength)
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

void CDialogInterface::OnStringToChar(CString strData, char chData[])
{
	int nCnt;
	wchar_t *chBuf;

	chBuf = strData.GetBuffer(strData.GetLength());
	nCnt  = WideCharToMultiByte(CP_ACP, 0, chBuf, -1, NULL, 0, NULL, NULL);
	WideCharToMultiByte(CP_ACP, 0, chBuf, -1, chData, nCnt, 0, 0);
}

void CDialogInterface::OnListNormalMsgDisplay(CString strMsg)
{
	int nIndex;	

	CTime time;

	CString strTemp;

	if (m_strOldMsg == strMsg)
	{
		//2011.0504 추가 같은 메세지가 나오는 문제 처리 
		m_lNormalWaitTime[1] = GetCurrentTime();
		m_lNormalWaitTime[2] = m_lNormalWaitTime[1] - m_lNormalWaitTime[0];
		
		if(m_lNormalWaitTime[2] < 0)
		{
			m_lNormalWaitTime[0] = GetTickCount();
			return;
		}
		if (m_lNormalWaitTime[2] > 10000) 
		{
			//OK 파일로 내용 저장 
		}
	}
	
	if (strMsg != _T(""))
	{
		m_lNormalWaitTime[0]	= GetCurrentTime();
		
		m_strOldMsg				= strMsg;
	}
	else
	{
		return;
	}
	
	nIndex = m_listData.GetCount();

	if (nIndex > 100) m_listData.ResetContent();   // 리스트 박스 컨트롤에 추가된 모든 데이터 삭제 

	time	= CTime::GetCurrentTime();
	strTemp.Format(_T("[%04d %02d %02d %02d:%02d:%02d] "), time.GetYear(),
														   time.GetMonth(),
														   time.GetDay(),
														   time.GetHour(),
														   time.GetMinute(),
														   time.GetSecond());

	strTemp += strMsg;
	nIndex = m_listData.AddString(strTemp, RGB(0, 0, 255));  // 현재 입력된 정보 리스트 박스 컨트롤에 추가 
	m_listData.SetCurSel(nIndex);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// barcode

void CDialogInterface::RfidCreate()
{
	clsRfid.Open(this);
}

void CDialogInterface::RfidDelete()
{
	clsRfid.Close();
}

int	CDialogInterface::BarcodeCreate(int nBarcode)
{
	CString strMsg;

	int nRet;
	int nNum;
	
	nNum = nBarcode -1;
	if (nNum < 0) return RET_ERROR;

	if (m_pCom[nNum] != NULL)
	{
		delete m_pCom[nNum];
		m_pCom[nNum] = NULL;
	}

	m_pCom[nNum] = new CComm;
	if (st_serial_info[nNum].byEnd[1] == 0)
	{
		m_pCom[nNum]->m_byEnd = 0x00;
	}
	else if (st_serial_info[nNum].byEnd[1] == 1)
	{
		m_pCom[nNum]->m_byEnd = 0x0A;
	}
	else
	{
		m_pCom[nNum]->m_byEnd = 0x0D;
	}

	nRet = m_pCom[nNum]->OpenSerial(st_serial_info[nNum].nSerialPort,
									st_serial_info[nNum].nSerialBaudrate, 
									st_serial_info[nNum].nSerialData, 
									st_serial_info[nNum].nSerialStop, 
									st_serial_info[nNum].nSerialParity);

	if (nRet)
	{
		strMsg.Format(_T("Barcode : %02d Port : %02d Open Pass"), nBarcode,
															      st_serial_info[nNum].nSerialPort);

/*		if (m_bThread == false)
		{
			m_bThread			= true;
			m_thrHandle = AfxBeginThread(CommunicationMessage, this);
		}*/
		switch (nNum)
		{
			case 0:
				SetTimer(TM_COM1, 10, NULL);
				break;

			case 1:
				SetTimer(TM_COM2, 10, NULL);
				break;

			case 2:
				SetTimer(TM_COM3, 10, NULL);
				break;

			case 3:
				SetTimer(TM_COM4, 10, NULL);
				break;

			case 4:
				SetTimer(TM_COM5, 10, NULL);
				break;
		}
	}
	else 
	{
		strMsg.Format(_T("Barcode : %02d Port : %02d Open Fail"), nBarcode,
															      st_serial_info[nNum].nSerialPort);

		if (m_pCom[nNum] != NULL)
		{
			delete m_pCom[nNum];
			m_pCom[nNum] = NULL;
		}

		m_strBarcodeLastError = strMsg;
		if (m_pWnd != NULL)
		{
//			m_pWnd->SendMessage(WM_BARCODE_MSG_1 + (nBarcode - 1), BARCODE_ERROR, (LPARAM)&m_strBarcodeLastError);
		}
	}
	OnListNormalMsgDisplay(strMsg);

	return nRet;
}

void CDialogInterface::BarcodeDelete(int nBarcode)
{
	CString strMsg;

	int nNum;
	
	nNum = nBarcode -1;
	if (nNum < 0) return;

	if (m_pCom[nNum] != NULL)
	{
/*		m_bThread[nNum] = false;
		while(WaitForSingleObject(m_thrHandle[nNum], 5000) != WAIT_OBJECT_0)
		{
			if (m_thrHandle[nNum] == NULL) break;
			Sleep(0);
		}
*/
		m_pCom[nNum]->CloseConnection();

		switch (nNum)
		{
			case 0:
				KillTimer(TM_COM1);
				break;

			case 1:
				KillTimer(TM_COM2);
				break;

			case 2:
				KillTimer(TM_COM3);
				break;

			case 3:
				KillTimer(TM_COM4);
				break;

			case 4:
				KillTimer(TM_COM5);
				break;
		}

		delete m_pCom[nNum];
		m_pCom[nNum] = NULL;
	}

	strMsg.Format(_T("Barcode : %02d Port : %02d Close"), nBarcode,
													      st_serial_info[nNum].nSerialPort);
	
	OnListNormalMsgDisplay(strMsg);
}

void CDialogInterface::BarcodeReadData(int nBarcode)
{
	CString strMsg;

	BYTE byData[100];

	int  nLength;
	int nNum;
	
	nNum = nBarcode -1;
	if (nNum < 0) return;

	if (m_pCom[nNum] != NULL)
	{
		nLength = st_serial_info[nNum].strOn.GetLength();

		m_pCom[nNum]->Empty(); // com buffer 비우기

		OnStringToChar(st_serial_info[nNum].strOn, (char*)byData);

		if (st_serial_info[nNum].byEnd[0] == 0)
		{
			m_pCom[nNum]->WriteCommBlock((LPSTR)byData, nLength);
		}
		else if (st_serial_info[nNum].byEnd[0] == 1)
		{
			byData[nLength] = 0x0A;
			m_pCom[nNum]->WriteCommBlock((LPSTR)byData, nLength + 1);
		}
		else
		{
			byData[nLength] = 0x0D;
			m_pCom[nNum]->WriteCommBlock((LPSTR)byData, nLength + 1);
		}

		strMsg.Format(_T("Barcode : %02d Trigger : %s"), nBarcode,
														 st_serial_info[nNum].strOn);
	}
	else
	{
		strMsg.Format(_T("Barcode : %02d Open Fail"), nBarcode);
		m_strBarcodeLastError = strMsg;
		if (m_pWnd != NULL)
		{
			m_pWnd->SendMessage(WM_BARCODE_MSG_1 + (nBarcode - 1), BARCODE_ERROR, (LPARAM)&m_strBarcodeLastError);
		}
	}

	OnListNormalMsgDisplay(strMsg);
}

void CDialogInterface::BarcodeReadData(int nBarcode, CString strTrigger)
{
	CString strMsg;

	BYTE byData[100];

	int  nLength;
	int nNum;
	
	nNum = nBarcode -1;
	if (nNum < 0) return;

	if (m_pCom[nNum] != NULL)
	{
		nLength = strTrigger.GetLength();

		m_pCom[nNum]->Empty(); // com buffer 비우기

		OnStringToChar(strTrigger, (char*)byData);

		if (st_serial_info[nNum].byEnd[0] == 0)
		{
			m_pCom[nNum]->WriteCommBlock((LPSTR)byData, nLength);
		}
		else if (st_serial_info[nNum].byEnd[0] == 1)
		{
			byData[nLength] = 0x0A;
			m_pCom[nNum]->WriteCommBlock((LPSTR)byData, nLength + 1);
		}
		else
		{
			byData[nLength] = 0x0D;
			m_pCom[nNum]->WriteCommBlock((LPSTR)byData, nLength + 1);
		}

		strMsg.Format(_T("Barcode : %02d Trigger : %s"), nBarcode,
														 st_serial_info[nNum].strOn);
	}
	else
	{
		strMsg.Format(_T("Barcode : %02d Open Fail"), nBarcode);
		m_strBarcodeLastError = strMsg;
		if (m_pWnd != NULL)
		{
			m_pWnd->SendMessage(WM_BARCODE_MSG_1 + (nBarcode - 1), BARCODE_ERROR, (LPARAM)&m_strBarcodeLastError);
		}
	}

	OnListNormalMsgDisplay(strMsg);
}

void CDialogInterface::Communication_1()
{
	int nNum = 0;
	int nLength;

	BYTE byData[100];

	CString strMsg[3];

	if (m_pCom[nNum] != NULL)
	{
		if (m_pCom[nNum]->m_bRevFlag)
		{
			nLength = m_pCom[nNum]->m_nLength;

			if (nLength > 0)
			{
				m_pCom[nNum]->ReadData(byData, nLength);

				strMsg[0] = OnCharToString((char*)byData, sizeof(byData));
				strMsg[1] = strMsg[0].Mid(0, nLength - st_serial_info[nNum].nDataSub);

				strMsg[2].Format(_T("Barcode : %02d Data : %s"), nNum + 1, strMsg[1]);

				if (m_pWnd != NULL)
				{
					m_pWnd->SendMessage(WM_BARCODE_MSG_1, BARCODE_DATA_1, (LPARAM)&strMsg[2]);
				}
				OnListNormalMsgDisplay(strMsg[2]);
			}
		}
	}
}

void CDialogInterface::Communication_2()
{
	int nNum = 1;
	int nLength;

	BYTE byData[100];

	CString strMsg[3];

	if (m_pCom[nNum] != NULL)
	{
		if (m_pCom[nNum]->m_bRevFlag)
		{
			nLength = m_pCom[nNum]->m_nLength;

			if (nLength > 0)
			{
				m_pCom[nNum]->ReadData(byData, nLength);

				strMsg[0] = OnCharToString((char*)byData, sizeof(byData));
				strMsg[1] = strMsg[0].Mid(0, nLength - st_serial_info[nNum].nDataSub);

				strMsg[2].Format(_T("Barcode : %02d Data : %s"), nNum + 1, strMsg[1]);

				if (m_pWnd != NULL)
				{
					m_pWnd->SendMessage(WM_BARCODE_MSG_2, BARCODE_DATA_1, (LPARAM)&strMsg[2]);
				}
				OnListNormalMsgDisplay(strMsg[2]);
			}
		}
	}
}

void CDialogInterface::Communication_3()
{
	int nNum = 2;
	int nLength;

	BYTE byData[100];

	CString strMsg[3];

	if (m_pCom[nNum] != NULL)
	{
		if (m_pCom[nNum]->m_bRevFlag)
		{
			nLength = m_pCom[nNum]->m_nLength;

			if (nLength > 0)
			{
				m_pCom[nNum]->ReadData(byData, nLength);

				strMsg[0] = OnCharToString((char*)byData, sizeof(byData));
				strMsg[1] = strMsg[0].Mid(0, nLength - st_serial_info[nNum].nDataSub);

				strMsg[2].Format(_T("Barcode : %02d Data : %s"), nNum + 1, strMsg[1]);

				if (m_pWnd != NULL)
				{
					m_pWnd->SendMessage(WM_BARCODE_MSG_3, BARCODE_DATA_1, (LPARAM)&strMsg[2]);
				}
				OnListNormalMsgDisplay(strMsg[2]);
			}
		}
	}
}

void CDialogInterface::Communication_4()
{
	int nNum = 3;
	int nLength;

	BYTE byData[100];

	CString strMsg[3];

	if (m_pCom[nNum] != NULL)
	{
		if (m_pCom[nNum]->m_bRevFlag)
		{
			nLength = m_pCom[nNum]->m_nLength;

			if (nLength > 0)
			{
				m_pCom[nNum]->ReadData(byData, nLength);

				strMsg[0] = OnCharToString((char*)byData, sizeof(byData));
				strMsg[1] = strMsg[0].Mid(0, nLength - st_serial_info[nNum].nDataSub);

				strMsg[2].Format(_T("Barcode : %02d Data : %s"), nNum + 1, strMsg[1]);

				if (m_pWnd != NULL)
				{
					m_pWnd->SendMessage(WM_BARCODE_MSG_4, BARCODE_DATA_1, (LPARAM)&strMsg[2]);
				}
				OnListNormalMsgDisplay(strMsg[2]);
			}
		}
	}
}

void CDialogInterface::Communication_5()
{
	int nNum = 4;
	int nLength;

	BYTE byData[100];

	CString strMsg[3];

	if (m_pCom[nNum] != NULL)
	{
		if (m_pCom[nNum]->m_bRevFlag)
		{
			nLength = m_pCom[nNum]->m_nLength;

			if (nLength > 0)
			{
				m_pCom[nNum]->ReadData(byData, nLength);

				strMsg[0] = OnCharToString((char*)byData, sizeof(byData));
				strMsg[1] = strMsg[0].Mid(0, nLength - st_serial_info[nNum].nDataSub);

				strMsg[2].Format(_T("Barcode : %02d Data : %s"), nNum + 1, strMsg[1]);

				if (m_pWnd != NULL)
				{
					m_pWnd->SendMessage(WM_BARCODE_MSG_5, BARCODE_DATA_1, (LPARAM)&strMsg[2]);
				}
				OnListNormalMsgDisplay(strMsg[2]);
			}
		}
	}
}


UINT CommunicationMessage(LPVOID lParam)
{
	CDialogInterface *pMsg = (CDialogInterface *)lParam;

	int nNum = 0;


	while(pMsg->m_bThread)
	{
		pMsg->Communication_1();
		pMsg->Communication_2();
		pMsg->Communication_3();
		pMsg->Communication_4();
		pMsg->Communication_5();
	}

	pMsg->m_thrHandle = NULL;

	return 0;
}

UINT CommunicationMessage_2(LPVOID lParam)
{
	CDialogInterface *pMsg = (CDialogInterface *)lParam;

	int nNum = 1;

/*
	while(pMsg->m_bThread[nNum])
	{
		switch(pMsg->m_nWaitTimeStep[nNum])
		{
			case 0:
				pMsg->m_dwWaitTime[nNum][0] = GetTickCount();

				pMsg->m_nWaitTimeStep[nNum] = 100;
				break;

			case 100:
				pMsg->m_dwWaitTime[nNum][1] = GetTickCount();
				pMsg->m_dwWaitTime[nNum][2] = pMsg->m_dwWaitTime[nNum][1] - pMsg->m_dwWaitTime[nNum][0];

				if (pMsg->m_dwWaitTime[nNum][2] <= 0)
				{
					pMsg->m_dwWaitTime[nNum][0] = GetTickCount();
					break;
				}

				if (pMsg->m_dwWaitTime[nNum][2] > 1000)
				{
					pMsg->Communication_2();

					pMsg->m_nWaitTimeStep[nNum] = 0;
				}
				break;
		}
	}

	pMsg->m_thrHandle[nNum] = NULL;
*/
	return 0;
}

UINT CommunicationMessage_3(LPVOID lParam)
{
	CDialogInterface *pMsg = (CDialogInterface *)lParam;

	int nNum = 2;
/*
	while(pMsg->m_bThread[nNum])
	{
		switch(pMsg->m_nWaitTimeStep[nNum])
		{
			case 0:
				pMsg->m_dwWaitTime[nNum][0] = GetTickCount();

				pMsg->m_nWaitTimeStep[nNum] = 100;
				break;

			case 100:
				pMsg->m_dwWaitTime[nNum][1] = GetTickCount();
				pMsg->m_dwWaitTime[nNum][2] = pMsg->m_dwWaitTime[nNum][1] - pMsg->m_dwWaitTime[nNum][0];

				if (pMsg->m_dwWaitTime[nNum][2] <= 0)
				{
					pMsg->m_dwWaitTime[nNum][0] = GetTickCount();
					break;
				}

				if (pMsg->m_dwWaitTime[nNum][2] > 1000)
				{
					pMsg->Communication_3();

					pMsg->m_nWaitTimeStep[nNum] = 0;
				}
				break;
		}
	}

	pMsg->m_thrHandle[nNum] = NULL;
	*/
	return 0;
}

UINT CommunicationMessage_4(LPVOID lParam)
{
	CDialogInterface *pMsg = (CDialogInterface *)lParam;

	int nNum = 3;
/*
	while(pMsg->m_bThread[nNum])
	{
		switch(pMsg->m_nWaitTimeStep[nNum])
		{
			case 0:
				pMsg->m_dwWaitTime[nNum][0] = GetTickCount();

				pMsg->m_nWaitTimeStep[nNum] = 100;
				break;

			case 100:
				pMsg->m_dwWaitTime[nNum][1] = GetTickCount();
				pMsg->m_dwWaitTime[nNum][2] = pMsg->m_dwWaitTime[nNum][1] - pMsg->m_dwWaitTime[nNum][0];

				if (pMsg->m_dwWaitTime[nNum][2] <= 0)
				{
					pMsg->m_dwWaitTime[nNum][0] = GetTickCount();
					break;
				}

				if (pMsg->m_dwWaitTime[nNum][2] > 1000)
				{
					pMsg->Communication_4();

					pMsg->m_nWaitTimeStep[nNum] = 0;
				}
				break;
		}
	}

	pMsg->m_thrHandle[nNum] = NULL;
*/
	return 0;
}

UINT CommunicationMessage_5(LPVOID lParam)
{
	CDialogInterface *pMsg = (CDialogInterface *)lParam;

	int nNum = 4;
/*
	while(pMsg->m_bThread[nNum])
	{

		switch(pMsg->m_nWaitTimeStep[nNum])
		{
			case 0:
				pMsg->m_dwWaitTime[nNum][0] = GetTickCount();

				pMsg->m_nWaitTimeStep[nNum] = 100;
				break;

			case 100:
				pMsg->m_dwWaitTime[nNum][1] = GetTickCount();
				pMsg->m_dwWaitTime[nNum][2] = pMsg->m_dwWaitTime[nNum][1] - pMsg->m_dwWaitTime[nNum][0];

				if (pMsg->m_dwWaitTime[nNum][2] <= 0)
				{
					pMsg->m_dwWaitTime[nNum][0] = GetTickCount();
					break;
				}

				if (pMsg->m_dwWaitTime[nNum][2] > 1000)
				{
					pMsg->Communication_5();

					pMsg->m_nWaitTimeStep[nNum] = 0;
				}
				break;
		}

		pMsg->Communication_5();
	}

	pMsg->m_thrHandle[nNum] = NULL;
*/
	return 0;
}


void CDialogInterface::OnBnClickedBtnHide()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	ShowWindow(SW_HIDE);
}


void CDialogInterface::OnInterfaceBarcodeConfig()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CDialogBarcodeConfig dlgBarcode;

	int i;

	if (dlgBarcode.DoModal() == IDOK)
	{
		for (i=0; i<5; i++)
		{
			if (m_pCom[i] != NULL)
			{
				BarcodeDelete(i);
				BarcodeCreate(i);
			}
		}
	}
}


void CDialogInterface::OnInterfaceBarcodeTest()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	if(m_pBarcode == NULL)
	{
		m_pBarcode					= new CDialogBarcodeTest;
		m_pBarcode->Create(this);
		m_pBarcode->ShowWindow(SW_SHOW);
	}
	else 
	{
		m_pBarcode->SetFocus();
	}
}


void CDialogInterface::OnInterfaceRfconfig()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CDialogRfidConfig dlgRfid;

	if (dlgRfid.DoModal() == IDOK)
	{
	}
}


void CDialogInterface::OnInterfaceRftest()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	if(m_pRfid == NULL)
	{
		m_pRfid					= new CDialogRfidTest;
		m_pRfid->Create(this);
		m_pRfid->ShowWindow(SW_SHOW);
	}
	else 
	{
		m_pRfid->SetFocus();
	}
}

LRESULT CDialogInterface::BarcodeMessage1(WPARAM wParam, LPARAM lParam)
{
	CString *strTrigger;

	switch(wParam)
	{
		case BARCODE_DATA_1:
			break;

		case BARCODE_ERROR_1:
			break;
		
		case BARCODE_TRIGGER_1_1:
			BarcodeReadData(1);
			break;

		case BARCODE_TRIGGER_1_2:
			strTrigger = (CString*)lParam;	
			BarcodeReadData(1, *strTrigger);
			break;

		case BARCODE_DELETE:
			if (m_pBarcode != NULL)
			{
				m_pBarcode->DestroyWindow();

				delete m_pBarcode;
				m_pBarcode = NULL;
			}
			break;
	}
	return 0;
}


LRESULT CDialogInterface::BarcodeMessage2(WPARAM wParam, LPARAM lParam)
{
	CString *strTrigger;

	switch(wParam)
	{
		case BARCODE_DATA_1:
			break;

		case BARCODE_ERROR_1:
			break;
		
		case BARCODE_TRIGGER_1_1:
			BarcodeReadData(2);
			break;

		case BARCODE_TRIGGER_1_2:
			strTrigger = (CString*)lParam;	
			BarcodeReadData(2, *strTrigger);
			break;

		case BARCODE_DELETE:
			if (m_pBarcode != NULL)
			{
				m_pBarcode->DestroyWindow();

				delete m_pBarcode;
				m_pBarcode = NULL;
			}
			break;
	}
	return 0;
}

LRESULT CDialogInterface::BarcodeMessage3(WPARAM wParam, LPARAM lParam)
{
	CString *strTrigger;

	switch(wParam)
	{
		case BARCODE_DATA_1:
			break;

		case BARCODE_ERROR_1:
			break;
		
		case BARCODE_TRIGGER_1_1:
			BarcodeReadData(3);
			break;

		case BARCODE_TRIGGER_1_2:
			strTrigger = (CString*)lParam;	
			BarcodeReadData(3, *strTrigger);
			break;

		case BARCODE_DELETE:
			if (m_pBarcode != NULL)
			{
				m_pBarcode->DestroyWindow();

				delete m_pBarcode;
				m_pBarcode = NULL;
			}
			break;
	}
	return 0;
}

LRESULT CDialogInterface::BarcodeMessage4(WPARAM wParam, LPARAM lParam)
{
	CString *strTrigger;

	switch(wParam)
	{
		case BARCODE_DATA_1:
			break;

		case BARCODE_ERROR_1:
			break;
		
		case BARCODE_TRIGGER_1_1:
			BarcodeReadData(4);
			break;

		case BARCODE_TRIGGER_1_2:
			strTrigger = (CString*)lParam;	
			BarcodeReadData(4, *strTrigger);
			break;

		case BARCODE_DELETE:
			if (m_pBarcode != NULL)
			{
				m_pBarcode->DestroyWindow();

				delete m_pBarcode;
				m_pBarcode = NULL;
			}
			break;
	}
	return 0;
}

LRESULT CDialogInterface::BarcodeMessage5(WPARAM wParam, LPARAM lParam)
{
	CString *strTrigger;

	switch(wParam)
	{
		case BARCODE_DATA_1:
			break;

		case BARCODE_ERROR_1:
			break;
		
		case BARCODE_TRIGGER_1_1:
			BarcodeReadData(5);
			break;

		case BARCODE_TRIGGER_1_2:
			strTrigger = (CString*)lParam;	
			BarcodeReadData(5, *strTrigger);
			break;

		case BARCODE_DELETE:
			if (m_pBarcode != NULL)
			{
				m_pBarcode->DestroyWindow();

				delete m_pBarcode;
				m_pBarcode = NULL;
			}
			break;
	}
	return 0;
}

LRESULT CDialogInterface::ClientRfidMessage(WPARAM wParam, LPARAM lParam)
{
	int nLength;

	CString strMsg;

	switch(wParam)
	{
		case CLIENT_CONNECT:
			if (m_pRfidC != NULL)
			{
				st_client_info.nConnect = NO;
		
				delete m_pRfidC;
				m_pRfidC = NULL;

				m_pRfidC = new CClientSocket();
				m_pRfidC->Create();
	
				m_pRfidC->OnOpen(this, 0);

				if (m_pRfidC->Connect(st_client_info.strIp, st_client_info.nPort))
				{
					delete m_pRfidC;
					m_pRfidC = NULL;

					m_strRfidLastError = _T("RFID Connect Error.");
					if (m_pWnd != NULL)
					{
						m_pWnd->SendMessage(WM_RFID_MSG, RFID_ERROR, (LPARAM)&m_strRfidLastError);
					}
					OnListNormalMsgDisplay(m_strRfidLastError);

					return 0;
				}
				else
				{
					OnListNormalMsgDisplay(m_strRfidLastError);
				}
			}
			else
			{
				st_client_info.nConnect = NO;
		
				m_pRfidC = new CClientSocket();
				m_pRfidC->Create();
	
				m_pRfidC->OnOpen(this, 0);

				if (m_pRfidC->Connect(st_client_info.strIp, st_client_info.nPort))
				{
					delete m_pRfidC;
					m_pRfidC = NULL;

					m_strRfidLastError = _T("RFID Connect Error.");
					if (m_pWnd != NULL)
					{
						m_pWnd->SendMessage(WM_RFID_MSG, RFID_ERROR, (LPARAM)&m_strRfidLastError);
					}
					OnListNormalMsgDisplay(m_strRfidLastError);

					return 0;
				}
				else
				{
					OnListNormalMsgDisplay(m_strRfidLastError);
				}
			}
			break;

		case CLIENT_CLOSE:
			if (m_pRfidC != NULL)
			{
				st_client_info.nConnect = NO;

				delete m_pRfidC;
				m_pRfidC = NULL;

				OnListNormalMsgDisplay(_T("RFID Close."));
			}
			break;

		case CLIENT_SEND:
			if (st_client_info.nConnect == YES)
			{
				if (m_pRfidC == NULL) return 0;

				OnStringToChar(st_client_info.strSend, st_client_info.chSend);
				nLength = st_client_info.strSend.GetLength();

				m_pRfidC->Send(st_client_info.chSend, nLength);

				strMsg = _T("[RFID SEND] ");
				strMsg += st_client_info.strSend;
				OnListNormalMsgDisplay(strMsg);
			}
			break;

		case CLIENT_REV:
			clsRfid.RfidTagData(st_client_info.strRev);

			strMsg = _T("[RFID RECIVE] ");
			strMsg += st_client_info.strRev;

			OnListNormalMsgDisplay(strMsg);
			break;

		case CLIENT_ACCEPT:
			if (lParam != 0)
			{
				st_client_info.nConnect = NO;
	
				delete m_pRfidC;
				m_pRfidC = NULL;

				m_strRfidLastError = _T("RFID Connect Error.");
				if (m_pWnd != NULL)
				{
					m_pWnd->SendMessage(WM_RFID_MSG, RFID_ERROR, (LPARAM)&m_strRfidLastError);
				}
				OnListNormalMsgDisplay(m_strRfidLastError);
				
				return 0;
			}
			else
			{
				st_client_info.nConnect = YES;

				OnListNormalMsgDisplay(m_strRfidLastError);
			}
			break;
	}

	return 0;
}

LRESULT CDialogInterface::RfidMessage(WPARAM wParam, LPARAM lParam)
{
	CString strMsg;

	int nNum;

	switch(wParam)
	{
		case RFID_DATA:
			if (lParam <= 0) nNum = 1;
			else nNum = lParam;

			if (m_pRfid != NULL)
			{
				m_pRfid->DataDisplay(nNum - 1);
			}
			break;

		case RFID_ERROR:
			m_strRfidLastError = clsRfid.m_strErrorMsg;
			if (m_pWnd != NULL)
			{
				m_pWnd->SendMessage(WM_RFID_MSG, RFID_ERROR, (LPARAM)&m_strRfidLastError);
			}
			break;

		case RFID_READ:
			if (lParam <= 0) nNum = 1;
			else nNum = lParam;

			clsRfid.ReadAllData(nNum);
			break;

		case RFID_WRITE:
			if (lParam <= 0) nNum = 1;
			else nNum = lParam;

			clsRfid.WriteAllData(lParam, st_rfid_info.strRfidData[nNum - 1]);
			break;

		case RFID_WRITE_GOOD:
			strMsg.Format(_T("CH=%02d WRITE=OK"), lParam);
			if (m_pWnd != NULL)
			{
				m_pWnd->SendMessage(WM_RFID_MSG, RFID_WRITE_GOOD, (LPARAM)&strMsg);
			}
			break;
	
		case RFID_WRITE_NG:
			m_strRfidLastError = clsRfid.m_strErrorMsg;
			strMsg.Format(_T("CH=%02d WRITE=NG MSG=%s"), lParam, m_strRfidLastError);
			if (m_pWnd != NULL)
			{
				m_pWnd->SendMessage(WM_RFID_MSG, RFID_WRITE_NG, (LPARAM)&strMsg);
			}
			break;
	
		case RFID_READ_GOOD:
			if (m_pRfid != NULL)
			{
				if (lParam < 0) nNum = 0;
				else nNum = lParam - 1;

				m_pRfid->DataDisplay(nNum);
			}
			else
			{
				strMsg.Format(_T("CH=%02d READ=OK %s"), lParam, st_rfid_info.strRfidTag);
				if (m_pWnd != NULL)
				{
					m_pWnd->SendMessage(WM_RFID_MSG, RFID_READ_GOOD, (LPARAM)&strMsg);
				}
			}
			break;
	
		case RFID_READ_NG:
			m_strRfidLastError = clsRfid.m_strErrorMsg;
			strMsg.Format(_T("CH=%02d READ=NG MSG=%s"), lParam, m_strRfidLastError);

			if (m_pWnd != NULL)
			{
				m_pWnd->SendMessage(WM_RFID_MSG, RFID_READ_NG, (LPARAM)&strMsg);
			}
			break;	

		case RFID_DELETE:
			if (m_pRfid != NULL)
			{
				delete m_pRfid;
				m_pRfid = NULL;
			}
			break;
	}

	return 0;
}

void CDialogInterface::RfidTagInfo(int nItem, int nStart, int nNum, int nWriteYesNo)
{
}

void CDialogInterface::RfidReadData(int nChan, int nItem, CString *strMsg)
{
/*	
	CString strMsg;

	strMsg.Format(_T("CH=%02d %s=%s"), nChan, st_rfid_info.strRfidTitle[nItem], st_rfid_info.strRfidData[nChan][nItem]);
	
	if (m_pWnd != NULL)
	{
		m_pWnd->SendMessage(WM_RFID_MSG, RFID_ERROR, (LPARAM)&strMsg);
	}
*/
	st_rfid_info.strRfidData[nChan][0] = _T("ABCD");
	st_rfid_info.strRfidData[nChan][10]= _T("1234");

	*strMsg = st_rfid_info.strRfidData[nChan][nItem];
}

void CDialogInterface::RfidReadAllData(int nChan, CString *strMsg)
{
/*
	CString strMsg;

	strMsg = st_rfid_info.strRfidTag;

	if (m_pWnd != NULL)
	{
		m_pWnd->SendMessage(WM_RFID_MSG, RFID_ERROR, (LPARAM)&strMsg);
	}
	*/
	int i;

	st_rfid_info.strRfidData[nChan][0] = _T("ABCD");
	st_rfid_info.strRfidData[nChan][10]= _T("1234");

	for (i=0; i<st_rfid_info.nTagNum; i++)
	{
		strMsg[i] = st_rfid_info.strRfidData[nChan][i];
	}
}

void CDialogInterface::RfidLastErrorMsg(CString *strMsg)
{
/*
	CString strMsg;

	strMsg.Format(_T("%s"), m_strRfidLastError);

	if (m_pWnd != NULL)
	{
		m_pWnd->SendMessage(WM_RFID_MSG, RFID_ERROR, (LPARAM)&strMsg);
	}
*/
	*strMsg = m_strRfidLastError;
}

void CDialogInterface::RfidReadTag(int nChan)
{
	clsRfid.ReadAllData(nChan);
}

void CDialogInterface::RfidWriteData(int nChan, int nItem, CString strMsg)
{
	clsRfid.WriteData(nChan, nItem, strMsg);
}

void CDialogInterface::RfidWriteAllData(int nChan, CString *strMsg)
{
	clsRfid.WriteAllData(nChan, strMsg);
}

void CDialogInterface::BarcodeLastErrorMsg(CString *strMsg)
{
	*strMsg = m_strBarcodeLastError;
}

void CDialogInterface::VnRCreate()
{
	VnRConfigLoad();

	clsVnR.Open(this);
	SendMessage(WM_SERVER_MSG, SERVER_CONNECT);
}

void CDialogInterface::VnRDelete()
{
	VnRConfigSave();
}

void CDialogInterface::VnRConfigLoad()
{
	CString strLoadFile = _T("C:\\Interface\\Hardware.TXT");
	CString strTemp;

	TCHAR chData[50];
	
	GetPrivateProfileString(_T("VnR"), _T("PORT"), _T("10000"), chData, sizeof(chData), strLoadFile);
	strTemp.Format(_T("%s"), chData);
	st_server_info.nPort = _wtoi(strTemp);

	GetPrivateProfileString(_T("VnR"), _T("CHAN_COUNT"), _T("1"), chData, sizeof(chData), strLoadFile);
	strTemp.Format(_T("%s"), chData);
	st_VnR_info.nChan = _wtoi(strTemp);
}


void CDialogInterface::VnRConfigSave()
{
	CString strSaveFile = _T("C:\\Interface\\Hardware.TXT");
	CString strTemp;

	strTemp.Format(_T("%d"), st_server_info.nPort);
	:: WritePrivateProfileString(_T("VnR"), _T("PORT"), LPCTSTR(strTemp), strSaveFile);

	strTemp.Format(_T("%d"), st_VnR_info.nChan);
	:: WritePrivateProfileString(_T("VnR"), _T("CHAN_COUNT"), LPCTSTR(strTemp), strSaveFile);
}


void CDialogInterface::VnRReadData(int nChan, double *dVolt, double *dResistance)
{
	*dVolt			= st_VnR_info.dVolt[nChan];
	*dResistance	= st_VnR_info.dResistance[nChan];
}

LRESULT CDialogInterface::ServerVnRMessage(WPARAM wParam, LPARAM lParam)
{
	int i;
	int nLength;
	
	CString strMsg;

	switch(wParam)
	{
		case SERVER_CONNECT:
			if (m_pVnRS != NULL)
			{
				m_pVnRS->OnClose();

				delete m_pVnRS;
				m_pVnRS = NULL;
			}

			// sevrer 생성
			m_pVnRS = new CServerSocket;

			// Tcp/IP server open
			if (m_pVnRS->OnOpen(this, st_server_info.nPort, 0))
			{
				strMsg = _T("[VnR] ");
				strMsg += _T("TTS_VNR_NETWORK Server Open Success.");

				OnListNormalMsgDisplay(strMsg);
			}
			else
			{
				strMsg = _T("[VnR] ");
				strMsg += _T("TTS_VNR_NETWORK Server Open Error.");

				OnListNormalMsgDisplay(strMsg);

				delete m_pVnRS;
				m_pVnRS = NULL;
			}
			break;

		case SERVER_CLOSE:
			if (m_pVnRS != NULL)
			{
				m_pVnRS->OnCloseClient(lParam);
			}
			break;

		case SERVER_REV:
			strMsg = _T("[VnR] ");
			strMsg += st_server_info.strRev;
			OnListNormalMsgDisplay(strMsg);

			clsVnR.OnDataReceive(st_server_info.strRev);
			break;

		case SERVER_SEND:
			for (i=0; i<MAX_USER; i++)
			{
				if (m_pVnRS != NULL)
				{
					// client가 server에 접속중이면 
					if (m_pVnRS->m_pClient[i] != NULL)
					{
						OnStringToChar(st_server_info.strSend, st_server_info.chSend);
						nLength = st_server_info.strSend.GetLength();

						m_pVnRS->m_pClient[i]->Send(st_server_info.chSend, nLength);
					}
				}
			}
			break;

		case SERVER_ACCEPT:
			clsVnR.OnMakeTime();
			break;
	}

	return 0;
}

void CDialogInterface::OnInterfaceVnrConfig()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CDialogVnRConfig dlgConfig;

	SendMessage(WM_SERVER_MSG, SERVER_CLOSE);

	if (dlgConfig.DoModal() == IDOK)
	{
		SendMessage(WM_SERVER_MSG, SERVER_CONNECT);
	}
}


void CDialogInterface::OnInterfaceVnrView()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CDialogVnRView dlgView;

	dlgView.DoModal();
}


void CDialogInterface::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	switch (nIDEvent)
	{
		case TM_COM1:
			Communication_1();
			break;

		case TM_COM2:
			Communication_2();
			break;

		case TM_COM3:
			Communication_3();
			break;

		case TM_COM4:
			Communication_4();
			break;

		case TM_COM5:
			Communication_5();
			break;
	}
	CDialog::OnTimer(nIDEvent);
}
