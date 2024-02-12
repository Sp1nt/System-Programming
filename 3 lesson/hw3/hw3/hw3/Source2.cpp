#include "Windows.h"
#include "windowsx.h"
#include "tchar.h"

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nShowCmd)
{
	WCHAR className[] = L"FirstWindow";

	WNDCLASSEX wndClass;
	wndClass.cbSize = sizeof(WNDCLASSEX);
	wndClass.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	wndClass.hInstance = hInstance;
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hIconSm = NULL;
	wndClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.lpszMenuName = NULL;
	wndClass.lpszClassName = className;

	wndClass.lpfnWndProc = WindowProc;

	if (!RegisterClassEx(&wndClass)) {
		return 0;
	}

	HWND hWnd = CreateWindowEx(
		0,
		className,
		L"My first window",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, //x,y
		CW_USEDEFAULT, CW_USEDEFAULT, //width, height
		NULL,
		NULL,
		hInstance,
		NULL
	);

	ShowWindow(hWnd, nShowCmd);
	UpdateWindow(hWnd);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		DispatchMessage(&msg);
	}

	return msg.wParam;
}

void KeyUpHandler(HWND hwnd, WPARAM wParam, LPARAM lParam);

int countClickLeftButtonMouse = 0;
int countClickRightButtonMouce = 0;
int countClickMiddleButtonMouce = 0;
_TCHAR buff[20]{ 0 };


// window. task - 3
int counterV = 0;
int counterH = 0;
int sides = 0;

bool f = false;
bool v = true;
bool h = false;

int sizeWidthWindow = 300;
int sizeHeightWindow = 300;

int screenWidth = GetSystemMetrics(SM_CXSCREEN);
int screenHeight = GetSystemMetrics(SM_CYSCREEN);

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	// 1
	switch (uMsg) {
	case WM_DESTROY:
		PostQuitMessage(0); //WM_QUIT
		break;

	case WM_LBUTTONDOWN: {
		// 2
		wsprintf(buff, _T("Count click left button mouse: %d"), countClickLeftButtonMouse++);
		SetWindowText(hwnd, buff);
		break;
	}
	case WM_RBUTTONUP: {
		wsprintf(buff, _T("Count click right button mouse: %d"), countClickRightButtonMouce++);
		SetWindowText(hwnd, buff);
		break;
	}
	case WM_MBUTTONUP: {
		wsprintf(buff, _T("Count click right middle mouse: %d"), countClickMiddleButtonMouce++);
		SetWindowText(hwnd, buff);
		break;
	}
					 // 3
	case WM_KEYUP: {
		KeyUpHandler(hwnd, wParam, lParam);
		break;
	}
	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}

	// buttons
	switch (wParam) {
	case VK_UP: {
		if (f && counterH != 0)
			SetWindowPos(hwnd, NULL, counterV, counterH -= 10, sizeWidthWindow, sizeHeightWindow, SWP_NOZORDER);
		break;
	}
	case VK_RIGHT: {
		if (f && counterV != (screenWidth - sizeWidthWindow))
			SetWindowPos(hwnd, NULL, counterV += 10, counterH, sizeWidthWindow, sizeHeightWindow, SWP_NOZORDER);
		break;
	}
	case VK_DOWN: {
		if (f && counterH != (screenHeight - sizeHeightWindow) - 40)
			SetWindowPos(hwnd, NULL, counterV, counterH += 10, sizeWidthWindow, sizeHeightWindow, SWP_NOZORDER);
		break;
	}
	case VK_LEFT: {
		if (f && counterV != 0)
			SetWindowPos(hwnd, NULL, counterV -= 10, counterH, sizeWidthWindow, sizeHeightWindow, SWP_NOZORDER);
		break;
	}
	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}

	return 0;
}



void KeyUpHandler(HWND hwnd, WPARAM wParam, LPARAM lParam) {
	if (wParam == VK_RETURN) {
		SetWindowPos(hwnd, NULL, 0, 0, sizeWidthWindow, sizeHeightWindow, SWP_NOZORDER);
		counterV = 0;
		counterH = 0;
		sides = 0;
		f = true;
	}
}