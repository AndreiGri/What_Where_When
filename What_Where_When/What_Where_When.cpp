#include <iostream>
#include <cstdlib>
using namespace std;

int main()
{
    // Изменение кодировки кансоли
    system("chcp 1251>nul");
    // Изменяем цвет консоли и текста
    system("color 80");
    // Отображение соообщения в консоли
    cout << "Програмируем на С++!" << endl;
    // Задержка консоли окна
    system("pause>nul");
    return 0;
}