#include "main.h"
#include "AppDelegate.h"
#include "CCEGLView.h"
#include "Tools.h"
#include "DbgHelp.h"

USING_NS_CC;

static void DumpMiniDump(HANDLE hFile, PEXCEPTION_POINTERS excpInfo)
{
	if (excpInfo == NULL)
	{
		// Generate exception to get proper context in dump
		__try
		{
			OutputDebugString(_T("raising exception\r\n"));
			RaiseException(EXCEPTION_BREAKPOINT, 0, 0, NULL);
		}
		__except (DumpMiniDump(hFile, GetExceptionInformation()),
			EXCEPTION_CONTINUE_EXECUTION)
		{
		}
	}
	else
	{
		OutputDebugString(_T("writing minidump\r\n"));
		MINIDUMP_EXCEPTION_INFORMATION eInfo;
		eInfo.ThreadId = GetCurrentThreadId();
		eInfo.ExceptionPointers = excpInfo;
		eInfo.ClientPointers = FALSE;

		MiniDumpWriteDump(
			GetCurrentProcess(),
			GetCurrentProcessId(),
			hFile,
			MiniDumpNormal,
			excpInfo ? &eInfo : NULL,
			NULL,
			NULL);
	}
}

int  cocosMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPTSTR    lpCmdLine,
	int       nCmdShow)
//int APIENTRY _tWinMain(HINSTANCE hInstance,
//	HINSTANCE hPrevInstance,
//	LPTSTR    lpCmdLine,
//	int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	
	// create the application instance
	AppDelegate app;
	CCEGLView* eglView = CCEGLView::sharedOpenGLView();

	RECT    rc;
	HWND m_hWnd = eglView->getHWnd();
	HWND hDesk = GetDesktopWindow();
	GetWindowRect(hDesk, &rc);
	SetWindowLong(m_hWnd, GWL_STYLE, WS_BORDER);
	//SetWindowPos( m_hWnd, HWND_TOPMOST, 0, 0, rc.right, rc.bottom, SWP_SHOWWINDOW );
	ShowWindow(hDesk, SW_SHOWMAXIMIZED);


	eglView->setViewName("Test");
	if (Ext_TiaoShi)
	{
		eglView->setFrameSize(1600, 900);
	}
	else
	{
		eglView->setFrameSize(1920, 1080);
	}


	RECT rcWindow;
	HWND xxtmp = eglView->getHWnd();
	GetWindowRect(xxtmp, &rcWindow);
	int w = (int)rcWindow.right;
	int h = (int)rcWindow.bottom;
	eglView->setFrameSize(w, h);

	return CCApplication::sharedApplication()->run();

}

int APIENTRY _tWinMain(HINSTANCE hInstance,
                       HINSTANCE hPrevInstance,
                       LPTSTR    lpCmdLine,
                       int       nCmdShow)
{
	Ext_TiaoShi = true;
	if (Ext_TiaoShi && AllocConsole())
	{
		freopen("CONOUT$", "w", stdout);
		printf("hello, world!");
	}
	else
	{
		freopen("DeBugMsg.txt", "w", stdout);
		printf("hello, world!");
	}

	printf("tWinMain");

	HANDLE m_hSingleProMutex;
	m_hSingleProMutex = CreateMutex(NULL, TRUE, L"SinglePro");
	if (m_hSingleProMutex)
	{
		if (ERROR_ALREADY_EXISTS == GetLastError())
		{
			exit(0);
		}
	}

	HANDLE hFile = CreateFile(_T("MiniDump.dmp"), GENERIC_READ | GENERIC_WRITE,
		0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	int code;

	if(!Ext_TiaoShi){
		__try
		{
			cocosMain(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
		}
		__except (code = GetExceptionCode(), DumpMiniDump(hFile, GetExceptionInformation()), EXCEPTION_EXECUTE_HANDLER) //�������쳣, ��¼�쳣��code, ����dump!!
		{
			printf("%x\n", code);
			wchar_t msg[512];
			wsprintf(msg, L"Exception happened. Exception code is %x", code);
			MessageBox(NULL, msg, L"Exception", MB_OK);
		}
	}
	else{
		cocosMain(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
	}
	CloseHandle(hFile);
	getchar();

	if (Ext_TiaoShi)
	{
		FreeConsole();
	}
	return 0;
}