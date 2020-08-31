#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
#define LL long long

using namespace std;

const int maxn = 2e5 + 5;
const LL MOD = 1e9 + 7;
int n, knd[maxn], knd_sz, p[maxn]; LL a[maxn];
struct Edge {
    int v, nex; LL w;
    Edge(int v=0, LL w=0, int nex=0) : v(v), w(w), nex(nex) {}
};
struct Graph {
    Edge E[maxn << 1];
    int hd[maxn], tote, tc[maxn], ti;
    void addedge(int u, int v, LL w) {
        if (tc[u] != ti) tc[u] = ti, hd[u] = 0;
        if (tc[v] != ti) tc[v] = ti, hd[v] = 0;
        E[++tote] = Edge(v, w, hd[u]), hd[u] = tote;
        E[++tote] = Edge(u, w, hd[v]), hd[v] = tote;
    }
    void destroy() { tote = 0, ti++; }
} G, vG;
int sz[maxn], wson[maxn], dep[maxn], grd[maxn], dfn[maxn], top[maxn], dfn_cnt;
void dfs1(int u, int fa) {
    grd[u] = fa, dep[u] = dep[fa] + 1, sz[u] = 1;
    for (int i = G.hd[u]; i; i = G.E[i].nex) {
        int v = G.E[i].v;
        if (v == fa) continue;
        dfs1(v, u), sz[u] += sz[v];
        if (!wson[u] || sz[wson[u]] < sz[v]) wson[u] = v;
    }
}
void dfs2(int u, int tp) {
    dfn[u] = ++dfn_cnt, top[u] = tp;
    if (!wson[u]) return ;
    dfs2(wson[u], tp);
    for (int i = G.hd[u]; i; i = G.E[i].nex) {
        int v = G.E[i].v;
        if (v == grd[u] || v == wson[u]) continue;
        dfs2(v, v);
    }
}

int get_lca(int u, int v) {
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]]) swap(u, v);
        u = grd[top[u]];
    }
    return dep[u] < dep[v] ? u : v;
}
LL get_dist(int u, int v) { return dep[u] + dep[v] - 2 * dep[get_lca(u, v)]; }

int stk[maxn], stk_sz;
bool cmp(int a, int b) { return dfn[a] < dfn[b]; }
void build_vG() {
    sort(knd+1, knd+1+knd_sz, cmp), stk[stk_sz=1] = 1, vG.destroy();
    for (int i = 1; i <= knd_sz; i++) {
        if (knd[i] == 1) continue;
        int u = knd[i], v = stk[stk_sz], l = get_lca(u, v);
        if (v == l) stk[++stk_sz] = u;
        else {
            while (stk_sz > 1 && dep[stk[stk_sz-1]] >= dep[l])
                vG.addedge(stk[stk_sz-1], stk[stk_sz], get_dist(stk[stk_sz-1], stk[stk_sz])),
                stk_sz--;
            if (l != stk[stk_sz]) 
                vG.addedge(l, stk[stk_sz], get_dist(l, stk[stk_sz])), stk[stk_sz] = l;
            stk[++stk_sz] = u;
        }
    }
    for (int i = 1; i < stk_sz; i++) vG.addedge(stk[i], stk[i+1], get_dist(stk[i], stk[i+1]));
}

LL phi[maxn], mu[maxn], pri[maxn], invphi[maxn], F1[maxn]; 
int vis[maxn], pri_sz;
LL qpow(LL a, LL b) {
    LL ret = 1;
    while (b) {
        if (b & 1) ret = ret * a % MOD;
        a = a * a % MOD, b >>= 1;
    }
    return ret;
}
void sieve() {
    int n = maxn - 5; mu[1] = phi[1] = 1;
    for (int i = 2; i <= n; i++) {
        if (!vis[i]) pri[++pri_sz] = i, phi[i] = i-1, mu[i] = -1;
        for (int j = 1; j <= pri_sz; j++) {
            LL x = i * pri[j];
            if (x > n) continue;
            vis[x] = 1;
            if (i % pri[j]) mu[x] = -mu[i], phi[x] = phi[i] * phi[pri[j]];
            else {
                mu[x] = 0, phi[x] = phi[i] * pri[j];
                break;
            }
        }
    }
    for (int i = 1; i <= n; i++) invphi[i] = qpow(phi[i], MOD - 2);
}

LL f[maxn], Sg[maxn], Sk[maxn], w[maxn];
void calc_F1() {
    for (int d = 1; d <= n; d++) 
        for (int i = d; i <= n; i += d)
            F1[i] = (F1[i] + d * invphi[d] % MOD * mu[i / d] % MOD + MOD) % MOD;
}

void dp(int u, int fa) {
    f[u] = Sg[u] = 0, Sk[u] = w[u];
    for (int i = vG.hd[u]; i; i = vG.E[i].nex) {
        int v = vG.E[i].v;
        if (v == fa) continue;
        dp(v, u);
        LL len = vG.E[i].w;
        LL w_uv = (Sg[u]*Sk[v]%MOD + len*Sk[u]%MOD*Sk[v]%MOD + Sk[u]*Sg[v]%MOD) % MOD;
        Sg[u] = (Sg[u] + Sg[v] + len*Sk[v] % MOD) % MOD;
        Sk[u] = (Sk[u] + Sk[v]) % MOD;
        f[u] = (f[u] + f[v] + w_uv) % MOD;
    }
    vG.hd[u] = w[u] = 0;
}
int main() {
    // freopen("test.in", "r", stdin);
    // freopen("test.out", "w", stdout);
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%lld", &a[i]), p[a[i]] = i;
    for (int i = 1; i < n; i++) {
        int u, v; scanf("%d%d", &u, &v);
        G.addedge(u, v, 1);
    }
    LL ans = 0;
    dfs1(1, 0), dfs2(1, 1), sieve(), calc_F1();
    for (int T = 1; T <= n; T++) {
        knd_sz = 0;
        for (int i = T; i <= n; i += T)
            knd[++knd_sz] = p[i], w[p[i]] = phi[i];
        build_vG(), dp(1, 0);
        ans = (ans + F1[T] * f[1] % MOD * 2 % MOD) % MOD;
    }
    printf("%lld\n", ans * qpow(n, MOD-2) % MOD * qpow(n-1, MOD-2) % MOD);
    return 0;
}