// minstd_rand
#include <random>
#include <iostream>
#include <vector>
#include <cctype>
#include <algorithm>

using namespace std;

// Задание 1 
vector<int> GenerateArray1(int n) {
    vector<int> arr1;
    minstd_rand gen(random_device{}());
    uniform_int_distribution<int> dist(100, 900);

    while (arr1.size() < n) {
        int num = dist(gen);
        if (num % 2 == 0) {
            arr1.push_back(num);
        }
    }
    return arr1;
}

// Генерация массива 2 из n/2 чисел в диапазоне [2, 50]
vector<int> GenerateArray2(int n) {
    vector<int> arr2;
    minstd_rand gen(random_device{}());
    uniform_int_distribution<int> dist(2, 50);

    while (arr2.size() < n / 2) {
        arr2.push_back(dist(gen));
    }
    return arr2;
}


//задание 2 
pair<vector<int>, vector<int>> Select_num(vector<int>& even_num, vector<int>& div_num){
    int count = 0;
    vector<int> ev_on_not_ev;
    for (const auto& num : even_num){
        if (count % 2 != 0){
            ev_on_not_ev.push_back(num);
        }
        count += 1;
    }

    count = 0;
    vector<int> not_ev_on_ev;
    for (const auto& num : div_num){
        if (count % 2 == 0 && num % 2 != 0){
            not_ev_on_ev.push_back(num);
        }
        count += 1;
    }

    return make_pair(ev_on_not_ev, not_ev_on_ev);
}

// Задание 3

vector<int> Div_mass(vector<int>& even_num, vector<int>& div_num, int k) {
    vector<int> nums;
    random_device rd;
    minstd_rand gen(rd());

    // Проверяем, что массивы не пустые и k > 0
    if (even_num.empty() || div_num.empty() || k <= 0) {
        return nums;
    }

    while (nums.size() < k) {
        uniform_int_distribution<> dist1(0, even_num.size() - 1);
        uniform_int_distribution<> dist2(0, div_num.size() - 1);

        int a = even_num[dist1(gen)];
        int b = div_num[dist2(gen)];

        // Исключаем деление на ноль
        if (b == 0) continue;

        int elem = a / b;
        nums.push_back(elem);
    }
    return nums;
}

// Задание 4
vector<char> GenerateSmb(int k){ // 
    random_device rd;
    minstd_rand gen(rd());

    vector<char> symb;
    uniform_int_distribution<int> dist (32, 126);
    while(symb.size() < k){
        char symbol = static_cast<unsigned char>(dist(gen));
        symb.push_back(symbol);
    }

    return symb;
}

vector<char> Del_cap_let(vector<char>& symbols){
    vector<char> result;
    for (const auto& ch : symbols) {
        if (!isupper(static_cast<unsigned char>(ch))) {
            result.push_back(ch);
        }
    }
    return result;
}

// Задание 5
vector<int> GenerateAndFilterArray(int n) {
    vector<int> arr;
    minstd_rand gen(random_device{}());
    uniform_int_distribution<int> dist(0, 300);

    while (arr.size() <= n){
        arr.push_back(dist(gen));
    }

    sort(arr.begin(), arr.end());

    vector<int> filtered;
    for (int num : arr) {
        int digits[10] = {0};
        int tmp = num;
        while (tmp > 0) {
            digits[tmp % 10]++;
            tmp /= 10;
        }
        for (int d : digits) {
            if (d >= 2) {
                filtered.push_back(num);
                break;
            }
        }
    }
    return filtered;
}