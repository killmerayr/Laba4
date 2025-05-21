#include <iostream>
#include <vector>

using namespace std;

vector<long long> bbs_generate(int count, long long p, long long q, long long seed) {
    long long M = p * q;
    long long x = (seed * seed) % M;
    vector<long long> sequence;
    sequence.push_back(x);

    for (int i = 1; i < count; ++i) {
        x = (x * x) % M;
        sequence.push_back(x);
    }

    return sequence;
}

long long mod_pow(long long base, long long st, long long mod) {
    long long result = 1;
    base %= mod;
    while (st > 0) {
        if (st % 2)
            result = (result * base) % mod;
        base = (base * base) % mod;
        st /= 2;
    }
    return result;
}