// CSServerDlg.h : header file
//

#if !defined(AFX_CSSERVERDLG_H__DBF2F844_8A74_4367_85A2_84620EC2C613__INCLUDED_)
#define AFX_CSSERVERDLG_H__DBF2F844_8A74_4367_85A2_84620EC2C613__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "resource.h"
#include "CSSClientDlg.h"
#include "ClientData.h"
#include "BSDlg.h"
#include "DESDlg.h"
#include "DatabaseDlg.h"
#include "..\public\ServerSocket.h"
#include "..\public\QuerySocketObject.h"
#include "..\public\ProtocolData.h"
#include "..\public\SoftKey.h"

//////////////////////////////////////////////////////////////////////////
//
#define    USER_LIMIT_VEHICLE_0						0
#define    USER_LIMIT_VEHICLE_200					200
#define    USER_LIMIT_VEHICLE_500					500
#define    USER_LIMIT_VEHICLE_5000					5000
#define    USER_LIMIT_VEHICLE_3400					3350
//////////////////////////////////////////////////////////////////////////
//	工作方式
#define		WORK_CSVALID							0x01
#define		WORK_BSVALID							0x02
//////////////////////////////////////////////////////////////////////////


//
#ifndef   __STUSERSENDINFO
#define   __STUSERSENDINFO
typedef struct _STUSERSENDINFO{

	STUSER		m_nUSER;
	int			m_nDataLen;
	char		*m_pSendBuf;
}STUSERSENDINFO,*PSTUSERSENDINFO;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCSServerDlg dialog

class CCSServerDlg : public CDialog
{
// Construction
public:
	CCSServerDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CCSServerDlg)
	enum { IDD = IDD_CSSERVER_DIALOG };
	CString		m_strDataInfo;
	CEdit		m_oDataInfo;
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCSServerDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL
public:
	CXTPDockingPane*		m_pWndDESPane;
	CXTPDockingPane*		m_pWndBSPane;
	CXTPDockingPane*		m_pWndClientPane;
	CXTPDockingPane*		m_pWndDataBasePane;
	CXTPDockingPaneManager  m_paneManager;
	CMenu					m_oMainMenu;			//菜单
public:
	CCSSClientDlg			m_oCSSClientDlg;
	CBSDlg					m_oBSDlg;
	CDESDlg					m_oDESDlg;
	CDatabaseDlg			m_oDatabaseDlg;
	CQuerySocketObject		m_oQuerySocketObj;
	SoftKey					m_oSoftKey;
public:
	CStringArray			m_oStrArrayVersion;
	CStringArray			m_oStrArrayTime;
public:
	//	bit0: 0/1			BS端口关闭/BS端口打开
	//	bit0: 0/1			CS端口关闭/CS端口打开
	unsigned char			m_nServerWorkMode;
public:
	// Socket UDP DES Server
	CSocketThread			m_oDESTCPServer;
	// Socket TCP BS Server
	CSocketThread			m_oBSTCPServer;
	// Socket TCP CL Server
	CSocketThread			m_oCLTCPServer;
	//　跟据用户名查Socket
	CMapStringToPtr			m_oMapUserToSocket;
	//	跟据DE查Socket
	CMapStringToPtr			m_oMapDESToSocket;	
	// 数库连接标志
	BOOL					m_bDatabaseStart;
	//
	unsigned char			m_nConnectStatus;
public:
	CXTTrayIcon				m_TrayIcon;
public:
	CString					m_strVersion;
	CString					m_strServerName;
	CString					m_strDatabaseName;
	CString					m_strUserName;
	CString					m_strUserPsd;
	CString					m_strlocalIP;
	UINT					m_nDESTCPPort;
	UINT					m_nCSTCPPort;
	UINT					m_nBSTCPPort;
	CString					m_strAuthor;

	CString					m_strImagePPath;
	CString					m_strImageVPath;
public:			
	CXTPStatusBar		    m_wndStatusBar;
public:
	UINT		GetDESTCPPort( void ) { return m_nDESTCPPort; }
	UINT		GetCLTCPPort( void ) { return m_nCSTCPPort; }
	UINT		GetBSTCPPort( void ) { return m_nBSTCPPort; }
	CString		GetMacAddr( );
	CString		Decode( CString	strSrc, int nKey );
public:
	void		SetCSWorkMode( unsigned char  nValue ) { m_nServerWorkMode |= nValue; }
	BOOL		IsCSWorkMode( void ) { return (m_nServerWorkMode & WORK_CSVALID) ? TRUE:FALSE; }	
	void		SetBSWorkMode( unsigned char  nValue ) { m_nServerWorkMode |= nValue; }
	BOOL		IsBSWorkMode( void ) { return (m_nServerWorkMode & WORK_BSVALID) ? TRUE:FALSE; }
