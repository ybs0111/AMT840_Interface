#include "StdAfx.h"
#include "ClientRfid.h"
#include ".\\Ctrl\\Variable.h"

CClientRfid clsRfid;

UINT OnRfidMessage(LPVOID lParam);

CClientRfid::CClientRfid(void)
{
	m_pWnd = NULL;
}


CClientRfid::~CClientRfid(void)
{
}

int	CClientRfid::OnHexToDecimal(CString strHex)
{
	char chHex[10];
	int val;

	OnStringToChar(strHex, chHex);


	chHex[2] = '\0';
	val = strtoul(chHex, NULL, 16);

	return val;
}

CString	CClientRfid::OnCharToString(char chData[], int nLength)
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

void CClientRfid::OnStringToChar(CString strData, char chData[])
{
	int nCnt;
	wchar_t *chBuf;

	chBuf = strData.GetBuffer(strData.GetLength());
	nCnt  = WideCharToMultiByte(CP_ACP, 0, chBuf, -1, NULL, 0, NULL, NULL);
	WideCharToMultiByte(CP_ACP, 0, chBuf, -1, chData, nCnt, 0, 0);
}


// CRfidCtrl 메시지 처리기입니다.
void CClientRfid::Open(CWnd *pWnd)
{
	bool bFlag = true;

	m_pWnd		= pWnd;

	if(m_bThread == false)
	{
		m_bThread = true;
		m_thrHandle = AfxBeginThread(OnRfidMessage, this);
	}
}


void CClientRfid::Close()
{
	m_bThread = false;

	while(WaitForSingleObject(m_thrHandle, 5000) != WAIT_OBJECT_0)
	{
		if (m_thrHandle == NULL) break;
		Sleep(0);
	}
}


void CClientRfid::Communication()
{
	switch (m_nCommStep)
	{
		case 0:
			if (m_nDataMsg != YES) break;

			m_nRetry	= 0;

			m_nCommStep = 100;
			break;

		case 100:
			if (st_client_info.nConnect == NO)
			{
				m_nCommStep = 200;
			}
			else
			{
				m_nCommStep = 1000;
			}
			break;

		case 200:
			m_dwWaitTime[0] = GetTickCount();

			if (m_pWnd != NULL)
			{
				m_pWnd->SendMessage(WM_CLIENT_MSG, CLIENT_CONNECT, 0);

				m_nCommStep = 300;
			}
			else 
			{
				m_nDataMsg	= NO;

				m_nCommStep = 0;
			}
			break;

		case 300:
			if (st_client_info.nConnect == YES)
			{
				m_nCommStep = 1000;
			}
			else 
			{
				m_dwWaitTime[1] = GetTickCount();
				m_dwWaitTime[2] = m_dwWaitTime[1] - m_dwWaitTime[0];

				if (m_dwWaitTime[2] <= (DWORD)0)
				{
					m_dwWaitTime[0] = GetTickCount();
					break;
				}

				if (m_dwWaitTime[2] > (DWORD) 10000)
				{
					m_nRetry++;
					if (m_nRetry >= 3)
					{
						m_nDataMsg	= NO;

						m_nCommStep = 0;
					}
					else
					{
						m_nCommStep = 200;
					}
				}
			}
			break;

		case 1000:
			m_dwWaitTime[0] = GetTickCount();

			st_client_info.strSend = m_strDataMsg;

			if (m_pWnd != NULL)
			{
				m_pWnd->SendMessage(WM_CLIENT_MSG, CLIENT_SEND, 0);

				m_nCommStep = 1100;
			}
			else
			{
				m_nDataMsg	= NO;

				m_nCommStep = 0;
			}
			break;

		case 1100:
			if (m_nCommBin == BIN_GOODBIN)
			{
				m_nCommStep = 1200;
			}
			else if (m_nCommBin == BIN_REJECTBIN)
			{
				m_nCommStep = 1200;
			}
			else
			{
				m_dwWaitTime[1] = GetTickCount();
				m_dwWaitTime[2] = m_dwWaitTime[1] - m_dwWaitTime[0];

				if (m_dwWaitTime[2] <= (DWORD)0)
				{
					m_dwWaitTime[0] = GetTickCount();
					break;
				}

				if (m_dwWaitTime[2] > (DWORD) 20000)
				{
					m_nRetry++;
					if (m_nRetry >= 3)
					{
						m_nCommStep = 1200;
					}
					else
					{
						m_nCommStep = 1000;
					}
				}
			}
			break;

		case 1200:
			m_dwWaitTime[0] = GetTickCount();

			if (m_pWnd != NULL)
			{
				m_pWnd->SendMessage(WM_CLIENT_MSG, CLIENT_CLOSE, 0);

				m_nCommStep = 1300;
			}
			else
			{
				m_nDataMsg	= NO;

				m_nCommStep = 0;
			}
			break;

		case 1300:
			m_dwWaitTime[1] = GetTickCount();
			m_dwWaitTime[2] = m_dwWaitTime[1] - m_dwWaitTime[0];

			if (m_dwWaitTime[2] <= (DWORD)0)
			{
				m_dwWaitTime[0] = GetTickCount();
				break;
			}

			if (m_dwWaitTime[2] > (DWORD) 500)
			{
				m_nDataMsg	= NO;

				m_nCommStep = 0;
			}
			break;
	}
}


