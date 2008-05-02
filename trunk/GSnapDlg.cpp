// GSnapDlg.cpp : implementation file
//

#include "stdafx.h"
#include "GSnap.h"
#include "GSnapDlg.h"
#include "http/MyHttps.h"
#include "xml/XmlNodeWrapper.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGSnapDlg dialog

CGSnapDlg::CGSnapDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGSnapDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGSnapDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGSnapDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGSnapDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CGSnapDlg, CDialog)
	//{{AFX_MSG_MAP(CGSnapDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_SHOWTASK, OnShowTask)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGSnapDlg message handlers

BOOL CGSnapDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here

	ModifyStyleEx(WS_EX_APPWINDOW,WS_EX_TOOLWINDOW);   

	// Hide main dialog
	WINDOWPLACEMENT wp;   
	wp.length = sizeof(WINDOWPLACEMENT);   
	wp.flags = WPF_RESTORETOMAXIMIZED;   
	wp.showCmd = SW_HIDE;   
	SetWindowPlacement(&wp); 
	
	// Hide app to tray
	ToTray();

	GetServerInfo();


	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CGSnapDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CGSnapDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CGSnapDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

CString CGSnapDlg::GetCurDir()
{
	// get the current work dir
	CString dir;
	char FileName[MAX_PATH];
	GetModuleFileName(AfxGetInstanceHandle(), FileName, MAX_PATH);
	dir = FileName;
	dir = dir.Left(dir.ReverseFind('\\'));

	return dir;
}

BOOL CGSnapDlg::UploadFile(CString strFilename, CString strTagName)
{
	if (m_strServer.IsEmpty())
	{
		return FALSE;
	}

	// init http server
	CMyHttps http;
	http.SetHttpServer(m_strServer, _ttoi(m_strPort), FALSE);
	CString strResponse;
	CString strImageURL;
	strImageURL.Format(_T("http://%s/%s/%s"), m_strServer, m_strUploadDir, strFilename);
	CString strFile = GetCurDir() + "\\" + strFilename;

	int iFileLen = 0;
	CFile file;
	char *pFile = NULL;
	try
	{
		BOOL bOpen = file.Open(strFile, CFile::modeRead);
		iFileLen = file.GetLength();
		pFile = new char[iFileLen + 1];
		memset(pFile, 0, iFileLen + 1);

		// read file
		file.Read(pFile, iFileLen);

		if (bOpen)
		{
			file.Close();
		}
	}
	catch (CException* e)
	{
		file.Close();
		e->Delete();
	}
	
	CString strImagePath = _T("c:/");
	strImagePath = strImagePath + strFilename;
	http.PostFile(pFile, iFileLen, _T("image/pjpeg"),
		strImagePath, m_strUrl, m_strFileTag, strResponse);

	delete[] pFile;


	// copy to clipboard
	if (OpenClipboard())
	{
		// Empty the Clipboard. This also has the effect
		// of allowing Windows to free the memory associated
		// with any data that is in the Clipboard
		EmptyClipboard();

		// Ok. We have the Clipboard locked and it's empty. 
		// Now let's allocate the global memory for our data.

		// Here I'm simply using the GlobalAlloc function to 
		// allocate a block of data equal to the text in the
		// "to clipboard" edit control plus one character for the
		// terminating null character required when sending
		// ANSI text to the Clipboard.
		HGLOBAL hClipboardData;
		hClipboardData = GlobalAlloc(GMEM_DDESHARE, 
			strImageURL.GetLength()+1);

		// Calling GlobalLock returns to me a pointer to the 
		// data associated with the handle returned from GlobalAlloc
		char * pchData;
		pchData = (char*)GlobalLock(hClipboardData);

		// At this point, all I need to do is use the standard 
		// C/C++ strcpy function to copy the data from the local 
		// variable to the global memory.
		strcpy(pchData, LPCSTR(strImageURL));


		// Once done, I unlock the memory - remember you don't call
		// GlobalFree because Windows will free the memory 
		// automatically when EmptyClipboard is next called.
		GlobalUnlock(hClipboardData);

		// Now, set the Clipboard data by specifying that 
		// ANSI text is being used and passing the handle to
		// the global memory.
		SetClipboardData(CF_TEXT,hClipboardData);

		// Finally, when finished I simply close the Clipboard
		// which has the effect of unlocking it so that other
		// applications can examine or modify its contents.
		CloseClipboard();
	}

	return TRUE;
}

