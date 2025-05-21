#include <iostream>
#include <vector>
#include "commands.hpp"

using namespace std;


int main() {
    long long p = 19;
    long long q = 23;
    long long seed = 7;
    int count = 5;

    vector<long long> result = bbs_generate(count, p, q, seed);

    cout << "BBS sequence: ";
    for (long long x : result) {
        cout << x << " ";
    }
    cout << endl;

    return 0;
}