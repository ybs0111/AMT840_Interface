#pragma once

#include ".\\Ctrl\\ClientSocket.h"

class CClientRfid
{
public:
	HANDLE				m_thrHandle;

	CWnd				*m_pWnd;

	BOOL				m_bThread;

	CString				m_strIP;
	//CString				m_strRfidData[2][50];
	//CString				m_strRfidTitle[50];
	CString				m_strErrorMsg;
	CString				m_strDataMsg;
	CString				m_strRfidTag;
	CString				m_strLoadFile;			//현재 로드되어 있는 설정 파일이름.

	int					m_nTagNum;
	int					m_nChan;
	int					m_nDataMsg;
	int					m_nPort;
	//int					m_nRfidPos[50];
	//int					m_nRfidNum[50];
	//int					m_nRfidTag[50];
	int					m_nCommStep;
	int					m_nCommBin;
	int					m_nRetry;

	DWORD				m_dwWaitTime[3];

	void				Open(CWnd *pWnd);
	void				Close();
	void				Communication();

	CString				LastErrorMsg();
	void				ReadData(int nChan, int nItem);
	void				ReadAllData(int nChan);
	CString				ConvertTagData(int nCount, CString strMsg);
	void				RfidTagInfo(int nItem, int nStart, int nNum, int nWriteYesNo);
	void				RfidTagData(CString strMsg);
	void				ReadTag(int nChan);
	void				WriteData(int nChan, int nItem, CString strMsg);
	void				WriteAllData(int nChan, CString *strMsg);

	CString				OnCharToString(char chData[], int nLength);
	void				OnStringToChar(CString strData, char chData[]);
	int					OnHexToDecimal(CString strHex);

public:
	CClientRfid(void);
	~CClientRfid(void);
};
extern CClientRfid clsRfid;