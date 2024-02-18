#include <windows.h>
#include "windowsx.h"
#include <tchar.h>
#include "resource.h"

BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPTSTR lpszCmdLine, int nCmdShow)
{
    return DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)DlgProc);
}

BOOL CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wp, LPARAM lp)
{
    static HWND hwndStatic;

    switch (message)
    {
    case WM_CLOSE:
        EndDialog(hWnd, 0);
        return TRUE;

    case WM_INITDIALOG: {
        hwndStatic = GetDlgItem(hWnd, IDOK);
        return TRUE;
    }
    case WM_MOUSEMOVE: {
        POINT point;
        GetCursorPos(&point);
        ScreenToClient(hWnd, &point);

        RECT rect;
        GetWindowRect(hwndStatic, &rect);

        InflateRect(&rect, 75, 75);

        if (PtInRect(&rect, point)) {
            int newX = rand() % (rect.right - rect.left - GetSystemMetrics(SM_CXSIZE));
            int newY = rand() % (rect.bottom - rect.top - GetSystemMetrics(SM_CYSIZE));
            SetWindowPos(hwndStatic, NULL, newX, newY, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
        }
        return TRUE;
    }
   }
    return FALSE;
}
