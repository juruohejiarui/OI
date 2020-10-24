#include <iostream>
#include <cstring>
#include <cstdio>
#include <string>
#include <cmath>

using namespace std;

const int maxn = 1e6 + 5;

int n, m, grd[maxn][21], dep[maxn], fail[maxn];
char str[maxn];

int getlca(int u, int v) {
    if (dep[u] < dep[v]) swap(u, v);
    for (int i = 19; i >= 0; i--)
        if (dep[grd[u][i]] >= dep[v]) u = grd[u][i];
    if (u == v) return grd[u][0];
    for (int i = 19; i >= 0; i--)
        if (grd[u][i] != grd[v][i])
            u = grd[u][i], v = grd[v][i];
    return grd[u][0];
}

int main() {
    // freopen("test.in", "r", stdin);
    // freopen("test.out", "w", stdout);
    scanf("%s%d", str + 1, &m), n = strlen(str + 1);
    fail[1] = 0, dep[1] = 1;
    for (int i = 2, j = 0; i <= n; i++) {
        while (str[i] != str[j + 1] && j) j = fail[j];
        if (str[i] == str[j + 1]) j++;
        fail[i] = j, grd[i][0] = j;
        // cout << fail[i] << ' ';
        dep[i] = dep[j] + 1;
        for (int k = 1; k < 20; k++) grd[i][k] = grd[grd[i][k - 1]][k - 1];
    }
    for (int i = 1; i <= m; i++) {
        int u, v; scanf("%d%d", &u, &v);
        printf("%d\n", getlca(u, v));
    }
    return 0;
}