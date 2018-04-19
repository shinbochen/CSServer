// DatabaseDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CSServer.h"
#include "DatabaseDlg.h"
#include "CSServerDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDatabaseDlg dialog


CDatabaseDlg::CDatabaseDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDatabaseDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDatabaseDlg)
	m_strDatabaseName = _T("");
	m_strServerName = _T("");
	m_strStatusInfo = _T("");
	m_strUserName = _T("");
	m_strUserPsd = _T("");
	//}}AFX_DATA_INIT
}


void CDatabaseDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDatabaseDlg)
	DDX_Control(pDX, IDC_BUTTON_CONNECT, m_oButtonConnect);
	DDX_Text(pDX, IDC_DATABASE_NAME, m_strDatabaseName);
	DDX_Text(pDX, IDC_SERVER_NAME, m_strServerName);
	DDX_Text(pDX, IDC_STATIC_INFO, m_strStatusInfo);
	DDX_Text(pDX, IDC_USER_NAME, m_strUserName);
	DDX_Text(pDX, IDC_USER_PSD, m_strUserPsd);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDatabaseDlg, CDialog)
	//{{AFX_MSG_MAP(CDatabaseDlg)
	ON_BN_CLICKED(IDC_BUTTON_CONNECT, OnButtonConnect)
	ON_EN_CHANGE(IDC_SERVER_NAME, OnChangeServerName)
	ON_EN_CHANGE(IDC_DATABASE_NAME, OnChangeServerName)
	ON_EN_CHANGE(IDC_USER_NAME, OnChangeServerName)
	ON_EN_CHANGE(IDC_USER_PSD, OnChangeServerName)

	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDatabaseDlg message handlers

BOOL CDatabaseDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_oButtonConnect.SetXButtonStyle(BS_XT_SEMIFLAT|BS_XT_WINXP_COMPAT|BS_XT_XPFLAT);
	UpdateData(FALSE);
	InitLabel( );
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
//////////////////////////////////////////////////////////////////////////
//
void  CDatabaseDlg::InitLabel( void ){
		
	GetDlgItem( IDC_STATIC_DB_CONFIG )->SetWindowText( GetLangStr(TEXT_DATABASE_CONFIG) );
	GetDlgItem( IDC_STATIC_SERVER_NAME )->SetWindowText( GetLangStr(TEXT_SERVER) );
	GetDlgItem( IDC_STATIC_DATABASE_NAME )->SetWindowText( GetLangStr(TEXT_DATABSE) );
	GetDlgItem( IDC_STATIC_USER_NAME )->SetWindowText( GetLangStr(TEXT_USER) );	
	GetDlgItem( IDC_STATIC_USER_PSD )->SetWindowText( GetLangStr(TEXT_PASSWORD) );
	GetDlgItem( IDC_BUTTON_CONNECT )->SetWindowText( GetLangStr(TEXT_START));

}
//////////////////////////////////////////////////////////////////////////
//
void CDatabaseDlg::IsConnectionStatus( BOOL  bStatusFlag ){
	
	CString			strData;
	CTime			oTime;
	CCSServerDlg	*pDlg = (CCSServerDlg*)AfxGetMainWnd();
	
	if (bStatusFlag){		
		m_strStatusInfo = "Connected Succeed!";
		strData.Format("%s", GetLangStr(TEXT_STOP) );
		GetDlgItem(IDC_BUTTON_CONNECT)->SetWindowText(strData);
		GetDlgItem(IDC_DATABASE_NAME)->EnableWindow(FALSE);
		GetDlgItem(IDC_SERVER_NAME)->EnableWindow(FALSE);
		GetDlgItem(IDC_USER_PSD)->EnableWindow(FALSE);
		GetDlgItem(IDC_USER_NAME)->EnableWindow(FALSE);
	}
	else {
		m_strStatusInfo = "DisConnect Error!";
		strData.Format("%s", GetLangStr(TEXT_START) );
		GetDlgItem(IDC_BUTTON_CONNECT)->SetWindowText(strData);
		GetDlgItem(IDC_DATABASE_NAME)->EnableWindow(TRUE);
		GetDlgItem(IDC_SERVER_NAME)->EnableWindow(TRUE);
		GetDlgItem(IDC_USER_PSD)->EnableWindow(TRUE);
		GetDlgItem(IDC_USER_NAME)->EnableWindow(TRUE);
	}
//	UpdateData(FALSE);
}

//////////////////////////////////////////////////////////////////////////
//
void CDatabaseDlg::OnButtonConnect(){
	
	UpdateData(TRUE);
	AfxGetMainWnd()->SendMessage(WM_SAVE_PARAMETER_CONFIG,NULL,NULL );
	AfxGetMainWnd()->SendMessage( WM_SOCKET_STARTSTOP, 3, 0 );
}

void CDatabaseDlg::OnChangeServerName() 
{
	UpdateData(TRUE);
	AfxGetMainWnd()->SendMessage(WM_SAVE_PARAMETER_CONFIG,NULL,NULL );
}
