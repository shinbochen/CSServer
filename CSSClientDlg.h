#if !defined(AFX_CSSCLIENTDLG_H__096C66AA_366D_49BF_B1F7_91CB524F418D__INCLUDED_)
#define AFX_CSSCLIENTDLG_H__096C66AA_366D_49BF_B1F7_91CB524F418D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CSSClientDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCSSClientDlg dialog

class CCSSClientDlg : public CDialog
{
// Construction
public:
	CCSSClientDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCSSClientDlg)
	enum { IDD = IDD_CSS_CLIENT_DLG };
	CListCtrl	m_oUserList;
	CButton	m_oCheckShow;
	CXTButton	m_oButtonProperty;
	CXTButton	m_oButtonConnect;
	CXTButton	m_oButtonStop;
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
	void			SetLocalIP( CString strIP ) { m_strLocalIP = strIP; }
	CString			GetLocalIP(void )  { return m_strLocalIP; }
	
	void			SetLocalPort( UINT nPort ) { m_nPort = nPort; }
	UINT			GetLocalPort( void ) { return m_nPort; }
public:
	void			IsConnectionStatus( BOOL  bStateus );
	void			UpdateWindowState( void );
	BOOL			SetRecHelpInfo( int	nDataLen, BOOL	bRecv);
public:
	void			AddUserLogInfo( CString strUserName, CString  strRemoteIP, UINT nRemotePort , CTime	oBeginTime);
	void			DeleteUserlogInfo( CString	strUserName, CString  strIP );
	void            DeleteUserlogInfo( CString   strUserName );
	CString	        FindIPPortByUser( CString strIP,  UINT  nPort );
public:
	void			InitLabel( void );
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCSSClientDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCSSClientDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnCheckShow();
	afx_msg void OnClose();
	afx_msg void OnConnectButton();
	afx_msg void OnPropertyButton();
	afx_msg void OnButtonStop();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CSSCLIENTDLG_H__096C66AA_366D_49BF_B1F7_91CB524F418D__INCLUDED_)
