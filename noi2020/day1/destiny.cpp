#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
#define LL long long

using namespace std;

const int maxn = 5e5 + 5;
const LL MOD = 998244353;
struct Query {
    int u, v;
} q[maxn];
struct Graph {
    struct Edge {
        int v, nex;
        Edge(int v, int nex) : v(v), nex(nex) {}
    } E[maxn << 1];
    
    int hd[maxn], tchk[maxn]/*时间标记，懒人写法*/, tote, ti/*实际上表示这是第几次建立虚树*/;
    
    void addedge(int u, int v) {
        if (tchk[u] != ti) tchk[u] = ti, hd[u] = 0;
        if (tchk[v] != ti) tchk[v] = ti, hd[v] = 0;
        E[++tote] = Edge(v, hd[u]), hd[u] = tote;
        E[++tote] = Edge(u, hd[v]), hd[v] = tote;
    }
  	void destroy() { tote = 0, ti++; }
} G, vG;
int grd[maxn][31], dfn[maxn], dfn_cnt, dep[maxn], knd[maxn], knd_sz;

int stk[maxn], stk_sz;

void dfs1(int u, int fa) {
    grd[u][0] = fa, dfn[u] = ++dfn_cnt;
    for (int i = 1; i <= 30; i++) grd[u][i] = grd[grd[u][i-1]][i-1];
    for (int i = G.hd[u]; i; i = G.E[i].nex) {
        int v = G.E[i].v;
        if (v == fa) continue;
        dep[v] = dep[u] + 1, dfs1(v, u);
    }
}

int get_lca(int u, int v) {
    if (dep[u] < dep[v]) swap(u, v);
    for (int i = 30; i >= 0; i--) if (dep[grd[u][i]] <= dep[v])
        u = grd[u][i];
    if (v == u) return v;
    for (int i = 30; i >= 0; i--)
        if (grd[u][i] != grd[v][i]) u = grd[u][i], v = grd[v][i];
    return grd[u][0];
}
bool cmp(int a, int b) { return dfn[a] < dfn[b]; }
void build_vG() {
    sort(knd + 1, knd + 1 + knd_sz, cmp), vG.destroy(), stk[stk_sz = 1] = 1;
    for (int i = 1; i <= knd_sz; i++) {
        if (knd[i] == 1) continue;
        int u = knd[i], v = stk[stk_sz], lca = get_lca(u, v);
        if (lca == v) stk[++stk_sz] = u;
        else {
            while (stk_sz > 1 && dep[lca] <= dep[stk[stk_sz - 1]])
                vG.addedge(stk[stk_sz - 1], stk[stk_sz]), stk_sz--;
            if (lca != stk[stk_sz])
                vG.addedge(lca, stk[stk_sz]), stk[stk_sz] = lca;
            stk[++stk_sz] = u;
        }
    }
    for (int i = stk_sz - 1; i >= 1; i--) vG.addedge(stk[i], stk[i + 1]);
}

LL qpow(LL a, LL b) {
    LL ret = 1;
    while (b) {
        if (b & 1) ret = ret * a % MOD;
        a = a * a % MOD, b >>= 1;
    }
    return ret;
}
int main() {
    freopen("test.in", "r", stdin);
    freopen("test.out", "w", stdout);
    int n, m; scanf("%d%d", &n, &m);
    for (int i = 1; i < n; i++) {
        int u, v; scanf("%d%d", &u, &v);
        G.addedge(u, v);
    }
    dep[1] = 1, dfs1(1, 0);
    for (int i = 1; i <= m; i++) {
        scanf("%d%d", &q[i].u, &q[i].v);
        knd[++knd_sz] = q[i].u, knd[++knd_sz] = q[i].v;
    }
    sort(knd + 1, knd + 1 + knd_sz);
    knd_sz = unique(knd + 1, knd + 1 + knd_sz) - knd - 1;
    build_vG();
    int vnd_sz = 0;
    for (int i = 1; i <= n; i++) if (vG.hd[i]) vnd_sz++; 
    for (int i = 1; i < (1 << (vnd_sz - 1)); i++) {
        
    }
    return 0;
}