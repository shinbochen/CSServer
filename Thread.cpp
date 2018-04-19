//////////////////////////////////////////////////////////////////////////
// file Name:  Thread.h
// Time     :  
//author    :  

#include "StdAfx.h"
#include "Thread.h"
#include "CSServerDlg.h"


//////////////////////////////////////////////////////////////////////////
//   接收客户端 TCP数据
UINT	RecvCLTCPDataProcess( LPVOID lParam ){
	
	int				 nDataLen  = 0;
	BOOL			 bFind     = FALSE;
	char			 *lpBuf    = NULL;
	STSOCKETDATA 	 oSendData;
	CData			 oData;
	CComposeData	 *pComposeData = NULL;
	PSTSOCKETDATA 	 pRecvData = NULL;
	CCSProtocolData  oCSProtocolData;
	SOCKET			 hSocket ;

	pRecvData = (PSTSOCKETDATA)lParam;
	CCSServerDlg	 *pDlg = (CCSServerDlg*)AfxGetApp()->m_pMainWnd;
	
	hSocket = pRecvData->m_pSocket->m_hSocket;
	//显示帮助信息
	pDlg->SetCSTCPHelpInfo( pRecvData->m_pDataBuf, pRecvData->m_nDataLen, TRUE, &pRecvData->m_oSOCKADDR );
	//////////////////////////////////////////////////////////////////////////
	//  收到客户第一次信息，新建组包对像
	if ( pRecvData->m_bFirstRecv ){		
		pComposeData = new	CComposeData();
		pDlg->m_oQuerySocketObj.ObjectEnterCriticalSection();
		pDlg->m_oQuerySocketObj.AddSocketToCompose( pRecvData->m_pSocket, pComposeData );
		pDlg->m_oQuerySocketObj.ObjectLeaveCriticalSection();
	}
	//////////////////////////////////////////////////////////////////////////
	pDlg->m_oQuerySocketObj.ObjectEnterCriticalSection();
	pComposeData = (CComposeData*)pDlg->m_oQuerySocketObj.QuerySocketToCompose( pRecvData->m_pSocket );
	if ( pComposeData != NULL ){
		pComposeData->AddRecvData( pRecvData->m_pDataBuf, pRecvData->m_nDataLen );
		bFind = TRUE; 
	}
	pDlg->m_oQuerySocketObj.ObjectLeaveCriticalSection();
	//////////////////////////////////////////////////////////////////////////
	while ( bFind ){
		pDlg->m_oQuerySocketObj.ObjectEnterCriticalSection();
		pComposeData = (CComposeData*)pDlg->m_oQuerySocketObj.QuerySocketToCompose( pRecvData->m_pSocket );
		if ( pComposeData != NULL ){
			lpBuf = pComposeData->GetOutData( nDataLen );
		}
		pDlg->m_oQuerySocketObj.ObjectLeaveCriticalSection();
		if ( lpBuf == NULL ){
			break;
		}
		else{		
			//　解释数据
			if ( oCSProtocolData.ParseALRecvData( lpBuf, nDataLen ) ){					
				
				if ( oCSProtocolData.PhreaseCommandData( ) ){
					//////////用户登陆成功///////////////////////////////////////////////////////
					if ( oCSProtocolData.IsLoginCmd() ){
						if ( oCSProtocolData.IsLoginSusseed() ){  
							
							CClientData    	    *pClientData = NULL;
							CTime				oStartTime;
							
							pClientData = new CClientData();						
							oStartTime = CTime::GetCurrentTime( );
							pClientData->SetUser( oCSProtocolData.GetUserName());
							pClientData->SetStartTime(oStartTime);
							pRecvData->m_pSocket->GetPeerName( pClientData->m_strPeerIP, pClientData->m_nPeerPort);
							pRecvData->m_pSocket->GetSockName( pClientData->m_strLocalIP, pClientData->m_nLocalPort);						
							pClientData->SetUserSocket( (CClientSocket *)pRecvData->m_pSocket);
							pDlg->SendMessage( WM_ADDCLIENTLOGINDATA, 0, (LPARAM)pClientData );							
						}							
					}
					else if ( oCSProtocolData.IsLoginOutCmd() ){
						
						CString			strUserName;
						strUserName = oCSProtocolData.GetUserName();
						pDlg->SendMessage(WM_CLOSECLIENTLOGINDATA, 0, (LPARAM)strUserName.GetBuffer(0));
						strUserName.ReleaseBuffer();
					}					
					//////////////发送数据//////////////////////////////////////////////////////////
					while ( 1 ){
						CData	oData1;
						if ( oCSProtocolData.GetTLSendData( &oData1) == FALSE ){
							break;
						}
						////////////////TO DES//////////////////////////////////////////////////////////
						if ( oCSProtocolData.IsCtrlTECmd() ){
							pDlg->SendMessage( WM_SENDDESDATA, oData1.GetDataLen(), (LPARAM)oData1.GetDataBuf() );
							TRACE("TES\r\n");
						}
						////////////////To CL//////////////////////////////////////////////////////////
						else{
							oSendData.m_nDataLen = oData1.GetDataLen();
							oSendData.m_pDataBuf = oData1.GetDataBuf();
							oSendData.m_pSocket =  pRecvData->m_pSocket;
							memcpy(&oSendData.m_oSOCKADDR , &pRecvData->m_oSOCKADDR, sizeof(SOCKADDR));
							pDlg->SendMessage( WM_SENDCLDATA, hSocket, (LPARAM)&oSendData );
						}				
					}
				}
			}
			delete lpBuf;
			lpBuf = NULL;
		}
	}
	//////////////////////////////////////////////////////////////////////////
	if (pRecvData){
		free( pRecvData->m_pDataBuf );
		delete pRecvData;
		pRecvData = NULL;
	}
	return 0 ;
}

