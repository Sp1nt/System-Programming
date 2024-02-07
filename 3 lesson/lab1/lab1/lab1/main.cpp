#include "Windows.h"
#include "tchar.h"
#include <string>
using std::wstring;

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

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
		CW_USEDEFAULT, CW_USEDEFAULT,
		CW_USEDEFAULT, CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	ShowWindow(hWnd, nShowCmd);
	UpdateWindow(hWnd);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	const int width = 300, height = 300;

	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		if (wParam == VK_RETURN) {
			MoveWindow(hWnd, 0, 0, width, height, true);
			SetTimer(hWnd, 1, 10, NULL);
		}
		else if (wParam == VK_ESCAPE) {
			KillTimer(hWnd, 1);
		}
		break;
	case WM_TIMER:
	{
		int displayWidth = GetSystemMetrics(SM_CXSCREEN);
		int displayHeight = GetSystemMetrics(SM_CYSCREEN);

		static int mover = 0;
		int CoordX = 10;
		int CoordY = 10;

		RECT rect;
		GetWindowRect(hWnd, &rect);

		switch (mover)
		{
		case 0:
			if (rect.right + CoordX >= displayWidth) {
				mover = 1;
			}
			SetWindowPos(hWnd, NULL, rect.left + CoordX, rect.top, width, height, SWP_NOZORDER);
			break;

		case 1:
			if (rect.bottom + CoordY >= displayHeight) {
				mover = 2;
			}
			SetWindowPos(hWnd, NULL, rect.left, rect.top + CoordY, width, height, SWP_NOZORDER);
			break;

		case 2:
			if (rect.left - CoordX <= 0) {
				mover = 3;
			}
			SetWindowPos(hWnd, NULL, rect.left - CoordX, rect.top, width, height, SWP_NOZORDER);
			break;

		case 3:
			if (rect.top - CoordY <= 0) {
				mover = 0;
			}
			SetWindowPos(hWnd, NULL, rect.left, rect.top - CoordY, width, height, SWP_NOZORDER);
			break;

		default:
			break;
		}
	}
		break;
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}

	return 0;
}