#if !defined(AFX_CONFIGDLG_H__AE43E35B_A4CD_4086_92D1_45CF3B74D8C5__INCLUDED_)
#define AFX_CONFIGDLG_H__AE43E35B_A4CD_4086_92D1_45CF3B74D8C5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ConfigDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CConfigDlg dialog

class CConfigDlg : public CDialog
{
// Construction
public:
	CConfigDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CConfigDlg)
	enum { IDD = IDD_CONFIG_DLG };
	CXTButton	m_oOk;
	CXTButton	m_oCancel;
	UINT	m_nPort;
	CString	m_strIP;
	//}}AFX_DATA
public:
	void	InitLabel();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConfigDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CConfigDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONFIGDLG_H__AE43E35B_A4CD_4086_92D1_45CF3B74D8C5__INCLUDED_)
