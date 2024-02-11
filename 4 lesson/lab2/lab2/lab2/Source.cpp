#include <windows.h>
#include <tchar.h>
#include "resource.h"

// Глобальные переменные
HWND hDlg;
int staticCount = 0;

// Прототипы функций
BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);

// Точка входа в приложение
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    // Создание диалогового окна
    hDlg = CreateDialog(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc);
    if (!hDlg)
    {
        MessageBox(NULL, "CreateDialog failed!", "Error", MB_OK | MB_ICONERROR);
        return 0;
    }

    // Отображение диалогового окна
    ShowWindow(hDlg, nCmdShow);

    // Цикл обработки сообщений
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        if (!IsDialogMessage(hDlg, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return msg.wParam;
}

// Обработчик сообщений для диалогового окна
BOOL CALLBACK DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_LBUTTONDOWN:
    {
        // Получаем координаты курсора мыши
        int x = GET_X_LPARAM(lParam);
        int y = GET_Y_LPARAM(lParam);

        // Создаем статик в указанных координатах
        CreateWindow("STATIC", std::to_string(++staticCount).c_str(),
            WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER,
            x, y, 50, 20, hwnd, NULL, NULL, NULL);
    }
    return TRUE;
    case WM_CLOSE:
        // Закрываем диалоговое окно
        DestroyWindow(hwnd);
        return TRUE;
    case WM_DESTROY:
        // Завершаем приложение
        PostQuitMessage(0);
        return TRUE;
    default:
        return FALSE;
    }
    return TRUE;
}
