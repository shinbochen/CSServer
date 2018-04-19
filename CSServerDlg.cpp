// CSServerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CSServer.h"
#include "CSServerDlg.h"
#include "..\public\Encrypt.h"
#include "nb30.h"
#include "..\public\EncryptionData.h"
#include "..\public\MacIP.h"

#pragma comment(lib,"netapi32.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//----------------
const int g_nMainMenuID[][2] = {
	IDC_EDIE_CLEAR,			TEXT_DELETE_ALL,
	0,						0,
	IDC_DES_SERVER,			TEXT_DES_SERVER,
	IDC_BS_SERVER,			TEXT_DBS_SERVER,
	IDC_CLS_SERVER,			TEXT_CLS_SERVER,
	IDC_DATABASE_SERVER,	TEXT_DATABASE_CONNECT,
	-1,						-1
};

// 	m_pMenu = new CMenu();
// 	m_pMenu->CreatePopupMenu();
// 	m_pMenu->AppendMenu(MF_STRING, IDC_EDIE_CLEAR,   "删除所有");
// 	m_pMenu->AppendMenu(MF_SEPARATOR, 0, "" );
// 	m_pMenu->AppendMenu(MF_STRING, IDC_DES_SERVER,   "DES通信服务器");
// 	m_pMenu->AppendMenu(MF_STRING, IDC_BS_SERVER,    "BS通信服务器");
// 	m_pMenu->AppendMenu(MF_STRING, IDC_CLS_SERVER,   "CLS通信服务器");
// 	m_pMenu->AppendMenu(MF_STRING, IDC_DATABASE_SERVER, "数据库服务器")

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA
public:	
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////
//
BOOL CAboutDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

/////////////////////////////////////////////////////////////////////////////
// CCSServerDlg dialog

CCSServerDlg::CCSServerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCSServerDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCSServerDlg)
	m_strDataInfo = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_strServerName = _T("(local)");
	m_strDatabaseName = _T("MapTrack_DB");
	m_strUserName = _T("sa");
	m_strUserPsd = _T("sa");
	m_strlocalIP = _T("192.168.1.118");
	m_nDESTCPPort = 9090;
	m_nCSTCPPort = 9900;
	m_nBSTCPPort = 9990;
	m_nConnectStatus = 0xFF;
	m_bDatabaseStart = FALSE;
	m_oMapUserToSocket.RemoveAll();
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_nServerWorkMode = 0;
	srand((unsigned)time(0)); 
	
 	int	nCnt = 0;	
	int	nSubMenu = 0;
	m_oMainMenu.CreateMenu();
	while( 1 ){
		if( g_nMainMenuID[nCnt][0] == -1 ){
			break;
		}
		else if( g_nMainMenuID[nCnt][0] > 0 ){			
			m_oMainMenu.AppendMenu(MF_STRING, g_nMainMenuID[nCnt][0], GetLangStr(g_nMainMenuID[nCnt][1]) );
		}
		else if( g_nMainMenuID[nCnt][0] == 0 ){
			m_oMainMenu.AppendMenu(MF_SEPARATOR, 0, "" );
		}
		nCnt++;
	}
	m_oStrArrayTime.RemoveAll();
}

void CCSServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCSServerDlg)
		DDX_Text(pDX, IDC_EDIT_DATA_INFO,	 m_strDataInfo);
		DDX_Control(pDX, IDC_EDIT_DATA_INFO, m_oDataInfo);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCSServerDlg, CDialog)
	//{{AFX_MSG_MAP(CCSServerDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SIZE()
	ON_WM_CLOSE()
	ON_COMMAND( IDC_EDIE_CLEAR,  OnEditClear)
	ON_COMMAND( IDC_DES_SERVER,  OnDESServer)
	ON_COMMAND( IDC_BS_SERVER,  OnBSServer)
	ON_COMMAND( IDC_CLS_SERVER,  OnClsServer)
	ON_COMMAND( IDC_DATABASE_SERVER, OnDatabaseServer)	
	ON_WM_TIMER()
	ON_COMMAND(ID_EXIT, OnExit)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_KICKIDLE, OnKickIdle)
	ON_MESSAGE(WM_SAVE_PARAMETER_CONFIG,	SaveParameterConfig)
	ON_MESSAGE(WM_SOCKET_STARTSTOP,			OnSocketStartStop)
	ON_MESSAGE(WM_ADDCLIENTLOGINDATA ,		OnAddLongUserData)
	ON_MESSAGE(WM_CLOSECLIENTLOGINDATA,		CloseUserMessage)
	ON_MESSAGE(WM_SOCKET_CLOSE,				OnSocketClose )	
	ON_MESSAGE(WM_SOCKET_CONNECT,			OnSocketConnect )
	ON_MESSAGE(WM_ADDDES_CONNECTDATA,		AddDESConnection)
	ON_MESSAGE(WM_SENDDESDATA,				PushDataToDESSendBuf)
	ON_MESSAGE(WM_SENDBSDATA,				PushDataToBSSendBuf)
	ON_MESSAGE(WM_SENDCLDATA,				PushDataToCLSendBuf)
	ON_MESSAGE(WM_FINDUSER_SOCKET,			FindUserToSocketSendBuf )
	ON_MESSAGE(WM_SOFTWART_ERROR_EXIT,		OnSoftwartErrorEixt )
	ON_MESSAGE(WM_SQL_DISCONNECT,			OnSQLDisconnect )
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////
//
static UINT indicators[] =
{
	ID_TIME_DATE,
	ID_TIME_APP,
};
//////////////////////////////////////////////////////////////////////////
//
static UINT icoArray[] =
{
	IDR_MAINFRAME,
};
//////////////////////////////////////////////////////////////////////////
//
BOOL CCSServerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);
	
	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL){
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty()){
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}
	SetIcon(m_hIcon, TRUE);		
	SetIcon(m_hIcon, FALSE);
	
	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	//////////////////////////////////////////////////////////////////////////
	m_paneManager.InstallDockingPanes(this);
	m_paneManager.SetTheme(xtpPaneThemeOffice2003);
	m_paneManager.UseSplitterTracker(FALSE);
	m_paneManager.SetShowContentsWhileDragging(TRUE);
	m_paneManager.SetAlphaDockingContext(TRUE);
	
	m_pWndClientPane = m_paneManager.CreatePane(
		IDR_CSSCLIENTPANE, CRect(0, 0,621, 230), xtpPaneDockLeft);
	
	m_pWndBSPane = m_paneManager.CreatePane(
		IDR_BSPANE, CRect(0, 0,621, 230), xtpPaneDockLeft);
	
	m_pWndDESPane = m_paneManager.CreatePane(
		IDR_DESPANE, CRect(0, 0,621, 230), xtpPaneDockLeft);
	
	m_pWndDataBasePane = m_paneManager.CreatePane(
		IDR_DATABASEPANE, CRect(0, 0,621, 230), xtpPaneDockLeft);
	
	m_paneManager.AttachPane(m_pWndDESPane, m_pWndDataBasePane);
	m_paneManager.AttachPane(m_pWndBSPane, m_pWndDESPane);
	m_paneManager.AttachPane(m_pWndClientPane, m_pWndBSPane);
	
	int nIDIcons[] = {IDR_CSSCLIENTPANE, IDR_DESPANE,IDR_BSPANE,IDR_DATABASEPANE};
	m_paneManager.SetIcons(IDB_APP_BMP, nIDIcons,
		_countof(nIDIcons), RGB(0, 255, 0));
    //重画面版
	XTPPaintManager()->SetTheme( xtpThemeOffice2003 );
	
	//////////////////////////////////////////////////////////////////////////
	// 读取日志
	GetInitData();
	GetInitStatusBar( );
	GetInitConfig( );
	GetPrivateData();

	InitApp();

	CCSProtocolData::ADBInitCriticalSection();

	CString			strWindowName;
	CString			strWindowName2;

	strWindowName.LoadString(IDS_VERSION);
	GetWindowText( strWindowName2 );	
	strWindowName2 +=" " + strWindowName;
	SetWindowText( strWindowName2 );
	// 创建托盘
	if (!m_TrayIcon.Create(
		_T("CSServer"),				// Toolktip text
		this,                       // Parent window
		IDR_MAINFRAME,              // Icon resource ID
		IDR_TRAY_MENU,              // Resource ID of popup menu
		IDR_MAINFRAME,              // Default menu item for popup menu
		false))                     // True if default menu item is located by position
	{
		TRACE0("Failed to create tray icon\n");
		return -1;
	}	
	m_TrayIcon.SetAnimationIcons( icoArray, _countof(icoArray));
	
	CString	 strTmp;

	#ifdef	TRACK_EARTH_SERVER
		//////////////////////////////////////////////////////////////////////////
		CString  strAuthor;
		CString  strNetwork;		
		
		#ifdef  TEXT_MACIP
			char		chBuf[128];

			memset( chBuf, 0x00, 128);

			if( GetMacByCmd( chBuf ) ){

				strNetwork.Format("%s", chBuf );
				strAuthor = Decode( strNetwork, 12 );
			}
		#else	
			strNetwork = GetMacAddr();
			strAuthor = Decode( strNetwork, 12 );
		#endif //TEXT_MACIP
		if (  strAuthor != m_strAuthor ){
			strTmp.Format( "%s %s:%s", GetLangStr(TEXT_WARING_NOT_AUTHORIZE), TEXT_AUTHOR_EMAIL, strNetwork );
			AfxMessageBox( strTmp );
			PostMessage(WM_COMMAND, IDOK, 0 );
			return FALSE;
		}
		SetCSWorkMode( WORK_BSVALID );
		SetCSWorkMode( WORK_CSVALID );
