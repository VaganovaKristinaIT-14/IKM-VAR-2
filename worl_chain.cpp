#include "Header.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <limits>

using namespace std;

string alphabet = "абвгдеёжзийклмнопрстуфхцчшщъыьэюя ";

bool validateString(const string& input) {
    if (input.empty()) {
        cout << "Ошибка. В строке должно быть хотя бы одно слово" << endl;
        return false;
    }

    for (char c : input) {
        if (alphabet.find(c) == string::npos) {
            cout << "Ошибка ввода! Строка должна содержать только русские строчные буквы и пробелы." << endl;
            return false;
        }
    }
    return true;
}

string getString(const char* prompt) {
    while (true) {
        cout << prompt << endl;
        string input;
        getline(cin, input);
        if (validateString(input)) {
            return input;
        }
    }
}

// Реализация методов класса wordNode
wordNode::wordNode(const string& w) : word(w), next(nullptr) {}

const string& wordNode::getWord() const { return word; }
void wordNode::setWord(const string& w) { word = w; }

wordNode* wordNode::getNext() { return next; }
void wordNode::setNext(wordNode* n) { next = n; }

// Реализация методов класса wordList
wordList::wordList() : head(nullptr), lastNode(nullptr) {}

char wordList::getLastChar(const string& word) const {
    if (word.empty()) return '\0';
    char last = word.back();
    return (last == 'ь' && word.size() > 1) ? word[word.size() - 2] : last;
}

void wordList::wordAdd(const string& word) {
    wordNode* newNode = new wordNode(word);
    if (!head) {
        head = newNode;
        lastNode = newNode;
    }
    else {
        lastNode->setNext(newNode);
        lastNode = newNode;
    }
}

bool wordList::backtrack(vector<string>& remainingWords, wordNode* current) {
    if (remainingWords.empty()) {
        return getLastChar(lastNode->getWord()) == head->getWord()[0]; //проверяем замкнутость цепочки
    }

    char neededChar = getLastChar(current->getWord()); // последняя буква первого слова
    for (size_t i = 0; i < remainingWords.size(); i++) {
        if (remainingWords[i][0] == neededChar) { //если последняя и первая буква совпадают
            wordNode* saveLast = lastNode; //обновляем сохранение
            string usedWord = remainingWords[i]; //запоминаем слово
            wordAdd(usedWord); //добавляем в список
            remainingWords.erase(remainingWords.begin() + i); //удаляем из вектора слово

            if (backtrack(remainingWords, lastNode)) {
                return true;
            }
            //откат назад
            remainingWords.insert(remainingWords.begin() + i, usedWord);
            if (saveLast) {
                //удаляем последний узел
                saveLast->setNext(nullptr);
                delete lastNode;
                lastNode = saveLast;
            }
        }
    }
    return false;
}

bool wordList::bildChainWord(const string& str) {
    vector<string> words;
    string word;
    stringstream ss(str);
    clear();

    while (ss >> word) {
        words.push_back(word);
    }

    if (words.empty()) {
        return false;
    }

    for (size_t i = 0; i < words.size(); i++) {
        wordAdd(words[i]);
        vector<string> remainingWords = words;
        remainingWords.erase(remainingWords.begin() + i); // удаляем первое слово цепочки

        if (backtrack(remainingWords, head)) { // попытка составления слова
            return true;
        }

        clear();
    }
    return false;
}

void wordList::PrintChain() const {
    wordNode* node = head;
    while (node != nullptr) {
        cout << node->getWord() << " ";
        node = node->getNext();
    }
    cout << endl;
}

void wordList::SaveChainToFile(const string& filename) const {
    ofstream file(filename);
    if (file.is_open()) {
        wordNode* node = head;
        while (node != nullptr) {
            file << node->getWord() << " ";
            node = node->getNext();
        }
        file << endl;
        file.close();
        cout << "Цепочка успешно сохранена в файл " << filename << endl;
    }
    else {
        cout << "Ошибка при открытии файла для записи" << endl;
    }
}

void wordList::clear() {
    while (head) {
        wordNode* temp = head;
        head = head->getNext();
        delete temp;
    }
    lastNode = nullptr;
}

wordList::~wordList() {
    clear();
}