#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>

using namespace std;

const int maxm = 15, maxn = 1e5 + 5;

struct Edge {
    int v, nex;
    Edge(int v = 0, int nex = 0) 
        : v(v), nex(nex) {}
} E[maxn << 2];
int tote, hd[maxn];

void addedge(int u, int v) {
    E[++tote] = Edge(v, hd[u]), hd[u] = tote;
}
int m, n, q, cnt, t[maxn], f[maxn][2], val[maxm][maxn];

int find_ans(int u, int a) {
    if (u <= m) return val[u][a];
    int ans = find_ans(f[u][0], a);
    if (f[u][0] != f[u][1]) {
        if (t[u] == 1) ans = max(ans, find_ans(f[u][1], a));
        else ans = min(ans, find_ans(f[u][1], a));
    }
    return ans;
}

int main() {
    freopen("compose.in", "r", stdin);
    freopen("compose.out", "w", stdout);
    // freopen("test.in", "r", stdin);
    // freopen("test.out", "w", stdout);
    scanf("%d%d%d", &m, &n, &q);
    for (int i = 1; i <= m; i++) 
        for (int j = 1; j <= n; j++)
            scanf("%d", &val[i][j]);
    cnt = m;
    for (int i = 1; i <= q; i++) {
        int ty, x, y; scanf("%d%d%d", &ty, &x, &y);
        if (ty == 1) {
            ++cnt, t[cnt] = 1;
            f[cnt][0] = x, f[cnt][1] = y;
        } else if (ty == 2) {
            ++cnt, t[cnt] = 2;
            f[cnt][0] = x, f[cnt][1] = y;
        } else printf("%d\n", find_ans(x, y));
    }
    return 0;
}