void CClientRfid::RfidTagInfo(int nItem, int nStart, int nNum, int nWriteYesNo)
{
	if (nItem >= 50) return;

	st_rfid_info.nRfidPos[nItem]	= nStart;
	st_rfid_info.nRfidNum[nItem]	= nNum;
	st_rfid_info.nRfidTag[nItem]	= nWriteYesNo;
}

CString	CClientRfid::LastErrorMsg()
{
	return m_strErrorMsg;
}


void CClientRfid::ReadData(int nChan, int nItem)
{
	int		i;
	int		nLength;
	int		nSum = 0;
	int		nBcc;
	int		nNum;

	CString strRfid = _T("");
	CString strMake = _T("");
	CString strLength;
	CString strTemp;
	CString strData;

	BYTE	byBuf[100];

	if (m_nDataMsg != NO)
	{
		m_strErrorMsg = _T("RFID Data Send Error");

		if (m_pWnd != NULL)
		{
			m_pWnd->SendMessage(WM_RFID_MSG, RFID_ERROR, nChan);
		}

		return;
	}

	if (m_bThread == false)
	{
		m_strErrorMsg = _T("RFID Open Error");

		if (m_pWnd != NULL)
		{
			m_pWnd->SendMessage(WM_RFID_MSG, RFID_ERROR, nChan);
		}

		return;
	}

	m_nChan		= nChan;
	if (m_nChan < 0) m_nChan = 1;
	
	nNum = m_nChan - 1;

	m_nCommBin	= BIN_NOTUESD;

	//strLength.Format(_T("%02x%02x"), m_nRfidPos[nItem],  m_nRfidNum[nItem]);
	strLength.Format(_T("%02X%02X"), st_rfid_info.nRfidPos[nItem],  st_rfid_info.nRfidNum[nItem]);
	strMake.Format(_T("%c01%2d%s"), 0x05, 80 + (nNum), strLength);

	nLength = strMake.GetLength();
	OnStringToChar(strMake, (char*) byBuf);

	for(i=0; i<nLength; i++)
	{
		nSum += byBuf[i];
	}

	nBcc = (nSum % 256);
	strTemp.Format(_T("%X"), nBcc);
	strTemp.MakeUpper();

	nLength = strTemp.GetLength();

	strRfid.Format(_T("%s%s%c"), strMake, strTemp.Mid(nLength - 2, 2), 0x03);
	m_strDataMsg = strRfid;

	m_nDataMsg = YES;
}


void CClientRfid::ReadAllData(int nChan)
{
	int		i;
	int		nLength = 0;
	int		nSum = 0;
	int		nBcc;
	int		nNum;

	CString strRfid = _T("");
	CString strMake = _T("");
	CString strLength;
	CString strTemp;
	CString strData;

	BYTE	byBuf[100];

	if (m_nDataMsg != NO)
	{
		m_strErrorMsg = _T("RFID Data Send Error");

		if (m_pWnd != NULL)
		{
			m_pWnd->SendMessage(WM_RFID_MSG, RFID_ERROR, nChan);
		}

		return;
	}

	if (m_bThread == false)
	{
		m_strErrorMsg = _T("RFID Open Error");

		if (m_pWnd != NULL)
		{
			m_pWnd->SendMessage(WM_RFID_MSG, RFID_ERROR, nChan);
		}

		return;
	}

	m_nChan		= nChan;
	if (m_nChan < 0) m_nChan = 1;
	
	nNum = m_nChan - 1;

	m_nCommBin	= BIN_NOTUESD;

	for (i=0; i<st_rfid_info.nTagNum; i++) nLength++;
	
	//strLength.Format(_T("%02x%02x"), m_nRfidPos[0],  112);
	strLength.Format(_T("%02X%02X"), st_rfid_info.nRfidPos[0],  112);
	strMake.Format(_T("%c01%2d%s"), 0x05, 80 + (nNum), strLength);

	nLength = strMake.GetLength();
	OnStringToChar(strMake, (char*) byBuf);

	for(i=0; i<nLength; i++)
	{
		nSum += byBuf[i];
	}

	nBcc = (nSum % 256);
	strTemp.Format(_T("%X"), nBcc);
	strTemp.MakeUpper();

	nLength = strTemp.GetLength();

	strRfid.Format(_T("%s%s%c"), strMake, strTemp.Mid(nLength - 2, 2), 0x03);

	m_strDataMsg = strRfid;

	m_nDataMsg = YES;
}


