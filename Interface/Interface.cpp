// Interface.cpp : 해당 DLL의 초기화 루틴을 정의합니다.
//

#include "stdafx.h"
#include "Interface.h"
#include ".\\ctrl\\Variable.h"
#include "DialogInterface.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//TODO: 이 DLL이 MFC DLL에 대해 동적으로 링크되어 있는 경우
//		MFC로 호출되는 이 DLL에서 내보내지는 모든 함수의
//		시작 부분에 AFX_MANAGE_STATE 매크로가
//		들어 있어야 합니다.
//
//		예:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// 일반적인 함수 본문은 여기에 옵니다.
//		}
//
//		이 매크로는 MFC로 호출하기 전에
//		각 함수에 반드시 들어 있어야 합니다.
//		즉, 매크로는 함수의 첫 번째 문이어야 하며 
//		개체 변수의 생성자가 MFC DLL로
//		호출할 수 있으므로 개체 변수가 선언되기 전에
//		나와야 합니다.
//
//		자세한 내용은
//		MFC Technical Note 33 및 58을 참조하십시오.
//

// CInterfaceApp

BEGIN_MESSAGE_MAP(CInterfaceApp, CWinApp)
END_MESSAGE_MAP()


// CInterfaceApp 생성

CInterfaceApp::CInterfaceApp()
{
	// TODO: 여기에 생성 코드를 추가합니다.
	// InitInstance에 모든 중요한 초기화 작업을 배치합니다.
}


// 유일한 CInterfaceApp 개체입니다.

CInterfaceApp theApp;


// CInterfaceApp 초기화

BOOL CInterfaceApp::InitInstance()
{
	CWinApp::InitInstance();

	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}

	return TRUE;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CDialogInterface;

CDialogInterface		*m_pMainDlg;

tagCLIENT_INFO			st_client_info;
tagSERVER_INFO			st_server_info;
tagSERIAL_INFO			st_serial_info[5];
tagRFID_INFO			st_rfid_info;
tagVnR_INFO				st_VnR_info;

extern "C" __declspec(dllexport)void Open(CWnd *pWnd)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	if(m_pMainDlg == NULL)
	{
		m_pMainDlg					= new CDialogInterface;
		m_pMainDlg->Create(pWnd);
		m_pMainDlg->ShowWindow(SW_HIDE);
	}
}


extern "C" __declspec(dllexport)void Close()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	int i;

	if (m_pMainDlg != NULL)
	{
		for (i=0; i<5; i++)
		{
			m_pMainDlg->BarcodeDelete(i);
		}
		m_pMainDlg->RfidDelete();
		m_pMainDlg->DestroyWindow();

		delete m_pMainDlg;
		m_pMainDlg = NULL;
	}
}

extern "C" __declspec(dllexport)void RfidCreate()
{	
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	if (m_pMainDlg != NULL)
	{
		m_pMainDlg->RfidCreate();
	}
}

extern "C" __declspec(dllexport)void RfidDelete()
{	
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	if (m_pMainDlg != NULL)
	{
		m_pMainDlg->RfidDelete();
	}
}

extern "C" __declspec(dllexport)void RfidReadData(int nChan, int nItem, CString *strMsg)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	
	if (m_pMainDlg != NULL)
	{
		m_pMainDlg->RfidReadData(nChan, nItem, strMsg);
	}
}

extern "C" __declspec(dllexport)void RfidReadAllData(int nChan, CString *strMsg)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	
	if (m_pMainDlg != NULL)
	{
		m_pMainDlg->RfidReadAllData(nChan, strMsg);
	}
}

extern "C" __declspec(dllexport)void RfidLastErrorMsg(CString *strMsg)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	
	if (m_pMainDlg != NULL)
	{
		m_pMainDlg->RfidLastErrorMsg(strMsg);
	}
}

extern "C" __declspec(dllexport)void RfidWriteData(int nChan, int nItem, CString strMsg)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	if (m_pMainDlg != NULL)
	{
		m_pMainDlg->RfidWriteData(nChan, nItem, strMsg);
	}
}

extern "C" __declspec(dllexport)void RfidWriteAllData(int nChan, CString *strMsg)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	if (m_pMainDlg != NULL)
	{
		m_pMainDlg->RfidWriteAllData(nChan, strMsg);
	}
}

extern "C" __declspec(dllexport)void RfidTagInfo(int nItem, int nStart, int nNum, int nWriteYesNo)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

//	clsRfid.RfidTagInfo(nItem, nStart, nNum, nWriteYesNo);
}

extern "C" __declspec(dllexport)void RfidReadTag(int nChan)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	
	if (m_pMainDlg != NULL)
	{
		m_pMainDlg->RfidReadTag(nChan);
	}
}

extern "C" __declspec(dllexport)int BarcodeCreate(int nBarcode)
{	
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	int nRet = RET_ERROR;

	if (m_pMainDlg != NULL)
	{
		nRet = m_pMainDlg->BarcodeCreate(nBarcode);
	}
	return nRet;
}

extern "C" __declspec(dllexport)void BarcodeDelete(int nBarcode)
{	
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	if (m_pMainDlg != NULL)
	{
		m_pMainDlg->BarcodeDelete(nBarcode);
	}
}

extern "C" __declspec(dllexport)void BarcodeRead(int nBarcode)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	if (m_pMainDlg != NULL)
	{
		m_pMainDlg->BarcodeReadData(nBarcode);
	}
}

extern "C" __declspec(dllexport)void BarcodeReadT(int nBarcode, CString strTrigger)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	if (m_pMainDlg != NULL)
	{
		m_pMainDlg->BarcodeReadData(nBarcode, strTrigger);
	}
}

extern "C" __declspec(dllexport)void BarcodeLastErrorMsg(CString *strMsg)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	
	if (m_pMainDlg != NULL)
	{
		m_pMainDlg->BarcodeLastErrorMsg(strMsg);
	}
}

// VnR 시작
extern "C" __declspec(dllexport)void VnRCreate()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	
	if (m_pMainDlg != NULL)
	{
		m_pMainDlg->VnRCreate();
	}
}

// VnR 종료
extern "C" __declspec(dllexport)void VnRDelete()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	
	if (m_pMainDlg != NULL)
	{
		m_pMainDlg->VnRDelete();
	}
}

// VnR Data
extern "C" __declspec(dllexport)void VnRReadData(int nChan, double *dVolt, double *dResistance)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	
	if (m_pMainDlg != NULL)
	{
		m_pMainDlg->VnRReadData(nChan, dVolt, dResistance);
	}
}