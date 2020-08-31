#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <string>
#include <cmath>
#define LL long long

using namespace std;

const int maxn = 1e5 + 5;
const LL INF = 1e17;

struct Edge {
    int v, nex;
    Edge(int v = 0, int nex = 0) : v(v), nex(nex) {}
} E[maxn << 1];
int hd[maxn], tote;
void addedge(int u, int v) {
    E[++tote] = Edge(v, hd[u]), hd[u] = tote;
    E[++tote] = Edge(u, hd[v]), hd[v] = tote;
}

int dep[maxn], grd[maxn][21];
LL w[maxn], f[maxn][2], f2[maxn][2], g[maxn][21][2][2];

void calc_f(int u, int fa) {
    f[u][0] = 0, f[u][1] = w[u];
    for (int i = hd[u]; i; i = E[i].nex) {
        int v = E[i].v;
        if (v == fa) continue;
        dep[v] = dep[u] + 1;
        calc_f(v, u);
        f[u][0] += f[v][1], f[u][1] += min(f[v][0], f[v][1]);
    }
}

void calc_f2(int u, int fa) {
    for (int i = hd[u]; i; i = E[i].nex) {
        int v = E[i].v;
        if (v == fa) continue;
        f2[v][0] = f2[u][1] + f[u][1] - min(f[v][0], f[v][1]);
        f2[v][1] = min(f2[u][1] + f[u][1] - min(f[v][0], f[v][1]), f2[u][0] + f[u][0] - f[v][1]);
        calc_f2(v, u);
    }
}

void calc_g(int u, int fa) {
    grd[u][0] = fa;
    g[u][0][0][0] = INF;
    g[u][0][0][1] = f[fa][0] - f[u][1];
    g[u][0][1][0] = f[fa][1] - min(f[u][0], f[u][1]);
    g[u][0][1][1] = f[fa][1] - min(f[u][0], f[u][1]);
    for (int i = 1; i <= 19; i++) {
        for (int k1 = 0; k1 < 2; k1++)
            for (int k2 = 0; k2 < 2; k2++)
                g[u][i][k1][k2] = INF;
        grd[u][i] = grd[grd[u][i-1]][i-1];
        for (int k1 = 0; k1 < 2; k1++)
            for (int k2 = 0; k2 < 2; k2++)
                for (int k3 = 0; k3 < 2; k3++)
                    g[u][i][k1][k2] = min(g[u][i][k1][k2],
                        g[u][i-1][k3][k2] + g[grd[u][i-1]][i-1][k1][k3]);
    }
    for (int i = hd[u]; i; i = E[i].nex) {
        int v = E[i].v;
        if (v == fa) continue;
        calc_g(v, u);
    }
}

LL hx[2], hy[2], thx[2], thy[2];

LL solve(int x, int a, int y, int b) {
    if (dep[x] < dep[y]) swap(x, y), swap(a, b);
    hx[a] = f[x][a], hy[b] = f[y][b], hx[a ^ 1] = INF, hy[b ^ 1] = INF;
    for (int i = 19; i >= 0; i--) {
        if (dep[grd[x][i]] >= dep[y]) {
            thx[0] = thx[1] = INF;
            for (int k1 = 0; k1 < 2; k1++)
                thx[0] = min(thx[0], hx[k1] + g[x][i][0][k1]),
                thx[1] = min(thx[1], hx[k1] + g[x][i][1][k1]);
            x = grd[x][i];
            hx[0] = thx[0], hx[1] = thx[1];
        }
    }
    if (x == y) return f2[x][b] + hx[b];
    for (int i = 19; i >= 0; i--) {
        thx[0] = thx[1] = thy[0] = thy[1] = INF;
        if (grd[x][i] != grd[y][i]) {
            for (int k1 = 0; k1 < 2; k1++)
                thx[0] = min(thx[0], hx[k1] + g[x][i][0][k1]),
                thx[1] = min(thx[1], hx[k1] + g[x][i][1][k1]),
                thy[0] = min(thy[0], hy[k1] + g[y][i][0][k1]),
                thy[1] = min(thy[1], hy[k1] + g[y][i][1][k1]);
            hx[0] = thx[0], hx[1] = thx[1], hy[0] = thy[0], hy[1] = thy[1];
            x = grd[x][i], y = grd[y][i];
        }
    }
    int lca = grd[x][0];
    return min(
        f2[lca][0]+f[lca][0] - f[x][1] - f[y][1] + hx[1] + hy[1],
        f2[lca][1]+f[lca][1] - min(f[x][0],f[x][1]) - min(f[y][0],f[y][1]) + min(hx[0],hx[1]) + min(hy[0],hy[1]) 
    );
}

int main() {
    // freopen("test.in", "r", stdin);
    // freopen("test.out", "w", stdout);
    int n, m; string type;
    cin >> n >> m >> type;
    for (int i = 1; i <= n; i++) scanf("%lld", &w[i]);
    for (int i = 1; i < n; i++) {
        int u, v; scanf("%d%d", &u, &v);
        addedge(u, v);
    }
    dep[1] = 1, calc_f(1, 0), calc_f2(1, 0), calc_g(1, 0);
    for (int i = 1; i <= m; i++) {
        int x, y, a, b;
        scanf("%d%d%d%d", &x, &a, &y, &b);
        LL ans = solve(x, a, y, b);
        printf("%lld\n", (ans >= INF ? -1 : ans));
    }
    return 0;
}