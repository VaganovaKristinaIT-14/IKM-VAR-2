
#include <string>
#include <vector>

using namespace std;

extern string alphabet; // ���������� ������� ����������

// �������� ������ �� ������������
bool validateString(const string& input);

// ��������� ������ ��� ����� � ����������(+�������� �� ����)
string getString(const char* prompt);

// ����� ���� ������
class wordNode {
private:
    string word;
    wordNode* next;
public:
    wordNode(const string& w);
    const string& getWord() const;
    void setWord(const string& w);
    wordNode* getNext();
    void setNext(wordNode* n);
};

// ����� ��������� ������
class wordList {
private:
    wordNode* head;
    wordNode* lastNode;

    // ��������� ��������� ����� 
    char getLastChar(const string& word) const;

public:
    wordList();
    ~wordList();

    // ���������� ���� � ������
    void wordAdd(const string& word);

    // ������� ���������� ������� � �������� ������ ������
    bool backtrack(vector<string>& remainingWords, wordNode* current);

    // ������� ���� ��������� ������ ���� � ���������� �������
    bool bildChainWord(const string& str);

    // ����� ������
    void PrintChain() const;

    // ���������� ������ � ����
    void SaveChainToFile(const string& filename) const;

    // �������
    void clear();
};


