#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>

using namespace std;

typedef vector<string> Ranking;

// Метод Борда
string borda_winner(const vector<Ranking>& votes, const vector<string>& candidates) {
    map<string, int> scores;
    int n = candidates.size();

    for (const auto& vote : votes) {
        for (int i = 0; i < n; ++i) {
            scores[vote[i]] += n - i - 1;
        }
    }

    string winner;
    int max_score = -1;

    for (const auto& [name, score] : scores) {
        if (score > max_score) {
            max_score = score;
            winner = name;
        }
    }

    return winner;
}

// Метод Кондорсе
string condorcet_winner(const vector<Ranking>& votes, const vector<string>& candidates) {
    int n = candidates.size();
    map<string, map<string, int>> pairwise_wins;

    // Подсчет побед в попарных сравнениях
    for (const auto& vote : votes) {
        for (const auto& cand1 : vote) {
            for (auto it2 = vote.begin(); it2 != vote.end(); ++it2) {
            if (*it2 == cand1) break;
            pairwise_wins[cand1][*it2]++;
            }
        }
    }

    for (const auto& cand1 : candidates) {
        bool wins_all = true;
        for (const auto& cand2 : candidates) {
            if (cand1 == cand2) continue;
            int c1_wins = pairwise_wins[cand1][cand2];
            int c2_wins = pairwise_wins[cand2][cand1];

            if (c1_wins <= c2_wins) {
                wins_all = false;
                break;
            }
        }
        if (wins_all) return cand1;
    }

    return "No Condorcet winner";
}

// Пример использования
int main() {
    vector<string> candidates = {"Petya", "Vasya", "Olya"};

    vector<Ranking> votes = {
        {"Vasya", "Olya", "Petya"},
        {"Olya", "Vasya", "Petya"},
        {"Vasya", "Petya", "Olya"},
        {"Olya", "Petya", "Vasya"},
        {"Vasya", "Olya", "Petya"}
    };

    string borda = borda_winner(votes, candidates);
    string condorcet = condorcet_winner(votes, candidates);

    cout << "Borda winner: " << borda << endl;
    cout << "Condorcet winner: " << condorcet << endl;

    if (borda != condorcet) {
        cout << "Методы дали разные результаты. Это возможно из-за различий в логике оценки." << endl;
    }

    return 0;
}
