// ***************************************************************
//  CMyHttps   version:  1.0  date: 03/30/2007
//  -------------------------------------------------------------
//  A wrapper class for https(default) and http
//  this class supports uploading files
//  -------------------------------------------------------------
//  Copyright (C) 2007 - All Rights Reserved
// ***************************************************************
//  Author - Charry Wong
// ***************************************************************
#include "StdAfx.h"
#include "MyHttps.h"
//#include "MyUtility.h"

	CMyHttps::CMyHttps() : 
		m_pSession(NULL),
		m_pConnection(NULL),
		m_Port(0),
		m_bSSL(FALSE)
	{

	}

	CMyHttps::CMyHttps(const CString &strHttpServer, INTERNET_PORT port) :
		m_pSession(NULL),
		m_pConnection(NULL),
		m_strHttpServer(strHttpServer),
		m_Port(port),
		m_bSSL(FALSE)
	{
		Open();
	}

	CMyHttps::~CMyHttps()
	{
		Close();
	}

	BOOL CMyHttps::SetHttpProxy(CString ip, UINT port) 
	{ 




		return TRUE; 
	} 

	BOOL CMyHttps::Open()
	{
		Close();
	

		try
		{
			m_pSession = new CInternetSession();

			// default timeout: 5 secs
			m_pSession->SetOption(INTERNET_OPTION_CONNECT_TIMEOUT, 5000);
			m_pSession->SetOption(INTERNET_OPTION_CONNECT_BACKOFF, 1000);
			m_pSession->SetOption(INTERNET_OPTION_CONNECT_RETRIES, 0);

			m_pConnection = m_pSession->GetHttpConnection(m_strHttpServer, m_Port);
		}
		catch(CInternetException * e)
		{
			//e->ReportError();
			e->Delete();
			return FALSE;
		}
		return TRUE;
	}

	BOOL CMyHttps::Close()
	{
		if(m_pConnection)
		{
			m_pConnection->Close();
			delete m_pConnection;
			m_pConnection = NULL;
		}

		if(m_pSession)
		{
			m_pSession->Close();
			delete m_pSession;
			m_pSession = NULL;
		}

		return TRUE;
	}

	DWORD CMyHttps::GetInternetFlag()
	{
		DWORD dwFlags = 0;

		// http with SSL
		if (m_bSSL)
		{
			dwFlags = INTERNET_FLAG_RELOAD |     
			INTERNET_FLAG_NO_CACHE_WRITE |   
			INTERNET_FLAG_KEEP_CONNECTION;  

			dwFlags |= INTERNET_FLAG_SECURE |
			INTERNET_FLAG_IGNORE_CERT_CN_INVALID |
			INTERNET_FLAG_IGNORE_CERT_DATE_INVALID;
		}
		// http
		else
		{
			dwFlags = INTERNET_FLAG_RELOAD | 
				INTERNET_FLAG_DONT_CACHE |
				INTERNET_FLAG_KEEP_CONNECTION;
		}

		return dwFlags;
	}

	BOOL CMyHttps::SetHttpServer(const CString &strHttpServer, INTERNET_PORT port, BOOL bSSL /* = TRUE */)
	{
		if(m_strHttpServer == strHttpServer && m_Port == port)
			return TRUE;

		m_strHttpServer = strHttpServer;
		m_Port = port;
		m_bSSL = bSSL;

		return Open();
	}

	// Post data to server
	// url indicates the relative path to the server, "/foo.asp"
