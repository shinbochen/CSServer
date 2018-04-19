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
版本记录:
date		version			description
2010-2-26	V2.05			增加了下载GPS数据功能，直接连服务器

2010-3-23	V2.05			增加了图像功能

2010-9-14   V2.10			修改了类CData::GetAt返回值,原来是字符型改成无符号型,
							字符型大于127就会出现负数，所以改成了无符号型

2011-04-25	V2.15			修改了SQL数据库断开的情况,每次请求都新建一个SQL连接, 处理完后，断开SQL连接
2012-03-26	V2.17			增加了握手指令
2013-04-10  V2.18           增加了湿度.加速感应器 查询内存处理数据
2031-08-05  V2.19		    修改了取组信息永远不出来
2013-08-30  V2.20		    修改了,用户登陆时查询组名方式
2013-10-11  V2.21			修改了登陆时组和用户的关系。
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