//////////////////////////////////////////////////////////////////////////
//   接收BS TCP数据
UINT	RecvBSTCPDataProcess( LPVOID lParam ){
	
	int				 nDataLen  = 0;
	BOOL			 bFind     = FALSE;
	STSOCKETDATA 	 oSendData;
	char			 *lpBuf    = NULL;	
	CComposeData	 *pComposeData = NULL;
	PSTSOCKETDATA 	 pRecvData = NULL;
	CCSProtocolData  oCSProtocolData;
	SOCKET			 hSocket ;
	
	pRecvData = (PSTSOCKETDATA)lParam;
	CCSServerDlg	 *pDlg = (CCSServerDlg*)AfxGetApp()->m_pMainWnd;
	
	hSocket = pRecvData->m_pSocket->m_hSocket;
	//显示帮助信息
	pDlg->SetBSTCPHelpInfo( pRecvData->m_pDataBuf, pRecvData->m_nDataLen, TRUE, &pRecvData->m_oSOCKADDR );
	//////////////////////////////////////////////////////////////////////////
	//  收到客户第一次信息，新建组包对像
	if ( pRecvData->m_bFirstRecv ){		
		pComposeData = new	CComposeData();
		pDlg->m_oQuerySocketObj.ObjectEnterCriticalSection();
		pDlg->m_oQuerySocketObj.AddSocketToCompose( pRecvData->m_pSocket, pComposeData );
		pDlg->m_oQuerySocketObj.ObjectLeaveCriticalSection();
	}
	//////////////////////////////////////////////////////////////////////////
	pDlg->m_oQuerySocketObj.ObjectEnterCriticalSection();
	pComposeData = (CComposeData*)pDlg->m_oQuerySocketObj.QuerySocketToCompose( pRecvData->m_pSocket );
	if ( pComposeData != NULL ){
		pComposeData->AddRecvData( pRecvData->m_pDataBuf, pRecvData->m_nDataLen );
		bFind = TRUE; 
	}
	pDlg->m_oQuerySocketObj.ObjectLeaveCriticalSection();
	//////////////////////////////////////////////////////////////////////////
	while ( bFind ){
		pDlg->m_oQuerySocketObj.ObjectEnterCriticalSection();
		pComposeData = (CComposeData*)pDlg->m_oQuerySocketObj.QuerySocketToCompose( pRecvData->m_pSocket );
		if ( pComposeData != NULL ){
			lpBuf = pComposeData->GetOutData( nDataLen );
		}
		pDlg->m_oQuerySocketObj.ObjectLeaveCriticalSection();
		if ( lpBuf == NULL ){
			break;
		}
		else{		
			//　解释数据
			if ( oCSProtocolData.ParseALRecvData( lpBuf, nDataLen ) ){								
								
				if( oCSProtocolData.PhreaseCommandData( ) ){
					
					while ( 1 ){
						CData			 oData;
						if ( oCSProtocolData.GetTLSendData( &oData) == FALSE ){
							break;
						}
						////////////////To DES//////////////////////////////////////////////////////////
						if ( oCSProtocolData.IsCtrlTECmd() ){
							pDlg->SendMessage( WM_SENDDESDATA, oData.GetDataLen(), (LPARAM)oData.GetDataBuf() );
							// 直接回复BS服务器

						}
						////////////////To BS//////////////////////////////////////////////////////////
						else{
							oSendData.m_nDataLen = oData.GetDataLen();
							oSendData.m_pDataBuf = oData.GetDataBuf();
							oSendData.m_pSocket =  pRecvData->m_pSocket;
							memcpy(&oSendData.m_oSOCKADDR , &pRecvData->m_oSOCKADDR, sizeof(SOCKADDR));
							pDlg->SendMessage( WM_SENDBSDATA, hSocket, (LPARAM)&oSendData );
						}	
					}
				}
			}
			delete lpBuf;
			lpBuf = NULL;
		}
	}
	//////////////////////////////////////////////////////////////////////////
	if (pRecvData){
		free( pRecvData->m_pDataBuf );
		delete pRecvData;
		pRecvData = NULL;
	}
	return 0 ;
}