#if(TIME_CONFIG_VERSION)
		CDBData::SetSoftwareVehicleTotal( USER_LIMIT_VEHICLE_3400 );
#else
		CDBData::SetSoftwareVehicleTotal( USER_LIMIT_VEHICLE_5000 );
#endif 
	#else
		//////////////////////////////////////////////////////////////////////////
		BOOL		bTimeFlag = TRUE;
		
		if( (m_oSoftKey.Ini( ) && m_oSoftKey.YCheckKey()) == FALSE ){	
			
			CTime		oCurrentTime = CTime::GetCurrentTime();
			int			nCurrentTime = 0;
			int			nTime = 0;	
			int			nTmp = 0;

			strTmp.Format("%d", oCurrentTime );
			nCurrentTime = 	atoi(strTmp.GetBuffer(0));
			strTmp.ReleaseBuffer();
			if( m_oStrArrayTime.GetSize() > 0 ){
				for ( int nCnt = 0; nCnt < m_oStrArrayTime.GetSize(); nCnt++ ){
					strTmp = m_oStrArrayTime.GetAt(nCnt);
					if( nCnt == 0 ){			//时间						
						nTime = atoi( strTmp.GetBuffer(0));
						strTmp.ReleaseBuffer();
					}
					else if( nCnt == 1 ){		//数量
						nTmp = atoi( strTmp.GetBuffer(0) );
						strTmp.ReleaseBuffer();
						if( nTmp == 0 ){
							CDBData::SetSoftwareVehicleTotal(USER_LIMIT_VEHICLE_0);	
						}
						else if( nTmp == 1 ){
							CDBData::SetSoftwareVehicleTotal(USER_LIMIT_VEHICLE_200);	
						}
						else if( nTmp == 2){
							CDBData::SetSoftwareVehicleTotal(USER_LIMIT_VEHICLE_500);	
						}
						else if( nTmp == 3 ){
							CDBData::SetSoftwareVehicleTotal(USER_LIMIT_VEHICLE_5000);
						}
					}
					else if( nCnt == 2 ){		//允许值
						nTmp = atoi(strTmp.GetBuffer(0) );
						strTmp.ReleaseBuffer();
						// BS
						if( nTmp & BSVALID ){
							SetCSWorkMode( WORK_BSVALID );
						}
						//  CS
						if( nTmp & CSVALID ){
							SetCSWorkMode( WORK_CSVALID );
						}
					}
				}				
				//	时间比较
				if( nTime > nCurrentTime  ){									
					bTimeFlag = FALSE;
				}
			}
			if( bTimeFlag ){
				strTmp.Format("%s%s", GetLangStr(TEXT_WARING_NOT_AUTHORIZE), TEXT_AUTHOR_EMAIL );
				MessageBox( strTmp ,GetLangStr(TEXT_WARNING), MB_OK|MB_ICONWARNING );
				PostMessage(WM_COMMAND, IDOK, 0 );
				return FALSE;
			}
		}	
		DWORD		dwVersion; 
		
		if( bTimeFlag == TRUE ){
			dwVersion = m_oSoftKey.GetIDVersion();
			if( ComparisonVersionID( dwVersion) == FALSE ){
				strTmp.Format("%s%s", GetLangStr(TEXT_WARING_NOT_AUTHORIZE), TEXT_AUTHOR_EMAIL );
				MessageBox( strTmp ,GetLangStr(TEXT_WARNING), MB_OK|MB_ICONWARNING );
				PostMessage(WM_COMMAND, IDOK, 0 );
				return FALSE;
			}
			//////////////////////////////////////////////////////////////////////////
			if( m_oSoftKey.IsBSServerValid() ){
				SetCSWorkMode( WORK_BSVALID );
			}
			if( m_oSoftKey.IsCSServerValid() ){
				SetCSWorkMode( WORK_CSVALID );
			}
			
			//////////////////////////////////////////////////////////////////////////
			switch( m_oSoftKey.GetUserLimit() ){
			case USER_LIMIT_0:
				CDBData::SetSoftwareVehicleTotal( USER_LIMIT_VEHICLE_0 );
				break;
			case USER_LIMIT_200:
				CDBData::SetSoftwareVehicleTotal( USER_LIMIT_VEHICLE_200 );
				break;
			case USER_LIMIT_500:
				CDBData::SetSoftwareVehicleTotal( USER_LIMIT_VEHICLE_500 );
				break;
			case USER_NO_LIMIT:
				CDBData::SetSoftwareVehicleTotal( USER_LIMIT_VEHICLE_5000 );
				break;
			}
			char		chBuf[20];

			strcpy( chBuf, "MapTrack" );
			m_oSoftKey.YCompareString( chBuf, "MapTrack", strlen(chBuf) );		
			if( m_oSoftKey.YGetLastError() != 0 ){
				strTmp.Format("%s%s", GetLangStr(TEXT_WARING_NOT_AUTHORIZE), TEXT_AUTHOR_EMAIL );
				MessageBox( strTmp ,GetLangStr(TEXT_WARNING), MB_OK|MB_ICONWARNING );
				PostMessage(WM_COMMAND, IDOK, 0 );
				return FALSE;
			}
			SetTimer(WM_TIMER_CHECK, 1000*60*5 , NULL );
		}
    #endif
