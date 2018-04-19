// CSSClientDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CSServer.h"
#include "CSSClientDlg.h"
#include "CSServerDlg.h"
#include "ConfigDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCSSClientDlg dialog


CCSSClientDlg::CCSSClientDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCSSClientDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCSSClientDlg)
	m_strConnNumber = _T("0");
	m_strLocalIP = _T("");
	m_strRecePack = _T("0");
	m_strRumTime = _T("0");
	m_strSendPack = _T("0");
	m_strStateInfo = _T("");
	//}}AFX_DATA_INIT
	m_nPort = 0;
	// 连接状态
	m_bStart = FALSE;
	// 接收包
	m_nRecvPackage = 0;
	// 发送包
	m_nSendPackage = 0;
	// 连接数
	m_nConnectNumber = 0;
	m_bShowStatus = FALSE;
}


void CCSSClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCSSClientDlg)
	DDX_Control(pDX, IDC_USER_LIST, m_oUserList);
	DDX_Control(pDX, IDC_CHECK_SHOW, m_oCheckShow);
	DDX_Control(pDX, IDC_PROPERTY_BUTTON, m_oButtonProperty);
	DDX_Control(pDX, IDC_CONNECT_BUTTON, m_oButtonConnect);
	DDX_Control(pDX, IDC_BUTTON_STOP, m_oButtonStop);
	DDX_Text(pDX, IDC_CONN_NUMBER, m_strConnNumber);
	DDX_Text(pDX, IDC_LOCAL_IP, m_strLocalIP);
	DDX_Text(pDX, IDC_RECE_PACKATGE, m_strRecePack);
	DDX_Text(pDX, IDC_RUM_TIME, m_strRumTime);
	DDX_Text(pDX, IDC_SEND_PACKATGE, m_strSendPack);
	DDX_Text(pDX, IDC_STATE, m_strStateInfo);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCSSClientDlg, CDialog)
	//{{AFX_MSG_MAP(CCSSClientDlg)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_CHECK_SHOW, OnCheckShow)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_CONNECT_BUTTON, OnConnectButton)
	ON_BN_CLICKED(IDC_PROPERTY_BUTTON, OnPropertyButton)
	ON_BN_CLICKED(IDC_BUTTON_STOP, OnButtonStop)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCSSClientDlg message handlers

BOOL CCSSClientDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_oButtonProperty.SetXButtonStyle(BS_XT_SEMIFLAT|BS_XT_WINXP_COMPAT|BS_XT_XPFLAT);
	m_oButtonConnect.SetXButtonStyle(BS_XT_SEMIFLAT|BS_XT_WINXP_COMPAT|BS_XT_XPFLAT);
	m_oButtonStop.SetXButtonStyle(BS_XT_SEMIFLAT|BS_XT_WINXP_COMPAT|BS_XT_XPFLAT);
	
	//////////////////////////////////////////////////////////////////////////
	// 创建列表
	m_oUserList.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT|LVS_EX_CHECKBOXES); 

	m_oUserList.InsertColumn(0, "UserName",     LVCFMT_LEFT, 120);
	m_oUserList.InsertColumn(1, "LoginTime",    LVCFMT_LEFT, 150);	
	m_oUserList.InsertColumn(2, "RemoteIP",     LVCFMT_LEFT, 180);
	m_oUserList.InsertColumn(3, "RemotePort",     LVCFMT_LEFT, 100);
	
	UpdateWindowState();
	UpdateData(FALSE);
	SetTimer(IDC_TIMER_UPDATE,1000,NULL);
	InitLabel();
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
//////////////////////////////////////////////////////////////////////////
//
void	CCSSClientDlg::InitLabel( void ){
	
	CString		strData;
	
	strData.Format("%s %s", GetLangStr(TEXT_LOGIN), GetLangStr(TEXT_USER) );
	GetDlgItem(IDC_STATIC_LOGIN)->SetWindowText(strData);
	GetDlgItem( IDC_STATIC_CONN_GROUP )->SetWindowText( GetLangStr(TEXT_CONNECT) );
	strData.Format("%s:", GetLangStr(TEXT_STATUS) );
	GetDlgItem( IDC_STATIC_STATE )->SetWindowText( strData );
	strData.Format("%s%s:", GetLangStr(TEXT_RUN), GetLangStr(TEXT_TIME));
	GetDlgItem( IDC_STATIC_RUM_TIME )->SetWindowText( strData );
	GetDlgItem( IDC_STATIC_ACTIVITY )->SetWindowText( GetLangStr(TEXT_ACTIVITY) );
	GetDlgItem( IDC_STATIC_SEND )->SetWindowText( GetLangStr(TEXT_SEND) );
	GetDlgItem( IDC_STATIC_RECV )->SetWindowText( GetLangStr(TEXT_RECEIVE) );
	strData.Format("%s:", GetLangStr(TEXT_DATA_PACKATGE) );
	GetDlgItem( IDC_STATIC_SEND_PACKATGE )->SetWindowText( strData );
	strData.Format("%s:", GetLangStr(TEXT_CONNECT_DATA) );
	GetDlgItem( IDC_STATIC_CONN_NUMBER )->SetWindowText( strData );
	GetDlgItem( IDC_CHECK_SHOW )->SetWindowText( GetLangStr(TEXT_SHOW) );
	GetDlgItem( IDC_PROPERTY_BUTTON )->SetWindowText( GetLangStr(TEXT_PROPERTY) );
	GetDlgItem( IDC_CONNECT_BUTTON )->SetWindowText( GetLangStr(TEXT_START) );
	GetDlgItem(IDC_STATIC_LOCAL_IP)->SetWindowText( GetLangStr(TEXT_LOCAL_IP) );
	GetDlgItem(IDC_BUTTON_STOP)->SetWindowText( GetLangStr(TEXT_DISABLE ) );
}

