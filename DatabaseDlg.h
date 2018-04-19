#if !defined(AFX_DATABASEDLG_H__073F3889_463C_4594_B81E_614766172E69__INCLUDED_)
#define AFX_DATABASEDLG_H__073F3889_463C_4594_B81E_614766172E69__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DatabaseDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDatabaseDlg dialog

class CDatabaseDlg : public CDialog
{
// Construction
public:
	CDatabaseDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDatabaseDlg)
	enum { IDD = IDD_DATABASE_DLG };
	CXTButton	m_oButtonConnect;
	CString		m_strDatabaseName;
	CString		m_strServerName;
	CString		m_strStatusInfo;
	CString		m_strUserName;
	CString		m_strUserPsd;
	//}}AFX_DATA
public:
	void	SetDatabaseName( CString strDatabaseName ) { m_strDatabaseName = strDatabaseName; }
	CString GetDatabaseName( void ) { return m_strDatabaseName; }

	void	SetServerName( CString strServerName ) { m_strServerName = strServerName; }
	CString GetServerName( void ) { return m_strServerName; }

	void	SetUserName( CString strUserName ) { m_strUserName = strUserName; }
	CString	GetUserName( void ) { return m_strUserName; }

	void    SetUserPsd( CString strUsePsd ) { m_strUserPsd = strUsePsd; }
	CString GetUserPsd( void)  { return m_strUserPsd; }

	void    IsConnectionStatus( BOOL  bStatusFlag );
public:
	void    InitLabel( void );
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDatabaseDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDatabaseDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonConnect();
	afx_msg void OnChangeServerName();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DATABASEDLG_H__073F3889_463C_4594_B81E_614766172E69__INCLUDED_)