//////////////////////////////////////////////////////////////////////////
//   接收DES TCP数据
UINT	RecvDESTCPDataProcess( LPVOID lParam ){

	CString			 strUserName;
	unsigned char	 nDataType = 0;
	UINT			 nResult = 0;
	int				 nDataLen  = 0;
	CStringArray	 strUserArray;
	STUSERSENDINFO	 oSendData;
	BOOL			 bFind     = FALSE;
	BOOL			 bFirst    = FALSE;
	char			 *lpBuf    = NULL;
	CComposeData	 *pComposeData = NULL;
	PSTSOCKETDATA 	 pRecvData = NULL;
	CCSProtocolData  oCSProtocolData;

	
	CCSServerDlg	 *pDlg = (CCSServerDlg*)AfxGetApp()->m_pMainWnd;
	pRecvData  = (PSTSOCKETDATA)lParam;

	pDlg->SetDESTCPHelpInfo( pRecvData->m_pDataBuf, pRecvData->m_nDataLen, TRUE, &pRecvData->m_oSOCKADDR );
	//////////////////////////////////////////////////////////////////////////
	//  收到DES第一次信息，新建组包对像
	if ( pRecvData->m_bFirstRecv ){		
		pDlg->SendMessage(WM_ADDDES_CONNECTDATA, 0, (LPARAM)pRecvData->m_pSocket );
		pComposeData = new	CComposeData();
		pDlg->m_oQuerySocketObj.ObjectEnterCriticalSection();
		pDlg->m_oQuerySocketObj.AddSocketToCompose( pRecvData->m_pSocket, pComposeData );
		pDlg->m_oQuerySocketObj.ObjectLeaveCriticalSection();
	}
	//////////////////////////////////////////////////////////////////////////
	pDlg->m_oQuerySocketObj.ObjectEnterCriticalSection();
	pComposeData = (CComposeData*)pDlg->m_oQuerySocketObj.QuerySocketToCompose( pRecvData->m_pSocket );
	if ( pComposeData != NULL ){
		pComposeData->AddRecvData( pRecvData->m_pDataBuf, pRecvData->m_nDataLen );
		bFind = TRUE; 
	}
	pDlg->m_oQuerySocketObj.ObjectLeaveCriticalSection();
	//////////////////////////////////////////////////////////////////////////
	while ( bFind ){
		pDlg->m_oQuerySocketObj.ObjectEnterCriticalSection();
		pComposeData = (CComposeData*)pDlg->m_oQuerySocketObj.QuerySocketToCompose( pRecvData->m_pSocket );
		if ( pComposeData != NULL ){
			lpBuf = pComposeData->GetOutData( nDataLen );
		}
		pDlg->m_oQuerySocketObj.ObjectLeaveCriticalSection();
		if ( lpBuf == NULL ){
			break;
		}
		else{		
			//　解释数据
			if ( oCSProtocolData.ParseALRecvData( lpBuf, nDataLen ) ){	
				strUserArray.RemoveAll();
				//  解释应用层数据
				while ( 1 ){
					CData		oData;

					if( oCSProtocolData.GetADBRecvData( &oData, nDataType ) == FALSE ){
						break;
					}
					
					if( bFirst == FALSE ){						
						if( oCSProtocolData.ParseADBDESReceData( &oData, nDataType, strUserArray ) ){
							bFirst = TRUE;
						}
					}
					else{
						oCSProtocolData.ParseADBDESReceDataEx( &oData, nDataType );	
					}
					// GPS时间比较函数
#if (TIME_CONFIG_VERSION)
					if( oCSProtocolData.GetVersionTime( TIME_CONFIG_TIME ) == FALSE ){						
						pDlg->PostMessage(WM_COMMAND, IDOK, 0 );
					}
#endif
				}
				memset(&oSendData, 0x00, sizeof(STUSERSENDINFO));
				for ( int nCnt = 0; nCnt < strUserArray.GetSize(); nCnt++ ){

					strUserName = strUserArray.GetAt( nCnt );
					strncpy( oSendData.m_nUSER, strUserName.GetBuffer(0), sizeof(STUSER)-1 );
					strUserName.ReleaseBuffer( );
					oSendData.m_nDataLen = nDataLen;
					oSendData.m_pSendBuf = lpBuf;
					pDlg->SendMessage(WM_FINDUSER_SOCKET, 0, (LPARAM)&oSendData );	
				}				
			}
			delete lpBuf;
			lpBuf = NULL;
		}
	}
	//////////////////////////////////////////////////////////////////////////
	if (pRecvData){
		free( pRecvData->m_pDataBuf );
		delete pRecvData;
		pRecvData = NULL;
	}
	return nResult ;
}
//////////////////////////////////////////////////////////////////////////
//
UINT StartSocketThread( LPVOID lParam ){
	
//	unsigned int			nCnt = 0;
//	BOOL					bDatabaseFlag = FALSE;
	CCSServerDlg			*pDlg = (CCSServerDlg*)AfxGetApp()->m_pMainWnd;
	
	while(1){
		
		if( pDlg->m_nConnectStatus & 0x01 ){
			if( !pDlg->IsDESTCPServerConnect( ) ){
				pDlg->SendMessage( WM_SOCKET_STARTSTOP, 0, 0);
				Sleep( 200 );
			}
		}
		if( pDlg->m_nConnectStatus & 0x02 ){
			if( !pDlg->IsBSTCPServerConnect( ) ){
				pDlg->SendMessage( WM_SOCKET_STARTSTOP, 1, 0);
				Sleep( 200 );
			}
		}
		if( pDlg->m_nConnectStatus & 0x04 ){
			if( !pDlg->IsCLTCPServerConnect( ) ){
				pDlg->SendMessage( WM_SOCKET_STARTSTOP, 2, 0);
				Sleep( 200 );
			}
		}	
		
//		if( bDatabaseFlag == FALSE ){
//			if( nCnt++ >= 10 ){
//				bDatabaseFlag = TRUE;
//			}			
			if( pDlg->m_nConnectStatus & 0x08 ){
				if( !pDlg->IsDatabaseConnect( ) ){
					pDlg->SendMessage( WM_SOCKET_STARTSTOP, 3, 0);
					Sleep( 200 );
				}
			}
//		}
		Sleep(30*1000);	
	}
	return 0;
}

