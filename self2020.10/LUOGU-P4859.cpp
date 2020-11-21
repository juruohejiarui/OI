#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
#define LL long long

using namespace std;

const int maxn = 2e3 + 5;
const LL MOD = 1e9 + 9;
int n, m, a[maxn], b[maxn], lim[maxn];

LL f[maxn][maxn], fac[maxn], ifac[maxn], inv[maxn];

void init() {
    fac[0] = ifac[0] = inv[1] = 1;
    for (int i = 1; i < maxn; i++) fac[i] = fac[i - 1] * i % MOD;
    for (int i = 2; i < maxn; i++) inv[i] = (MOD - MOD / i) * inv[MOD % i] % MOD;
    for (int i = 1; i < maxn; i++) ifac[i] = ifac[i - 1] * inv[i] % MOD;
}
LL qpow(LL a, LL b) {
    LL ret = 1;
    while (b) {
        if (b & 1) ret = ret * a % MOD;
        a = a * a % MOD, b >>= 1;
    }
    return ret;
}
inline LL C(int n, int m) { return fac[n] * ifac[m] % MOD * ifac[n - m] % MOD; }

int find_pre(int val) {
    int l = 1, r = n, ans = -1;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (b[mid] < val) ans = mid, l = mid + 1;
        else r = mid - 1;
    }
    return ans;
}
int main() {
    // freopen("test.in", "r", stdin);
    // freopen("test.out", "w", stdout);
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    for (int i = 1; i <= n; i++) scanf("%d", &b[i]);
    m = (n + m) / 2;
    sort(a + 1, a + 1 + n), sort(b + 1, b + 1 + n);
    for (int i = 1; i <= n; i++) lim[i] = find_pre(a[i]);
    init();
    f[0][0] = 1;
    for (int i = 1; i <= n; i++)
        for (int j = 0; j <= i; j++) {
            f[i][j] = f[i - 1][j];
            if (j && lim[i] != -1) 
                f[i][j] = (f[i][j] + f[i - 1][j - 1] * (lim[i] - (j - 1)) % MOD) % MOD;
        }
    
    LL ans = 0;
    for (int i = m; i <= n; i++) {
        LL val = f[n][i] * fac[n - i] % MOD * C(i, m) % MOD;
        if ((i - m) & 1) ans = (ans - val + MOD) % MOD;
        else ans = (ans + val) % MOD;
    }
    printf("%lld\n", ans);
    return 0;
}