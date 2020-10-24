#include <iostream>
#include <cstring>
#include <vector>
#include <cstdio>
#include <cmath>
#define LL long long

using namespace std;

const int maxn = 1e6 + 5;
const LL MOD = 998244353;

int n; LL k[maxn], b[maxn];
vector<int> G[maxn];

LL qpow(LL a, LL b) {
    LL ret = 1;
    while (b) {
        if (b & 1) ret = ret * a % MOD;
        a = a * a % MOD, b >>= 1;
    }
    return ret;
}

int main() {
    // freopen("test.in", "r", stdin);
    // freopen("test.out", "w", stdout);
    int id, m;
    scanf("%d%d%d", &id, &n, &m);
    for (int i = 1; i <= m; i++) {
        int u, v; scanf("%d%d", &u, &v);
        G[u].push_back(v);
    }
    k[1] = 1, b[1] = 0;
    for (int i = 1; i <= n; i++) {
        k[i + 1] = (G[i].size() + 1) * k[i] % MOD;
        b[i + 1] = (G[i].size() + 1) * b[i] % MOD;
        b[i + 1] = (b[i + 1] - G[i].size()  - 1 + MOD) % MOD;
        for (int j = 0; j < G[i].size(); j++) {
            int v = G[i][j];
            k[i + 1] = (k[i + 1] - k[v] + MOD) % MOD;
            b[i + 1] = (b[i + 1] - b[v] + MOD) % MOD;
        }
    }
    printf("%lld\n", (MOD - b[n + 1]) % MOD * qpow(k[n + 1], MOD - 2) % MOD);
    return 0;
}