void CClientRfid::ReadTag(int nChan)
{
	int		i;
	int		nLength = 0;
	int		nSum = 0;
	int		nBcc;

	CString strRfid = _T("");
	CString strMake = _T("");
	CString strLength;
	CString strTemp;
	CString strData;

	BYTE	byBuf[100];

	if (m_nDataMsg != NO)
	{
		m_strErrorMsg = _T("RFID Data Send Error");

		if (m_pWnd != NULL)
		{
//			m_pWnd->SendMessage(WM_RFID_MSG, RFID_ERROR, nChan);
		}
		return;
	}

	m_nChan		= nChan - 1;
	if (m_nChan < 0) m_nChan = 0;

	m_nCommBin	= BIN_NOTUESD;

	/*for (i=0; i<m_nTagNum; i++) 
		for (j=0; j<m_nRfidNum[i]; j++) nLength++;*/

	//strLength.Format(_T("%02x%02x"), m_nRfidPos[0],  112);
	strLength.Format(_T("%02X%02X"), st_rfid_info.nRfidPos[0],  112);
	strMake.Format(_T("%c01%2d%s"), 0x05, 80 + (m_nChan), strLength);

	nLength = strMake.GetLength();
	OnStringToChar(strMake, (char*) byBuf);

	for(i=0; i<nLength; i++)
	{
		nSum += byBuf[i];
	}

	nBcc = (nSum % 256);
	strTemp.Format(_T("%X"), nBcc);
	strTemp.MakeUpper();

	nLength = strTemp.GetLength();

	strRfid.Format(_T("%s%s%c"), strMake, strTemp.Mid(nLength - 2, 2), 0x03);
	m_strDataMsg = strRfid;

	m_nDataMsg = YES;
}


void CClientRfid::WriteData(int nChan, int nItem, CString strMsg)
{
	int		i;
	int		nLength;
	int		nSum = 0;
	int		nBcc;
	int		nNum;

	CString strRfid = _T("");
	CString strMake = _T("");
	CString strLength;
	CString strTemp;
	CString strData;
	CString strTag;

	BYTE	byBuf[1024];

	if (m_nDataMsg != NO)
	{
		m_strErrorMsg = _T("RFID Data Send Error");

		if (m_pWnd != NULL)
		{
			m_pWnd->SendMessage(WM_RFID_MSG, RFID_ERROR, nChan);
		}

		return;
	}

	if (m_bThread == false)
	{
		m_strErrorMsg = _T("RFID Open Error");

		if (m_pWnd != NULL)
		{
			m_pWnd->SendMessage(WM_RFID_MSG, RFID_ERROR, nChan);
		}

		return;
	}

	m_nChan		= nChan;
	if (m_nChan < 0) m_nChan = 1;
	
	nNum = m_nChan - 1;

	m_nCommBin	= BIN_NOTUESD;

	//strLength.Format(_T("%02x%02x"), m_nRfidPos[nItem], m_nRfidNum[nItem]);
	strLength.Format(_T("%02X%02X"), st_rfid_info.nRfidPos[nItem], st_rfid_info.nRfidNum[nItem]);
	strMake.Format(_T("%c01%d%s"), 0x05, 90 + (nNum), strLength);

	//if(strMsg.GetLength() > m_nRfidNum[nItem])
	nLength = strMsg.GetLength();
	if(nLength > st_rfid_info.nRfidNum[nItem])
	{
		//strData = strMsg.Mid(0, m_nRfidNum[nItem]);
		strData = strMsg.Mid(0, st_rfid_info.nRfidNum[nItem]);
	}
	else
	{
		strData = strMsg;
	}
	strTag = ConvertTagData(st_rfid_info.nRfidNum[nItem], strData);
	OnStringToChar(strTag, (char*) byBuf);


	//for(i=0; i<m_nRfidNum[nItem]; i++)
	for(i=0; i<st_rfid_info.nRfidNum[nItem]; i++)
	{
		strTemp.Format(_T("%X"), byBuf[i]);
		strMake += strTemp;
	}
	
	nLength = strMake.GetLength();

	OnStringToChar(strMake, (char*) byBuf);

	for(i=0; i<nLength; i++)
	{
		nSum += byBuf[i];
	}

	nBcc = (nSum % 256);
	strTemp.Format(_T("%X"), nBcc);
	strTemp.MakeUpper();
	nLength = strTemp.GetLength();

	strRfid.Format(_T("%s%s%c"), strMake, strTemp.Mid(nLength - 2, 2), 0x03);

	m_strDataMsg = strRfid;
	m_nDataMsg	= YES;
}


