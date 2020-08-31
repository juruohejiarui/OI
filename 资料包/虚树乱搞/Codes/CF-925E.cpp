#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
#include <cmath>
#define PAIR pair<int, int>

using namespace std;

const int maxn = 1e5 + 5;
struct Edge {
    int v, w, nex;
    Edge(int v=0, int w=0, int nex=0) : v(v), w(w), nex(nex) {}
};
struct Graph {
    Edge E[maxn << 1];
    int tchk[maxn], hd[maxn], ti, tote;
    
    void addedge(int u, int v, int w=0) {
        if (tchk[u] != ti) tchk[u] = ti, hd[u] = 0;
        if (tchk[v] != ti) tchk[v] = ti, hd[v] = 0;
        E[++tote] = Edge(v, w, hd[u]), hd[u] = tote;
        E[++tote] = Edge(u, w, hd[v]), hd[v] = tote;
    }
    void destroy() { tote = 0, ti++; }
} G, vG;

int n, rt, ans, qls[maxn], t[maxn], w[maxn], cnt[maxn], col[maxn], knd[maxn], knd_sz;
int dfn[maxn], dep[maxn], grd[maxn][25], dfn_cnt;

void init(int u, int fa) {
    grd[u][0] = fa, dep[u] = dep[fa] + 1, dfn[u] = ++dfn_cnt;
    for (int i = 1; i <= 18; i++) grd[u][i] = grd[grd[u][i-1]][i-1];
    for (int i = G.hd[u]; i; i = G.E[i].nex) {
        int v = G.E[i].v;
        if (v == fa) continue;
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
int update(int u, int fa) {
    int cnt = col[u];
    for (int i = G.hd[u]; i; i = G.E[i].nex) {
        int v = G.E[i].v;
        if (v == fa) continue;
        cnt += update(v, u);
    }
    w[u] = t[u] - cnt + 1;
    if (!col[u]) ans += (w[u] <= 0);
    return cnt;
}

int vfa[maxn], stk[maxn], stk_sz;
bool cmp(int a, int b) { return dfn[a] < dfn[b]; }
void build_vG() {
    sort(knd + 1, knd + 1 + knd_sz, cmp), stk[stk_sz = 1] = rt, vG.destroy();
    for (int i = 1; i <= knd_sz; i++) {
        if (knd[i] == rt) continue;
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
int lsid[maxn], w_ls_len[maxn], tmp[maxn], pos[maxn], tmp_sz, lsid_cnt;
vector<PAIR> w_ls[maxn];

int bin_search(int id, int val) {
    int l = 1, r = w_ls[id].size(), ans = 0;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (w_ls[id][mid - 1].first <= val) 
            ans = w_ls[id][mid-1].second, l = mid + 1;
        else r = mid - 1;
    }
    return ans;
}

void v_init(int u, int fa) {
    cnt[u] = 0;
    for (int i = vG.hd[u]; i; i = vG.E[i].nex) {
        int v = vG.E[i].v;
        if (v == fa) continue;
        v_init(v, u);
    }
    if (fa) {
        int id = lsid[u] = ++lsid_cnt;
        int* len = &w_ls_len[u], *p = &pos[u]; 
        vfa[u] = fa, u = grd[u][0], tmp_sz = 0;
        while (u != fa) {
            if (!col[u]) tmp[++tmp_sz] = w[u];
            u = grd[u][0];
        }
        sort(tmp+1, tmp+1+tmp_sz);
        w_ls[id].clear(), *len = 0, *p = -1;
        for (int i = 1; i <= tmp_sz; i++) {
            if (tmp[i] != tmp[i-1]) {
                w_ls[id].push_back(make_pair(tmp[i], 0)), (*len)++;
            }
            w_ls[id][*len - 1].second++;
            if (w_ls[id][*len - 1].first <= 0) *p = *len - 1;
        }
    }
}

void v_change(int u) {
    for (int nd = u; nd; nd = vfa[nd])
        ans -= (cnt[nd] >= w[nd]) * (!col[nd]);
    col[u] ^= 1; int delta = (col[u] == 1 ? 1 : -1);
    for (int nd = u; nd; nd = vfa[nd]) {
        cnt[nd] += delta, ans += (cnt[nd] >= w[nd]) * (!col[nd]);
        if (w_ls_len[nd]) {
            vector<PAIR>* vec = &w_ls[lsid[nd]];
            if (delta == 1 && pos[nd]+1 < w_ls_len[nd] && (*vec)[pos[nd]+1].first <= cnt[nd])
                    pos[nd]++, ans += (*vec)[pos[nd]].second;
            if (delta == -1 && pos[nd] >= 0 && (*vec)[pos[nd]].first > cnt[nd]) 
                ans -= (*vec)[pos[nd]].second, pos[nd]--;
        }
        
    }
}

int main() {
    int n, m; scanf("%d%d", &n, &m); tmp[0] = -99999999, rt = 1;
    int blksz = sqrt(m);
    for (int i = 2; i <= n; i++) {
        int fa; scanf("%d", &fa), G.addedge(fa, i), dep[i]++;
    }
    for (int i = 1; i <= n; i++) scanf("%d", &t[i]);
    init(rt, 0);
    for (int i = 1; i <= m; i += blksz) {
        ans = knd_sz = lsid_cnt = 0, update(rt, 0);
        for (int j = 0; j < blksz && i+j <= m; j++) 
            scanf("%d", &qls[i+j]), knd[++knd_sz] = abs(qls[i+j]);
        sort(knd+1, knd+1+knd_sz), knd_sz = unique(knd+1, knd+1+knd_sz) - knd - 1;

        build_vG(), v_init(1, 0);
        for (int j = 0; j < blksz && i+j <= m; j++) {
            v_change(abs(qls[i+j])); printf("%d ", ans);
        }
    }
    return 0;
}