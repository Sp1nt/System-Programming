#include <windows.h>
#include <tchar.h>


TCHAR szClassWindow[] = TEXT("��������� ����������");

int WINAPI _tWinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPTSTR lpszCmdLine, int nCmdShow)
{

    LPCTSTR               lpApplicationName;
    LPTSTR                lpCommandLine;
    LPSECURITY_ATTRIBUTES lpProcessAttributes;
    LPSECURITY_ATTRIBUTES lpThreadAttributes;
    BOOL                  bInheritHandles;
    DWORD                 dwCreationFlags;
    LPVOID                lpEnvironment;
    LPCTSTR               lpCurrentDirectory;
    LPSTARTUPINFO         lpStartupInfo;
    LPPROCESS_INFORMATION lpProcessInformation;

    HWND hWindow; // ���� "����������� ����"
    HWND hWindow1; // ���� "��� ���������"


    LPPROCESS_INFORMATION pi = { 0 };
    SHELLEXECUTEINFO sei = { 0 };

    SECURITY_ATTRIBUTES sa = { 0 };
    sa.nLength = sizeof(sa);

    STARTUPINFO si = { 0 };
    si.cb = sizeof(si);   // ������ ��������� � ������.
    si.dwX = 100; // ��������� �� X �������� ������ ���� ���������� ����, � ��������
    si.dwY = 100; //  ��������� �� Y �������� ������ ���� ���������� ����, � ��������
    si.dwXSize = 400; // ������� ����, � ��������
    si.dwYSize = 200; // ������� ����, � ��������
    si.dwXCountChars = NULL; //
    si.dwYCountChars = NULL; //
    si.dwFillAttribute = FOREGROUND_BLUE; //  ���������� ��������� ���� ������ � ����
    si.dwFlags = STARTF_USEPOSITION;
    si.wShowWindow = NULL;
    si.cbReserved2 = NULL;

    lpApplicationName = TEXT("c:\calc.exe");  // ��������� �� ��� ������������ �����
    lpCommandLine = NULL;                 // ��������� �� ��������� ������
    lpProcessAttributes = NULL;   // ��������� �� �������� ������������ ��������
    lpThreadAttributes = NULL;     // ��������� �� �������� ������������ ������
    bInheritHandles = TRUE;                // ��������� �� ���� ������������
    dwCreationFlags = CREATE_DEFAULT_ERROR_MODE;           // ����� ��������
    lpEnvironment = NULL;                 // ��������� �� ����� ���� �����
    lpCurrentDirectory = NULL;            // ��������� �� ��� �������� ��������
    lpStartupInfo = &si;             // ��������� �� ��������� STARTUPINFO
    lpProcessInformation = pi;     // ��������� �� ��������� PROCESS_INFORMATION

        CreateProcess(

            lpApplicationName,
            lpCommandLine,
            lpProcessAttributes,
            lpThreadAttributes,
            bInheritHandles,
            dwCreationFlags,
            lpEnvironment,
            lpCurrentDirectory,
            lpStartupInfo,
            lpProcessInformation

        );

    Sleep(30);

    HWND calc = FindWindow(_T("SciCalc"), NULL);
    SetWindowText(calc, _T("�������� ���������������"));


    /*CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);*/
}