//////////////////////////////////////////////////////////////////////////
//
void	CCSSClientDlg::IsConnectionStatus( BOOL  bStateus ){
	
	CString				strData;
	CString				strTime;
	CTime				oTime;
	
	oTime = CTime::GetCurrentTime();
	m_strRumTime = oTime.Format("%B %d, %Y %H:%M:%S");
	m_bStart = bStateus;
	if( bStateus ){
		m_strStateInfo = "CClinet Run...";
		strData.Format("&%s", GetLangStr(TEXT_STOP));
		GetDlgItem(IDC_CONNECT_BUTTON)->SetWindowText(strData);		
	}
	else{
		m_strStateInfo = "Clinet Stop!";
		strData.Format("&%s", GetLangStr(TEXT_START));
		GetDlgItem(IDC_CONNECT_BUTTON)->SetWindowText(strData);
	}
	UpdateData(FALSE);
}

//////////////////////////////////////////////////////////////////////////
//
void	CCSSClientDlg::UpdateWindowState( void ){
	
	CCSServerDlg	*pDlg = (CCSServerDlg*)AfxGetApp()->m_pMainWnd;
	
	m_strRecePack.Format("%d", m_nRecvPackage);
	m_strSendPack.Format("%d", m_nSendPackage );
	m_strConnNumber.Format("%d", m_nConnectNumber );	
	m_strConnNumber.Format("%d", pDlg->GetCLTCPActiveConnect());
}

//////////////////////////////////////////////////////////////////////////
//
BOOL	CCSSClientDlg::SetRecHelpInfo( int	nDataLen, BOOL	bRecv){
	
	if( nDataLen == 0 ){
		return FALSE;
	}
	if( bRecv ){		
		m_nRecvPackage += 1;
	}
	else{
		m_nSendPackage += 1;
	}
	UpdateWindowState();
	
	return m_bShowStatus;
}

//////////////////////////////////////////////////////////////////////////
//
void CCSSClientDlg::OnTimer(UINT nIDEvent){
	
	if (nIDEvent == IDC_TIMER_UPDATE){
		UpdateWindowState();
		UpdateData(FALSE);
	}
	CDialog::OnTimer(nIDEvent);
}

//////////////////////////////////////////////////////////////////////////
//
void CCSSClientDlg::OnCheckShow(){

	m_bShowStatus = m_oCheckShow.GetCheck();
}

//////////////////////////////////////////////////////////////////////////
//
void CCSSClientDlg::OnClose(){

	KillTimer( IDC_TIMER_UPDATE );	
	CDialog::OnClose();
}

//////////////////////////////////////////////////////////////////////////
//
void CCSSClientDlg::OnConnectButton(){

	AfxGetApp()->m_pMainWnd->SendMessage(WM_SOCKET_STARTSTOP,2,0);	
}