//  时间设置
#if(TIME_CONFIG_VERSION)
		
	CTime			oTime = CTime::GetCurrentTime();
	CString			strData;

	strData.Format("%d", oTime );
	int  nCurTime = atoi( strData.GetBuffer(0) );
	strData.ReleaseBuffer();
	if( nCurTime >= TIME_CONFIG_TIME ){		
		PostMessage(WM_COMMAND, IDOK, 0 );
		return FALSE;
	}
#endif 

	//////////////////////////////////////////////////////////////////////////
	AfxBeginThread( StartSocketThread, NULL );

	SetTimer( WM_TIMING_CHKIMAGE, MAX_TIME30MIN*1000, NULL );
	return TRUE;  
}
//////////////////////////////////////////////////////////////////////////
//
void CCSServerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

//////////////////////////////////////////////////////////////////////////
//
void CCSServerDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//////////////////////////////////////////////////////////////////////////
//
HCURSOR CCSServerDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

//////////////////////////////////////////////////////////////////////////
// 初始化对像
void   CCSServerDlg::InitApp( void ){
	
	m_oCSSClientDlg.Create(IDD_CSS_CLIENT_DLG, this);	
	m_pWndClientPane->Attach(&m_oCSSClientDlg);
	m_pWndClientPane->SetTitle(GetLangStr(TEXT_CLS_SERVER));
	
	m_oBSDlg.Create(IDD_BS_DLG, this);
	m_pWndBSPane->Attach(&m_oBSDlg);
	m_pWndBSPane->SetTitle(GetLangStr(TEXT_DBS_SERVER ) );
	
	m_oDESDlg.Create(IDD_DES_DLG, this);	
	m_pWndDESPane->Attach(&m_oDESDlg);
	m_pWndDESPane->SetTitle(GetLangStr(TEXT_DES_SERVER));

	m_oDatabaseDlg.Create(IDD_DATABASE_DLG, this);
	m_pWndDataBasePane->Attach( &m_oDatabaseDlg );
	m_pWndDataBasePane->SetTitle(GetLangStr(TEXT_DATABASE_CONNECT));
}

////////////////////////////////////////////////////////////////////
// 
CString CCSServerDlg::GetIniFileName(){

	CString			strResult;	

	strResult = GetModulePath( )+"\\CSServer.ini";
	return strResult;
}

////////////////////////////////////////////////////////////////////
//  
void CCSServerDlg::GetInitData(){
	
	CString			strAppName;
	CString			strKey;
	CString			strValue;
	CString			strData;
	
	
	strAppName = "CSServer";
	
	strKey="Version";
	GetPrivateProfileString( strAppName, strKey, "", strValue.GetBuffer(256), 255, GetIniFileName() );
	strValue.ReleaseBuffer();

	m_strVersion.LoadString(IDS_VERSION);

	// CSS_V2.05_20100402
	strData = strValue.Left(5);
	//if( m_strVersion == strValue ){
	if( m_strVersion.Find( strData) == 0 ){
		RestoreInitData();
	}
	else{
		strValue = m_strVersion;
		SaveInitData();
		WritePrivateProfileString( strAppName, strKey, strValue, GetIniFileName() );
	}
	return;
}

////////////////////////////////////////////////////////////////////
//  读取日志
void CCSServerDlg::RestoreInitData(){

	CString			strAppName;
	CString			strKey;
	CString			strValue;
	
	
	strAppName = "CSServer";
	
	strKey="DESTCPPort";
	GetPrivateProfileString( strAppName, strKey, "", strValue.GetBuffer(256), 255, GetIniFileName() );
	m_nDESTCPPort = atoi( strValue.GetBuffer(0) );
	strValue.ReleaseBuffer( );
	
	strKey="CSTCPPort";
	GetPrivateProfileString( strAppName, strKey, "", strValue.GetBuffer(256), 255, GetIniFileName() );
	m_nCSTCPPort = atoi( strValue.GetBuffer(0) );
	strValue.ReleaseBuffer( );

	strKey="BSTCPPort";
	GetPrivateProfileString( strAppName, strKey, "", strValue.GetBuffer(256), 255, GetIniFileName() );
	m_nBSTCPPort = atoi( strValue.GetBuffer(0) );
	strValue.ReleaseBuffer( );
	
	//  服务器名
	strKey="ServerName";
	GetPrivateProfileString( strAppName, strKey, "", strValue.GetBuffer(256), 255, GetIniFileName() );
	strValue.ReleaseBuffer( );
	m_strServerName = strValue;

	//  数据库名
	strKey="DatabaseName";
	GetPrivateProfileString( strAppName, strKey, "", strValue.GetBuffer(256), 255, GetIniFileName() );
	strValue.ReleaseBuffer( );
	m_strDatabaseName = strValue;

	//  用户名
	strKey="UserName";
	GetPrivateProfileString( strAppName, strKey, "", strValue.GetBuffer(256), 255, GetIniFileName() );
	strValue.ReleaseBuffer( );
	m_strUserName = strValue;

	//  用户密码
	strKey="UserPsd";	
	GetPrivateProfileString( strAppName, strKey, "", strValue.GetBuffer(256), 255, GetIniFileName() );
	strValue.ReleaseBuffer( );
	m_strUserPsd =	DecryptPassword(strValue);

	// 授权码
	strKey = "AuthorCode";
	GetPrivateProfileString( strAppName, strKey, "", strValue.GetBuffer(256), 255, GetIniFileName() );
	strValue.ReleaseBuffer();
	m_strAuthor = strValue;
	return;
}

////////////////////////////////////////////////////////////////////
//  保存日志
void CCSServerDlg::SaveInitData(){

	
	CString			strAppName;
	CString			strKey;
	CString			strValue;
	
	strAppName = "CSServer";	

	strKey="DESTCPPort";
	strValue.Format("%d",m_nDESTCPPort);		
	WritePrivateProfileString( strAppName, strKey, strValue, GetIniFileName() );

	strKey="CSTCPPort";
	strValue.Format("%d",m_nCSTCPPort);		
	WritePrivateProfileString( strAppName, strKey, strValue, GetIniFileName() );

	strKey="BSTCPPort";
	strValue.Format("%d",m_nBSTCPPort);		
	WritePrivateProfileString( strAppName, strKey, strValue, GetIniFileName() );
		
	strKey="ServerName";		
	strValue = m_strServerName;
	WritePrivateProfileString( strAppName, strKey, strValue, GetIniFileName() );

	strKey="DatabaseName";	
	strValue = m_strDatabaseName;
	WritePrivateProfileString( strAppName, strKey, strValue, GetIniFileName() );

	strKey="UserName";		
	strValue = m_strUserName;
	WritePrivateProfileString( strAppName, strKey, strValue, GetIniFileName() );

	strKey="UserPsd";	
	strValue = EncryptPassword( m_strUserPsd );
	WritePrivateProfileString( strAppName, strKey, strValue, GetIniFileName() );
	
	// 授权码
	strKey = "AuthorCode";
	strValue = m_strAuthor;
	WritePrivateProfileString( strAppName, strKey, strValue, GetIniFileName() );
	return;
}

