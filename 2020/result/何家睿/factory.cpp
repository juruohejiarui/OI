#include <iostream>
#include <cstring>
#include <cstdio>
#include <string>
#include <cmath>
#include <vector>

using namespace std;

const int maxn = 5e5 + 10, maxm = 4e5 + 5;
int str_len, len1, len2, ans[maxm], p[maxm], nex[maxm], pre[maxm], t1, t2;
string str[maxm];
struct Query {
    int l, r, id;
    Query(int l, int r, int id) : l(l), r(r), id(id) {}
};
struct STNode {
    int ls, rs, val;
} tr[maxn * 40];
int tr_cnt;
struct SAMNode {
    int ch[27], fa, len;
} nd[maxn];
int nd_cnt, lst, tid[maxn];
vector<Query> qls[maxn];
struct GEdge {
    int v, nex;
    GEdge(int v = 0, int nex = 0) : v(v), nex(nex) {}
} E[maxn];
int hd[maxn], tote;
int q_len;

int ST_build() {
    tr_cnt++;
    tr[tr_cnt].val = tr[tr_cnt].ls = tr[tr_cnt].rs = 0;
    return tr_cnt;
}
void ST_pushup(int o) {
    tr[o].val = 0;
    if (tr[o].ls) tr[o].val += tr[tr[o].ls].val;
    if (tr[o].rs) tr[o].val += tr[tr[o].rs].val;
}

void ST_update(int o, int l, int r, int p, int val) {
    if (l == r) { tr[o].val += val; return ; }
    int mid = (l + r) >> 1;
    if (p <= mid) {
        if (!tr[o].ls) tr[o].ls = ST_build();
        ST_update(tr[o].ls, l, mid, p, val);
    } else if (p > mid) {
        if (!tr[o].rs) tr[o].rs = ST_build();
        ST_update(tr[o].rs, mid+1, r, p, val);
    }
    ST_pushup(o);
}
int ST_query(int o, int l, int r, int ql, int qr) {
    if (!o) return 0;
    if (ql <= l && r <= qr) return tr[o].val;
    int mid = (l + r) >> 1;
    if (qr <= mid) return ST_query(tr[o].ls, l, mid, ql, qr);
    else if (ql > mid) return ST_query(tr[o].rs, mid + 1, r, ql, qr);
    else return ST_query(tr[o].ls, l, mid, ql, qr) + ST_query(tr[o].rs, mid + 1, r, ql, qr);
}
int ST_merge(int p, int q, int l, int r) {
    if (!p || !q) return p | q;
    if (l == r) {
        tr[p].val += tr[q].val;
        return p;
    }
    int mid = (l + r) >> 1;
    tr[p].ls = ST_merge(tr[p].ls, tr[q].ls, l, mid);
    tr[p].rs = ST_merge(tr[p].rs, tr[q].rs, mid + 1, r);
    ST_pushup(p);
    return p;
}

void SAM_init() {
    nd_cnt = lst = 1; tid[1] = ST_build();
}
void SAM_update(int c) {
    int p = lst, np = lst = ++nd_cnt;
    nd[np].len = nd[p].len + 1;
    for (; p && !nd[p].ch[c]; p = nd[p].fa) nd[p].ch[c] = np;
    if (!p) nd[np].fa = 1;
    else {
        int v = nd[p].ch[c];
        if (nd[p].len + 1 == nd[v].len) nd[np].fa = v;
        else {
            int nv = ++nd_cnt; nd[nv] = nd[v];
            nd[nv].len = nd[p].len + 1;
            nd[v].fa = nd[np].fa = nv;
            for (; p && nd[p].ch[c] == v; p = nd[p].fa) nd[p].ch[c] = nv;
        }
    }
    tid[np] = ST_build();
    ST_update(tid[np], 1, str_len, nd[np].len, 1);
}
void G_addedge(int u, int v) {
    E[++tote] = GEdge(v, hd[u]), hd[u] = tote;
}
void G_build() {
    for (int i = 2; i <= nd_cnt; i++) G_addedge(nd[i].fa, i);
}

void calc_ans(int u) {
    for (int i = hd[u]; i; i = E[i].nex) {
        int v = E[i].v;
        calc_ans(v);
        tid[u] = ST_merge(tid[u], tid[v], 1, str_len);
    }
}

int main() {
    // freopen("test.in", "r", stdin);
    // freopen("test.out", "w", stdout);
    freopen("factory.in", "r", stdin);
    freopen("factory.out", "w", stdout);
    int n, rt = 0;
    int len = 0, fir = 0, fir_r = 0, fir_q = 0, len_r = 0, ls = 0, ls_r = 0, ls_q = 0;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        string tt; cin >> tt;
        if (tt[0] == '+') {
            if (!rt) {
                len += tt.size() - 1, str[i] = tt;
                if (!ls) fir = i;
                else nex[ls] = i;
                ls = i;
            } else {
                len_r += tt.size() - 1, str[i] = tt;
                if (!ls_r) fir_r = i;
                else nex[ls_r] = i, pre[i] = ls_r;
                ls_r = i;
            }
        } else if (tt[0] == '?') {
            if (!ls_q) fir_q = i;
            else nex[ls_q] = i;
            ls_q = i;
            if (rt) for (int j = tt.size() - 1; j >= 1; j--)
                str[i] += tt[j];
            else str[i] = tt.substr(1, tt.size() - 1);
        } else rt ^= 1;
    }
    str_len = len + len_r; len1 = len, len2 = len_r;
    int tmp = 1;
    for (int i = ls_r; i; i = pre[i]) p[i] = tmp, tmp += str[i].size() - 1;
    tmp = 1;
    for (int i = fir; i; i = nex[i]) p[i] = tmp + len_r, tmp += str[i].size() - 1;
    t1 = fir; t2 = fir_r; 
    SAM_init();
    for (int i = ls_r; i; i = pre[i]) 
        for (int j = str[i].size() - 1; j >= 1; j--)
            SAM_update(str[i][j] - 'a');
    for (int i = fir; i; i = nex[i])
         for (int j = 1; j < str[i].size(); j++)
            SAM_update(str[i][j] - 'a');
    G_build();
    calc_ans(1);
    
    return 0;
}