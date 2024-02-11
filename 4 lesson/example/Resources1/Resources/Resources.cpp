#include <windows.h>
#include "resource.h"
#include <tchar.h>

LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);

TCHAR szClassWindow[] = TEXT("��������� ����������");
HICON hIcon;
HCURSOR hCursor1, hCursor2, hCursor3, hCursor4;

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
	wcl.hIcon = LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON1)); // ������ ����������� �� �������� ����������	
	wcl.hCursor = LoadCursor(hInst, MAKEINTRESOURCE(IDC_CURSOR2));	// ������ ����������� �� �������� ����������	
	wcl.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH); 
	wcl.lpszMenuName = NULL;	
	wcl.lpszClassName = szClassWindow;	
	wcl.hIconSm = NULL;	
	if (!RegisterClassEx(&wcl))
		return 0;
	hWnd = CreateWindowEx(0, szClassWindow, TEXT("�������"), WS_OVERLAPPEDWINDOW,	
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
	switch(message)
	{
		case WM_DESTROY: 
			PostQuitMessage(0);
			break;
		case WM_CREATE:
			{
				// �������� ���������� ����������
				HINSTANCE hInstance = GetModuleHandle(0); 
				// ��������� ������ �� �������� ����������
				hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON2)); 

				// ��������� ������� �� �������� ����������
				hCursor1 = LoadCursor(hInstance, MAKEINTRESOURCE(IDC_CURSOR1));
				hCursor2 = LoadCursor(hInstance, MAKEINTRESOURCE(IDC_CURSOR2)); 
				hCursor3 = LoadCursor(hInstance, MAKEINTRESOURCE(IDC_CURSOR3));
				hCursor4 = LoadCursor(hInstance, MAKEINTRESOURCE(IDC_CURSOR4));

			}
			break;
		case WM_MOUSEMOVE:
			{
				// ������������� ��� ��� ���� ������ � ����������� �� ��������������� ��������� ����
				RECT rect;
				GetClientRect(hWnd, &rect);

				int x = LOWORD(lParam);
				int y = HIWORD(lParam);

				int midX = (rect.right - rect.left) / 2;
				int midY = (rect.bottom - rect.top) / 2;


				if (x < midX && y < midY)
					SetCursor(hCursor1); // ������� ����� ����
				else if (x >= midX && y < midY)
					SetCursor(hCursor2); // ������� ������ ����
				else if (x < midX && y >= midY)
					SetCursor(hCursor3); // ������ ����� ����
				else
					SetCursor(hCursor4); // ������ ������ ����
			}
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