//////////////////////////////////////////////////////////////////////////
//
void  CCSServerDlg::GetInitConfig(void ){

	m_strlocalIP =	GetLocalIP();
	// 数据库操作
	m_oDatabaseDlg.SetServerName( m_strServerName );
	m_oDatabaseDlg.SetDatabaseName( m_strDatabaseName );
	m_oDatabaseDlg.SetUserName( m_strUserName );
	m_oDatabaseDlg.SetUserPsd( m_strUserPsd );

	// BS设置
	m_oBSDlg.SetLocalIP( m_strlocalIP );
	m_oBSDlg.SetLocalPort( m_nBSTCPPort );
	// CL设置
	m_oCSSClientDlg.SetLocalIP( m_strlocalIP );
	m_oCSSClientDlg.SetLocalPort( m_nCSTCPPort );
	// DES设置
	m_oDESDlg.SetLocalIP( m_strlocalIP );
	m_oDESDlg.SetLocalPort( m_nDESTCPPort );
}
//////////////////////////////////////////////////////////////////////////
//
void  CCSServerDlg::GetInitStatusBar( void ){

	CString     strTime;
	CString		strData;
	CTime		oTime;
	
	oTime   = CTime::GetCurrentTime();		
	strTime.Format("%s: ", GetLangStr(TEXT_TIME) );
	strTime += oTime.Format("%Y-%m-%d %H:%M:%S ");
	m_wndStatusBar.SetPaneWidth(0, 410);
	m_wndStatusBar.SetPaneWidth(1, 185);
	
	strData.Format(" %s: %s ", GetLangStr(TEXT_VERSION),m_strVersion );
	m_wndStatusBar.SetPaneText(0, strData);
	m_wndStatusBar.SetPaneText(1,strTime);	
	SetTimer(WM_UPDATE_TIME,1000,NULL);
}

//////////////////////////////////////////////////////////////////////////
//
void	CCSServerDlg::SaveParameterConfig( WPARAM  wParam, LPARAM lParam ){

	//////////////////////////////////////////////////////////////////////////
	m_strServerName = m_oDatabaseDlg.GetServerName();
	m_strDatabaseName = m_oDatabaseDlg.GetDatabaseName();
	m_strUserName = m_oDatabaseDlg.GetUserName();
	m_strUserPsd = m_oDatabaseDlg.GetUserPsd();
	//////////////////////////////////////////////////////////////////////////
	m_nBSTCPPort = m_oBSDlg.GetLocalPort();
	//////////////////////////////////////////////////////////////////////////
	m_nDESTCPPort = m_oDESDlg.GetLocalPort();
	//////////////////////////////////////////////////////////////////////////
	m_nCSTCPPort = m_oCSSClientDlg.GetLocalPort();
	SaveInitData();
}

//////////////////////////////////////////////////////////////////////////
//
LRESULT CCSServerDlg::OnKickIdle(WPARAM, LPARAM){
	
	m_paneManager.UpdatePanes();	
	m_wndStatusBar.SendMessage(WM_IDLEUPDATECMDUI, TRUE);	
	return 0;
}

//////////////////////////////////////////////////////////////////////////
//
void CCSServerDlg::OnSize(UINT nType, int cx, int cy){

	CDialog::OnSize(nType, cx, cy);
	
	CRect rcClient(0, 0, cx, cy);
	RepositionBars(0, 0xffff, AFX_IDW_PANE_FIRST, 0, 0, &rcClient);
	
	RepositionBars(0, 0xffff, AFX_IDW_PANE_FIRST, reposQuery, &rcClient, &rcClient);
	if (m_oDataInfo.GetSafeHwnd()){	
		
		m_oDataInfo.MoveWindow(rcClient);
	}
}

//////////////////////////////////////////////////////////////////////////
// CL TCP SOCKET 联接
BOOL	CCSServerDlg::StartCLTCPServer( void ){
	
	return m_oCLTCPServer.StartServer(GetCLTCPPort(),
		SOCK_STREAM, RecvCLTCPDataProcess );
}

//////////////////////////////////////////////////////////////////////////
// CLOSE CL TCP SOCKET 联接
void	CCSServerDlg::StopCLTCPServer( void ){
	
	CString				strKey;
	POSITION			pos ;
	CClientData			*pClientData = NULL;	
	
	m_oCLTCPServer.Stop();	
	pos =	m_oMapUserToSocket.GetStartPosition();
	while ( pos != NULL ){
		m_oMapUserToSocket.GetNextAssoc(pos, strKey, (void*&)pClientData );
		if ( pClientData ){
			delete  pClientData;
			pClientData = NULL;
		}
		m_oMapUserToSocket.RemoveKey( strKey );
	}
}

//////////////////////////////////////////////////////////////////////////
// BS TCP SOCKET 联接
BOOL	CCSServerDlg::StartBSTCPServer( void ){

	return m_oBSTCPServer.StartServer(GetBSTCPPort(),
		SOCK_STREAM, RecvBSTCPDataProcess );
}

//////////////////////////////////////////////////////////////////////////
// CLOSE BS TCP SOCKET 联接
void	CCSServerDlg::StopBSTCPServer( void ){
		
	m_oBSTCPServer.Stop();
}

//////////////////////////////////////////////////////////////////////////
// DES TCP SOCKET 联接
BOOL	CCSServerDlg::StartDESTCPServer( void ){
	
	return m_oDESTCPServer.StartServer(GetDESTCPPort(),
		SOCK_STREAM, RecvDESTCPDataProcess );
}

//////////////////////////////////////////////////////////////////////////
// CLOSE DES TCP SOCKET 联接
void	CCSServerDlg::StopDESTCPServer( void ){
	
	CString				strKey ;
	POSITION			pos;
	CClientSocket		*pSocket = NULL;
	
	pos  = m_oMapDESToSocket.GetStartPosition();
	while ( pos != NULL ){
		m_oMapDESToSocket.GetNextAssoc( pos, strKey, (void*&)pSocket );
		if ( pSocket != NULL ){
			pSocket->Close();
			delete pSocket;
			pSocket = NULL;
		}
		m_oMapDESToSocket.RemoveKey( strKey );	
		if ( m_oDESTCPServer.m_pSocket ){
			((CServerSocket*)m_oDESTCPServer.m_pSocket)->DecAccpetSockets();
		}
	}

	m_oDESTCPServer.Stop();
}

