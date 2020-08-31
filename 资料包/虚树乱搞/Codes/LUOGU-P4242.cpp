#include <algorithm>
#include <cstring>
#include <cstdio>
#include <cmath>
#define LL long long

using namespace std;

const int maxn = 1e5 + 5;

int n, knd[maxn], _knd[maxn], knd_sz, isknd[maxn]; LL ans[maxn];
struct Edge { int v,w,nex; Edge(int v=0, int w=0, int nex=0) : v(v),w(w),nex(nex) {} };
struct ltreedt {
    int lc, rc, v;
    ltreedt(int lc=0, int rc=0, int v=0) : lc(lc), rc(rc), v(v) { }
    friend ltreedt operator + (ltreedt l, ltreedt r) {
        if (!l.lc) return r;
        if (!r.lc) return l;
        return ltreedt(l.lc, r.rc, l.v + r.v - (l.rc == r.lc));
    }
};
struct Graph {
    Edge E[maxn << 1];
    int hd[maxn], tote, tc[maxn], ti;
    void addedge(int u, int v, int w=0) {
        if (tc[u] != ti) tc[u] = ti, hd[u] = 0; if (tc[v] != ti) tc[v] = ti, hd[v] = 0;
        E[++tote] = Edge(v, w, hd[u]), hd[u] = tote;
        E[++tote] = Edge(u, w, hd[v]), hd[v] = tote;
    }
    void destroy() { tote = 0, ti++; }
} G, vG;

struct ltree {
    #define LS(o) (o << 1)
    #define RS(o) (o << 1 | 1)
    ltreedt dt[maxn << 2]; int tag[maxn << 2];
    void push_down(int o) {
        if (tag[o]) {
            dt[LS(o)].lc = dt[LS(o)].rc = dt[RS(o)].lc = dt[RS(o)].rc = tag[o];
            tag[LS(o)] = tag[RS(o)] = tag[o];
            dt[LS(o)].v = dt[RS(o)].v = 1;
            tag[o] = 0;
        }
    }
    void change(int o, int l, int r, int ql, int qr, int c) {
        if (l > qr || r < ql) return ;
        if (ql <= l && r <= qr) { 
            dt[o].lc = dt[o].rc = tag[o] = c, dt[o].v = 1;
            return ;
        }
        push_down(o);
        int mid = (l + r) >> 1;
        change(LS(o), l, mid, ql, qr, c), change(RS(o), mid+1, r, ql, qr, c);
        dt[o] = dt[LS(o)] + dt[RS(o)];
    }
    ltreedt ask(int o, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) return dt[o];
        push_down(o);
        int mid = (l + r) >> 1;
        if (qr <= mid) return ask(LS(o), l, mid, ql, qr);
        else if (ql > mid) return ask(RS(o), mid+1, r, ql, qr);
        else return ask(LS(o), l, mid, ql, qr) + ask(RS(o), mid+1, r, ql, qr);
    }
} ltr;

int sz[maxn], grd[maxn], wson[maxn], top[maxn], dep[maxn], dfn[maxn], nd[maxn], dfn_cnt;
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
    dfn[u] = ++dfn_cnt, nd[dfn_cnt] = u, top[u] = tp;
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
void path_change(int u, int v, int c) {
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]]) swap(u, v);
        ltr.change(1, 1, n, dfn[top[u]], dfn[u], c);
        u = grd[top[u]];
    }
    if (dep[u] < dep[v]) swap(u, v);
    ltr.change(1, 1, n, dfn[v], dfn[u], c);
}
ltreedt path_ask(int u, int v) {
    ltreedt ret = ltreedt();
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]]) swap(u, v);
        ret = ltr.ask(1, 1, n, dfn[top[u]], dfn[u]) + ret;
        u = grd[top[u]];
    }
    if (dep[u] < dep[v]) swap(u, v);
    ret = ltr.ask(1, 1, n, dfn[v], dfn[u]) + ret;
    return ret;
}

int stk[maxn], s_sz;
bool cmp(int a, int b) { return dfn[a] < dfn[b]; }
void build_vG() {
    sort(knd+1, knd+1+knd_sz, cmp), stk[s_sz = 1] = 1, vG.destroy();
    for (int i = 1; i <= knd_sz; i++) {
        if (knd[i] == 1) continue;
        int u = knd[i], v = stk[s_sz], lca = get_lca(u, v);
        if (v == lca) stk[++s_sz] = u;
        else {
            while (s_sz > 1 && dep[stk[s_sz-1]] >= dep[lca])
                vG.addedge(stk[s_sz], stk[s_sz-1], path_ask(stk[s_sz], stk[s_sz-1]).v-1), s_sz--;
            if (lca != stk[s_sz]) vG.addedge(lca, stk[s_sz], path_ask(lca, stk[s_sz]).v-1), stk[s_sz] = lca;
            stk[++s_sz] = u;
        }
    }
    for (int i = 1; i < s_sz; i++) vG.addedge(stk[i], stk[i+1], path_ask(stk[i], stk[i+1]).v-1);
}

