
#include <string>
#include <vector>

using namespace std;

extern string alphabet; // Объявление внешней переменной

// Проверка строки на корректность
bool validateString(const string& input);

// Получение строки при вводе с клавиатуры(+проверка на ввод)
string getString(const char* prompt);

// Класс узла списка
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

// Класс структуры списка
class wordList {
private:
    wordNode* head;
    wordNode* lastNode;

    // Получение последней буквы 
    char getLastChar(const string& word) const;

public:
    wordList();
    ~wordList();

    // Добавление узла в список
    void wordAdd(const string& word);

    // Перебор построения цепочки с заданным первым словом
    bool backtrack(vector<string>& remainingWords, wordNode* current);

    // Перебор всех возможных первых слов и построение цепочек
    bool bildChainWord(const string& str);

    // Вывод списка
    void PrintChain() const;

    // Сохранение списка в файл
    void SaveChainToFile(const string& filename) const;

    // Очистка
    void clear();
};


