// BSDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CSServer.h"
#include "BSDlg.h"
#include "CSServerDlg.h"
#include "ConfigDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBSDlg dialog


CBSDlg::CBSDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBSDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBSDlg)
	m_strConnNumber = _T("0");
	m_strLocalIP = _T("");
	m_strRecePack = _T("0");
	m_strRumTime = _T("0");
	m_strSendPack = _T("0");
	m_strStateInfo = _T("0");
	//}}AFX_DATA_INIT
	// 连接状态
	m_bStart = FALSE;
	// 接收包
	m_nRecvPackage = 0;
	// 发送包
	m_nSendPackage = 0;
	// 连接数
	m_nConnectNumber = 0;
	m_nPort = 0;
	m_bShowStatus = FALSE;
}


void CBSDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBSDlg)
	DDX_Control(pDX, IDC_CHECK_SHOW, m_oCheckShow);
	DDX_Control(pDX, IDC_PROPERTY_BUTTON, m_oButtonProperty);
	DDX_Control(pDX, IDC_CONNECT_BUTTON, m_oButtonConnect);
	DDX_Text(pDX, IDC_CONN_NUMBER, m_strConnNumber);
	DDX_Text(pDX, IDC_LOCAL_IP, m_strLocalIP);
	DDX_Text(pDX, IDC_RECE_PACKATGE, m_strRecePack);
	DDX_Text(pDX, IDC_RUM_TIME, m_strRumTime);
	DDX_Text(pDX, IDC_SEND_PACKATGE, m_strSendPack);
	DDX_Text(pDX, IDC_STATE, m_strStateInfo);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CBSDlg, CDialog)
	//{{AFX_MSG_MAP(CBSDlg)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_CHECK_SHOW, OnCheckShow)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_CONNECT_BUTTON, OnConnectButton)
	ON_BN_CLICKED(IDC_PROPERTY_BUTTON, OnPropertyButton)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBSDlg message handlers

BOOL CBSDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_oButtonProperty.SetXButtonStyle(BS_XT_SEMIFLAT|BS_XT_WINXP_COMPAT|BS_XT_XPFLAT);
	m_oButtonConnect.SetXButtonStyle(BS_XT_SEMIFLAT|BS_XT_WINXP_COMPAT|BS_XT_XPFLAT);
	
	UpdateWindowState();
	UpdateData(FALSE);
	SetTimer(IDC_TIMER_UPDATE,1000,NULL);
	InitLabel();
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
//////////////////////////////////////////////////////////////////////////
//
void	CBSDlg::InitLabel( void ){
	
	CString		strData;
		
	GetDlgItem(IDC_STATIC_ACTIVITY_EDIT)->SetWindowText(GetLangStr(TEXT_ACTIVITY) );
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
}

//////////////////////////////////////////////////////////////////////////
//
void	CBSDlg::IsConnectionStatus( BOOL  bStateus ){
	
	CString				strData;
	CString				strTime;
	CTime				oTime;
	
	oTime = CTime::GetCurrentTime();
	m_strRumTime = oTime.Format("%B %d, %Y %H:%M:%S");
	m_bStart = bStateus;
	if( bStateus ){
		m_strStateInfo = "BSServer Run...";
		strData.Format("&%s", GetLangStr(TEXT_STOP));
		GetDlgItem(IDC_CONNECT_BUTTON)->SetWindowText(strData);		
	}
	else{
		m_strStateInfo = "BSServer Stop!";
		strData.Format("&%s", GetLangStr(TEXT_START));
		GetDlgItem(IDC_CONNECT_BUTTON)->SetWindowText(strData);
	}
	UpdateData(FALSE);
}

//////////////////////////////////////////////////////////////////////////
//
void	CBSDlg::UpdateWindowState( void ){
	
	CCSServerDlg	*pDlg = (CCSServerDlg*)AfxGetApp()->m_pMainWnd;
	
	m_strRecePack.Format("%d", m_nRecvPackage);
	m_strSendPack.Format("%d", m_nSendPackage );
	m_strConnNumber.Format("%d", m_nConnectNumber );	
	m_strConnNumber.Format("%d", pDlg->GetBSTCPActiveConnect());
}

//////////////////////////////////////////////////////////////////////////
//
BOOL	CBSDlg::SetRecHelpInfo( int	nDataLen, BOOL	bRecv){
	
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
void CBSDlg::OnTimer(UINT nIDEvent){
	
	if (nIDEvent == IDC_TIMER_UPDATE){
		UpdateWindowState();
		UpdateData(FALSE);
	}
	CDialog::OnTimer(nIDEvent);
}

//////////////////////////////////////////////////////////////////////////
//
void CBSDlg::OnCheckShow() {
	m_bShowStatus = m_oCheckShow.GetCheck();	
}

//////////////////////////////////////////////////////////////////////////
//
void CBSDlg::OnClose(){

	KillTimer( IDC_TIMER_UPDATE );
	CDialog::OnClose();
}

//////////////////////////////////////////////////////////////////////////
//
void CBSDlg::OnConnectButton(){
	
	AfxGetApp()->m_pMainWnd->SendMessage(WM_SOCKET_STARTSTOP,1,0);
}

/////////////////////////////////////////////////////////////////////////
//
void CBSDlg::OnPropertyButton(){

	CString		 strData; 	
	CConfigDlg	 oConfigDlg;
	
	oConfigDlg.m_strIP = m_strLocalIP;
	oConfigDlg.m_nPort = m_nPort;
	if ( oConfigDlg.DoModal() == IDOK ){
		if ( m_bStart ){	
			strData.Format("BS %s", GetLangStr( TEXT_RUN_PAEASE_STOP_FIRST ) );
			MessageBox( strData, GetLangStr(TEXT_WARNING), MB_ICONWARNING );
		}
		else{
			m_strLocalIP = oConfigDlg.m_strIP;
			m_nPort = oConfigDlg.m_nPort;
			AfxGetApp()->m_pMainWnd->SendMessage(WM_SAVE_PARAMETER_CONFIG, NULL, NULL );
		}		
	}
}
