// ***************************************************************
//  CMyHttps   version:  1.0  date: 03/30/2007
//  -------------------------------------------------------------
//  A wrapper class for http, https(default)
//  support http proxy
//  -------------------------------------------------------------
//  Copyright (C) 2007 - All Rights Reserved
// ***************************************************************
//  Author - Charry Wong
// ***************************************************************
#pragma once

#include <afxinet.h>



	class CMyHttps
	{
	public:
		CMyHttps(void);
		CMyHttps(const CString &strHttpServer, INTERNET_PORT port);
	public:
		~CMyHttps(void);

		BOOL SetHttpServer(const CString & strHttpServer,INTERNET_PORT port, BOOL bSSL = TRUE);
		BOOL PostTextFile(CString &text, CString filename, CString url, CString &response);
		BOOL PostFile(TCHAR *pFile, int iFileLen, CString filetype, CString filename,
			CString url, CString strTagName, CString &response);
		BOOL Get(CString &response, CString &url);


	private:
		BOOL Open();
		BOOL Close();
		BOOL SetHttpProxy(CString ip, UINT port);
		DWORD GetInternetFlag();
		CString MakeRequestHeaders(CString& strBoundary);
		CString MakePreFileData(CString& strBoundary, CString& strFileName, CString strFileType, CString strTagName);
		CString MakePostFileData(CString& strBoundary);

		CInternetSession *m_pSession;
		CHttpConnection *m_pConnection;
		CString m_strHttpServer;
		INTERNET_PORT m_Port;
		DWORD m_dwStatusCode;

		BOOL m_bSSL;
	};