//////////////////////////////////////////////////////////////////////////
//
void CCSSClientDlg::OnPropertyButton(){
	
	CString		 strData;
	CConfigDlg	 oConfigDlg;
	
	oConfigDlg.m_strIP = m_strLocalIP;
	oConfigDlg.m_nPort = m_nPort;
	if ( oConfigDlg.DoModal() == IDOK ){
		if ( m_bStart ){
			strData.Format("CLS %s", GetLangStr( TEXT_RUN_PAEASE_STOP_FIRST ) );
			MessageBox( strData, GetLangStr(TEXT_WARNING), MB_ICONWARNING );
		}
		else{
			m_strLocalIP = oConfigDlg.m_strIP;
			m_nPort = oConfigDlg.m_nPort;
			AfxGetApp()->m_pMainWnd->SendMessage(WM_SAVE_PARAMETER_CONFIG, NULL, NULL );
		}		
	}
}

//////////////////////////////////////////////////////////////////////////
//
void  CCSSClientDlg::AddUserLogInfo( CString strUserName, CString  strRemoteIP, UINT nRemotePort , CTime	oBeginTime){

	CString	strData;
	int		nCnt = 0;
	int		nSubItemCnt = 1;

	nCnt = m_oUserList.GetItemCount();
	m_oUserList.InsertItem(nCnt, strUserName );

	m_oUserList.SetItemText(nCnt, nSubItemCnt++, oBeginTime.Format("%Y-%m-%d %H:%M:%S"));
	m_oUserList.SetItemText(nCnt, nSubItemCnt++, strRemoteIP );
	strData.Format("%d", nRemotePort );
	m_oUserList.SetItemText(nCnt, nSubItemCnt++, strData);
}	

//////////////////////////////////////////////////////////////////////////
//
void CCSSClientDlg::DeleteUserlogInfo( CString	strUserName, CString  strIP ){

	int					nCountItem = 0;
	int					nCnt;
	
	nCountItem = m_oUserList.GetItemCount();
	for( nCnt = 0; nCnt < nCountItem; nCnt++){
		CString			strTmpUser;
		CString			strTmpIP;
		
		strTmpUser = m_oUserList.GetItemText(nCnt, 0 );
		strTmpIP = m_oUserList.GetItemText( nCnt , 2 );
		if( strUserName == strTmpUser && strIP == strTmpIP){
			m_oUserList.DeleteItem( nCnt );
			break;
		}
	}	
}

//////////////////////////////////////////////////////////////////////////
//
void CCSSClientDlg::DeleteUserlogInfo( CString   strUserName ){

	int					nCountItem = 0;
	int					nCnt;
	int					nLen = 0;
	
	nCountItem = m_oUserList.GetItemCount();
	for( nCnt = 0; nCnt < nCountItem; nCnt++){
		CString			strTmpUser;
		
		strTmpUser = m_oUserList.GetItemText(nCnt, 0 );		
		if( strUserName == strTmpUser ){
			m_oUserList.DeleteItem( nCnt );
			break;
		}
	}	
}

//////////////////////////////////////////////////////////////////////////
//
CString	 CCSSClientDlg::FindIPPortByUser( CString strIP,  UINT  nPort ){
	
	CString		strResult;
	CString		strData;
	CString		strTemp;	
	int			nItemCount = 0;

	nItemCount = m_oUserList.GetItemCount();

	for ( int nCnt = 0; nCnt < nItemCount; nCnt++ ){
		strData = m_oUserList.GetItemText(nCnt, 2 );
		if ( strData == strIP ){
			strTemp.Format("%d", nPort );
			strData = m_oUserList.GetItemText(nCnt, 3);
			if ( strTemp == strData ){
				strResult  = m_oUserList.GetItemText(nCnt, 0 );
				break;
			}
		}
	}
	return   strResult;
}
//////////////////////////////////////////////////////////////////////////
//
void CCSSClientDlg::OnButtonStop(){
	
	CString			strUserName;
	int				nSelectItem = 0;
	CCSServerDlg 	*pDlg = (CCSServerDlg*)AfxGetApp()->m_pMainWnd;
	BOOL			bFlag = FALSE;

	if( MessageBox( GetLangStr(TEXT_ARE_YOU_SURE), GetLangStr(TEXT_WARNING), MB_ICONWARNING|MB_YESNOCANCEL) == IDYES){
		for ( int nCnt = 0; nCnt < m_oUserList.GetItemCount(); nCnt++ ){
			if ( m_oUserList.GetCheck( nCnt )){
				strUserName = m_oUserList.GetItemText(nCnt, 0);
				m_oUserList.DeleteItem( nCnt );
				pDlg->CloseUserLogin( strUserName );
				bFlag = TRUE;
			}		
		}
		if( bFlag == FALSE){
			MessageBox( GetLangStr(TEXT_PLEASE_SELECT_USER), GetLangStr(TEXT_WARNING), MB_ICONASTERISK|MB_ICONINFORMATION);
		}
	}	
}