//////////////////////////////////////////////////////////////////////////
// Database 联接
BOOL	CCSServerDlg::StartConnectDatabase(void){
	
	StopConnectDataBase();
	// 
	CCSProtocolData::SetDatabaseParameter( m_strServerName, m_strDatabaseName, m_strUserName, m_strUserPsd );

	if ( CDBData::Connect( m_strServerName, m_strDatabaseName, m_strUserName, m_strUserPsd ) ){

		if( CDBData::DBGetImagePath( m_strImagePPath, m_strImageVPath ) ){
			CCSProtocolData::SetImagePath( m_strImagePPath, m_strImageVPath );
		}
		if( CDBData::GetVehicleCurrent() > CDBData::GetSoftwareVehicleTotal() ){
			SendMessage( WM_SOFTWART_ERROR_EXIT , 0, NULL );
		}
		CCSProtocolData::SetServerUserPsd( m_strUserName, m_strUserPsd );
		return  TRUE;
	}
	else{
		return FALSE;
	}
	return FALSE;
}
//////////////////////////////////////////////////////////////////////////
//
void	CCSServerDlg::OnSoftwartErrorEixt( WPARAM  wParam, LPARAM  lParam ){

	StopCLTCPServer(  );
	StopBSTCPServer(  );
	StopDESTCPServer(  );
	StopConnectDataBase(  );
	CCSProtocolData::ADBDeleteCriticalSection();
	CDialog::OnClose();
	CDialog::OnOK();
	if( wParam == 0 ){
		MessageBox( "Error: 1536!", GetLangStr(TEXT_WARNING), MB_OK|MB_ICONINFORMATION ); 	
	}
	else{
		MessageBox( "Error: 1537!", GetLangStr(TEXT_WARNING), MB_OK|MB_ICONINFORMATION ); 	
	}
}

//////////////////////////////////////////////////////////////////////////
// 关闭 Database 联接
void	CCSServerDlg::StopConnectDataBase( void ){
	
	CDBData::DisConnect();
}

//////////////////////////////////////////////////////////////////////////
//
void	CCSServerDlg::OnSocketStartStop( WPARAM wParam, LPARAM  lParam ){

	switch( wParam ){
	case 0:
		if( m_oDESTCPServer.m_bStart ){
			m_nConnectStatus &= ~0x01;
			StopDESTCPServer();
			m_oDESTCPServer.m_bStart = FALSE;
			m_oDESDlg.IsConnectionStatus(m_oDESTCPServer.m_bStart);
			
		}
		else{
			m_nConnectStatus |= 0x01;
			m_oDESTCPServer.m_bStart = StartDESTCPServer();
			m_oDESDlg.IsConnectionStatus(m_oDESTCPServer.m_bStart);
		}
		break;
		
	case 1:
		if( IsBSWorkMode() ){
			if( m_oBSTCPServer.m_bStart){
				m_nConnectStatus &= ~0x02;
				StopBSTCPServer();
				m_oBSTCPServer.m_bStart = FALSE;
				m_oBSDlg.IsConnectionStatus(m_oBSTCPServer.m_bStart);
			}
			else{
				m_nConnectStatus |= 0x02;
				m_oBSTCPServer.m_bStart = StartBSTCPServer();
				m_oBSDlg.IsConnectionStatus(m_oBSTCPServer.m_bStart);
			}
		}
		break;
		
	case 2:
		if( IsCSWorkMode() ){
			if( m_oCLTCPServer.m_bStart ){
				m_nConnectStatus &= ~0x04;
				StopCLTCPServer();
				m_oCLTCPServer.m_bStart = FALSE;
				m_oCSSClientDlg.IsConnectionStatus(m_oCLTCPServer.m_bStart);
			}
			else{
				m_nConnectStatus |= 0x04;
				m_oCLTCPServer.m_bStart = StartCLTCPServer();
				m_oCSSClientDlg.IsConnectionStatus( m_oCLTCPServer.m_bStart );
			}
		}
		break;
	case 3:
		if( m_bDatabaseStart ){
			m_nConnectStatus &= ~0x08;	
			m_bDatabaseStart = FALSE;
			StopConnectDataBase( );
			m_oDatabaseDlg.IsConnectionStatus( FALSE );			
		}
		else{			
			m_nConnectStatus |= 0x08;
			if( StartConnectDatabase() ){
				m_bDatabaseStart = TRUE;
			}			
			m_oDatabaseDlg.IsConnectionStatus( m_bDatabaseStart );
		}
		break;	
	default:
		ASSERT(FALSE);
		break;
	}
}

/////////////////////////////////////////////////////////////////////////////
// DES　TCP Server的活动连接
int	CCSServerDlg::GetDESTCPActiveConnect( void ){ 
	
	if( m_oDESTCPServer.m_pSocket ){
		return ((CServerSocket*)(m_oDESTCPServer.m_pSocket))->GetAccpetSockets();
	}
	else{
		return 0;
	}
}

/////////////////////////////////////////////////////////////////////////////
// BS　TCP Server的活动连接
int	CCSServerDlg::GetBSTCPActiveConnect( void ){ 
	
	if( m_oBSTCPServer.m_pSocket ){
		return ((CServerSocket*)(m_oBSTCPServer.m_pSocket))->GetAccpetSockets();
	}
	else{
		return 0;
	}
}

/////////////////////////////////////////////////////////////////////////////
// CL　TCP Server的活动连接
int	CCSServerDlg::GetCLTCPActiveConnect( void ){ 
	
	if( m_oCLTCPServer.m_pSocket ){
		return ((CServerSocket*)(m_oCLTCPServer.m_pSocket))->GetAccpetSockets();
	}
	else{
		return 0;
	}
}

//////////////////////////////////////////////////////////////////////////
//
void	CCSServerDlg::SetDESTCPHelpInfo(LPVOID lpBuf, int nDataLen, BOOL bRecvFlag, PSOCKADDR pSockAddr /* = NULL  */){

	CString		strName;

	if ( m_oDESDlg.SetRecHelpInfo( nDataLen, bRecvFlag )){

		strName = "DESTCP" ;
		ShowReceData( strName.GetBuffer(0), strName.GetLength(), lpBuf, nDataLen, bRecvFlag, pSockAddr  );
		strName.ReleaseBuffer();
	}
}

//////////////////////////////////////////////////////////////////////////
//
void	CCSServerDlg::SetBSTCPHelpInfo(LPVOID lpBuf, int nDataLen, BOOL bRecvFlag, PSOCKADDR pSockAddr /* = NULL  */){
	
	CString		strName;

	if ( m_oBSDlg.SetRecHelpInfo( nDataLen, bRecvFlag )){
		
		strName = "BSTCP" ;
		ShowReceData( strName.GetBuffer(0), strName.GetLength(), lpBuf, nDataLen, bRecvFlag, pSockAddr  );
		strName.ReleaseBuffer();
	}
}

//////////////////////////////////////////////////////////////////////////
//
void	CCSServerDlg::SetCSTCPHelpInfo(LPVOID lpBuf, int nDataLen, BOOL bRecvFlag, PSOCKADDR pSockAddr /* = NULL  */){
	
	CString		strName;

	if ( m_oCSSClientDlg.SetRecHelpInfo( nDataLen, bRecvFlag )){
	
		strName = "CLS" ;
		ShowReceData( strName.GetBuffer(0), strName.GetLength(), lpBuf, nDataLen, bRecvFlag, pSockAddr  );
		strName.ReleaseBuffer();
	}
}

//////////////////////////////////////////////////////////////////////////
//
void    CCSServerDlg::ShowReceData(char *pAppName, int nAppLen, LPVOID lpBuf, int nDataLen, BOOL bRecvFlag, PSOCKADDR pSockAddr /* = NULL  */){
	
	PSTHELPDATA	  pHelpData = NULL;
	
	pHelpData = new STHELPDATA;
	pHelpData->m_pBuf = (char*) malloc(nDataLen);
	pHelpData->m_pAppName = (char*) malloc( nAppLen );
	pHelpData->m_nDataLen = nDataLen;
	pHelpData->m_nAppLen = nAppLen;
	pHelpData->m_bRecFlag = bRecvFlag;
	pHelpData->m_pDlg = this;
	memcpy( pHelpData->m_pAppName, pAppName, nAppLen );
	memcpy( pHelpData->m_pBuf, lpBuf, nDataLen );
	if ( pSockAddr ){
		memcpy(&pHelpData->m_oSockAddr, pSockAddr, sizeof(SOCKADDR));
	}
	AfxBeginThread( AddAppHelpDataThread, pHelpData );
}

