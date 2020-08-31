#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
#include <cmath>
#include <unordered_map>

using namespace std;

const int maxn = 1e8 + 5;
vector<int> vec, vec2;
unordered_map<int, int> m;
int main() {
    // freopen("test.out", "w", stdout);
    cout << time(NULL) << endl;
    for (int i = 1; i <= 1e6; i++) m[i] = i + 1;
    cout << time(NULL) << endl;
    m.clear();
    cout << time(NULL) << endl;
    return 0;
}