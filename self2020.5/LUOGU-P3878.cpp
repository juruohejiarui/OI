#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <ctime>
#define LL long long

using namespace std;

const int maxn = 1005;

LL ans, v1_sz, v2_sz, v1[maxn], v2[maxn], s1, s2;

void change(int x, int y) {
    s1 = s1 - v1[x] + v2[y], s2 = s2 - v2[y] + v1[x];
    swap(v1[x], v2[y]);
}

void SA() {
    for (double T = 5e3; T > 1e-14; T *= 0.996) {
        int a = rand() % v1_sz + 1, b = rand() % v2_sz + 1;
        change(a, b);
        LL t1 = llabs(s1 - s2);
        if (t1 < ans) ans = t1;
        else if (exp(ans - t1) * RAND_MAX)
    }
}

void solve() {
    int n; scanf("%d", &n);
    if (n == 1) {
        int t; scanf("%d", &t);
        printf("%d\n", t);
        return ;
    }
    s1 = s2 = 0, v1_sz = n / 2, v2_sz = n - v1_sz;
    for (int i = 1; i <= v1_sz; i++)
        scanf("%lld", &v1[i]), s1 += v1[i];
    for (int i = v1_sz + 1; i <= n; i++)
        scanf("%lld", &v2[i - v1_sz]), s2 += v2[i - v1_sz];
    ans = llabs(s1 - s2);
    int a = 80;
    while (a--) SA();
    printf("%lld\n", ans);
}
int main() {
    srand(time(NULL));
    // freopen("test.in", "r", stdin);
    // freopen("test.out", "w", stdout);
    int T; cin >> T;
    while (T--) solve();
    return 0;
}