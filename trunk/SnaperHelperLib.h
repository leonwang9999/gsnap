/////////////////////////////////////////////////////////////////////////////
//FUNCTION HEADER
/////////////////////////////////////////////////////////////////////////////
#ifndef SnaperHelperLib_H
#define SnaperHelperLib_H

#ifdef __cplusplus
extern "C" {
#endif
 
HBITMAP WINAPI GetDesktopImage(LPSIZE lpSize = NULL);
HBITMAP WINAPI GetWindowImage(LPSIZE lpSize = NULL);
HBITMAP WINAPI GetRegionImage(LPSIZE lpSize = NULL);	
HBITMAP WINAPI GetClipboardImage(LPSIZE lpSize = NULL, BOOL bPlaySound = TRUE);

BOOL    WINAPI TrapPrintScreen(HWND hWnd);
BOOL    WINAPI UnTrapPrintScreen(HWND hWnd);

const UINT UWM_PRINTSCREEN = RegisterWindowMessage("UWM_PRINTSCREEN");

#ifdef __cplusplus
}
#endif
  
#endif;