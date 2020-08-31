#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>

using namespace std;

const int maxn = 1e5 + 5, logn = 20, INF = 1e8;
struct Graph {
    struct Edge {
        int v, nex;
        Edge(int v=0, int nex=0) : v(v), nex(nex) {}
    } E[maxn << 1];
    int tchk[maxn], hd[maxn], ti, tote;
    
    void addedge(int u, int v) {
        if (tchk[u] != ti) tchk[u] = ti, hd[u] = 0;
        if (tchk[v] != ti) tchk[v] = ti, hd[v] = 0;
        E[++tote] = Edge(v, hd[u]), hd[u] = tote;
        E[++tote] = Edge(u, hd[v]), hd[v] = tote;
    }
    void destroy() { tote = 0, ti++; }
} G, vG;
int knd[maxn], knd_sz, isknd[maxn];
int dep[maxn], dfn[maxn], grd[maxn][25], dfn_cnt;

void init(int u, int fa) {
    grd[u][0] = fa, dep[u] = dep[fa] + 1, dfn[u] = ++dfn_cnt;
    for (int i = 1; i <= logn; i++) grd[u][i] = grd[grd[u][i-1]][i-1];
    for (int i = G.hd[u]; i; i = G.E[i].nex) {
        int v = G.E[i].v;
        if (v == fa) continue;
        init(v, u);
    }
}

int get_lca(int u, int v) {
    if (dep[u] < dep[v]) swap(u, v);
    for (int i = logn; i >= 0; i--) if (dep[grd[u][i]] >= dep[v]) u = grd[u][i];
    if (u == v) return u;
    for (int i = logn; i >= 0; i--) if (grd[u][i] != grd[v][i])
        u = grd[u][i], v = grd[v][i];
    return grd[u][0];
}

int stk[maxn], stk_sz;
bool cmp(int a, int b) { return dfn[a] < dfn[b]; }
void build_vG() {
    sort(knd+1, knd+1+knd_sz, cmp), vG.destroy(), stk[stk_sz = 1] = 1;
    for (int i = 1; i <= knd_sz; i++) {
        if (knd[i] == 1) continue;
        int u = knd[i], v = stk[stk_sz], lca = get_lca(u, v);
        if (v == lca) stk[++stk_sz] = u;
        else {
            while (stk_sz > 1 && dep[stk[stk_sz-1]] >= dep[lca])
                vG.addedge(stk[stk_sz-1], stk[stk_sz]), stk_sz--;
            if (stk[stk_sz] != lca) 
                vG.addedge(lca, stk[stk_sz]), stk[stk_sz] = lca;
            stk[++stk_sz] = u;
        }
    }
    for (int i = 1; i < stk_sz; i++) vG.addedge(stk[i], stk[i+1]);
}

long long f[maxn][2];
void calc_f(int u, int fa) {
    if (isknd[u]) {
        f[u][0] = INF, f[u][1] = 0;
        for (int i = vG.hd[u]; i; i = vG.E[i].nex) {
            int v = vG.E[i].v;
            if (v == fa) continue;
            calc_f(v, u), f[u][1] += f[v][0];
        }
    } else {
        f[u][0] = 0, f[u][1] = INF;
        long long gu0 = 1;
        for (int i = vG.hd[u]; i; i = vG.E[i].nex) {
            int v = vG.E[i].v;
            if (v == fa) continue;
            calc_f(v, u);
            f[u][1] = min(f[u][0] + f[v][1], f[u][1] + f[v][0]);
            f[u][0] += f[v][0], gu0 += min(f[v][1], f[v][0]);
            
        }
        f[u][0] = min(f[u][0], gu0);
    }
    if (dep[u] - dep[fa] > 1) f[u][0] = min(f[u][0], f[u][1] + 1);
    // printf("f[%d] = {%d,%d}\n", u, f[u][0], f[u][1]);
}

void solve() {
    for (int i = 1; i <= knd_sz; i++) isknd[knd[i]] = 0;
    scanf("%d", &knd_sz);
    for (int i = 1; i <= knd_sz; i++) scanf("%d", &knd[i]), isknd[knd[i]] = 1;
    build_vG();
    calc_f(1, 0);
    long long ans = min(f[1][0], f[1][1]);
    if (ans >= INF) printf("-1\n");
    else printf("%lld\n", ans);
}

int main() {
    // freopen("test.in", "r", stdin);
    // freopen("test.out", "w", stdout);
    int n; scanf("%d", &n);
    for (int i = 1; i < n; i++) {
        int u, v; scanf("%d%d", &u, &v);
        G.addedge(u, v);
    }
    init(1, 0);
    int T; scanf("%d", &T);
    while (T--) solve();
    return 0;
}