#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
#define LL long long

using namespace std;

const int maxn = 1000005;

int n;
struct Graph {
    struct Edge {
        int v, nex; LL w;
        Edge() {}
        Edge(int v, LL w, int nex) : v(v), w(w), nex(nex) {} 
    } E[maxn << 1];

    int tchk[maxn], hd[maxn], ti, tote;

    void addedge(int u, int v, LL w) {
        if (tchk[u] != ti) tchk[u] = ti, hd[u] = 0;
        if (tchk[v] != ti) tchk[v] = ti, hd[v] = 0;

        E[++tote] = Edge(v, w, hd[u]), hd[u] = tote;
        E[++tote] = Edge(u, w, hd[v]), hd[v] = tote;

        // printf("connect %d and %d\n", u, v);
    }

    inline void destroy() { tote = 0, ti++; }
} G, vG;

int grd[maxn][25], dfn[maxn], dep[maxn], dfn_cnt; 
LL s[maxn];

void init(int u, int fa) {
    dfn[u] = ++dfn_cnt, grd[u][0] = fa, dep[u] = dep[fa] + 1;
    for (int i = 1; i <= 20; i++) grd[u][i] = grd[grd[u][i-1]][i-1];

    for (int i = G.hd[u]; i; i = G.E[i].nex) {
        int v = G.E[i].v;
        if (v == fa) continue;
        s[v] = s[u] + G.E[i].w, init(v, u);
    }
}

int get_lca(int u, int v) {
    if (dep[u] < dep[v]) swap(u, v);
    for (int i = 18; i >= 0; i--) 
        if (dep[grd[u][i]] >= dep[v]) u = grd[u][i];
    if (u == v) return u;
    for (int i = 18; i >= 0; i--)
        if (grd[u][i] != grd[v][i]) u = grd[u][i], v = grd[v][i];
    return grd[u][0];
}

inline int get_dist(int u, int v) { return s[u] + s[v] - 2 * s[get_lca(u, v)]; }

int h[maxn], h_sz, is_knd[maxn], stk[maxn], stk_sz;

bool cmp(int a, int b) { return dfn[a] < dfn[b]; }

void build_vG() {
    sort(h + 1, h + 1 + h_sz, cmp), vG.destroy(), stk[stk_sz = 1] = 1;
    for (int i = 1; i <= h_sz; i++) {
        if (h[i] == 1) continue;
        int u = h[i], v = stk[stk_sz], lca = get_lca(u, v);
        if (lca == v) stk[++stk_sz] = u;
        else {
            while (stk_sz > 1 && dep[stk[stk_sz - 1]] >= dep[lca]) 
                vG.addedge(stk[stk_sz], stk[stk_sz - 1], get_dist(stk[stk_sz], stk[stk_sz - 1])),
                stk_sz--;
            if (lca != stk[stk_sz])
                vG.addedge(stk[stk_sz], lca, get_dist(stk[stk_sz], lca)), stk[stk_sz] = lca;
            stk[++stk_sz] = u;
        }
    }
    for (int i = 1; i < stk_sz; i++)
        vG.addedge(stk[i], stk[i + 1], get_dist(stk[i], stk[i + 1]));
}

LL minl[maxn], maxl[maxn], knd_cnt[maxn], ans_max, ans_min, ans_sum;

void calc_ans(int u, int fa) {
    int sec_max = maxl[u] = 0, sec_min = minl[u] = 1e8;
    knd_cnt[u] = is_knd[u];
    int ktr_cnt = 0;
    if (is_knd[u]) minl[u] = 0, ktr_cnt++;

    for (int i = vG.hd[u]; i; i = vG.E[i].nex) {
        int v = vG.E[i].v; LL len = vG.E[i].w;
        if (v == fa) continue;
        calc_ans(v, u); 
        knd_cnt[u] += knd_cnt[v];
        if (knd_cnt[v]) ktr_cnt++;
        
        ans_sum += knd_cnt[v] * (h_sz - knd_cnt[v]) * len;

        LL val = len + minl[v];
        if (val < minl[u]) sec_min = minl[u], minl[u] = val;
        else if (val < sec_min) sec_min = val;
        
        val = len + maxl[v];
        if (val > maxl[u]) sec_max = maxl[u], maxl[u] = val;
        else if (val > sec_max) sec_max = val;
    }
    if (ktr_cnt <= 1) return ;

    ans_max = max(ans_max, maxl[u] + sec_max);
    ans_min = min(ans_min, minl[u] + sec_min);
}

int main() {
    // freopen("test.in", "r", stdin);
    // freopen("test.out", "w", stdout);

    scanf("%d", &n);
    for (int i = 1; i < n; i++) {
        int u, v; scanf("%d%d", &u, &v);
        G.addedge(u, v, 1);
    }
    init(1, 0);
    int T; scanf("%d", &T);
    // printf("----\n");
    while (T--) {
        // printf("----\n");
        for (int i = 1; i <= h_sz; i++) is_knd[h[i]] = 0;
        scanf("%d", &h_sz);
        for (int i = 1; i <= h_sz; i++) 
            scanf("%d", &h[i]), is_knd[h[i]] = 1;
        build_vG();
        ans_sum = ans_max = 0, ans_min = 1e8;
        calc_ans(1, 0);
        printf("%lld %lld %lld\n", ans_sum, ans_min, ans_max);
    }
    return 0;
}