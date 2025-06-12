#include "Header.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <windows.h>

using namespace std;

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "RU");
    cout << "Вариант ввода:\n"
        << "1. С клавиатуры\n"
        << "2. Из файла\n"
        << "Ваш выбор:";
    int choice;
    wordList chain;
    while (!(cin >> choice) || choice < 1 || choice > 2) {
        cin.clear();
        cin.ignore((numeric_limits<streamsize>::max)(), '\n');
        cout << "Ошибка. Введите число от 1 до 2: ";
    }
    cin.clear();
    cin.ignore((numeric_limits<streamsize>::max)(), '\n');
    string s;

    switch (choice) {
    case 1:
        s = getString("Введите строку (слова с маленькой буквы через пробел)");
        cout << "Ваша строка: " << s << endl;
        break;

    case 2: {
        string p = "input.txt";
        ifstream file(p);
        if (file.is_open()) {
            getline(file, s);
            cout << "Прочитанная строка: " << s << endl;
            file.close();

            if (!validateString(s)) {
                cout << "Строка в файле не соответствует требованиям." << endl;
                return 1;
            }
        }
        else {
            cout << "Ошибка открытия файла" << endl;
            return 1;
        }
        break;
    }
    default:
        break;
    }

    if (chain.bildChainWord(s)) {
        cout << "Цепь построена: ";
        chain.PrintChain();
        chain.SaveChainToFile("output.txt");
    }
    else {
        cout << "Цепь построить невозможно" << endl;
    }
    return 0;
}
