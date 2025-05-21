#pragma once
#include <vector>
#include <utility>

// Задание 1
std::vector<int> GenerateArray1(int n);
std::vector<int> GenerateArray2(int n);

// Задание 2
std::pair<std::vector<int>, std::vector<int>> Select_num(std::vector<int>& even_num, std::vector<int>& div_num);

// Задание 3
std::vector<int> Div_mass(std::vector<int>& even_num, std::vector<int>& div_num, int k);

// Задание 4
std::vector<char> GenerateSmb(int k);
std::vector<char> Del_cap_let(std::vector<char>& symbols);

// Задание 5
std::vector<int> GenerateAndFilterArray(int n);