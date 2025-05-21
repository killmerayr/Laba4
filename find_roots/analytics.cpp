#include <cmath>
#include <limits>
#include <functional>
#include <stdexcept>
#include <vector>
#include <algorithm>

using namespace std;
// x^2 + e^x = 2
const double eps = 1e-6;
 
// === Отделение корней === //
bool IsExist(double start, double end){
    auto f = [](double x) {
        return x * x + exp(x) - 2;
    };
    return f(start) * f(end) < 0;
}

double Func(double x){
    return pow(x, 2) + exp(x) - 2;
}
double Func_pr(double x){
    return 2 * x + exp(x);
}
double Func_pr2(double x){
    return 2 + exp(x);
}

double Fi1(double x){
    return log(2 - pow(x, 2));
}
double Fi1_pr(double x){
    return -2 * x / (2 - x * x);
}

double Fi2(double x){
    return sqrt(2 - exp(x));
}
double Fi2_pr(double x){
    return -exp(x) / (2 * sqrt(2 - exp(x)));
}

bool OneRoot(double start, double end, double step = 0.01){
    if (!IsExist(start, end)) return false;

    vector<double> signs;
    double x = 0;

    for (double x = start; x <= end; x += step){
        signs.push_back(Func_pr(x));
    }
    
    int count_positive = 0, count_negative = 0;
    for (const auto& sg : signs){
        if (sg > 0) count_positive += 1;
        if (sg < 0) count_negative += 1;
    }

    if (count_positive == signs.size() || count_negative == signs.size()){
        return true;
    }
    
    return false;
}

bool ThRollya(double start, double end){
    if (Func(start) == Func(end)) {
        return true;
    }
    return false;
}

// === Метод половинного деления === //

pair<double, int> Half_div(double a, double b, double eps){
    int k = 0;

    if (Func(a) * Func(b) >= 0){ 
        throw runtime_error("Возможно, функция не меняет знака");
    }

    while ((b - a) > eps){
        double c = (a + b) / 2;
        if (Func(a) * Func(c) < 0){
            b = c;
        }
        else {
            a = c;
        }
        k++;
    }
    return make_pair(((a + b) / 2), k);
}

// === Метод Ньютона === //
pair<double, int> Newtone(double x, double eps, int max_iter){
    int k = 0;
    if (Func(x) * Func_pr2(x) > 0){
        while (abs(Func(x)) > eps && k < max_iter){
            x = x - Func(x) / Func_pr(x);
            k ++;
        }
    }
    else{
        throw runtime_error("Неверно заданное приближение");
    }
    return make_pair(x, k);
}

// === Метод простых итераций === //
double MaxDerivative(const function<double(double)>& f_pr, double a, double b, double step) {
    double maxVal = 0.0;
    for (double x = a; x <= b; x += step) {
        double val = fabs(f_pr(x));
        if (isnan(val) || isinf(val)) return numeric_limits<double>::infinity();
        maxVal = max(maxVal, val);
    }
    return maxVal;
}

// Вспомогательная функция для округления до тысячных
double round3(double x) {
    return std::round(x * 1000.0) / 1000.0;
}

// Метод простых итераций
struct IterationResult {
    double root;
    int iterations;
    std::vector<double> values;
};

IterationResult SimpleIteration(double x0, double eps, int max_iter, double a, double b, double q, double step) {
    using func = function<double(double)>;

    // Кандидаты для phi-функций
    vector<pair<func, func>> phi_candidates = {
        {Fi1, Fi1_pr},
        {Fi2, Fi2_pr}
    };

    func chosen_phi = nullptr;
    double min_max = numeric_limits<double>::infinity();

    // Выбор phi-функции с минимальным max |phi'| < q
    for (const auto& [phi, phi_pr] : phi_candidates) {
        double max_der = MaxDerivative(phi_pr, a, b, step);
        if (max_der < q && max_der < min_max) {
            min_max = max_der;
            chosen_phi = phi;
        }
    }

    if (!chosen_phi) throw runtime_error("Нет подходящей fi-функции: условие сходимости не выполняется");

    int k = 0;
    double x1 = x0;
    std::vector<double> values = {x0};
    while (k < max_iter) {
        x1 = chosen_phi(x0);
        if (isnan(x1) || isinf(x1)) {
            throw runtime_error("Итерация ушла в область неопределенности!");
        }
        values.push_back(x1);
        if (fabs(x1 - x0) <= eps) break;
        x0 = x1;
        k++;
    }
    return {round3(x1), k, values};
}