#include <iostream>
#include <cstdlib>
#include <fstream>
#include <vector>
using namespace std;

void searchQuestion(int& s, vector<bool>& vec)
{
	s = (s % vec.size());
	while (vec[s] == false)
	{
		s++;
		s = (s % vec.size());
	}
	vec[s] = false;
}

void scrolling(int& a, vector<bool>vec)
{
	a = (a % vec.size());
}

void searchKakuelsh(string text, vector<int>& vec, int d = 1)
{
	char ch;
	int c = 0;
	ifstream search;
	search.open(text, ios::binary);
	while (!search.eof())
	{
		search.get(ch);
		if ((c % d) == 0 && ch == 0xA)
		{
			vec.push_back(search.tellg());
			++c;
		}
		else
		{
			if (ch == 0xA)
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
	buf[vec[c + 1] - vec[c] - 2] = 0;
	questionAnswer.close();
	string str(buf);
	return str;
}

string answIn()
{
	string text;
	cout << " Скопируйте и вставьте верный ответ: ";
	cin >> text;
	return text;
}

int main()
{
	system("chcp 1251>nul");                                                                // Изменение кодировки кансоли
	system("color 80");                                                                     // Изменяем цвет консоли и текста
	int r = 0;                                                                              // Переменная для записи кол-ва правильных ответов
	int w = 0;                                                                              // Переменная для записи кол-ва неверных ответов
	int count = 0;                                                                          // Переменная для записи текущего значения
	int as = 0;
	vector<bool>veccount = { true,true,true,true,true };
	int c = veccount.size();
	string text1 = "Answer.txt";
	string text2 = "Question.txt";
	int ask = 0;                                                                         // Переменная записи значения смещения
	int e = 0;                                                                           // Переменная хранения последнего сектора 
	vector<int>answ;                                                                     // Вектор для записи контрольных точек в ответах
	vector<int>ques;                                                                     // Вектор для записи контрольных точек в вопросах
	searchKakuelsh(text1, answ);                                                         // Вызов метода для записи контрольных точек ответов
	searchKakuelsh(text2, ques, 4);                                                      // Вызов метода для записи контрольных точек вопросов
	
	while (c)
	{
		cout << " Введите офсет (смещение) относительно текущего сектора на барабане: ";
		cin >> ask;
		scrolling(ask, veccount);
		ask += e;
		searchQuestion(ask, veccount);
		e = ask;
		string a = reedOut(text1, ask, answ);
		cout << reedOut(text2, ask, ques) << endl;
		string b = answIn();
		if (a.compare(b) == 0)
		{
			cout << " Верно! " << endl << endl;
			r++;
		}
		else
		{
			cout << " Не верно! Правильный ответ: " << a << endl << endl;
			w++;
		}
		c--;
	}

	cout << " Верных ответов: " << r << endl;
	cout << " Неверных ответов: " << w << endl;

	
	system("pause>nul");                                                                 // Задержка консоли окна
	return 0;
}