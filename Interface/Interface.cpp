// Interface.cpp : �ش� DLL�� �ʱ�ȭ ��ƾ�� �����մϴ�.
//

#include "stdafx.h"
#include "Interface.h"
#include ".\\ctrl\\Variable.h"
#include "DialogInterface.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//TODO: �� DLL�� MFC DLL�� ���� �������� ��ũ�Ǿ� �ִ� ���
//		MFC�� ȣ��Ǵ� �� DLL���� ���������� ��� �Լ���
//		���� �κп� AFX_MANAGE_STATE ��ũ�ΰ�
//		��� �־�� �մϴ�.
//
//		��:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// �Ϲ����� �Լ� ������ ���⿡ �ɴϴ�.
//		}
//
//		�� ��ũ�δ� MFC�� ȣ���ϱ� ����
//		�� �Լ��� �ݵ�� ��� �־�� �մϴ�.
//		��, ��ũ�δ� �Լ��� ù ��° ���̾�� �ϸ� 
//		��ü ������ �����ڰ� MFC DLL��
//		ȣ���� �� �����Ƿ� ��ü ������ ����Ǳ� ����
//		���;� �մϴ�.
//
//		�ڼ��� ������
//		MFC Technical Note 33 �� 58�� �����Ͻʽÿ�.
//

// CInterfaceApp

BEGIN_MESSAGE_MAP(CInterfaceApp, CWinApp)
END_MESSAGE_MAP()


// CInterfaceApp ����

CInterfaceApp::CInterfaceApp()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	// InitInstance�� ��� �߿��� �ʱ�ȭ �۾��� ��ġ�մϴ�.
}


// ������ CInterfaceApp ��ü�Դϴ�.

CInterfaceApp theApp;


// CInterfaceApp �ʱ�ȭ

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

// VnR ����
extern "C" __declspec(dllexport)void VnRCreate()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	
	if (m_pMainDlg != NULL)
	{
		m_pMainDlg->VnRCreate();
	}
}

// VnR ����
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