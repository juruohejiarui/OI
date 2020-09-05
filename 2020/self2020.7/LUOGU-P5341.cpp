#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>

using namespace std;

const int maxn = 2e5 + 5;

int n, K, poss;
struct SAMNode { 
    int ch[27], fa, len, cnt;
    void init() {
        for (int i = 0; i < 26; i++) ch[i] = 0;
        fa = len = cnt = 0;
    } 
} nd[maxn];
int nd_cnt, lst;
void SAM_copy(SAMNode& a, SAMNode& b) {
    for (int i = 0; i < 26; i++) b.ch[i] = a.ch[i];
    b.fa = a.fa, b.len = a.len;
}
void SAM_init() {
    nd[nd_cnt = lst = 1].init();
}
void SAM_insert(int c) {
    int p = lst, np = lst = ++nd_cnt;
    nd[np].init();
    nd[np].len = nd[p].len + 1;
    for (; p && !nd[p].ch[c]; p = nd[p].fa) nd[p].ch[c] = np;
    if (!p) nd[np].fa = 1;
    else {
        int v = nd[p].ch[c];
        if (nd[v].len == nd[p].len + 1) nd[np].fa = v;
        else {
            int nv = ++nd_cnt;
            nd[nv].init();
            SAM_copy(nd[v], nd[nv]), nd[nv].len = nd[p].len + 1;
            nd[v].fa = nd[np].fa = nv;
            for (; p && nd[p].ch[c] == v; p = nd[p].fa) nd[p].ch[c] = nv;
        }
    }
    nd[np].cnt = 1;
}
int C[maxn];
inline int lowbit(int x) { return x & -x; }
void TARR_init() {
    for (int i = 1; i <= n; i++) C[i] = 0;
}
int TARR_ask(int x) { 
    int ret = 0;
    for (; x; x -= lowbit(x)) ret += C[x];
    return ret;
}
void TARR_add(int x, int val) {
    for (; x <= n; x += lowbit(x)) C[x] += val;
}
struct Edge {
    int v, nex;
    Edge(int v = 0, int nex = 0) : v(v), nex(nex) {}
} E[maxn];
int hd[maxn], tote;
inline void G_addedge(int u, int v) {
    E[++tote] = Edge(v, hd[u]), hd[u] = tote;
}
void G_build() {
    memset(hd, 0, sizeof(hd)), tote = 0;
    for (int i = 2; i <= nd_cnt; i++) G_addedge(nd[i].fa, i);
}
void G_dfs(int u) {
    for (int i = hd[u]; i; i = E[i].nex) {
        int v = E[i].v;
        G_dfs(v), nd[u].cnt += nd[v].cnt;
    }
    if (u != 1 && nd[u].cnt == K) 
        TARR_add(nd[nd[u].fa].len + 1, nd[u].cnt),
        TARR_add(nd[u].len + 1, -nd[u].cnt),
        poss = 1;
}

string str;
void solve() {
    SAM_init(), TARR_init();
    cin >> str >> K;
    n = str.size(), poss = 0;
    for (int i = 0; i < str.size(); i++) SAM_insert(str[i] - 'a');
    G_build(), G_dfs(1);
    if (!poss) printf("-1\n");
    else {
        int ans = 0, mx_cnt = 0;
        for (int i = 1; i <= n; i++) {
            int cnt = TARR_ask(i);
            if (cnt >= mx_cnt) ans = i, mx_cnt = cnt;
        }
        printf("%d\n", ans);
    }
}
int main() {
    // freopen("test.in", "r", stdin);
    // freopen("test.out", "w", stdout);
    int T; scanf("%d", &T);
    while(T--) solve();
    return 0;
}