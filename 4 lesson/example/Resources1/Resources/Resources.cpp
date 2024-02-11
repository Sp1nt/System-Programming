#include <windows.h>
#include "resource.h"
#include <tchar.h>

LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);

TCHAR szClassWindow[] = TEXT("Каркасное приложение");
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
	wcl.hIcon = LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON1)); // иконка загружается из ресурсов приложения	
	wcl.hCursor = LoadCursor(hInst, MAKEINTRESOURCE(IDC_CURSOR2));	// курсор загружается из ресурсов приложения	
	wcl.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH); 
	wcl.lpszMenuName = NULL;	
	wcl.lpszClassName = szClassWindow;	
	wcl.hIconSm = NULL;	
	if (!RegisterClassEx(&wcl))
		return 0;
	hWnd = CreateWindowEx(0, szClassWindow, TEXT("Ресурсы"), WS_OVERLAPPEDWINDOW,	
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
				// получаем дескриптор приложения
				HINSTANCE hInstance = GetModuleHandle(0); 
				// загружаем иконку из ресурсов приложения
				hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON2)); 

				// загружаем курсоры из ресурсов приложения
				hCursor1 = LoadCursor(hInstance, MAKEINTRESOURCE(IDC_CURSOR1));
				hCursor2 = LoadCursor(hInstance, MAKEINTRESOURCE(IDC_CURSOR2)); 
				hCursor3 = LoadCursor(hInstance, MAKEINTRESOURCE(IDC_CURSOR3));
				hCursor4 = LoadCursor(hInstance, MAKEINTRESOURCE(IDC_CURSOR4));

			}
			break;
		case WM_MOUSEMOVE:
			{
				// устанавливаем тот или иной курсор в зависимости от местонахождения указателя мыши
				RECT rect;
				GetClientRect(hWnd, &rect);

				int x = LOWORD(lParam);
				int y = HIWORD(lParam);

				int midX = (rect.right - rect.left) / 2;
				int midY = (rect.bottom - rect.top) / 2;


				if (x < midX && y < midY)
					SetCursor(hCursor1); // Верхний левый угол
				else if (x >= midX && y < midY)
					SetCursor(hCursor2); // Верхний правый угол
				else if (x < midX && y >= midY)
					SetCursor(hCursor3); // Нижний левый угол
				else
					SetCursor(hCursor4); // Нижний правый угол
			}
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

