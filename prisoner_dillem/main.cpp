#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include "algorithms.hpp"

using namespace std;

// Подсчет очков по правилам
pair<int, int> get_scores(bool a, bool b) {
    if (a && b) return {24, 24};
    if (!a && !b) return {4, 4};
    if (a && !b) return {0, 20};
    if (!a && b) return {20, 0};
    return {0, 0}; 
}

// Функция для запуска игры между двумя алгоритмами
int play_game(
    bool (*algoA)(int32_t, vector<bool>&, vector<bool>&),
    bool (*algoB)(int32_t, vector<bool>&, vector<bool>&),
    string nameA, string nameB
) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(100, 200);
    int rounds = dist(gen);

    vector<bool> choicesA, choicesB;
    int scoreA = 0, scoreB = 0;

    for (int round = 0; round < rounds; ++round) {
        bool moveA = algoA(round, choicesA, choicesB);
        bool moveB = algoB(round, choicesB, choicesA);
        choicesA.push_back(moveA);
        choicesB.push_back(moveB);

        auto [pointsA, pointsB] = get_scores(moveA, moveB);
        scoreA += pointsA;
        scoreB += pointsB;
    }

    cout << "Game: " << nameA << " vs " << nameB << " | Rounds: " << rounds << endl;
    cout << nameA << " score: " << scoreA << endl;
    cout << nameB << " score: " << scoreB << endl;
    cout << "-----------------------------" << endl;

    // Возвращаем оба счета для определения победителя
    return scoreA > scoreB ? 1 : (scoreA < scoreB ? 2 : 0); // 1 - A победил, 2 - B победил, 0 - ничья
}

int main() {
    //Турнирная сетка: полуфиналы и финал
    //Полуфинал 1: Algo1 vs Algo2
    int winner1 = play_game(Algo2, Algo3, "Algo1", "Algo2");

    // Полуфинал 2: победитель полуфинала 1 vs Algo3
    if (winner1 == 1) {
        int final_winner = play_game(Algo2, Algo3, "Algo1", "Algo3");
        cout << "Финал: ";
        if (final_winner == 1) cout << "Algo2 победил!" << endl;
        else if (final_winner == 2) cout << "Algo3 победил!" << endl;
        else cout << "Ничья в финале!" << endl;
    } else if (winner1 == 2) {
        int final_winner = play_game(Algo2, Algo3, "Algo2", "Algo3");
        cout << "Финал: ";
        if (final_winner == 1) cout << "Algo2 победил!" << endl;
        else if (final_winner == 2) cout << "Algo3 победил!" << endl;
        else cout << "Ничья в финале!" << endl;
    } else {
        // Если ничья в первом полуфинале, оба проходят в финал
        int final_winner1 = play_game(Algo1, Algo3, "Algo1", "Algo3");
        int final_winner2 = play_game(Algo2, Algo3, "Algo2", "Algo3");
        cout << "Финал 1: ";
        if (final_winner1 == 1) cout << "Algo1 победил!" << endl;
        else if (final_winner1 == 2) cout << "Algo3 победил!" << endl;
        else cout << "Ничья!" << endl;
        cout << "Финал 2: ";
        if (final_winner2 == 1) cout << "Algo2 победил!" << endl;
        else if (final_winner2 == 2) cout << "Algo3 победил!" << endl;
        else cout << "Ничья!" << endl;
    }


    return 0;
}