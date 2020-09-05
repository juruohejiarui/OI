#include <iostream>
#include <cstring>
#include <cstdio>
#include <string>
#include <cmath>

using namespace std;

const int maxn = 105;
int n;
string str;
int main() {
    // freopen("test.in", "r", stdin);
    // freopen("test.out", "w", stdout);
    cin >> n >> str;
    bool is_succ = true;
    for (int i = 0; i < n; i++) 
        if (str[i] != str[n - i - 1]) is_succ = false;
    if (is_succ) printf("yes\n");
    else printf("no\n");
    return 0;
}