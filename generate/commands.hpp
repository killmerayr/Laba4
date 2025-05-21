#pragma once
#include <vector>

// Генерация последовательности BBS
std::vector<long long> bbs_generate(int count, long long p, long long q, long long seed);

// Быстрое возведение в степень по модулю
long long mod_pow(long long base, long long exp, long long mod);