public:
	// 建立SOCKET 联接
	BOOL		StartCLTCPServer( void );
	BOOL		StartBSTCPServer( void );
	BOOL		StartDESTCPServer( void );
	BOOL		StartConnectDatabase(void);
	// 关闭SOCKET 联接
	void		StopCLTCPServer( void );
	void		StopBSTCPServer( void );
	void		StopDESTCPServer( void );
	void		StopConnectDataBase( void );
public:
	BOOL		IsCLTCPServerConnect( ) { return m_oCLTCPServer.m_bStart;}
	BOOL		IsBSTCPServerConnect( ) { return m_oBSTCPServer.m_bStart;}
	BOOL		IsDESTCPServerConnect( ){ return m_oDESTCPServer.m_bStart;}
	BOOL		IsDatabaseConnect()     { return m_bDatabaseStart;}
public:
	int			GetDESTCPActiveConnect( void );
	int			GetBSTCPActiveConnect( void );
	int			GetCLTCPActiveConnect( void );
public:
	void		InitApp( void );
	void		GetInitConfig( void );
	void        GetInitStatusBar( void );
public:
	void		RestoreInitData( void );
	void		SaveInitData( void );
	void		GetInitData( void );
	CString		GetIniFileName( void );
	void		GetPrivateData();
	BOOL		ComparisonVersionID( DWORD	dwVersionID );
	// 定时检测
	void		OnTimingCheckKey();
public:
	void	SetDESTCPHelpInfo( LPVOID lpBuf, int nDataLen, BOOL bRecvFlag, PSOCKADDR pSockAddr = NULL );
	void	SetBSTCPHelpInfo( LPVOID lpBuf, int nDataLen, BOOL bRecvFlag, PSOCKADDR pSockAddr = NULL );
	void	SetCSTCPHelpInfo( LPVOID lpBuf, int nDataLen, BOOL bRecvFlag, PSOCKADDR pSockAddr = NULL );
	void    ShowReceData(char		*pAppName, 
							int			nAppLen,
							LPVOID		lpBuf, 
							int			nDataLen, 
							BOOL		bRecvFlag, 
							PSOCKADDR	pSockAddr  = NULL );
public:
	void		DeleteUserloginInfo( CClientData	*pData, unsigned char	nType = 0 );
	void	    CloseUserLogin( CString  strUserName, unsigned char	 nType = 0 );
public:
	void       SendDESBuf(char *lpBuf, int nLen );
	void       FindUserToCLSendBuf( CString  strUserName,  char *lpBuf, int nLen );
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CCSServerDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnClose();
	afx_msg void OnEditClear();
	afx_msg void OnDESServer();
	afx_msg void OnBSServer();
	afx_msg void OnClsServer();
	afx_msg void OnDatabaseServer();
	virtual void OnOK();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnExit();
	//}}AFX_MSG
	afx_msg LRESULT OnKickIdle(WPARAM, LPARAM);
	afx_msg void	SaveParameterConfig(WPARAM wParam, LPARAM lParam );
	afx_msg void	OnSocketStartStop( WPARAM wParam, LPARAM  lParam );
	afx_msg void    OnAddLongUserData( WPARAM wParam, LPARAM lParam );
	afx_msg void	CloseUserMessage( WPARAM wParam, LPARAM lParam );
	afx_msg void    OnSocketClose( WPARAM wParam, LPARAM  lParam );
	afx_msg void    OnSocketConnect( WPARAM wParam, LPARAM lParam );
	afx_msg void    AddDESConnection( WPARAM wParam, LPARAM lParam );
	afx_msg void	PushDataToDESSendBuf( WPARAM wParam, LPARAM lParam );
	afx_msg void    PushDataToBSSendBuf( WPARAM wParam, LPARAM lParam );
	afx_msg void    PushDataToCLSendBuf( WPARAM wParam, LPARAM lParam );
	afx_msg void    FindUserToSocketSendBuf( WPARAM  wParam, LPARAM  lParam );
	afx_msg void	OnSoftwartErrorEixt( WPARAM  wParam, LPARAM  lParam );
	afx_msg void    OnSQLDisconnect( WPARAM	wParam, LPARAM  lParam );
	DECLARE_MESSAGE_MAP()
};

#ifndef  __STHELPDATA
#define  __STHELPDATA
typedef	struct _STHELPDATA{	
	char			 *m_pAppName;
	int				  m_nAppLen;
	char			 *m_pBuf;
	int				  m_nDataLen;
	BOOL			  m_bRecFlag;
	SOCKADDR		  m_oSockAddr;
	CCSServerDlg	 *m_pDlg;
}STHELPDATA, *PSTHELPDATA;
#endif  //__STHELPDATA

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CSSERVERDLG_H__DBF2F844_8A74_4367_85A2_84620EC2C613__INCLUDED_)
