#include <iostream>
#include <cstdlib>
#include <fstream>
using namespace std;

int main()
{
    // Изменение кодировки кансоли
    system("chcp 1251>nul");
    // Изменяем цвет консоли и текста
    system("color 80");
    
    // Задержка консоли окна
    system("pause>nul");
    return 0;
}