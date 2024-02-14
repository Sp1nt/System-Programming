#include <windows.h>
#include <tchar.h>
#include <vector>
#include "resource.h"
#include "windowsx.h"

BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);

HWND hStatic1, hStatic2;
HINSTANCE hInst;

static int localStaticCounter = 0;

POINT startCoord; 
POINT finishCoord;



std::vector<std::vector<int>> ArrayStatic = {};

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPTSTR lpszCmdLine, int nCmdShow) {
    hInst = hInstance;
    return DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)DlgProc);
}

BOOL CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) 
{
    switch (message)
    {
    case WM_CLOSE:
        EndDialog(hWnd, 0);
        return TRUE;
    case WM_LBUTTONDOWN: {
        startCoord.x = LOWORD(lParam);
        startCoord.y = HIWORD(lParam);

        return TRUE;
    }
    case WM_LBUTTONUP: {
        finishCoord.x = LOWORD(lParam);
        finishCoord.y = HIWORD(lParam);

        RECT rect;
        rect.left = min(startCoord.x, finishCoord.x);
        rect.top = min(startCoord.y, finishCoord.y);
        rect.right = max(startCoord.x, finishCoord.x);
        rect.bottom = max(startCoord.y, finishCoord.y);

        if (rect.right - rect.left >= 10 && rect.bottom - rect.top >= 10) {
            hStatic2 = CreateWindowEx(0, TEXT("STATIC"), 0,
                WS_CHILD | WS_VISIBLE | WS_BORDER | SS_CENTER | WS_EX_CLIENTEDGE,
                rect.left, rect.top,
                rect.right - rect.left,
                rect.bottom - rect.top,
                hWnd, 0, hInst, 0);

            SetWindowLongPtr(hStatic2, GWLP_USERDATA, localStaticCounter++);    // Устанавливаем уникальный идентификатор статического окна
            SetWindowText(hStatic2, 0);

            ArrayStatic.push_back({ rect.left, rect.top,rect.right - rect.left, rect.bottom - rect.top });
        }
        else {
            MessageBox(0,
                _TEXT("Minimum size 10 by 10"),
                _TEXT("Information"),
                MB_OK | MB_ICONWARNING);
        }

        return TRUE;
    }
    case WM_RBUTTONDOWN: {
        POINT point;
        _TCHAR buffer[256];

        point.x = GET_X_LPARAM(lParam);
        point.y = GET_Y_LPARAM(lParam);

        HWND staticWindow = ChildWindowFromPoint(hWnd, point); // Получаем окно, на которое был произведен клик

        if (staticWindow != hWnd) {
            HWND uniqueID = ChildWindowFromPointEx(hWnd, point, CWP_ALL);   // Получаем уникальный идентификатор окна
            int uniqueInfo = GetWindowLongPtr(uniqueID, GWLP_USERDATA); // Получаем информацию о статическом окне

            wsprintf(buffer, _TEXT("#%d. x: %d, y: %d. width: %d, height: %d"), uniqueInfo,
                ArrayStatic[uniqueInfo][0], ArrayStatic[uniqueInfo][1],
                ArrayStatic[uniqueInfo][2], ArrayStatic[uniqueInfo][3]);
            SetWindowText(hWnd, buffer);
        }
        return TRUE;
    }


    }

    return FALSE;
}
