#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
#define LL long long
#define FOR(i, j, k) for (int i = (j); i <= (k); i++)
#define ADD_M(a, b) ((a) = ((a) + (b)) % MOD)

using namespace std; 

const int maxn = 2e3 + 5;
const LL MOD = 998244353;
int n, a[maxn], cnt[maxn];
LL f[maxn][maxn], g[maxn][maxn], c[maxn][maxn];

int main() {
    // freopen("game.in", "r", stdin);
    // freopen("game.out", "w", stdout);
    freopen("test.in", "r", stdin);
    freopen("test.out", "w", stdout);
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]), cnt[a[i]]++;
    FOR (i, 0, maxn - 1) f[i][0] = g[i][0] = 1;
    FOR (i, 1, maxn - 1) FOR (j, 1, i)
        ADD_M(c[i][j], c[i-1][j] + c[i-1][j-1]);
    FOR (i, 1, n) for (int j = 1; j * i < maxn; j++)
        g[i][j] = c[i * j - 1][i - 1] * g[i][j - 1] % MOD;
    f[n + 1][0] = 1;
    for (int i = n + 1, s = 0; i >= 2; i--, s += cnt[i]) 
        FOR (j, 0, s) if (f[i][j]) {
            for (int k = 0; k * (i - 1) <= j + cnt[i - 1]; k++) {
                f[i-1][j+cnt[i-1]-k*(i-1)] += f[i][j] * c[j+cnt[i-1]][k*(i-1)] % MOD * g[i-1][k] % MOD;
                f[i-1][j+cnt[i-1]-k*(i-1)] %= MOD;
            }
        }
    printf("%lld\n", f[1][0]);
    return 0;
}