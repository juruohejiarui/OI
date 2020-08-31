#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>

using namespace std;

const int maxn = 1e6 + 6;

struct SAMNode { int ch[27], f, fa, sz, len; } nd[maxn];
int nd_cnt, lst;
void SAM_copy(SAMNode& from, SAMNode& to) {
    for (int i = 0; i < 26; i++) to.ch[i] = from.ch[i];
    to.fa = from.fa, to.len = from.len;
}
void SAM_init() { nd_cnt = lst = 1; }
void SAM_insert(int c) {
    int p = lst, np = lst = ++nd_cnt;
    nd[np].len = nd[p].len + 1;
    for (; p && !nd[p].ch[c]; p = nd[p].fa) nd[p].ch[c] = np;
    if (!p) nd[np].fa = 1;
    else {
        int v = nd[p].ch[c];
        if (nd[v].len == nd[p].len + 1) nd[np].fa = v;
        else {
            int nv = ++nd_cnt;
            SAM_copy(nd[v], nd[nv]), nd[nv].len = nd[p].len + 1;
            nd[v].fa = nd[np].fa = nv;
            for (; p && nd[p].ch[c] == v; p = nd[p].fa) nd[p].ch[c] = nv;
        }
    }
    nd[np].sz = 1;
}

int t, k, fl[maxn], ls[maxn], cnt[maxn];
void calc_sz_f() {
    for (int i = 1; i <= nd_cnt; i++) fl[nd[i].len]++;
    for (int i = 1; i <= nd_cnt; i++) fl[i] += fl[i - 1];
    for (int i = 1; i <= nd_cnt; i++) ls[fl[nd[i].len]--] = i;
    for (int i = nd_cnt; i >= 1; i--) nd[nd[ls[i]].fa].sz += nd[ls[i]].sz;
    for (int i = 1; i <= nd_cnt; i++) nd[i].f = (t ? nd[i].sz : (nd[i].sz = 1));
    nd[1].f = nd[1].sz = 0;
    for (int i = nd_cnt; i >= 1; i--) 
        for (int c = 0; c < 26; c++) nd[ls[i]].f += nd[nd[ls[i]].ch[c]].f;
}
void find_ans(int u) {
    if (k <= nd[u].sz) return ;
    k -= nd[u].sz;
    for (int c = 0; c < 26; c++) {
        int v = nd[u].ch[c];
        if (!v) continue;
        if (k <= nd[v].f) {
            putchar(c + 'a'), find_ans(v);
            return ;
        } else k -= nd[v].f;
    }
}

string str;
int main() {
    // freopen("test.in", "r", stdin);
    // freopen("test.out", "w", stdout);
    cin >> str >> t >> k;
    SAM_init();
    for (int i = 0; i < str.size(); i++) SAM_insert(str[i] - 'a');
    calc_sz_f();
    if (nd[1].f < k) printf("-1\n");
    else find_ans(1);
    return 0;
}