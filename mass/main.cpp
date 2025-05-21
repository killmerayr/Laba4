#include <iostream>
#include <vector>
#include "commands.hpp"

using namespace std;

int main() {
    int n = 10; // n должно быть четным
    int k = 12; // k >= 10

    // 1. Генерация массивов
    vector<int> arr1 = GenerateArray1(n);
    vector<int> arr2 = GenerateArray2(n);

    cout << "Массив 1: ";
    for (int x : arr1) cout << x << " ";
    cout << endl;

    cout << "Массив 2: ";
    for (int x : arr2) cout << x << " ";
    cout << endl;

    // 2. 
    auto [even_on_odd, odd_on_even] = Select_num(arr1, arr2);

    cout << "Четные элементы массива 1 на нечетных местах: ";
    for (int x : even_on_odd) cout << x << " ";
    cout << endl;

    cout << "Нечетные элементы массива 2 на четных местах: ";
    for (int x : odd_on_even) cout << x << " ";
    cout << endl;

    // 3. Массив из k чисел - результат целочисленного деления случайных элементов
    vector<int> div_arr = Div_mass(arr1, arr2, k);
    cout << "Массив целочисленного деления (k=" << k << "): ";
    for (int x : div_arr) cout << x << " ";
    cout << endl;

    // 4. Массив случайных символов и удаление заглавных букв
    vector<char> symbols = GenerateSmb(k);
    cout << "Массив символов: ";
    for (char c : symbols) cout << c << " ";
    cout << endl;

    vector<char> no_caps = Del_cap_let(symbols);
    cout << "Без заглавных букв: ";
    for (char c : no_caps) cout << c << " ";
    cout << endl;

    // 5. Массив из [0, 300], сортировка, фильтрация по повторяющимся цифрам
    vector<int> filtered = GenerateAndFilterArray(n);
    cout << "Массив с повторяющимися цифрами: ";
    for (int x : filtered) cout << x << " ";
    cout << endl;

    return 0;
}