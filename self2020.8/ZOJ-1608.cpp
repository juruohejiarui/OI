#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
#define D double

using namespace std;

inline D squ(D a) { return a * a; }
D a, b, r1, r2;
void solve() {
    if (a > b) swap(a, b);
    if (r1 > r2) swap(r1, r2);
    if (a < r2 * 2) { printf("No\n"); return ; }
    if (squ(r1 + r2) <= squ(a - r1 - r2) + squ(b - r1 - r2)) 
        printf("Yes\n");
    else printf("No\n");
}

int main() {
    // freopen("test.in", "r", stdin);
    // freopen("test.out", "w", stdout);
    while (scanf("%lf%lf%lf%lf", &a, &b, &r1, &r2) != EOF) solve();
    return 0;
}