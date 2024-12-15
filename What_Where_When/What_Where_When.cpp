#include <iostream>
#include <cstdlib>
#include <fstream>
#include <vector>
using namespace std;

int a = 0;
int b = 0;

void searchKakuelsh(vector<int>& vec, string text)
{
    char ch;
    int k = 0;
    

    ifstream search;
    search.open(text, ios::binary);

    while (search)
    {
        search.get(ch);
        if (search)
        {
            if (ch == '\n')
            {
                vec.push_back(search.tellg());
            }
        }
    }
    search.close();
}

string reedOut(int a, int b, string text, vector<int> vec)
{
    int c = vec[a];
    int d = vec[b];
    char ch;
    char buf[200];
    ifstream questionAnswer;
    questionAnswer.open(text, ios::binary);
    questionAnswer.seekg(c);
    questionAnswer.read(buf, sizeof buf);
    questionAnswer.close();
    buf[d] = 0;
    string str(buf);
    return str;
}

string answIn()
{
    string text;
    cout << " Введите ответ: ";
    cin >> text;
    return text;
}

int main()
{
    
    system("chcp 1251>nul");                                                                                    // Изменение кодировки кансоли
    system("color 80");                                                                                         // Изменяем цвет консоли и текста
    vector<int>answ(2);
    vector<int>quest(4);
    searchKakuelsh(answ, "Answers.txt");
    searchKakuelsh(quest, "Questions.txt");
    int n = 0;
    
    string reedOut(a, b, "Questions.txt", quest);
    string reedOut(a, b, "Answers.txt", answ);

    bool result{  };
    if (result)
    {
        cout << " Ответ верный!" << endl;
    }
    else
    {
        cout << " Ответ не верный!!!" << endl;
    }
    
    // Задержка консоли окна
    system("pause>nul");
    return 0;
}