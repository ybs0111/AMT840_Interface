#include "StdAfx.h"
#include "VnRCtrl.h"
#include ".\\Ctrl\\Variable.h"
CVnRCtrl clsVnR;

CVnRCtrl::CVnRCtrl(void)
{
}


CVnRCtrl::~CVnRCtrl(void)
{
}

void CVnRCtrl::Open(CWnd *pWnd)
{
	m_pWnd		= pWnd;
}

void CVnRCtrl::OnDataReceive(CString strMsg)
{
	CString strFunc;
	CString strData;
	CString strTemp;
	CString strLog = _T("[VnR >> HANDLER]");

	int	nLength;
	int nPos[3];
	int nMcID;
	int nPort;
	double dVolt, dResistance;

	nLength = strMsg.GetLength();

	strData = strMsg.Mid(1, nLength-1);

	nPos[0] = -1;
	nPos[0] = strData.Find(_T("EOSOK"), 0);

	if (nPos[0] >= 0)
	{
		OnMakeAsd();
	}
	else
	{
		nPos[0] = -1;
		nPos[0] = strData.Find(_T("PNG"), 0);

		if (nPos[0] >= 0)
		{
			OnMakePngok();
		}
		else 
		{
			nPos[0] = -1;
			nPos[0] = strData.Find(_T("EOS"), 0);

			if (nPos[0] >= 0)
			{
				nPos[0] = 0;
				nPos[1] = strData.Find(_T(","), nPos[0]);
				nPos[2] = strData.Find(_T(","), nPos[1] + 1);
				strTemp	= strData.Mid(nPos[1] + 1, nPos[2] - (nPos[1] + 1));
				nMcID	= _wtoi(strTemp);

				nPos[0] = nPos[2];
				nPos[1] = strData.Find(_T(","), nPos[0]);
				nPos[2] = strData.Find(_T(","), nPos[1] + 1);
				strTemp	= strData.Mid(nPos[1] + 1, nPos[2] - (nPos[1] + 1));
				nPort	= _wtoi(strTemp);

				nPos[0]		= nPos[2];
				nPos[1]		= strData.Find(_T(","), nPos[0]);
				nPos[2]		= strData.Find(_T(","), nPos[1] + 1);
				strTemp		= strData.Mid(nPos[1] + 1, nPos[2] - (nPos[1] + 1));
				dVolt		= _wtof(strTemp);

				nPos[0]		= nPos[2];
				nPos[1]		= strData.Find(_T(","), nPos[0]);
				nPos[2]		= strData.Find(_T(","), nPos[1] + 1);
				strTemp		= strData.Mid(nPos[1] + 1, nPos[2] - (nPos[1] + 1));
				dResistance	= _wtof(strTemp);

				if (nPort < 0 || nPort > 9) return;
		
				st_VnR_info.dVolt[nPort - 1]		= dVolt;
				st_VnR_info.dResistance[nPort - 1]	= dResistance;
			}
		}
	}
}

void CVnRCtrl::OnMakeTime()
{
	CTime time = CTime::GetCurrentTime();
	CString strData;

	strData.Format(_T("%cTIM  %04d%02d%02d%02d%02d%02d%c"), 0x02,
													        time.GetYear(),
													        time.GetMonth(),
													        time.GetDay(),
													        time.GetHour(),
													        time.GetMinute(),
													        time.GetSecond(),
													        0x03);
 
	st_server_info.strSend = strData;

	if (m_pWnd != NULL)
	{
		m_pWnd->SendMessage(WM_SERVER_MSG, SERVER_SEND, 0);
	}
}

void CVnRCtrl::OnMakeAsd()
{
	CString strData;
	CString strLog = _T("[HANDLER >> VnR] ");

	strData.Format(_T("%cASD %c"), 0x02,
								   0x03);

	st_server_info.strSend = strData;


	if (m_pWnd != NULL)
	{
		m_pWnd->SendMessage(WM_SERVER_MSG, SERVER_SEND, 0);
	}
}

void CVnRCtrl::OnMakePngok()
{
	CString strData;
	CString strLog = _T("[HANDLER >> VnR] ");

	strData.Format(_T("%cPNGOK%c"), 0x02, 0x03);

	st_server_info.strSend = strData;

	if (m_pWnd != NULL)
	{
		m_pWnd->SendMessage(WM_SERVER_MSG, SERVER_SEND, 0);
	}
}