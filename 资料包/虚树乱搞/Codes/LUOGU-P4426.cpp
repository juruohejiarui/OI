#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
#define LL long long

using namespace std;

const int maxn = 1e5 + 25;
const LL MOD = 998244353;

struct Edge { int v, nex; Edge(int v=0, int nex=0) : v(v), nex(nex) {} };
struct Graph {
    Edge E[maxn << 1];
    int hd[maxn], tc[maxn], ti, tote;
    void addedge(int u, int v) {
        if (tc[u] != ti) tc[u] = ti, hd[u] = 0;
        if (tc[v] != ti) tc[v] = ti, hd[v] = 0;
        E[++tote] = Edge(v, hd[u]), hd[u] = tote;
        E[++tote] = Edge(u, hd[v]), hd[v] = tote;
    }
    void destroy() { tote = 0, ti++; }
} G, vG;

int n, m, hvknd[maxn], vnd[maxn], vnd_sz, knd[maxn], knd_sz; 
LL of[maxn][2], f[maxn][2], g[maxn][2][2], vfa[maxn][2];

int vis[maxn], dfn[maxn], dep[maxn], grd[maxn][25], dfn_cnt;
void init(int u, int fa) {
    vis[u] = 1;
    grd[u][0] = fa, dep[u] = dep[fa] + 1, dfn[u] = ++dfn_cnt;
    for (int i = 1; i <= 18; i++) grd[u][i] = grd[grd[u][i-1]][i-1];
    for (int i = G.hd[u]; i; i = G.E[i].nex) {
        int v = G.E[i].v;
        if (v == fa || vis[v]) continue;
        init(v, u);
    }
}
void set_hvknd(int u, int fa) {
    for (int i = G.hd[u]; i; i = G.E[i].nex) {
        int v = G.E[i].v;
        if (v == fa) continue;
        set_hvknd(v, u), hvknd[u] += hvknd[v];
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

int stk[maxn], stk_sz;
bool cmp(int a, int b) { return dfn[a] < dfn[b]; }
void build_vG() {
    sort(knd + 1, knd + 1 + knd_sz, cmp), stk[stk_sz = 1] = 1, vG.destroy();
    for (int i = 1; i <= knd_sz; i++) {
        if (knd[i] == 1) continue;
        int u = knd[i], v = stk[stk_sz], lca = get_lca(u, v);
        if (lca == v) stk[++stk_sz] = u;
        else {
            while (stk_sz > 1 && dep[lca] <= dep[stk[stk_sz - 1]])
                vG.addedge(stk[stk_sz-1], stk[stk_sz]), stk_sz--;
            if (stk[stk_sz] != lca) vG.addedge(stk[stk_sz], lca), stk[stk_sz] = lca;
            stk[++stk_sz] = u;
        }
    }
    for (int i = 1; i < stk_sz; i++) vG.addedge(stk[i], stk[i+1]);
}

void calc_f(int u, int fa) {
    f[u][0] = f[u][1] = 1;
    for (int i = G.hd[u]; i; i = G.E[i].nex) {
        int v = G.E[i].v;
        if (v == grd[u][0] || v == fa) continue;
        calc_f(v, u);
        f[u][0] = f[u][0] * ((f[v][0] + f[v][1]) % MOD) % MOD;
        f[u][1] = f[u][1] * f[v][0] % MOD;
    }
}

void calc_of(int u, int fa) {
    of[u][0] = of[u][1] = 1;
    for (int i = G.hd[u]; i; i = G.E[i].nex) {
        int v = G.E[i].v;
        if (v == fa || hvknd[v]) continue;
        calc_of(v, u);
        of[u][0] = of[u][0] * ((of[v][0] + of[v][1]) % MOD) % MOD;
        of[u][1] = of[u][1] * of[v][0] % MOD;
    }
    
}

void calc_g(int u, int fa) {
    g[u][0][0] = g[u][0][1] = g[u][1][0] = 1;
    int nd = u;
    if (nd != 1) while (grd[nd][0] != fa) {
        LL r00 = g[u][0][0], r01 = g[u][0][1], r10 = g[u][1][0], r11 = g[u][1][1];
        int gr = grd[nd][0];
        calc_f(gr, nd);
        g[u][0][0] = (f[gr][0] * r00 % MOD + f[gr][1] * r10 % MOD) % MOD;
        g[u][0][1] = (f[gr][0] * r01 % MOD + f[gr][1] * r11 % MOD) % MOD;
        g[u][1][0] = f[gr][0] * r00 % MOD, g[u][1][1] = f[gr][0] * r01 % MOD;

        nd = grd[nd][0];
    }
    calc_of(u, fa), vnd[++vnd_sz] = u;
    for (int i = vG.hd[u]; i; i = vG.E[i].nex) {
        int v = vG.E[i].v;
        if (v == fa) continue;
        calc_g(v, u);
    }
}

LL vf[maxn][2];
void calc_vf(int u, int fa) {
    for (int i = vG.hd[u]; i; i = vG.E[i].nex) {
        int v = vG.E[i].v;
        if (v == fa) continue;
        calc_vf(v, u);
        vf[u][0] = vf[u][0] * ((vf[v][0] * g[v][0][0] % MOD + vf[v][1] * g[v][0][1] % MOD) % MOD) % MOD;
        vf[u][1] = vf[u][1] * ((vf[v][0] * g[v][1][0] % MOD + vf[v][1] * g[v][1][1] % MOD) % MOD) % MOD;
    }
}

int st[maxn], ed[maxn], spst[maxn], sped[maxn], sp_sz;
int main() {
    // freopen("test.in", "r", stdin);
    // freopen("test.out", "w", stdout);

    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++) {
        int u, v; scanf("%d%d", &u, &v);
        G.addedge(u, v), st[i] = u, ed[i] = v;
    }
    init(1, 0), G.destroy();
    for (int i = 2; i <= n; i++) G.addedge(grd[i][0], i);
    for (int i = 1; i <= m; i++) {
        if (dep[st[i]] > dep[ed[i]]) swap(st[i], ed[i]);
        if (grd[ed[i]][0] != st[i]) 
            knd[++knd_sz] = st[i], knd[++knd_sz] = ed[i],
            spst[++sp_sz] = st[i], sped[sp_sz] = ed[i],
            hvknd[st[i]] = hvknd[ed[i]] = 1;
    }
    LL ans = 0;
    sort(knd+1, knd+1+knd_sz), knd_sz = unique(knd+1, knd+1+knd_sz) - knd - 1;
    build_vG(), set_hvknd(1, 0);
    calc_g(1, 0);
    for (int S = 0; S < (1 << sp_sz); S++) {
        for (int i = 1; i <= vnd_sz; i++) vf[vnd[i]][0] = of[vnd[i]][0], vf[vnd[i]][1] = of[vnd[i]][1];
        for (int i = 1; i <= sp_sz; i++) 
            if (S & (1 << (i-1))) vf[spst[i]][0] = vf[sped[i]][1] = 0;
            else vf[spst[i]][1] = 0;
        calc_vf(1, 0);
        ans += (vf[1][0] + vf[1][1]) % MOD, ans %= MOD;
    }
    printf("%lld\n", ans);
    return 0;
}