//////////////////////////////////////////////////////////////////////////
//
void CCSServerDlg::OnOK(){

	CDialog::OnOK();
}

//////////////////////////////////////////////////////////////////////////
//
void CCSServerDlg::OnClose(){

	if( MessageBox(GetLangStr(TEXT_ARE_YOU_SURE), GetLangStr(TEXT_EXIT), MB_ICONASTERISK|MB_ICONINFORMATION|MB_YESNO) == IDYES ){

		StopCLTCPServer(  );
		StopBSTCPServer(  );
		StopDESTCPServer(  );
		StopConnectDataBase(  );
		// 释放组织数据
		m_oQuerySocketObj.DeleteComposeObject( );
		KillTimer(WM_TIMER_CHECK);
		KillTimer( WM_TIMING_CHKIMAGE );
		CCSProtocolData::ADBDeleteCriticalSection();
		CDialog::OnClose();
	}	
}

//////////////////////////////////////////////////////////////////////////
//
void CCSServerDlg::OnAddLongUserData( WPARAM wParam, LPARAM lParam ){
	
	CString					strUserKey;
	BOOL					bFlag = FALSE;
	CClientData				*pTmpData = NULL;
	CClientData				*pData = (CClientData*)lParam;

	if ( pData != NULL ){
		
		if ( m_oMapUserToSocket.Lookup(pData->m_strUser, (void*&)pTmpData)){
			bFlag = TRUE;
		}
		if ( bFlag ){
			m_oCSSClientDlg.DeleteUserlogInfo( pTmpData->m_strUser, pTmpData->m_strPeerIP );
			// 关闭以前相同的用户		
			CloseUserLogin( pTmpData->m_strUser, 1 );
			// 再增加计数
			((CServerSocket*)m_oCLTCPServer.m_pSocket)->IncAccpetSockets();
		}
		else{
			if ( m_oCLTCPServer.m_pSocket ){
				((CServerSocket*)m_oCLTCPServer.m_pSocket)->IncAccpetSockets();
			}
		}
		m_oMapUserToSocket.SetAt( pData->m_strUser, pData );
		m_oCSSClientDlg.AddUserLogInfo( pData->m_strUser, pData->m_strPeerIP, pData->m_nPeerPort, pData->m_oStartTime );
	}	
}

//////////////////////////////////////////////////////////////////////////
//
void CCSServerDlg::DeleteUserloginInfo( CClientData *pData, unsigned char nType /* = 0 */ ){ //CClientData	*pData ){

	int				nLen = 0;
	char			*pBuf = NULL;
	CString			strUserName;

	strUserName.Format( "%s", pData->m_strUser );
	m_oCSSClientDlg.DeleteUserlogInfo( pData->m_strUser, pData->m_strPeerIP );	
	if( pData != NULL ){		
		
		nLen  = strUserName.GetLength();
		pBuf =(char*) malloc( nLen+1 );
		ASSERT(pBuf);
		memset( pBuf, 0x00, nLen+1 );
		strncpy( pBuf, strUserName.GetBuffer(0), nLen );
		strUserName.ReleaseBuffer();

	//	m_oSoftKey.Ystrcpy( pBuf, strUserName.GetBuffer(0) );
	//	strUserName.ReleaseBuffer();
		
		if( nType == 0 ){
			AfxBeginThread( ProcessDelLoginOutUser, pBuf );
		}
		
		((CServerSocket*)m_oCLTCPServer.m_pSocket)->DecAccpetSockets();
		m_oMapUserToSocket.RemoveKey( pData->m_strUser );
		pData->FreeMemory();
		delete pData;
		pData = NULL;		
	}
}

//////////////////////////////////////////////////////////////////////////
//  关闭用户登陆
void  CCSServerDlg::CloseUserMessage( WPARAM wParam, LPARAM lParam ){
	
	CString		strUserName;

	strUserName.Format("%s", lParam );
	CloseUserLogin( strUserName );
}

//////////////////////////////////////////////////////////////////////////
//
void  CCSServerDlg::CloseUserLogin( CString strUserName, unsigned char nType /* = 0 */ ) {

	CClientData		*pData = NULL;

	if ( m_oMapUserToSocket.Lookup(strUserName, (void*&)pData)){

		DeleteUserloginInfo( pData, nType );		
	}
}

//////////////////////////////////////////////////////////////////////////
//  关闭
void   CCSServerDlg::OnSocketClose( WPARAM wParam, LPARAM  lParam ){

	CString				strKey;	
	POSITION			pos ;
	BOOL				bFind = FALSE;
	CClientData			*pClientData = NULL;
	CClientSocket		*pTmpSocket = NULL;
	CClientSocket		*pSocket = (CClientSocket*)lParam;

	//////////////////////////////////////////////////////////////////////////
	//
	m_oQuerySocketObj.ObjectEnterCriticalSection();
	m_oQuerySocketObj.DeleteComposeObject( pSocket );
	m_oQuerySocketObj.ObjectLeaveCriticalSection();
	//////////////////////////////////////////////////////////////////////////
	//  检测用户数
	pos = m_oMapUserToSocket.GetStartPosition();
	while ( pos != NULL ){
		m_oMapUserToSocket.GetNextAssoc( pos, strKey, (void*&)pClientData );
		if ( pClientData != NULL){
			if ( pClientData->m_pClientSocket == pSocket ){
				
				DeleteUserloginInfo( pClientData );
				bFind = TRUE;
				break;
			}
		}
	}	
	// 检测DES
	if ( bFind == FALSE ){
		pos = m_oMapDESToSocket.GetStartPosition();
		while ( pos != NULL ){
			m_oMapDESToSocket.GetNextAssoc( pos, strKey, (void*&)pTmpSocket );
			if ( pTmpSocket != NULL ){
				if ( pTmpSocket == pSocket ){
					if ( m_oDESTCPServer.m_pSocket ){
						((CServerSocket*)m_oDESTCPServer.m_pSocket)->DecAccpetSockets();
					}			
					m_oMapDESToSocket.RemoveKey( strKey );
					pSocket->Close( );
					delete pSocket;
					pSocket = NULL;
					bFind = TRUE;
					break;
				}
			}	
		}
	}
	//
	if( bFind == FALSE ){
		//	ASSERT( FALSE );		
		TRACE( "not Find socket\r\n");
	}
}

