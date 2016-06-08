; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CProperties
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Reminder.h"
LastPage=0

ClassCount=10
Class1=CReminderApp
Class2=CReminderDoc
Class3=CReminderView
Class4=CMainFrame

ResourceCount=4
Resource1=IDD_ABOUTBOX
Class5=CAboutDlg
Class6=CMessageInfo
Class7=CTickerWnd
Class8=CTickerItem
Resource2=IDR_MAINFRAME
Resource3=IDD_QHELP
Class9=CProperties
Class10=CQHelp
Resource4=IDD_PROPERTIES

[CLS:CReminderApp]
Type=0
HeaderFile=Reminder.h
ImplementationFile=Reminder.cpp
Filter=N
LastObject=CReminderApp
BaseClass=CWinApp
VirtualFilter=AC

[CLS:CReminderDoc]
Type=0
HeaderFile=ReminderDoc.h
ImplementationFile=ReminderDoc.cpp
Filter=N

[CLS:CReminderView]
Type=0
HeaderFile=ReminderView.h
ImplementationFile=ReminderView.cpp
Filter=C
LastObject=CReminderView

[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=W
BaseClass=CFrameWnd
VirtualFilter=fWC
LastObject=CMainFrame



[CLS:CAboutDlg]
Type=0
HeaderFile=Reminder.cpp
ImplementationFile=Reminder.cpp
Filter=D

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_FILE_MRU_FILE1
Command6=ID_APP_EXIT
Command7=ID_EDIT_UNDO
Command8=ID_EDIT_CUT
Command9=ID_EDIT_COPY
Command10=ID_EDIT_PASTE
Command11=ID_APP_ABOUT
CommandCount=11

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_UNDO
Command5=ID_EDIT_CUT
Command6=ID_EDIT_COPY
Command7=ID_EDIT_PASTE
Command8=ID_EDIT_UNDO
Command9=ID_EDIT_CUT
Command10=ID_EDIT_COPY
Command11=ID_EDIT_PASTE
Command12=ID_NEXT_PANE
Command13=ID_PREV_PANE
CommandCount=13

[CLS:CMessageInfo]
Type=0
HeaderFile=MessageInfo.h
ImplementationFile=MessageInfo.cpp
BaseClass=generic CWnd
Filter=W

[CLS:CTickerWnd]
Type=0
HeaderFile=TickerWnd.h
ImplementationFile=TickerWnd.cpp
BaseClass=CWnd
Filter=W
VirtualFilter=WC
LastObject=CTickerWnd

[CLS:CTickerItem]
Type=0
HeaderFile=TickerItem.h
ImplementationFile=TickerItem.cpp
BaseClass=generic CWnd
Filter=W

[DLG:IDD_PROPERTIES]
Type=1
Class=CProperties
ControlCount=11
Control1=IDOK,button,1342242817
Control2=IDC_SLIDER1,msctls_trackbar32,1342242857
Control3=IDC_SPEEDGROUP,button,1342177287
Control4=IDC_STATIC,static,1342308352
Control5=IDC_NOWLIST,listbox,1353777409
Control6=IDC_BUTTON1,button,1342242816
Control7=IDC_BUTTON2,button,1342242816
Control8=IDC_BUTTON3,button,1342242816
Control9=IDC_BUTTON4,button,1342242816
Control10=IDC_BUTTON5,button,1342242816
Control11=IDC_BUTTON6,button,1342242816

[CLS:CProperties]
Type=0
HeaderFile=Properties.h
ImplementationFile=Properties.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_NOWLIST
VirtualFilter=dWC

[DLG:IDD_QHELP]
Type=1
Class=CQHelp
ControlCount=2
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816

[CLS:CQHelp]
Type=0
HeaderFile=QHelp.h
ImplementationFile=QHelp.cpp
BaseClass=CDialog
Filter=D
LastObject=CQHelp

