# Microsoft Developer Studio Project File - Name="CSServer" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=CSServer - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "CSServer.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "CSServer.mak" CFG="CSServer - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "CSServer - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "CSServer - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "CSServer - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 my3l_Ex.lib /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "CSServer - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /Zm500 /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 my3l_Ex.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "CSServer - Win32 Release"
# Name "CSServer - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\public\ADODB.cpp
# End Source File
# Begin Source File

SOURCE=.\BSDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ClientData.cpp
# End Source File
# Begin Source File

SOURCE=.\ConfigDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\CSSClientDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\CSServer.cpp
# End Source File
# Begin Source File

SOURCE=.\CSServer.rc
# End Source File
# Begin Source File

SOURCE=.\CSServerDlg.cpp
# End Source File
# Begin Source File

SOURCE=..\public\Data.cpp
# End Source File
# Begin Source File

SOURCE=.\DatabaseDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\DESDlg.cpp
# End Source File
# Begin Source File

SOURCE=..\public\Encrypt.cpp
# End Source File
# Begin Source File

SOURCE=..\public\EncryptionData.cpp
# End Source File
# Begin Source File

SOURCE=..\public\Language.cpp
# End Source File
# Begin Source File

SOURCE=..\public\LanguageCN.cpp
# End Source File
# Begin Source File

SOURCE=..\public\LanguageEN.cpp
# End Source File
# Begin Source File

SOURCE=..\public\MacIP.cpp
# End Source File
# Begin Source File

SOURCE=..\public\ProtocolData.cpp
# End Source File
# Begin Source File

SOURCE=..\public\public.cpp
# End Source File
# Begin Source File

SOURCE=..\public\QuerySocketObject.cpp
# End Source File
# Begin Source File

SOURCE=..\public\ServerSocket.cpp
# End Source File
# Begin Source File

SOURCE=..\public\SoftKey.cpp
# End Source File
# Begin Source File

SOURCE=..\public\SQLDBData.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\Thread.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\public\ADODB.h
# End Source File
# Begin Source File

SOURCE=.\BSDlg.h
# End Source File
# Begin Source File

SOURCE=.\ClientData.h
# End Source File
# Begin Source File

SOURCE=.\ConfigDlg.h
# End Source File
# Begin Source File

SOURCE=.\CSSClientDlg.h
# End Source File
# Begin Source File

SOURCE=.\CSServer.h
# End Source File
# Begin Source File

SOURCE=.\CSServerDlg.h
# End Source File
# Begin Source File

SOURCE=..\public\Data.h
# End Source File
# Begin Source File

SOURCE=.\DatabaseDlg.h
# End Source File
# Begin Source File

SOURCE=..\public\DBHeader.h
# End Source File
# Begin Source File

SOURCE=.\DESDlg.h
# End Source File
# Begin Source File

SOURCE=..\public\Encrypt.h
# End Source File
# Begin Source File

SOURCE=..\public\EncryptionData.h
# End Source File
# Begin Source File

SOURCE=..\public\Language.h
# End Source File
# Begin Source File

SOURCE=..\public\LanguageCN.h
# End Source File
# Begin Source File

SOURCE=..\public\LanguageEN.h
# End Source File
# Begin Source File

SOURCE=..\public\MacIP.h
# End Source File
# Begin Source File

SOURCE=..\public\my3l_Ex.h
# End Source File
# Begin Source File

SOURCE=..\public\ProtocolData.h
# End Source File
# Begin Source File

SOURCE=..\public\public.h
# End Source File
# Begin Source File

SOURCE=..\public\QuerySocketObject.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=..\public\ServerSocket.h
# End Source File
# Begin Source File

SOURCE=..\public\SoftKey.h
# End Source File
# Begin Source File

SOURCE=..\public\SQLDBData.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=..\public\Structs.h
# End Source File
# Begin Source File

SOURCE=.\Thread.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\app_bmp.bmp
# End Source File
# Begin Source File

SOURCE=.\res\BSPane.ico
# End Source File
# Begin Source File

SOURCE=.\res\CSSClientPane.ico
# End Source File
# Begin Source File

SOURCE=.\res\CSServer.ico
# End Source File
# Begin Source File

SOURCE=.\res\CSServer.rc2
# End Source File
# Begin Source File

SOURCE=.\res\Database.ico
# End Source File
# Begin Source File

SOURCE=.\res\DBSPane.ico
# End Source File
# Begin Source File

SOURCE=.\res\DESPane.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00001.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00002.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon1.ico
# End Source File
# Begin Source File

SOURCE=.\res\network.ico
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
