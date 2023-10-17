#undef UNICODE   // Pārslēgt projektu ASCII režīmā 
#include <windows.h> 
#include <stdio.h> 
#include "stdio.h"//stdio
#include "resource.h"  
#pragma warning(disable : 4996)  // Ziņojumu apstrādātāja prototips 
BOOL CALLBACK MainWndProc(HWND, UINT, WPARAM, LPARAM);  

// Galvenā funkcija  
// // ja galvenā loga šablonam ir piešķirts resursa identifikators IDD_MAINDIALOG 
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int) {  
	DialogBox(   
		hInstance,    
		MAKEINTRESOURCE(IDD_MAINDIALOG),    
		NULL,    
		DLGPROC(MainWndProc)  );  
	return 0; 
}  // Ziņojumu apstrādātājs 

void ShowInfo(HWND wnd) {
	// Computer Name
	char buf[100];
	DWORD size = 100;
	if (!GetComputerName(buf, &size)) strcpy_s(buf, "error");
	SetDlgItemText(wnd, IDC_COMPNAME, buf);
	// User Name
	if (!GetUserName(buf, &size)) strcpy_s(buf, "error");
	SetDlgItemText(wnd, IDC_USERNAME, buf);
	// OS version
	OSVERSIONINFO ver;
	ver.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	GetVersionEx(&ver);
	sprintf_s(buf, "%d.%d (build %d) %s", ver.dwMajorVersion, ver.dwMinorVersion, ver.dwBuildNumber, ver.szCSDVersion);
	SetDlgItemText(wnd, IDC_VERSION, buf);
	// Physical memory
	MEMORYSTATUSEX statex;
	statex.dwLength = sizeof(statex);
	GlobalMemoryStatusEx(&statex);
	sprintf_s(buf, "%I64d MB", statex.ullTotalPhys / 1024/1024);
	SetDlgItemText(wnd, IDC_TOTALRAM, buf);
	// Free memory
	sprintf_s(buf, "%I64d MB", statex.ullAvailPhys / 1024 / 1024);
	SetDlgItemText(wnd, IDC_FREERAM, buf);
	// Percent of memory in use. GlobalMemoryStatusEx
	sprintf_s(buf, "%I64d MB", statex.dwMemoryLoad / 1024 / 1024);
	SetDlgItemText(wnd, IDC_PERCENTRAM, buf);
	// Current Date and Time. GetLocalTime
	SYSTEMTIME sm;
	GetLocalTime(&sm);
	sprintf_s
	SetDlgItemText(wnd, IDC_DATETIME, buf);
	// Time since power on. GetTickCount
}

BOOL CALLBACK MainWndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam) {  
	switch (Msg) { // pārbaudīt ziņojuma identifikatoru  
	case WM_INITDIALOG: // ja tas ir inicializācijas paziņojums     
		SetTimer(hWnd, NULL, 200, NULL);
		ShowInfo(hWnd);				// izpildīt inicializācijas darbības   
		return TRUE;  
	case WM_COMMAND: // ja tas ir paziņojums no vadības elementa   
		switch (LOWORD(wParam)) { // pārbaudīt vadības elementa ID   
		case IDOK: // ja bija uzspiesta Close poga    
			DestroyWindow(hWnd); // aizvērt logu    
			return TRUE;  
		}   
		return FALSE;   
	case WM_DESTROY: // ja tas ir pabeigšanas pieprasījums   
		PostQuitMessage(0); // pabeigt programmu   
		return TRUE;  
	}  
	return FALSE; 
} 