; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CDatabaseDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "CSServer.h"

ClassCount=8
Class1=CCSServerApp
Class2=CCSServerDlg
Class3=CAboutDlg

ResourceCount=9
Resource1=IDD_CONFIG_DLG
Resource2=IDR_MAINFRAME
Resource3=IDD_CSSERVER_DLG
Resource4=IDD_DES_DLG
Resource5=IDD_BS_DLG
Class4=CCSSClientDlg
Class5=CDatabaseDlg
Class6=CDESDlg
Resource6=IDD_ABOUTBOX
Class7=CBSDlg
Resource7=IDD_DATABASE_DLG
Class8=CConfigDlg
Resource8=IDD_CSS_CLIENT_DLG
Resource9=IDR_TRAY_MENU

[CLS:CCSServerApp]
Type=0
HeaderFile=CSServer.h
ImplementationFile=CSServer.cpp
Filter=N
LastObject=CCSServerApp

[CLS:CCSServerDlg]
Type=0
HeaderFile=CSServerDlg.h
ImplementationFile=CSServerDlg.cpp
Filter=D
LastObject=ID_EXIT
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=CSServerDlg.h
ImplementationFile=CSServerDlg.cpp
Filter=D
LastObject=CAboutDlg
BaseClass=CDialog
VirtualFilter=dWC

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_CSSERVER_DLG]
Type=1
Class=CCSServerDlg
ControlCount=1
Control1=IDC_EDIT_DATA_INFO,edit,1352734724

[DLG:IDD_CSS_CLIENT_DLG]
Type=1
Class=CCSSClientDlg
ControlCount=25
Control1=IDC_USER_LIST,SysListView32,1350631437
Control2=IDC_STATIC_LOGIN,button,1342177287
Control3=IDC_BUTTON_STOP,button,1342242816
Control4=IDC_STATIC_CONN_GROUP,button,1342177287
Control5=IDC_STATIC_ACTIVITY,button,1342177287
Control6=IDC_STATIC_STATE,static,1342308354
Control7=IDC_STATE,static,1342308352
Control8=IDC_STATIC_SEND,static,1342308352
Control9=IDC_STATIC_RECV,static,1342308352
Control10=IDC_STATIC,static,1342177287
Control11=IDC_STATIC,static,1342177287
Control12=IDC_STATIC,static,1342177287
Control13=IDC_STATIC_SEND_PACKATGE,static,1342308354
Control14=IDC_STATIC,static,1342177283
Control15=IDC_SEND_PACKATGE,static,1342308354
Control16=IDC_RECE_PACKATGE,static,1342308354
Control17=IDC_STATIC_CONN_NUMBER,static,1342308354
Control18=IDC_CONN_NUMBER,static,1342308354
Control19=IDC_CHECK_SHOW,button,1342242819
Control20=IDC_PROPERTY_BUTTON,button,1342242816
Control21=IDC_CONNECT_BUTTON,button,1342242816
Control22=IDC_STATIC_RUM_TIME,static,1342308354
Control23=IDC_STATIC_LOCAL_IP,static,1342308354
Control24=IDC_LOCAL_IP,static,1342308352
Control25=IDC_RUM_TIME,static,1342308352

[DLG:IDD_DES_DLG]
Type=1
Class=CDESDlg
ControlCount=24
Control1=IDC_STATIC_ACTIVITY_EDIT,button,1342177287
Control2=IDC_CHECK_SHOW,button,1342242819
Control3=IDC_PROPERTY_BUTTON,button,1342242816
Control4=IDC_CONNECT_BUTTON,button,1342242816
Control5=IDC_EDIT1,edit,1352732804
Control6=IDC_STATIC_CONN_GROUP,button,1342177287
Control7=IDC_STATIC_ACTIVITY,button,1342177287
Control8=IDC_STATIC_STATE,static,1342308354
Control9=IDC_STATE,static,1342308352
Control10=IDC_STATIC_SEND,static,1342308352
Control11=IDC_STATIC_RECV,static,1342308352
Control12=IDC_STATIC,static,1342177287
Control13=IDC_STATIC,static,1342177287
Control14=IDC_STATIC,static,1342177287
Control15=IDC_STATIC_SEND_PACKATGE,static,1342308354
Control16=IDC_STATIC,static,1342177283
Control17=IDC_SEND_PACKATGE,static,1342308354
Control18=IDC_RECE_PACKATGE,static,1342308354
Control19=IDC_STATIC_CONN_NUMBER,static,1342308354
Control20=IDC_CONN_NUMBER,static,1342308354
Control21=IDC_STATIC_RUM_TIME,static,1342308354
Control22=IDC_STATIC_LOCAL_IP,static,1342308354
Control23=IDC_LOCAL_IP,static,1342308352
Control24=IDC_RUM_TIME,static,1342308352

