﻿#include <iostream>
#include <cstdlib>
#include <fstream>
#include <vector>
using namespace std;

void searchQuestion(int& l, int s, vector<bool>& vec)                                   // Метод для поиска вопроса который ещё не был задан
{
	s = ((s + l) % vec.size());                                                         // Устраняем варианты не входящие в диапазон вектора vec
	while (vec[s] == false)                                                             // Пока выбранный элемент вектора vec имеет значение false
	{
		s++;                                                                            // переходим к следующему элементу вектора                                                     
		s = (s % vec.size());                                                           // если значение s превышает диапазон элементов вектора
	}                                                                                   // округляем это значение на величину вектора
	vec[s] = false;                                                                     // После нахождения очередного элемента со значением true
	l = s;                                                                              // присваиваем ему значение false и значение переменной s
}                                                                                       // сохраняем в переменной l для использования вдальнейшем

void searchKakuelsh(string text, vector<int>& vec, int d = 1)                           // Метод для нахождения контрольных точек в файле
{
	char ch;                                                                            // Переменная для записи значений из потока
	int c = 0;                                                                          // Счётчик контрольных точек
	ifstream search;                                                                    // Объявляем поток
	search.open(text, ios::binary);                                                     // Открываем поток
	while (!search.eof())                                                               // Цикл пока не конец потока
	{
		search.get(ch);                                                                 // Считываем элементы потока 
		if ((c % d) == 0 && ch == 0xA)                                                  // Если остаток деления счётчика c на переменную d равен 0
		{                                                                               // и считанный элемент является переносом строки
			vec.push_back(search.tellg());                                              // добавляем в вектор vec номер считанного элемента
			++c;                                                                        // увеличивае счётчик на 1
		}
		else                                                                            // иначе
		{
			if (ch == 0xA)                                                              // если считанный элемент является переносом строки
			{
				++c;                                                                    // увеличивае счётчик на 1
			}
		}
	}
	search.close();                                                                     // Закрываем поток
}

string reedOut(string text, int c, vector<int> vec)                                     // Метод для считывания текста из файла
{
	char buf[200];                                                                      // Массив для записи текста
	ifstream questionAnswer;                                                            // Объявляем поток для чтения из файла
	questionAnswer.open(text, ios::binary);                                             // Открываем поток файла text
	questionAnswer.seekg(vec[c]);                                                       // В потоке находим точку начала чтения взятую из вектора
	questionAnswer.read(buf, sizeof(buf));                                              // Начинаем записывать в буфер из потока
	buf[vec[c + 1] - vec[c] - 2] = 0;                                                   // Определяем точку конца записи из потока
	questionAnswer.close();                                                             // Закрываем поток
	string str(buf);                                                                    // Преобразуем буфер в строку
	return str;                                                                         // Возвращаем строку
}

string answIn()                                                                         // Метод для ввода выбранного ответа
{
	string text;
	cout << " Скопируйте и вставьте верный ответ: ";
	cin >> text;
	return text;
}

int main()
{
	system("chcp 1251>nul");                                                            // Изменение кодировки кансоли
	system("color 80");                                                                 // Изменяем цвет консоли и текста
	int r = 0;                                                                          // Переменная для записи кол-ва правильных ответов
	int w = 0;                                                                          // Переменная для записи кол-ва неверных ответов
	string text1 = "Answer.txt";                                                        // Записываем в переменную адрес файла с ответами
	string text2 = "Question.txt";                                                      // Записываем в переменную адрес файла с вопросами
	ifstream ans(text1);
	if (!ans)                                                                           // Проверка возможности открытия файла "Answer.txt"
	{
		ans.close();
		cout << " Не удаётся открыть файл " << text1 << endl;                           // Если файл не откроется выводится сообщение и
		system("pause>nul");
		return 1;                                                                       // программа заканчивается возвращая ошибку 1
	}
	else
	{
		ifstream quest(text2);
		if (!quest)                                                                     // Проверка возможности открытия файла "Question.txt"
		{
			quest.close();
			cout << " Не удаётся открыть файл " << text2 << endl;                       // Если файл не откроется выводится сообщение и
			system("pause>nul");
			return 1;                                                                   // программа заканчивается возвращая ошибку 1
		}
	}
	
	
	
	int ask = 0;                                                                        // Переменная записи значения смещения
	int lastNumber = 0;                                                                 // Переменная хранения последнего сектора 
	vector<int>answ;                                                                    // Вектор для записи контрольных точек в ответах
	vector<int>ques;                                                                    // Вектор для записи контрольных точек в вопросах
	searchKakuelsh(text1, answ);                                                        // Вызов метода для записи контрольных точек ответов
	searchKakuelsh(text2, ques, 4);                                                     // Вызов метода для записи контрольных точек вопросов
	vector<bool>veccount;                                                               // Вектор для записи отвеченных вопросов
	for (int i = 0; i < ques.size() - 1; i++)                                           // Заполняем вектор значениями true относительно
	{                                                                                   // кол-ва вопросов
		veccount.push_back(true);
	}
	int count = veccount.size();                                                        // Переменная равная кол-ву вопросов
	while (count)                                                                       // Цикл до count == 0
	{
		cout << " Введите офсет относительно текущего сектора на барабане: ";           // Запрос офсета
		cin >> ask;                                                                     // запись значения офсета в переменную
		searchQuestion(lastNumber, ask, veccount);                                      // Вызов метода searchQuestion()
		cout << reedOut(text2, lastNumber, ques) << endl;                               // Выводим вопрос
		if (reedOut(text1, lastNumber, answ).compare(answIn()) == 0)                    // Сравниваем ответ из метода reedOut() и метода answIn()
		{
			cout << '\a';
			cout << " Верно! " << endl << endl;                                         // Выводим если ответы одинаковы
			r++;                                                                        // Инкркментируем переменную right
		}
		else                                                                            // Иначе выводим второй ответ
		{
			cout << '\a';
			cout << " Не верно! Правильный ответ: " 
				<< reedOut(text1, lastNumber, answ) << endl << endl;
			w++;                                                                        // Инкркментируем переменную wrong
		}
		count--;                                                                        // Декрементируем счётчик итераций
	}

	cout << " Верных ответов: " << r << endl;                                           // Выводим кол-во правильных ответов
	cout << " Неверных ответов: " << w << endl;                                         // Выводим кол-во не верных ответов

	system("pause>nul");                                                                // Задержка консоли окна
	return 0;
}