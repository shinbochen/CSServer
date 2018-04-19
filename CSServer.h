// CSServer.h : main header file for the CSSERVER application
//

#if !defined(AFX_CSSERVER_H__867E2887_F593_4BA2_A1FA_742885900274__INCLUDED_)
#define AFX_CSSERVER_H__867E2887_F593_4BA2_A1FA_742885900274__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/*
�汾��¼:
date		version			description
2010-2-26	V2.05			����������GPS���ݹ��ܣ�ֱ����������

2010-3-23	V2.05			������ͼ����

2010-9-14   V2.10			�޸�����CData::GetAt����ֵ,ԭ�����ַ��͸ĳ��޷�����,
							�ַ��ʹ���127�ͻ���ָ��������Ըĳ����޷�����

2011-04-25	V2.15			�޸���SQL���ݿ�Ͽ������,ÿ�������½�һ��SQL����, ������󣬶Ͽ�SQL����
2012-03-26	V2.17			����������ָ��
2013-04-10  V2.18           ������ʪ��.���ٸ�Ӧ�� ��ѯ�ڴ洦������
2031-08-05  V2.19		    �޸���ȡ����Ϣ��Զ������
2013-08-30  V2.20		    �޸���,�û���½ʱ��ѯ������ʽ
2013-10-11  V2.21			�޸��˵�½ʱ����û��Ĺ�ϵ��
*/

/////////////////////////////////////////////////////////////////////////////
// CCSServerApp:
// See CSServer.cpp for the implementation of this class
//

class CCSServerApp : public CWinApp
{
public:
	CCSServerApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCSServerApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CCSServerApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CSSERVER_H__867E2887_F593_4BA2_A1FA_742885900274__INCLUDED_)
