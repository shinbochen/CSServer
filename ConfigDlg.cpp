// ConfigDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CSServer.h"
#include "ConfigDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CConfigDlg dialog


CConfigDlg::CConfigDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CConfigDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CConfigDlg)
	m_nPort = 0;
	m_strIP = _T("");
	//}}AFX_DATA_INIT
}


void CConfigDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConfigDlg)
	DDX_Control(pDX, IDOK, m_oOk);
	DDX_Control(pDX, IDCANCEL, m_oCancel);
	DDX_Text(pDX, IDC_EDIT2, m_nPort);
	DDV_MinMaxUInt(pDX, m_nPort, 0, 65535);
	DDX_Text(pDX, IDC_EDIT1, m_strIP);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CConfigDlg, CDialog)
	//{{AFX_MSG_MAP(CConfigDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConfigDlg message handlers

BOOL CConfigDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_oOk.SetXButtonStyle(BS_XT_SEMIFLAT|BS_XT_WINXP_COMPAT|BS_XT_XPFLAT);	
	m_oCancel.SetXButtonStyle(BS_XT_SEMIFLAT|BS_XT_WINXP_COMPAT|BS_XT_XPFLAT);	
	InitLabel( );
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
//////////////////////////////////////////////////////////////////////////
//
void  CConfigDlg::InitLabel( void ){
	
	CString		strData;

	strData.Format("%s:", GetLangStr(TEXT_SERVER_IP) );
	GetDlgItem(IDC_IP_NAME)->SetWindowText(strData);
	strData.Format("TCP%s:", GetLangStr(TEXT_PORT) );
	GetDlgItem(IDC_PORT)->SetWindowText(strData);
	GetDlgItem(IDOK)->SetWindowText(GetLangStr(TEXT_OK));
	GetDlgItem(IDCANCEL)->SetWindowText(GetLangStr(TEXT_CANCEL));
}
void CConfigDlg::OnOK() 
{
	UpdateData(TRUE);
	CDialog::OnOK();
}