int fl[maxn], vsz[maxn], cls[maxn], l_ls[maxn], cls_sz, vct_sz, wroot, wroot_ct;
LL psum, pcnt, tsum, tcnt;
void calc_vsz(int u, int fa) {
    vsz[u] = 1;
    for (int i = vG.hd[u]; i; i = vG.E[i].nex) {
        int v = vG.E[i].v;
        if (v == fa || fl[v]) continue;
        calc_vsz(v, u), vsz[u] += vsz[v]; 
    }
}
void find_wroot(int u, int fa) {
    int max_ct = 0;
    for (int i = vG.hd[u]; i; i = vG.E[i].nex) {
        int v = vG.E[i].v;
        if (v == fa || fl[v]) continue;
        find_wroot(v, u);
        max_ct = max(max_ct, vsz[v]);
    }
    max_ct = max(max_ct, vct_sz - vsz[u]);
    if (max_ct < wroot_ct) wroot = u, wroot_ct = max_ct;
}
void calc_ans(int u, int fa, int len) {
    if (isknd[u]) {
        ans[u] += len * pcnt + psum;
        tsum += len + 1, tcnt++;
    }
    for (int i = vG.hd[u]; i; i = vG.E[i].nex) {
        int v = vG.E[i].v;
        if (v == fa || fl[v]) continue;
        calc_ans(v, u, len + vG.E[i].w);
    }
}
void divide(int u) {
    psum = pcnt = cls_sz = 0;
    if (isknd[u]) psum = pcnt = 1, ans[u]++;
    for (int i = vG.hd[u]; i; i = vG.E[i].nex) {
        int v = vG.E[i].v;
        if (fl[v]) continue;
        tsum = tcnt = 0, calc_ans(v, u, vG.E[i].w), psum += tsum, pcnt += tcnt;
        cls[++cls_sz] = v, l_ls[cls_sz] = vG.E[i].w;
    }
    if (isknd[u]) ans[u] += psum - 1;
    psum = pcnt = 0;
    for (int i = cls_sz; i >= 1; i--) {
        int v = cls[i];
        tsum = tcnt = 0, calc_ans(v, u, l_ls[i]), psum += tsum, pcnt += tcnt;
    }
    fl[u] = 1;
    for (int i = vG.hd[u]; i; i = vG.E[i].nex) {
        int v = vG.E[i].v;
        if (fl[v]) continue;
        calc_vsz(v, u), wroot_ct = 1e8, vct_sz = vsz[v];
        find_wroot(v, u), divide(wroot);
    }
    fl[u] = 0;
}

int c[maxn];

void build_ltr(int o, int l, int r) {
    if (l == r) {
        ltr.dt[o].lc = ltr.dt[o].rc = c[nd[l]], ltr.dt[o].v = 1;
        return ;
    }
    int mid = (l+r) >> 1;
    build_ltr(LS(o), l, mid), build_ltr(RS(o), mid+1, r);
    ltr.dt[o] = ltr.dt[LS(o)] + ltr.dt[RS(o)];
}

int main() {
    // freopen("test.in", "r", stdin);
    // freopen("test.out", "w", stdout);
    int m; scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%d", &c[i]);
    for (int i = 1; i < n; i++) {
        int u, v; scanf("%d%d", &u, &v);
        G.addedge(u, v);
    }
    dfs1(1, 0), dfs2(1, 1), build_ltr(1, 1, n);
    while (m--) {
        int t; scanf("%d", &t);
        if (t == 1) {
            int u, v, c; scanf("%d%d%d", &u, &v, &c);
            path_change(u, v, c);
        } else {
            for (int i = 1; i <= knd_sz; i++) isknd[knd[i]] = ans[knd[i]] = 0;
            scanf("%d", &knd_sz);
            for (int i = 1; i <= knd_sz; i++) {
                scanf("%d", &knd[i]);
                isknd[knd[i]] = 1, _knd[i] = knd[i];
            }
            build_vG();
            wroot_ct = 1e8, vct_sz = n, calc_vsz(1, 0), find_wroot(1, 0), divide(wroot);
            for (int i = 1; i <= knd_sz; i++) printf("%lld ", ans[_knd[i]]);
            putchar('\n');
        }
    }
    return 0;
}