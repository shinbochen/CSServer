#if !defined(AFX_BSDLG_H__CA544026_B303_4E39_BB9B_5A381A7BA047__INCLUDED_)
#define AFX_BSDLG_H__CA544026_B303_4E39_BB9B_5A381A7BA047__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BSDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBSDlg dialog

class CBSDlg : public CDialog
{
// Construction
public:
	CBSDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CBSDlg)
	enum { IDD = IDD_BS_DLG };
	CButton	m_oCheckShow;
	CXTButton	m_oButtonProperty;
	CXTButton	m_oButtonConnect;
	CString	m_strConnNumber;
	CString	m_strLocalIP;
	CString	m_strRecePack;
	CString	m_strRumTime;
	CString	m_strSendPack;
	CString	m_strStateInfo;
	//}}AFX_DATA
public:
	// 连接状态
	BOOL			m_bStart;
	// 接收包
	int				m_nRecvPackage;
	// 发送包
	int				m_nSendPackage;
	// 连接数
	int				m_nConnectNumber;
	// 端口号
	UINT			m_nPort;
	BOOL			m_bShowStatus;
public:
	void			InitLabel( void );
public:
	void			SetLocalIP( CString strIP ) { m_strLocalIP = strIP; }
	CString			GetLocalIP(void )  { return m_strLocalIP; }

	void			SetLocalPort( UINT nPort ) { m_nPort = nPort; }
	UINT			GetLocalPort( void ) { return m_nPort; }
public:
	void			IsConnectionStatus( BOOL  bStateus );
	void			UpdateWindowState( void );
	BOOL			SetRecHelpInfo( int	nDataLen, BOOL	bRecv);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBSDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CBSDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnCheckShow();
	afx_msg void OnClose();
	afx_msg void OnConnectButton();
	afx_msg void OnPropertyButton();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BSDLG_H__CA544026_B303_4E39_BB9B_5A381A7BA047__INCLUDED_)
