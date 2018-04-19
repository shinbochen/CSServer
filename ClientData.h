// ClientData.h: interface for the CClientData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CLIENTDATA_H__DC80F32A_5184_4006_81E0_46B6162080B7__INCLUDED_)
#define AFX_CLIENTDATA_H__DC80F32A_5184_4006_81E0_46B6162080B7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "..\public\ServerSocket.h"
enum{
	TERMINAL_WORK_TCP = 0,
	TERMINAL_WORK_UDP=1
};

class CClientData : public CObject{
	
public:
	CClientData( );
	virtual ~CClientData();
	
public:
	CString				m_strUser;
	CTime				m_oStartTime;
	CString				m_strPeerIP;
	unsigned int		m_nPeerPort;
	CString				m_strLocalIP;
	unsigned int		m_nLocalPort;
	CClientSocket		*m_pClientSocket;
	BOOL				m_bLoginSuccess;
	
public:
	void		SetUser( CString str){ m_strUser = str;}
	void		SetUserSocket( CClientSocket *pSocket ){ m_pClientSocket = pSocket; }
	void		SetStartTime( CTime oTime){m_oStartTime = oTime; }		
	CString		GetUser( void ){ return m_strUser;}
	
public:
	void		FreeMemory( void );	
	void		StopSocket( void );
};

#endif // !defined(AFX_CLIENTDATA_H__DC80F32A_5184_4006_81E0_46B6162080B7__INCLUDED_)
