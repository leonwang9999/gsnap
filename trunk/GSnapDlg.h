// GSnapDlg.h : header file
//

#if !defined(AFX_GSNAPDLG_H__AFFEE6B0_27A9_4FF3_97DD_664C9EA97B7F__INCLUDED_)
#define AFX_GSNAPDLG_H__AFFEE6B0_27A9_4FF3_97DD_664C9EA97B7F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#define WM_SHOWTASK		(WM_USER + 100)
#define WM_SHOWMYWINDOW (WM_USER + 101)


/////////////////////////////////////////////////////////////////////////////
// CGSnapDlg dialog

class CGSnapDlg : public CDialog
{
// Construction
public:
	CGSnapDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CGSnapDlg)
	enum { IDD = IDD_GSNAP_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGSnapDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CGSnapDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	afx_msg LRESULT OnShowTask(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()

private:
	BOOL CaptureRegion();
	BOOL UploadFile(CString strFilename, CString strTagName);
	void ToTray();
	DWORD GetTalk();
	BOOL GetServerInfo();
	CString GetCurDir();

	void Test();

private:
	CString m_strServer;
	CString m_strUploadDir;
	CString m_strUrl;
	CString m_strFileTag;
	CString m_strPort;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GSNAPDLG_H__AFFEE6B0_27A9_4FF3_97DD_664C9EA97B7F__INCLUDED_)