void CClientRfid::WriteAllData(int nChan, CString *strMsg)
{
	int		i;
	int		nLength;
	int		nSum = 0;
	int		nBcc;
	int     nCount = 0;
	int		nStart;
	int		nNum;

	CString strRfid = _T("");
	CString strMake = _T("");
	CString strLength;
	CString strTemp;
	CString strData;
	CString strTag;

	BYTE	byBuf[1024];

	if (m_nDataMsg != NO)
	{
		m_strErrorMsg = _T("RFID Data Send Error");

		if (m_pWnd != NULL)
		{
			m_pWnd->SendMessage(WM_RFID_MSG, RFID_ERROR, nChan);
		}

		return;
	}

	if (m_bThread == false)
	{
		m_strErrorMsg = _T("RFID Open Error");

		if (m_pWnd != NULL)
		{
			m_pWnd->SendMessage(WM_RFID_MSG, RFID_ERROR, nChan);
		}

		return;
	}

	m_nChan		= nChan;
	if (m_nChan < 0) m_nChan = 1;
	
	nNum = m_nChan - 1;

	m_nCommBin	= BIN_NOTUESD;

	nLength = 0;
	nStart	= -1;

	for (i=0, nLength=0; i<st_rfid_info.nTagNum; i++)
	{
		if (st_rfid_info.nRfidTag[i] == YES)
		{
			nLength += st_rfid_info.nRfidNum[i];
			if (nStart < 0)
			{
				nStart = st_rfid_info.nRfidPos[i];
			}
		}
	}

	strLength.Format(_T("%02X%02X"), nStart, nLength);
	strMake.Format(_T("%c01%d%s"), 0x05, 90 + (nNum), strLength);

	for (i=0; i<st_rfid_info.nTagNum; i++)
	{
		//if (m_nRfidTag[i] == YES)
		strTemp = _T("");
		if (st_rfid_info.nRfidTag[i] == YES)
		{
			if (strMsg[i] != _T(""))
			{
				//if (strMsg[i].GetLength() > m_nRfidNum[i])
				nLength = strMsg[i].GetLength();
				if (nLength > st_rfid_info.nRfidNum[i])
				{
					//strTemp = strMsg[i].Mid(m_nRfidPos[i], m_nRfidNum[i]);
					strTemp = strMsg[i].Mid(st_rfid_info.nRfidPos[i], st_rfid_info.nRfidNum[i]);
				}
				else
				{
					strTemp = strMsg[i];
				}

				strTag = ConvertTagData(st_rfid_info.nRfidNum[i], strTemp);
				strData += strTag;
			}
			else
			{
				strTag = ConvertTagData(st_rfid_info.nRfidNum[i], strTemp);
				strData += strTag;
			}
		}
	}

	OnStringToChar(strData, (char*) byBuf);

	nLength = strData.GetLength();
	for(i=0; i<nLength; i++)
	{
		strTemp.Format(_T("%X"), byBuf[i]);
		strMake += strTemp;
	}
	
	nLength = strMake.GetLength();

	OnStringToChar(strMake, (char*) byBuf);

	for(i=0; i<nLength; i++)
	{
		nSum += byBuf[i];
	}

	nBcc = (nSum % 256);
	strTemp.Format(_T("%X"), nBcc);
	strTemp.MakeUpper();
	nLength = strTemp.GetLength();

	strRfid.Format(_T("%s%s%c"), strMake, strTemp.Mid(nLength - 2, 2), 0x03);
	m_strDataMsg	= strRfid;
	m_nDataMsg		= YES;
}


