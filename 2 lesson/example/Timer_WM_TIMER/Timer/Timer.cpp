#include <windows.h>
#include <tchar.h>
#include <time.h>

LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);

TCHAR szClassWindow[] = TEXT("��������� ����������");	

int WINAPI _tWinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPTSTR lpszCmdLine, int nCmdShow)
{
	HWND hWnd;
	MSG Msg;
	WNDCLASSEX wcl;
	wcl.cbSize = sizeof(wcl);	
	wcl.style = CS_HREDRAW | CS_VREDRAW;	
	wcl.lpfnWndProc = WindowProc;	
	wcl.cbClsExtra = 0;	
	wcl.cbWndExtra = 0; 	
	wcl.hInstance = hInst;	
	wcl.hIcon = LoadIcon(NULL, IDI_APPLICATION);	
	wcl.hCursor = LoadCursor(NULL, IDC_ARROW);	
	wcl.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH); 
	wcl.lpszMenuName = NULL;	
	wcl.lpszClassName = szClassWindow;	
	wcl.hIconSm = NULL;	
	if (!RegisterClassEx(&wcl))
		return 0;
	hWnd = CreateWindowEx(0, szClassWindow, TEXT("������ � ��������"), WS_OVERLAPPEDWINDOW,	
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInst, NULL);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	while(GetMessage(&Msg, NULL, 0, 0))
	{
		TranslateMessage(&Msg);	
		DispatchMessage(&Msg);	
	}
	return Msg.wParam;
}	


LRESULT CALLBACK WindowProc (HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static time_t t;
	static TCHAR str[100];

	switch(message)
	{
		case WM_DESTROY: 
			PostQuitMessage(0);
			break;
		case WM_TIMER:
			t = time(NULL);	// ���������� ������, ��������� � 01.01.1970
			lstrcpy(str, _tctime(&t));  // ������������ ������ ���������� �������:  ���� ����� ����� ����:������:������� ���
			str[lstrlen(str) - 1] = '\0';
			SetWindowText(hWnd, str);	// ����� ���� � ������� � ��������� ����
			break;
		case WM_KEYDOWN:
			if(wParam == VK_RETURN)
				SetTimer(hWnd, 1, 1000, NULL);	// ��������� ������� �� ������� ������� <ENTER>
			else if(wParam == VK_ESCAPE)
				KillTimer(hWnd, 1);	// ����������� ������� �� ������� ������� <ESC>
			break;	
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

