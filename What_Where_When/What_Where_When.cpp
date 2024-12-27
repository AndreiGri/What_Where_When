#include <iostream>
#include <cstdlib>
#include <fstream>
#include <vector>
using namespace std;

int search_question(int s, vector<int>& vec)
{
	while (vec.size())
	{
		s = s % vec.size();
		for (int i = 0; i < vec.size(); i++)
		{
			if (vec[i] == s)
			{
				vec.erase(find(vec.begin(), vec.end(), s));
				return s;
			}
		}
		s++;
	}
}

void searchKakuelsh(string text, int d, vector<int>& vec)
{
	char ch;
	int c = 0;
	ifstream search;
	search.open(text, ios::binary);
	while (!search.eof())
	{
		search.get(ch);
		if ((c % d) == 0 && ch == '\n')
		{
			vec.push_back(search.tellg());
			++c;
		}
		else
		{
			if (ch == '\n')
			{
				++c;
			}
		}
	}
	search.close();
}

string reedOut(string text, int c, vector<int> vec)
{
	char buf[200];
	ifstream questionAnswer;
	questionAnswer.open(text, ios::binary);
	questionAnswer.seekg(vec[c]);
	questionAnswer.read(buf, sizeof(buf));
	buf[vec[c + 1] - vec[c]] = 0;
	questionAnswer.close();
	string str(buf);
	return str;
}

string answIn()
{
	string text;
	cout << " Скопируйте и вставьте ответ: ";
	cin >> text;
	return text + '\r' + '\n';
}

int main()
{
	system("chcp 1251>nul");                                                                                    // Изменение кодировки кансоли
	system("color 80");                                                                                         // Изменяем цвет консоли и текста
	vector<int> vec = { 1, 2, 3, 4, 5 };
	string text1 = "Answer.txt";
	string text2 = "Question.txt";
	int ask = 0;
	vector<int>answ;
	vector<int>ques;
	searchKakuelsh(text1, 1, answ);
	searchKakuelsh(text2, 4, ques);
	
	for (int i = 0; i < answ.size(); i++)
	{
		cout << answ[i] << ' ';
	}
	cout << endl;
	for (int i = 0; i < ques.size(); i++)
	{
		cout << ques[i] << ' ';
	}
	cout << endl;
	cout << " Введите номер вопроса: ";
	cin >> ask;
	ask = search_question(ask, vec);
	string a = reedOut(text1, ask - 1, answ);
	cout << a;
	cout << reedOut(text2, ask - 1, ques);
	
	string b = answIn();
	
	if (a.compare(b) == 0)
	{
		cout << " Верно! " << endl;
	}
	else
	{
		cout << " Не верно! " << endl;
	}
	// Задержка консоли окна
	system("pause>nul");
	return 0;
}