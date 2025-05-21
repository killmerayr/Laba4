#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>
#include "analytics.hpp"
#include <utility>

using namespace std;

// x^2 + e^x = 2

// Графическое отделение корней (поиск интервалов смены знака)
vector<pair<double, double>> SeparateRoots(double a, double b, double step) {
    vector<pair<double, double>> intervals;
    double prev = Func(a);
    double x_prev = a;
    for (double x = a + step; x <= b; x += step) {
        double curr = Func(x);
        if (prev * curr < 0) {
            intervals.emplace_back(x_prev, x);
        }
        prev = curr;
        x_prev = x;
    }
    return intervals;
}

std::pair<double, int> SimpleIteration(double x0, double eps, int max_iter, double l, double r, double lambda, double alpha);

int main() {
    double a = -2, b = 2, step = 0.01, eps = 1e-4; // ε = 10^-4
    int max_iter = 2000;

    // 1. Графическое отделение корней
    auto intervals = SeparateRoots(a, b, step);
    cout << "Интервалы смены знака (отделение корней):" << endl;
    for (const auto& [l, r] : intervals) {
        cout << "[" << fixed << setprecision(4) << l << ", " << r << "]" << endl;
    }
    cout << endl;

    // 2. Метод половинного деления 
    cout << "Метод половинного деления :" << endl;
    cout << setw(5) << "N" << setw(15) << "a_n" << setw(15) << "b_n" << setw(15) << "b_n - a_n" << setw(15) << "f(c)" << endl;
    for (const auto& [l, r] : intervals) {
        double left = l, right = r;
        int k = 0;
        while ((right - left) > eps) {
            double c = (left + right) / 2;
            double fc = Func(c);
            cout << setw(5) << k
                 << setw(15) << fixed << setprecision(4) << left
                 << setw(15) << fixed << setprecision(4) << right
                 << setw(15) << fixed << setprecision(4) << right - left
                 << setw(15) << fixed << setprecision(4) << fc << endl;
            if (Func(left) * fc < 0)
                right = c;
            else
                left = c;
            ++k;
        }
        cout << "Корень: " << fixed << setprecision(4) << (left + right) / 2 << " за " << k << " итераций\n\n";
    }

    // 3. Метод Ньютона и простых итераций
    cout << "Метод Ньютона:" << endl;
    cout << setw(5) << "N" << setw(20) << "x_n" << setw(20) << "x_n+1" << setw(20) << "|x_n+1 - x_n|" << setw(20) << "f(x_n+1)" << endl;
    for (const auto& [l, r] : intervals) {
        double x = (l + r) / 2;
        int k = 0;
        double x_next;
        do {
            x_next = x - Func(x) / Func_pr(x);
            cout << setw(5) << k
                 << setw(20) << fixed << setprecision(4) << x
                 << setw(20) << fixed << setprecision(4) << x_next
                 << setw(20) << fixed << setprecision(4) << fabs(x_next - x)
                 << setw(20) << fixed << setprecision(4) << Func(x_next) << endl;
            x = x_next;
            ++k;
        } while (fabs(Func(x)) > eps && k < max_iter);
        cout << "Корень: " << fixed << setprecision(4) << x << " за " << k << " итераций\n\n";
    }

    cout << "Метод простых итераций:" << endl;
    cout << setw(5) << "N" << setw(20) << "x_n" << setw(20) << "x_n+1" << setw(20) << "|x_n+1 - x_n|" << setw(20) << "f(x_n+1)" << endl;
    for (const auto& [l, r] : intervals) {
        double x0 = (l + r) / 2;
        try {
            auto [root, iters] = SimpleIteration(x0, eps, max_iter, l, r, 1.0, 0.01);
            double x = x0;
            for (int k = 0; k < iters; ++k) {
                double x_next = Fi1(x);
                if (isnan(x_next) || isinf(x_next)) {
                    cout << "Итерация ушла в область неопределенности!" << endl;
                    break;
                }
                cout << setw(5) << k
                     << setw(20) << fixed << setprecision(4) << x
                     << setw(20) << fixed << setprecision(4) << x_next
                     << setw(20) << fixed << setprecision(4) << fabs(x_next - x)
                     << setw(20) << fixed << setprecision(4) << Func(x_next) << endl;
                if (fabs(x_next - x) <= eps) break;
                x = x_next;
            }
            cout << "Корень: " << fixed << setprecision(4) << root << " за " << iters << " итераций\n\n";
        } catch (const exception& e) {
            cout << "Ошибка: " << e.what() << endl;
        }
    }

    // 4. Вывод всех корней
    cout << "Все найденные корни:" << endl;
    for (const auto& [l, r] : intervals) {
        double left = l, right = r;
        while ((right - left) > eps) {
            double c = (left + right) / 2;
            if (Func(left) * Func(c) < 0)
                right = c;
            else
                left = c;
        }
        cout << fixed << setprecision(4) << (left + right) / 2 << endl;
    }

    // 5. Сравнение скорости сходимости (по количеству итераций)
    // Вывод уже есть выше в таблицах

    return 0;
}