BOOL CGSnapDlg::CaptureRegion()
{
	CSize Size;
    HBITMAP hImage = GetRegionImage(&Size);
	if (hImage)
	{
		CxImage *newImage = new CxImage();
		newImage->CreateFromHBITMAP(hImage);

		CTime time = CTime::GetCurrentTime();
		CString strTime;
		strTime = time.Format(_T("%Y-%m-%d_%H-%M-%S"));
		strTime += _T(".jpg");
		
		// newImage->Save("xx.png", CXIMAGE_SUPPORT_PNG);

		if (newImage->IsValid())
		{
			if(!newImage->IsGrayScale()) 
				newImage->IncreaseBpp(24);

			newImage->SetJpegQuality(99);
			newImage->Save(strTime, CXIMAGE_FORMAT_JPG);
		}

		delete newImage;

		// active Google Talk Window
		HWND hTalk = NULL;
		hTalk = ::FindWindow("Chat View", NULL);
		CWnd *p = FromHandle(hTalk);
		if (p)
			p->SetForegroundWindow();

		// upload image to server
		UploadFile(strTime, m_strFileTag);
	}

	return TRUE;
}


LRESULT CGSnapDlg::OnShowTask(WPARAM wParam, LPARAM lParam)
{
	if(wParam != IDR_MAINFRAME)
		return 1;

	switch(lParam)
	{
		// right click
		case WM_RBUTTONUP:				
		{ 
			CPoint point;
			GetCursorPos(&point);

			CMenu menu;
			menu.LoadMenu(IDR_MENU_POPUP);
			int nRet = menu.GetSubMenu(0)->TrackPopupMenu(
				TPM_LEFTALIGN | TPM_RETURNCMD,
				point.x, 
				point.y,
				this);

			if (nRet == IDM_EXIT)
			{
				// remove icon from tray
				NOTIFYICONDATA nid;
				nid.cbSize = (DWORD)sizeof(NOTIFYICONDATA);
				nid.hWnd = this->m_hWnd;
				nid.uID = IDR_MAINFRAME;
				nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP ;
				nid.uCallbackMessage = WM_SHOWTASK;		// custom message
				nid.hIcon = LoadIcon(AfxGetInstanceHandle(), 
					MAKEINTRESOURCE(IDR_MAINFRAME));
				strcpy(nid.szTip, _T("GSnap"));
				Shell_NotifyIcon(NIM_DELETE, &nid);

				EndDialog(0);
			}


			if (nRet == IDM_CAPTURE)
			{
				CaptureRegion();
			}

			if (nRet == IDM_ABOUT)
			{
				CAboutDlg dlg;
				dlg.DoModal();
			}

		
		}

		break;
	}
	return 0;
}

void CGSnapDlg::ToTray()
{
	NOTIFYICONDATA nid;
	nid.cbSize = (DWORD)sizeof(NOTIFYICONDATA);
	nid.hWnd = this->m_hWnd;
	nid.uID = IDR_MAINFRAME;
	nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP ;
	nid.uCallbackMessage = WM_SHOWTASK;		// custom message
	nid.hIcon = LoadIcon(AfxGetInstanceHandle(),
		MAKEINTRESOURCE(IDR_MAINFRAME));
	strcpy(nid.szTip, _T("GSnap"));			// tips
	Shell_NotifyIcon(NIM_ADD, &nid);		// add icon to tray
	ShowWindow(SW_HIDE);					// hide main window
} 


DWORD CGSnapDlg::GetTalk()
{
	HANDLE hSnap=CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0); 
	PROCESSENTRY32 pe;
	
	pe.dwSize = sizeof(pe); 
	BOOL bNext=Process32First(hSnap, &pe); 
	DWORD pid;
	while(bNext) 
	{
		if (strcmp("googletalk.exe", pe.szExeFile))
		{
			pid = pe.th32ProcessID;
			break;
		}
		bNext = Process32Next(hSnap, &pe); 
	} 
	CloseHandle(hSnap);


	// return CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, pid);
	return pid;
}


void CGSnapDlg::Test()
{

}

BOOL CGSnapDlg::GetServerInfo()
{
	utility::CXmlDocumentWrapper xmlDoc;
	CString strConfigXmlPath = GetCurDir();
	xmlDoc.Load(strConfigXmlPath + _T("\\g.xml"));
	
	utility::CXmlNodeWrapper node(xmlDoc.AsNode());
	m_strServer = node.GetValue(_T("server"));
	m_strUploadDir = node.GetValue(_T("uploadpath"));
	m_strUrl = node.GetValue(_T("url"));
	m_strPort = node.GetValue(_T("port"));
	m_strFileTag = node.GetValue(_T("tagname"));

	return TRUE;
}
