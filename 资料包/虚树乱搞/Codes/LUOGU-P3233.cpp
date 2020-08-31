#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>

using namespace std;

const int maxn = 3e5 + 5, logn = 20;

struct Graph {
    struct Edge {
        int v, w, nex;
        Edge(int v = 0, int w = 0, int nex = 0) : v(v), w(w), nex(nex) {}
    } E[maxn << 1];
    
    int hd[maxn], tchk[maxn], ti, tote;
    
    void addedge(int u, int v, int w) {
        if (tchk[u] != ti) tchk[u] = ti, hd[u] = 0;
        if (tchk[v] != ti) tchk[v] = ti, hd[v] = 0;
        E[++tote] = Edge(v, w, hd[u]), hd[u] = tote;
        E[++tote] = Edge(u, w, hd[v]), hd[v] = tote;
    }
    void destroy() { tote = 0, ti++; }
} G, vG;

int n, _knd[maxn], knd[maxn], knd_sz, isknd[maxn];
int sz[maxn], dep[maxn], dfn[maxn], grd[maxn][25], dfn_cnt;

void init(int u, int fa) {
    dep[u] = dep[fa] + 1, dfn[u] = ++dfn_cnt, grd[u][0] = fa, sz[u] = 1;
    for (int i = 1; i <= logn; i++) grd[u][i] = grd[grd[u][i-1]][i-1];

    for (int i = G.hd[u]; i; i = G.E[i].nex) {
        int v = G.E[i].v;
        if (v == fa) continue;
        init(v, u), sz[u] += sz[v];
    }
}

int get_lca(int u, int v) {
    if (dep[u] < dep[v]) swap(u, v);
    for (int i = logn; i >= 0; i--) if (dep[grd[u][i]] >= dep[v]) u = grd[u][i];
    if (u == v) return u;
    for (int i = logn; i >= 0; i--) 
        if (grd[u][i] != grd[v][i]) u = grd[u][i], v = grd[v][i];
    return grd[u][0];
}

inline int get_dist(int u, int v) { return dep[u] + dep[v] - 2 * dep[get_lca(u, v)]; }
inline int get_grand(int u, int dist) { 
    for (int i = logn; i >= 0; i--) if (dist >= (1 << i)) u = grd[u][i], dist -= (1 << i);
    return u;
}
int stk[maxn], stk_sz;
bool cmp(int a, int b) { return dfn[a] < dfn[b]; }
void build_vG() {
    sort(knd + 1, knd + 1 + knd_sz, cmp), vG.destroy(), stk[stk_sz = 1] = 1;
    for (int i = 1; i <= knd_sz; i++) {
        if (knd[i] == 1) continue;
        int u = knd[i], v = stk[stk_sz], lca = get_lca(u, v);
        if (v == lca) stk[++stk_sz] = u;
        else {
            while (stk_sz > 1 && dep[stk[stk_sz-1]] >= dep[lca])
                vG.addedge(stk[stk_sz-1], stk[stk_sz], get_dist(stk[stk_sz-1], stk[stk_sz])), stk_sz--;
            if (stk[stk_sz] != lca) 
                vG.addedge(stk[stk_sz], lca, get_dist(stk[stk_sz], lca)), stk[stk_sz] = lca;
            stk[++stk_sz] = u;
        }
    }
    for (int i = 1; i < stk_sz; i++) vG.addedge(stk[i], stk[i+1], get_dist(stk[i], stk[i+1]));
}

int blg[maxn], dist[maxn], ans_ls[maxn];
void dfs1(int u, int fa) {
    dist[u] = 99999999;
    for (int i = vG.hd[u]; i; i = vG.E[i].nex) {
        int v = vG.E[i].v;
        if (v == fa) continue;
        dfs1(v, u);
        if (dist[u] > dist[v] + vG.E[i].w) dist[u] = dist[v] + vG.E[i].w, blg[u] = blg[v];
        else if (dist[u] == dist[v] + vG.E[i].w && blg[v] < blg[u]) blg[u] = blg[v];
    }
    if (isknd[u]) dist[u] = 0, blg[u] = u;
}
void dfs2(int u, int fa) {
    for (int i = vG.hd[u]; i; i = vG.E[i].nex) {
        int v = vG.E[i].v;
        if (v == fa) continue;
        if (dist[v] > dist[u] + vG.E[i].w) {
            dist[v] = dist[u] + vG.E[i].w, blg[v] = blg[u];
        } else if (dist[v] == dist[u] + vG.E[i].w && blg[v] > blg[u]) blg[v] = blg[u];
        dfs2(v, u);
    }
}

void calc_edge(int u, int v, int len) {
    int l1 = (dist[u] - dist[v] + len) >> 1, t1, val;
    if (dist[v] + l1 == dist[u] + (len - l1) && blg[v] > blg[u]) t1 = get_grand(v, l1 - 1);
    else t1 = get_grand(v, l1);
    val = sz[t1] - sz[v];
    ans_ls[blg[u]] -= val, ans_ls[blg[v]] += val;
}

void calc(int u, int fa) {
    ans_ls[blg[u]] += sz[u];
    for (int i = vG.hd[u]; i; i = vG.E[i].nex) {
        int v = vG.E[i].v;
        if (v == fa) continue;
        ans_ls[blg[u]] -= sz[v];
        if (blg[u] != blg[v]) calc_edge(u, v, vG.E[i].w);
        calc(v, u);
    }
}

void solve_query() {
    for (int i = 1; i <= knd_sz; i++) isknd[knd[i]] = ans_ls[knd[i]] = 0;
    scanf("%d", &knd_sz);
    for (int i = 1; i <= knd_sz; i++) scanf("%d", &knd[i]), _knd[i] = knd[i], isknd[knd[i]] = 1;

    build_vG();
    dfs1(1, 0), dfs2(1, 0);
    calc(1, 0);
    for (int i = 1; i <= knd_sz; i++) printf("%d ", ans_ls[_knd[i]]);
    putchar('\n');
}

int main() {
    // freopen("test.in", "r", stdin);
    // freopen("test.out", "w", stdout);
    int n; scanf("%d", &n);
    for (int i = 1; i < n; i++) {
        int u, v; scanf("%d%d", &u, &v);
        G.addedge(u, v, 1);
    }
    init(1, 0);
    int T; scanf("%d", &T);
    while (T--) solve_query();
    return 0;
}