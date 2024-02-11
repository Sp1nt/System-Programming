#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <tchar.h>
#include <ctime>



INT WINAPI _tWinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPTSTR lpszCmdLine, int nCmdShow) {

	//1 task

	_TCHAR str1[] = _TEXT("Programming in C++, Java, Python. Knowledge of algorithms and data structures.");
	_TCHAR str2[] = _TEXT("Bachelor of Science in Computer Science, 'Step' University. 3 years of experience at Logic.");
	_TCHAR str3[] = _TEXT("Proficiency in English at the Upper-Intermediate level. Interest in machine learning.");

	
	int totalSum = _tcslen(str1) + _tcslen(str2) + _tcslen(str3);


	int AverageSum = totalSum / 3;


	_TCHAR InfoWindow[255];
	_stprintf_s(InfoWindow, _T("Average Letters: %d)"), AverageSum);

	MessageBox(0,
		str1,
		_TEXT("Skills and Qualifications:"), MB_OK | MB_ICONINFORMATION);

	MessageBox(0,
		str2,
		_TEXT("Education and work experience:"), MB_OK | MB_ICONINFORMATION);

	MessageBox(0,
		str3,
		_TEXT("Additional Information:"), MB_OK | MB_ICONINFORMATION);

	MessageBox(0,
		InfoWindow,
		_TEXT("Infomation Window"), MB_OK | MB_ICONINFORMATION);



	//2 task

	srand(time(NULL));
	_TCHAR buffer[60];
	int start;
	int attempts = 0;

	bool flag = false;
	bool gameFlag = true;

	do {
		int rNumber = 1 + rand() % 100;
		
		wsprintf(buffer, _TEXT("You guessed a number %d ?"), rNumber);
		start = MessageBox(0, buffer, _TEXT("GAME"), MB_YESNOCANCEL | MB_ICONQUESTION);

		if (start == IDYES) {
			MessageBox(0, _TEXT("I guessed your number."), _TEXT("GAME"), MB_OK | MB_ICONASTERISK);
			wsprintf(buffer, _TEXT("Number of attempts: %d"), attempts);
			MessageBox(0, buffer, _TEXT("GAME"), MB_OK | MB_ICONASTERISK);
			flag = true;
		}

		if (flag) {
			int playAgain = MessageBox(0, _TEXT("Do you want to play again?"), _TEXT("GAME"), MB_YESNO | MB_ICONWARNING);
			if (playAgain == IDYES) {
				attempts = -1;
				flag = false;
			}
			else {
				gameFlag = false;
			}
		}
		attempts++;
	} while (start != IDCANCEL && gameFlag);

	if (!gameFlag || start == IDCANCEL) {
		MessageBox(0,
			_TEXT("End of the game!"),
			_TEXT("GAME"), MB_OK | MB_ICONSTOP);
	}



	return 0;
}

