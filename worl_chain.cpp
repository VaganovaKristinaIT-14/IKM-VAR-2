#include "Header.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <limits>

using namespace std;

string alphabet = "�������������������������������� ";

bool validateString(const string& input) {
    if (input.empty()) {
        cout << "������. � ������ ������ ���� ���� �� ���� �����" << endl;
        return false;
    }

    for (char c : input) {
        if (alphabet.find(c) == string::npos) {
            cout << "������ �����! ������ ������ ��������� ������ ������� �������� ����� � �������." << endl;
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

// ���������� ������� ������ wordNode
wordNode::wordNode(const string& w) : word(w), next(nullptr) {}

const string& wordNode::getWord() const { return word; }
void wordNode::setWord(const string& w) { word = w; }

wordNode* wordNode::getNext() { return next; }
void wordNode::setNext(wordNode* n) { next = n; }

// ���������� ������� ������ wordList
wordList::wordList() : head(nullptr), lastNode(nullptr) {}

char wordList::getLastChar(const string& word) const {
    if (word.empty()) return '\0';
    char last = word.back();
    return (last == '�' && word.size() > 1) ? word[word.size() - 2] : last;
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
        return getLastChar(lastNode->getWord()) == head->getWord()[0]; //��������� ����������� �������
    }

    char neededChar = getLastChar(current->getWord()); // ��������� ����� ������� �����
    for (size_t i = 0; i < remainingWords.size(); i++) {
        if (remainingWords[i][0] == neededChar) { //���� ��������� � ������ ����� ���������
            wordNode* saveLast = lastNode; //��������� ����������
            string usedWord = remainingWords[i]; //���������� �����
            wordAdd(usedWord); //��������� � ������
            remainingWords.erase(remainingWords.begin() + i); //������� �� ������� �����

            if (backtrack(remainingWords, lastNode)) {
                return true;
            }
            //����� �����
            remainingWords.insert(remainingWords.begin() + i, usedWord);
            if (saveLast) {
                //������� ��������� ����
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
        remainingWords.erase(remainingWords.begin() + i); // ������� ������ ����� �������

        if (backtrack(remainingWords, head)) { // ������� ����������� �����
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
        cout << "������� ������� ��������� � ���� " << filename << endl;
    }
    else {
        cout << "������ ��� �������� ����� ��� ������" << endl;
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