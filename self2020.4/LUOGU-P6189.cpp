#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
#define LL long long

using namespace std;

const int maxn = 1e5 + 5, maxm = 325;

int n, m;
LL MOD, f[maxn], g[maxm][maxn], s[maxn];

void getf() {
    f[0] = 1;
    for (int i = 1; i < m; i++)
        for (int j = i; j <= n; j++)
            f[j] = (f[j] + f[j-i]) % MOD;
}

void getg() {
    g[0][0] = s[0] = 1;
    for (int i = 1; i <= m; i++)
        for (int j = m; j <= n; j++)
            g[i][j] = (g[i-1][j-m] + g[i][j-i]) % MOD,
            s[j] = (s[j] + g[i][j]) % MOD;
}
int main() {
    freopen("test.in", "r", stdin);
    freopen("test.out", "w", stdout);
    scanf("%d%lld", &n, &MOD);
    m = sqrt(n), getf(), getg();
    LL ans = 0;
    for (int i = 0; i <= n; i++)
        ans = (ans + s[i] * f[n - i] % MOD) % MOD;
    printf("%lld\n", ans);
    return 0;
}