[CLS:CCSSClientDlg]
Type=0
HeaderFile=CSSClientDlg.h
ImplementationFile=CSSClientDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CCSSClientDlg
VirtualFilter=dWC

[CLS:CDESDlg]
Type=0
HeaderFile=DESDlg.h
ImplementationFile=DESDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CDESDlg
VirtualFilter=dWC

[DLG:IDD_DATABASE_DLG]
Type=1
Class=CDatabaseDlg
ControlCount=11
Control1=IDC_STATIC_DB_CONFIG,button,1342177287
Control2=IDC_STATIC_SERVER_NAME,static,1342308354
Control3=IDC_STATIC_DATABASE_NAME,static,1342308354
Control4=IDC_STATIC_USER_NAME,static,1342308354
Control5=IDC_STATIC_USER_PSD,static,1342308354
Control6=IDC_SERVER_NAME,edit,1350631552
Control7=IDC_DATABASE_NAME,edit,1350631552
Control8=IDC_USER_NAME,edit,1350631552
Control9=IDC_USER_PSD,edit,1350631584
Control10=IDC_BUTTON_CONNECT,button,1342242816
Control11=IDC_STATIC_INFO,static,1342308352

[CLS:CDatabaseDlg]
Type=0
HeaderFile=DatabaseDlg.h
ImplementationFile=DatabaseDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_SERVER_NAME
VirtualFilter=dWC

[DLG:IDD_BS_DLG]
Type=1
Class=CBSDlg
ControlCount=24
Control1=IDC_STATIC_ACTIVITY_EDIT,button,1342177287
Control2=IDC_CHECK_SHOW,button,1342242819
Control3=IDC_PROPERTY_BUTTON,button,1342242816
Control4=IDC_CONNECT_BUTTON,button,1342242816
Control5=IDC_EDIT1,edit,1352732804
Control6=IDC_STATIC_CONN_GROUP,button,1342177287
Control7=IDC_STATIC_ACTIVITY,button,1342177287
Control8=IDC_STATIC_STATE,static,1342308354
Control9=IDC_STATIC_RUM_TIME,static,1342308354
Control10=IDC_STATIC_LOCAL_IP,static,1342308354
Control11=IDC_STATE,static,1342308352
Control12=IDC_LOCAL_IP,static,1342308352
Control13=IDC_RUM_TIME,static,1342308352
Control14=IDC_STATIC_SEND,static,1342308352
Control15=IDC_STATIC_RECV,static,1342308352
Control16=IDC_STATIC,static,1342177287
Control17=IDC_STATIC,static,1342177287
Control18=IDC_STATIC,static,1342177287
Control19=IDC_STATIC_SEND_PACKATGE,static,1342308354
Control20=IDC_STATIC,static,1342177283
Control21=IDC_SEND_PACKATGE,static,1342308354
Control22=IDC_RECE_PACKATGE,static,1342308354
Control23=IDC_STATIC_CONN_NUMBER,static,1342308354
Control24=IDC_CONN_NUMBER,static,1342308354

[CLS:CBSDlg]
Type=0
HeaderFile=BSDlg.h
ImplementationFile=BSDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CBSDlg
VirtualFilter=dWC

[DLG:IDD_CONFIG_DLG]
Type=1
Class=CConfigDlg
ControlCount=7
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC_CONFIG,button,1342177287
Control4=IDC_IP_NAME,static,1342308352
Control5=IDC_PORT,static,1342308352
Control6=IDC_EDIT1,edit,1350631552
Control7=IDC_EDIT2,edit,1350631552

[CLS:CConfigDlg]
Type=0
HeaderFile=ConfigDlg.h
ImplementationFile=ConfigDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CConfigDlg

[MNU:IDR_TRAY_MENU]
Type=1
Class=CCSServerDlg
Command1=ID_EXIT
CommandCount=1

