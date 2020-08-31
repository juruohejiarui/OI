#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
#define LL long long

using namespace std;

const int maxn = 2e3 + 5;
const LL MOD = 998244353;
int a[maxn], n, mxl[maxn], len[maxn];
LL ans;
void dfs(int x, int cnt) {
    if (x > n) { ans = (ans + 1) % MOD; return ; }
    for (int i = 1; i <= cnt; i++) {
        if (mxl[i] <= len[i]) continue;
        len[i]++;
        dfs(x + 1, cnt);
        len[i]--;
    }
    mxl[cnt + 1] = a[x], len[cnt + 1] = 1;
    dfs(x + 1, cnt + 1);
}

int main() {
    freopen("game.in", "r", stdin);
    freopen("game.out", "w", stdout);
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    sort(a + 1, a + 1 + n);
    dfs(1, 0);
    printf("%lld\n", ans);
    return 0;
}