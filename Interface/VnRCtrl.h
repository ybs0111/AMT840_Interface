#pragma once
class CVnRCtrl
{
public:
	CWnd				*m_pWnd;


	void	Open(CWnd *pWnd);
	void	OnMakeTime();
	void	OnMakeAsd();
	void	OnMakePngok();
	void	OnDataReceive(CString strRev);

public:
	CVnRCtrl(void);
	~CVnRCtrl(void);
};
extern CVnRCtrl clsVnR;