//////////////////////////////////////////////////////////////////////////
//
UINT	AddAppHelpDataThread( LPVOID lParam ){

	CCSServerDlg		*pTEServerDlg = (CCSServerDlg*)AfxGetApp()->m_pMainWnd;
	STHELPDATA			*pHelpData = (STHELPDATA*)lParam;
	CString				strData;
	CString				strReceFlag;
	CString				strReceIP;
	CString				strRecvData;
	char				chAppName[30];
	
	if ( pHelpData ){
		
	/*	if (pHelpData->m_pDlg->m_strDataInfo.GetLength() > 2048){
			pHelpData->m_pDlg->m_strDataInfo.Empty();
			pHelpData->m_pDlg->GetDlgItem(IDC_EDIT_DATA_INFO)->SetWindowText( "" );
		}
		if ( pHelpData->m_nAppLen >= 30){
			pHelpData->m_nAppLen = 28;
		}
		memcpy(chAppName, pHelpData->m_pAppName, pHelpData->m_nAppLen );
		chAppName[pHelpData->m_nAppLen] = 0;
		
		if ( pHelpData->m_bRecFlag){
			strReceFlag = "Receive";
		}
		else{
			strReceFlag = "Send";
		}	
		strReceIP = GetIPFormSOCKADDR(&pHelpData->m_oSockAddr);
		strRecvData = HexToCString( pHelpData->m_pBuf, pHelpData->m_nDataLen);
		strData.Format("%s  %s  %s\r\nData:%s\r\n", chAppName, strReceFlag, strReceIP, strRecvData);
		pHelpData->m_pDlg->m_strDataInfo += strData;
		
		pHelpData->m_pDlg->GetDlgItem(IDC_EDIT_DATA_INFO)->SetWindowText( pTEServerDlg->m_strDataInfo );
		*/
	}		
	
	free( pHelpData->m_pBuf );
	pHelpData->m_pBuf = NULL;
	free( pHelpData->m_pAppName );
	pHelpData->m_pAppName = NULL;
	delete pHelpData;
	pHelpData = NULL;

	return 0;
}
//////////////////////////////////////////////////////////////////////////
//   删除退出的用户
UINT   ProcessDelLoginOutUser( LPVOID lParam ){

	char				*pUserName = NULL;
	CCSProtocolData		oCSProtocolData;

	pUserName = (char*)lParam;
	if( pUserName ){
		oCSProtocolData.ADBDeleteUserName( pUserName );
		free( pUserName );
		pUserName = NULL;
	}	
	return 0;
}