void CClientRfid::RfidTagData(CString strMsg)
{
	int i, j;
	int nLength, nHeader;
	int nVal;
	int nPos[2];
	int nNum;

	char chData[1024];
	
	CString strFunc;
	CString strTemp;
	CString strData;
	CString strHex;
	CString strTag;

	nLength		= strMsg.GetLength();

	if (nLength > 1024) return;
	
	OnStringToChar(strMsg, chData);

	nHeader = chData[0];

	if (m_nChan < 0) m_nChan = 1;
	
	nNum = m_nChan - 1;

	if (chData[nLength-1] == 0x03)
	{
		m_strRfidTag += strMsg;

		nHeader = m_strRfidTag.GetAt(0);

		strFunc = m_strRfidTag.Mid(3, 2);

		if (strFunc == _T("80") || strFunc == _T("81"))
		{
			if (nHeader != 0x02)
			{
				if (m_pWnd != NULL)
				{
					OnStringToChar(m_strErrorMsg, chData);

					m_pWnd->SendMessage(WM_RFID_MSG, RFID_READ_NG, (LPARAM)chData);
				}
				m_nCommBin = BIN_REJECTBIN;

				m_strRfidTag = _T("");

				return;
			}
			strData.Format(_T("TAG_COUNT=%02d"), st_rfid_info.nTagNum);
			st_rfid_info.strRfidTag = strData;
			st_rfid_info.strRfidTag += _T(" ");

			for (i=0; i<st_rfid_info.nTagNum; i++)
			{
				nPos[0] = (st_rfid_info.nRfidPos[i] * 2) + 5;
				nPos[1] = st_rfid_info.nRfidNum[i] * 2;

				strTemp  = m_strRfidTag.Mid(nPos[0], nPos[1]);

				st_rfid_info.strRfidData[nNum][i] = _T("");

				for (j=0; j<st_rfid_info.nRfidNum[i] * 2; j+=2)
				{
					nVal = OnHexToDecimal(strTemp.Mid(j, 2));
					strHex.Format(_T("%c"), nVal);

					if (strHex != _T(" "))
					{
						st_rfid_info.strRfidData[nNum][i] += strHex;
					}
				}

				strTag.Format(_T("%s=%s"), st_rfid_info.strRfidTitle[i], st_rfid_info.strRfidData[nNum][i]);
				st_rfid_info.strRfidTag +=strTag;
				st_rfid_info.strRfidTag += _T(" ");
			}

			if (m_pWnd != NULL)
			{
				OnStringToChar(strData, chData);

				m_pWnd->SendMessage(WM_RFID_MSG, RFID_READ_GOOD, m_nChan);
			}

			m_nCommBin = BIN_GOODBIN;
		}
		else if(strFunc == _T("90") || strFunc == _T("91"))
		{
			if (chData[0] == 0x06)
			{
				m_nCommBin = BIN_GOODBIN;

				if (m_pWnd != NULL)
				{
					OnStringToChar(strMsg, chData);

					m_pWnd->SendMessage(WM_RFID_MSG, RFID_WRITE_GOOD, m_nChan);
				}
			}
			else
			{
				m_strErrorMsg = _T("RFID data write command fail.");
				if (m_pWnd != NULL)
				{
					OnStringToChar(m_strErrorMsg, chData);

					m_pWnd->SendMessage(WM_RFID_MSG, RFID_WRITE_NG, m_nChan);
				}
				m_nCommBin = BIN_REJECTBIN;
			}
		}
		else
		{
			m_strErrorMsg = _T("RFID is not respond.");
			if (m_pWnd != NULL)
			{
				OnStringToChar(m_strErrorMsg, chData);

				m_pWnd->SendMessage(WM_RFID_MSG, RFID_ERROR, m_nChan);
			}
			m_nCommBin = BIN_REJECTBIN;
		}

		m_strRfidTag = _T("");
	}
	else
	{
		m_strRfidTag += strMsg;
	}

}

CString	CClientRfid::ConvertTagData(int nCount, CString strMsg)
{
	CString strData;

	int nLength;
	int i;
	int nNum;

	strData = strMsg;
	nLength = strMsg.GetLength();

	nNum = nCount-nLength;
	if (nNum < 0) nNum = 0;
	for (i=0; i<nNum; i++)
	{
		strData += _T(" ");
	}

	return strData;
}


UINT OnRfidMessage(LPVOID lParam)
{
	CClientRfid *pMsg = (CClientRfid *)lParam;


	while(pMsg->m_bThread)
	{
		pMsg->Communication();
	}

	pMsg->m_thrHandle = NULL;

	return 0;
}