//////////////////////////////////////////////////////////////////////////
//  
void   CCSServerDlg::OnSocketConnect( WPARAM wParam, LPARAM lParam ){

	
}
//////////////////////////////////////////////////////////////////////////
//	DES连接数
void  CCSServerDlg::AddDESConnection( WPARAM wParam, LPARAM lParam ){
	
	CString				strData;
	CString				strKey;
	int					nSize = 0;
	POSITION			pos;
	CClientSocket		*pTmpSocket = NULL;
	CClientSocket		*pSocket = (CClientSocket*)lParam;
	
	if ( pSocket != NULL ){
		pos = m_oMapDESToSocket.GetStartPosition();
		while ( pos != NULL ){
			m_oMapDESToSocket.GetNextAssoc( pos, strKey, (void*&)pTmpSocket);
			nSize++;
		}
		strData.Format("DES%d", nSize );
		m_oMapDESToSocket.SetAt( strData, pSocket );
		((CServerSocket*)m_oDESTCPServer.m_pSocket)->IncAccpetSockets();
	}
}

//////////////////////////////////////////////////////////////////////////
//  发送数据到DES服务器
void  CCSServerDlg::SendDESBuf(char *lpBuf, int nLen ){

	CString			 strKey;
	int				 nSockAddrLen;
	POSITION		 pos;
	SOCKADDR		 oSOCKADDR;
	CClientSocket	 *pSocket = NULL;

	nSockAddrLen = sizeof( SOCKADDR );
	pos = m_oMapDESToSocket.GetStartPosition();
	while ( pos != NULL ){
		m_oMapDESToSocket.GetNextAssoc( pos, strKey, (void*&)pSocket );		
		if ( pSocket != NULL ){
			pSocket->GetPeerName( &oSOCKADDR,   &nSockAddrLen );
			pSocket->AddSendData( lpBuf, nLen,  &oSOCKADDR );
		}		
	}
}

//////////////////////////////////////////////////////////////////////////
//   收到DES发送数据事件
void	CCSServerDlg::PushDataToDESSendBuf( WPARAM wParam, LPARAM lParam ){

	SendDESBuf((char*)lParam,  wParam );
}

//////////////////////////////////////////////////////////////////////////
//  发送数据到BS服务器
void  CCSServerDlg::PushDataToBSSendBuf( WPARAM wParam, LPARAM lParam ){
	
	PSTSOCKETDATA	pSendData = NULL;
	
	pSendData = (PSTSOCKETDATA)lParam;		
	if( pSendData->m_pSocket &&
		(pSendData->m_pSocket->m_hSocket == wParam)){
		((CClientSocket*)(pSendData->m_pSocket))->AddSendData(pSendData->m_pDataBuf, pSendData->m_nDataLen, &pSendData->m_oSOCKADDR );
		SetBSTCPHelpInfo( pSendData->m_pDataBuf, pSendData->m_nDataLen, FALSE, &pSendData->m_oSOCKADDR);
	}
}


//////////////////////////////////////////////////////////////////////////
//  发送数据到CL服务器
void  CCSServerDlg::PushDataToCLSendBuf( WPARAM wParam, LPARAM lParam ){
	
	PSTSOCKETDATA	pSendData = NULL;
	
	pSendData = (PSTSOCKETDATA)lParam;		
	if( pSendData->m_pSocket && 
		(pSendData->m_pSocket->m_hSocket == wParam)){
		((CClientSocket*)(pSendData->m_pSocket))->AddSendData(pSendData->m_pDataBuf, pSendData->m_nDataLen, &pSendData->m_oSOCKADDR );
		SetCSTCPHelpInfo( pSendData->m_pDataBuf, pSendData->m_nDataLen, FALSE, &pSendData->m_oSOCKADDR);
	}
}

//////////////////////////////////////////////////////////////////////////
//
void CCSServerDlg::FindUserToSocketSendBuf( WPARAM  wParam, LPARAM  lParam ){

	PSTUSERSENDINFO			pSendUserInfo = (PSTUSERSENDINFO)lParam;
	
	FindUserToCLSendBuf( pSendUserInfo->m_nUSER, pSendUserInfo->m_pSendBuf, pSendUserInfo->m_nDataLen );
}

//////////////////////////////////////////////////////////////////////////
//  发送到指定用户
void  CCSServerDlg::FindUserToCLSendBuf( CString  strUserName,  char *lpBuf, int nLen ){

	int					nSockAddrLen;
	SOCKADDR			oSOCKADDR;
	CClientData			*pClientData = NULL;
	
	if ( m_oMapUserToSocket.Lookup( strUserName, (void*&) pClientData) ){

		if ( pClientData != NULL ){
			if ( pClientData->m_pClientSocket != NULL ){
				nSockAddrLen = sizeof( SOCKADDR );
				pClientData->m_pClientSocket->GetPeerName( &oSOCKADDR, &nSockAddrLen );
				pClientData->m_pClientSocket->AddSendData( lpBuf, nLen , &oSOCKADDR );
				SetCSTCPHelpInfo( lpBuf, nLen, FALSE, &oSOCKADDR );
			}			
		}
	}
}

//////////////////////////////////////////////////////////////////////////
//
void  CCSServerDlg::OnEditClear(){
	
	m_strDataInfo.Empty();
	GetDlgItem(IDC_EDIT_DATA_INFO)->SetWindowText("");
}
//////////////////////////////////////////////////////////////////////////
// 
void  CCSServerDlg::OnDESServer(){
	
	m_paneManager.ShowPane( IDR_DESPANE );
}
//////////////////////////////////////////////////////////////////////////
//
void  CCSServerDlg::OnBSServer(){

	m_paneManager.ShowPane(IDR_BSPANE );
}
//////////////////////////////////////////////////////////////////////////
//
void  CCSServerDlg::OnClsServer(){
	
	m_paneManager.ShowPane(IDR_CSSCLIENTPANE );
}
//////////////////////////////////////////////////////////////////////////
//
void  CCSServerDlg::OnDatabaseServer(){
	
	m_paneManager.ShowPane(IDR_DATABASEPANE );
}
//////////////////////////////////////////////////////////////////////////
//
void CCSServerDlg::OnTimer(UINT nIDEvent) 
{
	CString     strCLSStatus;
	CString     strDESStatus;
	CString		strBSStatus;
	CString		strData;
	CString     strTime;
	CTime		oTime;
	
	if ( nIDEvent == WM_UPDATE_TIME){
		
		if ( m_oDESTCPServer.m_bStart ){
			strDESStatus.Format("DES:TCP %s",  GetLangStr(TEXT_ENABLE));
		}
		else{
			strDESStatus.Format("DES:TCP %s",  GetLangStr(TEXT_DISABLE));
		}
		if ( m_oCLTCPServer.m_bStart )	{
			strCLSStatus.Format("CLS:TCP %s",  GetLangStr(TEXT_START));
		}
		else{
			strCLSStatus.Format("CLS:TCP %s",  GetLangStr(TEXT_DISABLE));
		}
		if ( m_oBSTCPServer.m_bStart )	{
			strBSStatus.Format("BS:TCP %s",  GetLangStr(TEXT_START));
		}
		else{
			strBSStatus.Format("BS:TCP %s",  GetLangStr(TEXT_DISABLE));
		}
		strData.Format(" %s: %s  %s  %s  %s", GetLangStr(TEXT_VERSION),m_strVersion, strDESStatus , strCLSStatus, strBSStatus);
		m_wndStatusBar.SetPaneText(0, strData);
		
		oTime = CTime::GetCurrentTime();
		strTime.Format("%s: ", GetLangStr(TEXT_TIME));
		strTime += oTime.Format("%Y-%m-%d %H:%M:%S ");
		m_wndStatusBar.SetPaneText(1,strTime);
	}	
	if( nIDEvent == WM_TIMER_CHECK ){
		OnTimingCheckKey();
	}
	if( nIDEvent == WM_TIMING_CHKIMAGE ){
		// 定时删除内存图片
		CCSProtocolData::DelTimingChkImage();
	}
	CDialog::OnTimer(nIDEvent);
}
//////////////////////////////////////////////////////////////////////////
//
BOOL CCSServerDlg::PreTranslateMessage(MSG* pMsg) 
{
	if(pMsg->message==WM_RBUTTONDOWN)  { 
		if(pMsg->hwnd==::GetDlgItem(m_hWnd,IDC_EDIT_DATA_INFO))   
		{   					
			CXTPCommandBars::TrackPopupMenu( &m_oMainMenu , TPM_LEFTALIGN|TPM_LEFTBUTTON|TPM_RIGHTBUTTON, pMsg->pt.x,pMsg->pt.y, this);
			return   TRUE;   
		}   
	}
	return CDialog::PreTranslateMessage(pMsg);
}
//////////////////////////////////////////////////////////////////////////
//
void CCSServerDlg::OnExit() 
{
	OnClose();	
	CDialog::OnOK();
}
//////////////////////////////////////////////////////////////////////////
//
typedef		struct _ASTAT_{
	
	ADAPTER_STATUS	adapt;
	NAME_BUFFER		nameBuff[30];	
}ASTAT, *PASTAT;

