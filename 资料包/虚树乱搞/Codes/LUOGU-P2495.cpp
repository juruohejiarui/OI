#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
#define LL long long

using namespace std;

const int maxn = 250005, maxm = 5e5 + 5;

int n, m, h[maxn], h_sz, is_knd[maxn];
LL f[maxn];

struct Graph {
    struct Edge {
        int v, nex; LL w;
        Edge() {}
        Edge(int v, LL w, int nex) : v(v), w(w), nex(nex) {}
    } E[maxn << 1];
    
    int hd[maxn], tchk[maxn], tote, ti;
    
    void addedge(int u, int v, int w) {
        if (tchk[u] != ti) tchk[u] = ti, hd[u] = 0;
        if (tchk[v] != ti) tchk[v] = ti, hd[v] = 0;
        f[u] = f[v] = -1;

        // printf("connect %d and %d\n", u, v);
        E[++tote] = Edge(v, w, hd[u]), hd[u] = tote;
        E[++tote] = Edge(u, w, hd[v]), hd[v] = tote;
    }
} G, vG;

//---------------------LCA, MINW---------------------
int log_n, dfn_cnt, minw[maxn][25], grd[maxn][25], dfn[maxn], dep[maxn];

void init(int u, int fa) {
    grd[u][0] = fa, dep[u] = dep[fa] + 1, dfn[u] = ++dfn_cnt;
    
    for (int i = 1; i <= 18; i++) {
        grd[u][i] = grd[grd[u][i-1]][i-1];
        minw[u][i] = min(minw[u][i-1], minw[grd[u][i-1]][i-1]);
    }

    for (int i = G.hd[u]; i; i = G.E[i].nex) {
        int v = G.E[i].v;
        if (v == fa) continue;
        minw[v][0] = G.E[i].w;
        init(v, u);
    }
}
int get_lca(int u, int v) {
    if (dep[u] < dep[v]) swap(u, v);
    for (int i = 18; i >= 0; i--) if (dep[grd[u][i]] >= dep[v]) u = grd[u][i];
    if (u == v) return u;
    for (int i = 18; i >= 0; i--) if (grd[u][i] != grd[v][i]) 
        u = grd[u][i], v = grd[v][i];
    return grd[u][0];
}

int get_minw(int u, int v) {
    int ret = 99999999;
    if (dep[u] < dep[v]) swap(u, v);
    for (int i = 18; i >= 0; i--)
        if (dep[grd[u][i]] >= dep[v]) 
            ret = min(ret, minw[u][i]), u = grd[u][i];
    if (u == v) return ret;
    for (int i = 18; i >= 0; i--) if (grd[u][i] != grd[v][i])
        ret = min(ret, min(minw[u][i], minw[v][i])),
        u = grd[u][i], v = grd[v][i];
    return ret;
}
//---------------------LCA, MINW---------------------

bool cmp(int a, int b) { return dfn[a] < dfn[b]; }

int stk[maxn], stk_sz;

void build_vG() {
    sort(h + 1, h + 1 + h_sz, cmp);
    vG.tote = 0, vG.ti++, stk[stk_sz = 1] = 1;

    for (int i = 1; i <= h_sz; i++) {
        if (h[i] == 1) continue;
        int u = h[i], v = stk[stk_sz], lca = get_lca(u, v);
        if (lca == v) stk[++stk_sz] = u;
        else {
            while (stk_sz > 1 && dep[lca] <= dep[stk[stk_sz - 1]])
                vG.addedge(stk[stk_sz - 1], stk[stk_sz], get_minw(stk[stk_sz - 1], stk[stk_sz])),
                stk_sz--;
            if (lca != stk[stk_sz]) {
                vG.addedge(lca, stk[stk_sz], get_minw(lca, stk[stk_sz]));
                stk[stk_sz] = lca;
            }
            stk[++stk_sz] = u;
        }
    }
    for (int i = stk_sz - 1; i >= 1; i--) 
        vG.addedge(stk[i], stk[i + 1], get_minw(stk[i], stk[i + 1]));
}

void calc_f(int u, int fat) {
    f[u] = 0;
    for (int i = vG.hd[u]; i; i = vG.E[i].nex) {
        int v = vG.E[i].v;
        if (v == fat) continue;
        calc_f(v, u);
        if (is_knd[v]) f[u] += vG.E[i].w;
        else f[u] += min(vG.E[i].w, f[v]);
    }
}

int main() {
    // freopen("test.in", "r", stdin);
    // freopen("test.out", "w", stdout);
    scanf("%d", &n);
    for (int i = 1; i < n; i++) {
        int u, v, w; scanf("%d%d%d", &u, &v, &w);
        G.addedge(u, v, w);
    }
    scanf("%d", &m);
    
    // cout << "-----\n";
    init(1, 0);
    while (m--) {
        // cout << "-----\n";
        for (int i = 1; i <= h_sz; i++) is_knd[h[i]] = 0;
        scanf("%d", &h_sz);
        for (int i = 1; i <= h_sz; i++)
            scanf("%d", &h[i]), is_knd[h[i]] = 1;
        
        build_vG(), calc_f(1, 0);
        printf("%lld\n", f[1]);
    }
    return 0;
}