//DEL 	int CMyHttps::Post(CString &request, CString &url, CString &response)
//DEL 	{
//DEL 		if(!m_pConnection)
//DEL 			return FALSE;
//DEL 
//DEL 		CHttpFile *pFile = NULL;
//DEL 		try
//DEL 		{
//DEL 			DWORD dwFlags = GetInternetFlag();
//DEL 
//DEL 			pFile = m_pConnection->OpenRequest(CHttpConnection::HTTP_VERB_POST,
//DEL 				url, NULL, 1, NULL,	NULL, dwFlags);
//DEL 
//DEL 			if(pFile)
//DEL 			{
//DEL 				pFile->AddRequestHeaders(_T("Content-Type: application/x-www-form-urlencoded;"));
//DEL 				BOOL bRequestOK = pFile->SendRequest(NULL, 0, 
//DEL 					(LPVOID)(LPTSTR)(request.GetBuffer(0)),
//DEL 					request.GetLength());
//DEL 				request.ReleaseBuffer();
//DEL 
//DEL 				if(!bRequestOK)
//DEL 				{
//DEL 					pFile->Close();
//DEL 					delete pFile;
//DEL 					return FALSE;
//DEL 				}
//DEL 
//DEL 				// Status Code
//DEL 				pFile->QueryInfoStatusCode(m_dwStatusCode);
//DEL 				if(m_dwStatusCode != 200)
//DEL 				{
//DEL 					pFile->Close();
//DEL 					delete pFile;
//DEL 					return FALSE;
//DEL 				}
//DEL 
//DEL 				// get the size of Content-Length
//DEL 				CString strContentLength;
//DEL 				pFile->QueryInfo(HTTP_QUERY_CONTENT_LENGTH, strContentLength);
//DEL 				int nContentLength = _ttoi(strContentLength);
//DEL 
//DEL 				UINT nReadCount = 0;
//DEL 
//DEL 				int HTTP_READ_BUFFER_SIZE = nContentLength > 0 ? nContentLength : 4096;
//DEL 				TCHAR * szBuf = new TCHAR[HTTP_READ_BUFFER_SIZE+1];
//DEL 				memset(szBuf, 0, HTTP_READ_BUFFER_SIZE+1);
//DEL 
//DEL 				response.Empty();
//DEL 
//DEL 				while(true)
//DEL 				{
//DEL 					memset(szBuf,0,HTTP_READ_BUFFER_SIZE+1);
//DEL 					// nReadCount = pFile->Read(szBuf,HTTP_READ_BUFFER_SIZE);
//DEL 					nReadCount = pFile->Read(szBuf,
//DEL 						(pFile->GetLength() < HTTP_READ_BUFFER_SIZE) ? pFile->GetLength() : HTTP_READ_BUFFER_SIZE);
//DEL 
//DEL 					if(nReadCount <= 0)
//DEL 					{
//DEL 						break;
//DEL 					}
//DEL 
//DEL 					response += szBuf;
//DEL 				}
//DEL 
//DEL 				response += szBuf;
//DEL 				delete []szBuf;
//DEL 
//DEL 				pFile->Close();
//DEL 				delete pFile;
//DEL 			}
//DEL 		}
//DEL 		catch(CInternetException * e)
//DEL 		{
//DEL 			// e->ReportError();
//DEL 			pFile->Close();
//DEL 			delete pFile;
//DEL 			e->Delete();
//DEL 			return FALSE;
//DEL 		}
//DEL 
//DEL 		return TRUE;
//DEL 	}

	// Post data to server
	// url indicates the relative path to the server, "/foo.asp"
	BOOL CMyHttps::PostTextFile(CString &text, CString filename, CString url, CString &response)
	{
		int iLen = text.GetLength();

		BOOL bRet = PostFile(text.GetBuffer(NULL), iLen, _T("text/plain"), 
			filename, url, _T("foobar"), response);

		return bRet;
	}


	BOOL CMyHttps::PostFile(TCHAR *pFileToUpload, int iFileLen, CString filetype,
		CString filename, CString url, CString strTagName, CString &response)
	{
		if(!m_pConnection)
			return FALSE;

		CHttpFile *pFile = NULL;

		try
		{
			DWORD dwFlags = GetInternetFlag();

			pFile = m_pConnection->OpenRequest(CHttpConnection::HTTP_VERB_POST,
				url, NULL, 1, NULL,	NULL, dwFlags);

			CString strHTTPBoundary = _T("IllBeVerySurprisedIfThisTurnsUp");
			CString strPreFileData = MakePreFileData(strHTTPBoundary, filename, filetype, strTagName);
			CString strPostFileData = MakePostFileData(strHTTPBoundary);

			DWORD dwTotalRequestLength = 
				strPreFileData.GetLength() +
				strPostFileData.GetLength() + iFileLen;

			if(pFile)
			{
				pFile->AddRequestHeaders(MakeRequestHeaders(strHTTPBoundary));
				BOOL bRequestOK = pFile->SendRequestEx(dwTotalRequestLength, HSR_SYNC | HSR_INITIATE);

				if(!bRequestOK)
				{
					pFile->Close();
					delete pFile;
					return FALSE;
				}

 				pFile->Write((LPTSTR)(LPCTSTR)strPreFileData, strPreFileData.GetLength());
 				pFile->Write((LPTSTR)(LPCTSTR)pFileToUpload, iFileLen);
 				pFile->Write((LPTSTR)(LPCTSTR)strPostFileData, strPostFileData.GetLength());
 				pFile->EndRequest(HSR_SYNC);


				// Status Code
				pFile->QueryInfoStatusCode(m_dwStatusCode);
				if(m_dwStatusCode != 200)
				{
					pFile->Close();
					delete pFile;
					return FALSE;
				}

				// get the size of Content-Length
				CString strContentLength;
				pFile->QueryInfo(HTTP_QUERY_CONTENT_LENGTH, strContentLength);
				int nContentLength = _ttoi(strContentLength);

				UINT nReadCount = 0;

				int HTTP_READ_BUFFER_SIZE = nContentLength > 0 ? nContentLength : 4096;
				char * szBuf = new char[HTTP_READ_BUFFER_SIZE+1];
				memset(szBuf, 0, HTTP_READ_BUFFER_SIZE+1);

				response.Empty();

				while(true)
				{
					memset(szBuf,0,HTTP_READ_BUFFER_SIZE+1);
					//				nReadCount = pFile->Read(szBuf,HTTP_READ_BUFFER_SIZE);
					nReadCount = pFile->Read(szBuf,
						(pFile->GetLength() < HTTP_READ_BUFFER_SIZE) ? pFile->GetLength() : HTTP_READ_BUFFER_SIZE);

					if(nReadCount <= 0)
					{
						break;
					}

					response += szBuf;
				}

				response += szBuf;
				delete []szBuf;

				pFile->Close();
				delete pFile;
			}
		}
		catch(CInternetException * e)
		{
			//		e->ReportError();
			pFile->Close();
			delete pFile;
			e->Delete();
			return FALSE;
		}

		return TRUE;
	}

	int CMyHttps::Get(CString &response, CString &url)
	{
		if(!m_pConnection)
			return FALSE;

		CHttpFile *pFile = NULL;

		try
		{
			DWORD dwFlags = GetInternetFlag();

			pFile = m_pConnection->OpenRequest(CHttpConnection::HTTP_VERB_GET, url
				,NULL, 1, NULL,	NULL,
				dwFlags);

// 			INTERNET_PROXY_INFO   proxyinfo;   
// 			proxyinfo.dwAccessType   =   INTERNET_OPEN_TYPE_PROXY;   
// 			proxyinfo.lpszProxy   =   "119.119.119.9:8080";   
// 			proxyinfo.lpszProxyBypass   =   NULL;   
// 
// 			BOOL xxx=	m_pConnection->SetOption(INTERNET_OPTION_PROXY,   (LPVOID)&proxyinfo,   sizeof(INTERNET_PROXY_INFO));   
// 			//pFile->SetOption(INTERNET_OPTION_PROXY_USERNAME,   strUsername,   strlen(strUsername)+1);   
			//pFile->SetOption(INTERNET_OPTION_PROXY_PASSWORD,   strPassword,   strlen(strPassword)+1);  

			if(pFile)
			{
				BOOL bRequestOK = pFile->SendRequest();
				if(!bRequestOK)
				{
					pFile->Close();
					delete pFile;
					return FALSE;
				}

				pFile->QueryInfoStatusCode(m_dwStatusCode);
				if(m_dwStatusCode != 200)
				{
					pFile->Close();
					delete pFile;
					return FALSE;
				}

				CString strContentLength;
				pFile->QueryInfo(HTTP_QUERY_CONTENT_LENGTH, strContentLength);
				int nContentLength = _ttoi(strContentLength);

				UINT nReadCount = 0;

				int HTTP_READ_BUFFER_SIZE = nContentLength > 0 ? nContentLength : 4096;
				char * szBuf = new char[HTTP_READ_BUFFER_SIZE+1];
				memset(szBuf, 0, HTTP_READ_BUFFER_SIZE+1);

				response.Empty();

				while(true)
				{
					memset(szBuf,0,HTTP_READ_BUFFER_SIZE+1);
					nReadCount = pFile->Read(szBuf, HTTP_READ_BUFFER_SIZE);
					//				nReadCount = pFile->Read(szBuf,(pFile->GetLength() < HTTP_READ_BUFFER_SIZE) ? pFile->GetLength() : HTTP_READ_BUFFER_SIZE);
					if(nReadCount <= 0)
					{
						break;
					}

					response += szBuf;
				}

				response += szBuf;
				delete []szBuf;

				pFile->Close();
				delete pFile;
			}
		}
		catch(CInternetException * e)
		{
			//		e->ReportError();
			pFile->Close();
			delete pFile;
			e->Delete();
			return FALSE;
		}

		return TRUE;
	}



	CString CMyHttps::MakeRequestHeaders(CString& strBoundary)
	{
		CString strFormat;
		CString strData;
		strFormat = _T("Content-Type: multipart/form-data; boundary=%s\r\n");
		strData.Format(strFormat, strBoundary);
		return strData;
	}

	CString CMyHttps::MakePreFileData(CString& strBoundary, CString& strFileName,
		CString strFileType, CString strTagName)
	{
		CString strFormat;
 	
  		strFormat += _T("--%s");
  		strFormat += _T("\r\n");
  		strFormat += _T("Content-Disposition: form-data; name=\"%s\"; filename=\"%s\"");
  		strFormat += _T("\r\n");
  		strFormat += _T("Content-Type: %s");
  		strFormat += _T("\r\n");
  		strFormat += _T("Content-Transfer-Encoding: binary");
  		strFormat += _T("\r\n\r\n");

		CString strData;
  		strData.Format(strFormat, strBoundary, strTagName, strFileName, strFileType);

		return strData;
	}

	CString CMyHttps::MakePostFileData(CString& strBoundary)
	{
		CString strFormat;
		CString strData;
		strFormat = _T("\r\n");
		strFormat += _T("--%s");
		strFormat += _T("\r\n");
		strFormat += _T("Content-Disposition: form-data; name=\"submitted\"");
		strFormat += _T("\r\n\r\n");
		strFormat += _T("charry.org");
		strFormat += _T("\r\n");
		strFormat += _T("--%s--");
		strFormat += _T("\r\n");
		strData.Format(strFormat, strBoundary, strBoundary);

		return strData;
	}

