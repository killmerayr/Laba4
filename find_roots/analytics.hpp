#pragma once
#include <vector>
#include <utility>
#include <functional>

// Проверка существования корня на отрезке
bool IsExist(double start, double end);

// Основная функция и её производные
double Func(double x);
double Func_pr(double x);
double Func_pr2(double x);

// Функции для простых итераций и их производные
double Fi1(double x);
double Fi1_pr(double x);
double Fi2(double x);
double Fi2_pr(double x);

// Проверка единственности корня на отрезке
bool OneRoot(double start, double end, double step = 0.01);

// Теорема Ролля
bool ThRollya(double start, double end);

// Метод половинного деления (бисекции)
std::pair<double, int> Half_div(double a, double b, double eps);

// Метод Ньютона
std::pair<double, int> Newtone(double x, double eps, int max_iter);

// Максимальное значение производной на отрезке
double MaxDerivative(const std::function<double(double)>& f_pr, double a, double b, double step);

// Метод простых итераций с автоматическим выбором fi
std::pair<double, int> SimpleIterationAuto(double x0, double eps, int max_iter, double a, double b, double q, double step);