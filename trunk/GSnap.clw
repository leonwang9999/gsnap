; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CGSnapApp
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "GSnap.h"

ClassCount=3
Class1=CGSnapApp
Class2=CGSnapDlg
Class3=CAboutDlg

ResourceCount=7
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDR_MENU_POPUP (English (U.S.))
Resource4=IDD_GSNAP_DIALOG (English (U.S.))
Resource5=IDD_ABOUTBOX (English (U.S.))
Resource6=IDD_GSNAP_DIALOG
Resource7=IDR_MENU_POPUP

[CLS:CGSnapApp]
Type=0
HeaderFile=GSnap.h
ImplementationFile=GSnap.cpp
Filter=N
BaseClass=CWinApp
VirtualFilter=AC
LastObject=CGSnapApp

[CLS:CGSnapDlg]
Type=0
HeaderFile=GSnapDlg.h
ImplementationFile=GSnapDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=CGSnapDlg

[CLS:CAboutDlg]
Type=0
HeaderFile=GSnapDlg.h
ImplementationFile=GSnapDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_GSNAP_DIALOG]
Type=1
Class=CGSnapDlg
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352

[DLG:IDD_GSNAP_DIALOG (English (U.S.))]
Type=1
Class=?
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352

[DLG:IDD_ABOUTBOX (English (U.S.))]
Type=1
Class=?
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[MNU:IDR_MENU_POPUP (English (U.S.))]
Type=1
Class=?
Command1=IDM_CAPTURE
Command2=IDM_ABOUT
Command3=IDM_EXIT
CommandCount=3

[MNU:IDR_MENU_POPUP]
Type=1
Class=?
Command1=IDM_CAPTURE
Command2=IDM_ABOUT
Command3=IDM_EXIT
CommandCount=3