//////////////////////////////////////////////////////////////////////////
//
CString	CCSServerDlg::GetMacAddr( ){
	
	LANA_ENUM		lana_enum;
	NCB				ncb;
	ASTAT			Adapter;	
	unsigned char	uRetCode;
	CString			strMAC;
	
	
	memset(&ncb, 0, sizeof(ncb));
	ncb.ncb_command = NCBENUM;
	ncb.ncb_buffer = (unsigned char *)&lana_enum;
	ncb.ncb_length = sizeof(lana_enum);
	uRetCode = Netbios(&ncb);
	
	if(uRetCode != NRC_GOODRET){
		return	"";
	}
	
	memset(&ncb, 0, sizeof(ncb));
	ncb.ncb_command = NCBRESET;
	ncb.ncb_lana_num = lana_enum.lana[0];
	uRetCode = Netbios(&ncb);
	
	if(uRetCode != NRC_GOODRET){
		return	"";
	}
	
	memset(&ncb, 0, sizeof(ncb));
	ncb.ncb_command = NCBASTAT;
	ncb.ncb_lana_num = lana_enum.lana[0];
	strcpy((char *)ncb.ncb_callname, "*");
	ncb.ncb_buffer = (unsigned char *)&Adapter;
	ncb.ncb_length = sizeof(Adapter);
	uRetCode = Netbios(&ncb);
	if(uRetCode != NRC_GOODRET){
		return	"";
	}
	
	strMAC.Format("%02X%02X%02X%02X%02X%02X",
		Adapter.adapt.adapter_address[0],
		Adapter.adapt.adapter_address[1],
		Adapter.adapt.adapter_address[2],
		Adapter.adapt.adapter_address[3],
		Adapter.adapt.adapter_address[4],
		Adapter.adapt.adapter_address[5]);
	
	return strMAC;
}
//////////////////////////////////////////////////////////////////////////
//   
CString	 CCSServerDlg::Decode( CString	strSrc, int nKey ){
	
	char		*pEnd = NULL;
	CString		strResult;
	CString		strTmp;
	BOOL		bExit = FALSE;
	int			nCnt = 0;
	
	while ( !bExit ){
		unsigned long		ulTmp;
		char				nTmp[25];
		
		if( strSrc.GetLength() <= 4 ){
			bExit = TRUE;
			strTmp = strSrc;
		}
		else{
			strTmp = strSrc.Left(4);
			strSrc = strSrc.Mid(4);
		}
		
		ulTmp = strtoul( strTmp.GetBuffer(0), &pEnd, 16 );
		strTmp.ReleaseBuffer();
		ulTmp += nKey;
		ulTmp += nCnt++;
		
		itoa( ulTmp, nTmp, 8 );
		if( strResult.IsEmpty() == FALSE ){
			strResult += "-";
		}
		strResult += nTmp;
	}
	return strResult;
}
////////////////////////////////////////////////////////////////////
//
void CCSServerDlg::GetPrivateData(){
	
	CFile				oFile;	
	unsigned char		*lpDest = NULL;
	int					nLen = 0;
	CString				strData = "";
	
	
	if( oFile.Open( GetModulePath()+"\\1.dat", CFile::modeRead ) ){
		nLen = oFile.GetLength();
		lpDest = (unsigned char *)malloc( nLen );
		oFile.Read( lpDest, nLen );
		
		nLen = DeCodeData( lpDest, lpDest, nLen, 12 );		
		*(lpDest+nLen) = 0x00;
		strData = lpDest;
		free( lpDest );
		lpDest = NULL;
		oFile.Close();
	}
	GetStringArrayFromString( m_oStrArrayVersion, strData, ';' );

	if( oFile.Open( GetModulePath()+"\\2.dat", CFile::modeRead ) ){
		nLen = oFile.GetLength();
		lpDest = (unsigned char *)malloc( nLen );
		oFile.Read( lpDest, nLen );
		
		nLen = DeCodeData( lpDest, lpDest, nLen, 12 );		
		*(lpDest+nLen) = 0x00;
		strData = lpDest;
		free( lpDest );
		lpDest = NULL;
		oFile.Close();
	}
	GetStringArrayFromString( m_oStrArrayTime, strData, ';' );
	return;
}

//////////////////////////////////////////////////////////////////////////
//		比较版本ID号
BOOL	CCSServerDlg::ComparisonVersionID( DWORD	dwVersionID ){
	
	unsigned char		nSize = 0;
	CString				strVersion;
	CString				strTmp;
	BOOL				bResult = FALSE;
	
	strVersion.Format("%d", dwVersionID );
	for ( int nCnt = 0; nCnt < m_oStrArrayVersion.GetSize(); nCnt++ ){
		strTmp = m_oStrArrayVersion.GetAt( nCnt );
		if( strTmp == strVersion ){
			bResult = TRUE;
			break;
		}
	}
	
	return bResult;
}
//////////////////////////////////////////////////////////////////////////
// 定时检测
void	CCSServerDlg::OnTimingCheckKey(){
	
	int			nRandomData;
	CString		strTmp;
	char		chBuf[20];
	
	KillTimer( WM_TIMER_CHECK );
	strcpy( chBuf, "MapTrack" );
	m_oSoftKey.YCompareString( chBuf, "MapTrack", strlen(chBuf) );		
	if( m_oSoftKey.YGetLastError() != 0 ){		
		SendMessage( WM_SOFTWART_ERROR_EXIT , 1, NULL );
		return;
	}	
	nRandomData = rand()%100;
	SetTimer(WM_TIMER_CHECK, 1000*60*nRandomData , NULL );
}
//////////////////////////////////////////////////////////////////////////
//
void   CCSServerDlg::OnSQLDisconnect( WPARAM	wParam, LPARAM  lParam ){

	m_nConnectStatus |= 0x08;	
	m_bDatabaseStart = FALSE;
	StopConnectDataBase( );
	m_oDatabaseDlg.IsConnectionStatus( FALSE );	
}