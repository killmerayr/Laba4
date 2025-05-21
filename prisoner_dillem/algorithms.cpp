// #include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Algo1: Всегда предает (остается для теста)
bool Algo1(int32_t round_number, vector<bool>& self_choices, vector<bool>& enemy_choices) {
    return false;
}

// Algo2: "Зеркальный" — начинает с сотрудничества, потом повторяет ход противника
bool Algo2(int32_t round_number, vector<bool>& self_choices, vector<bool>& enemy_choices) {
    if (round_number == 0) return true; // Первый ход — сотрудничество
    // Если противник предал в прошлом ходу — предаем, иначе сотрудничаем
    return enemy_choices[round_number - 1];
}

// Algo3: "Аналитик" — если противник часто предает, начинаем предавать
bool Algo3(int32_t round_number, vector<bool>& self_choices, vector<bool>& enemy_choices) {
    if (round_number < 3) return true; // Первые 3 хода — сотрудничаем

    int betray_count = count(enemy_choices.begin(), enemy_choices.end(), false);
    double betray_rate = static_cast<double>(betray_count) / round_number;

    if (betray_rate > 0.6) return false; // Если предательств больше 60% — предаем
    return true; // Иначе сотрудничаем
}