#define _CRT_SECURE_NO_WARNINGS
#define _UNICODE
#include <iostream>
#include <tchar.h>

using namespace std;

void SpacesToTabs(_TCHAR str[]) {
    for (int i = 0; i < _tcslen(str); i++) {
        if (str[i] == ' ')
            str[i] = '\t';
    }
}

void CountSymbols(_TCHAR str[]) {
    int nLetters = 0;
    int nDigits = 0;

    for (int i = 0; i < _tcslen(str); i++) {
        if (_istalpha(str[i])) {
            nLetters++;
        }
        else if (_istdigit(str[i])) {
            nDigits++;
        }
    }

    wcout << "Number Of Letters: " << nLetters << endl
        << "Number Of Digits: " << nDigits << endl;
}

void CheckerWord(_TCHAR str[]) {
    int count = 0;
    int nDigits = 0;

    for (int i = 0; i <= _tcslen(str); i++) {
        if (_istalpha(str[i])) { 
            nDigits++;
        }
        else {
            if (nDigits >= 2) { 
                count++;
            }
            nDigits = 0;
        }
    }

    wcout << "Words: " << count << endl;
}

void CheckerVowels(_TCHAR str[]) {
    int vowels = 0;
    for (int i = 0; i < _tcslen(str); i++) {
        if (str[i] == 'a' || str[i] == 'A' || str[i] == 'i' || str[i] == 'I' || str[i] == 'o' ||
            str[i] == 'O' || str[i] == 'u' || str[i] == 'U' || str[i] == 'e' || str[i] == 'E' ||
            str[i] == 'y' || str[i] == 'Y')
            vowels++;
    }
    wcout << "Vowels: " << vowels << endl;
}

bool isPalindromes(_TCHAR str[]) {
    int len = _tcslen(str);
    for (int i = 0; i < len / 2; i++) {
        if (str[i] != str[len - i - 1]) {
            return false;
        }
    }
    return true;
}

_TCHAR* DeleteByIndex(_TCHAR str[], int index);
_TCHAR* DeleteBySymbol(_TCHAR str[], char symb);
_TCHAR* AddSymbolByIndex(_TCHAR str[], char symb, int index);



int main()
{
    //1
    _TCHAR myStr[90] = _TEXT("Lorem Ipsum is simply dummy text of the prentaing and typesetting industry.");

    SpacesToTabs(myStr);

    wcout << myStr << endl;

    wcout << endl << endl << endl;

    //2

    _TCHAR myStr1[90] = _TEXT("Lorem 4r3243 is sim43ply dummy 12 of the 3622 and typesetting 7667.");

    CountSymbols(myStr1);

    wcout << endl << endl << endl;

    //3

    _TCHAR myStr2[90] = _TEXT("Lorem Ipsumthe prentaing typesetting industry");

    CheckerWord(myStr2);

    wcout << endl << endl << endl;

    //4

    _TCHAR myStr3[90] = _TEXT("Lorem Ipsumthe prentaing typesetting industry");

    CheckerVowels(myStr3);

    wcout << endl << endl << endl;

    //5

    _TCHAR myStr4[90] = _TEXT("refer");
    if (isPalindromes(myStr4)) {
        cout << "The string is a palindrome." << endl;
    }
    else {
        cout << "The string is not a palindrome." << endl;
    }

    wcout << endl << endl << endl;

    //6

    _TCHAR myStr5[90] = _TEXT("Lorem");

    _TCHAR* newStr5 = DeleteByIndex(myStr5, 3);
    wcout << newStr5 << endl;

    wcout << endl << endl << endl;

    //7

    _TCHAR* newStr6 = DeleteBySymbol(myStr5, 'o');
    wcout << newStr6 << endl;

    wcout << endl << endl << endl;

    //8

    _TCHAR* newStr7 = AddSymbolByIndex(myStr5, 'f', 2);
    wcout << newStr7 << endl;

    return 0;
}


_TCHAR* DeleteByIndex(_TCHAR str[], int index) {
    int len = _tcslen(str);

    _TCHAR* tempString = new _TCHAR[len + 1];

    int j = 0;

    for (int i = 0; i < len; i++) {
        if (i != index) {
            tempString[j++] = str[i];
        }
    }

    tempString[j] = '\0';

    return tempString;
}

_TCHAR* DeleteBySymbol(_TCHAR str[], char symb) {
    int len = _tcslen(str);
    int j = 0;
    _TCHAR* result = new _TCHAR[len + 1];

    for (int i = 0; i < len; i++) {
        if (str[i] != symb) {
            result[j++] = str[i];
        }
    }
    result[j] = '\0';

    return result;
}

_TCHAR* AddSymbolByIndex(_TCHAR str[], char symb, int index) {
    int len = _tcslen(str);

    _TCHAR* result = new _TCHAR[len + 2];

    for (int i = 0; i < index; i++) {
        result[i] = str[i];
    }


    result[index] = symb;


    for (int i = index; i < len + 1; i++) {
        result[i + 1] = str[i];
    }

    return result;
}