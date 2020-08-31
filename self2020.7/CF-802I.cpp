#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
#define LL long long

using namespace std;

const int maxn = 2e5 + 5;
struct SAMNode { 
    int len, fa, ch[27]; 
    void init() { memset(ch, 0, sizeof(ch)), len = 0, fa = 0; }
} nd[maxn];
int lst, nd_cnt, cnt[maxn];
inline void SAM_init() { nd_cnt = lst = 1, nd[1].init(); } 
void SAM_insert(int c) {
    int p = lst, np = lst = ++nd_cnt;
    nd[np].init();
    cnt[np] = 1;
    nd[np].len = nd[p].len + 1;
    for (; p && !nd[p].ch[c]; p = nd[p].fa) nd[p].ch[c] = np;
    if (!p) nd[np].fa = 1;
    else {
        int v = nd[p].ch[c];
        if (nd[v].len == nd[p].len + 1) nd[np].fa = v;
        else {
            int nv = ++nd_cnt;
            cnt[nv] = 0;
            nd[nv] = nd[v], nd[nv].len = nd[p].len + 1;
            nd[v].fa = nd[np].fa = nv;
            for (; p && nd[p].ch[c] == v; p = nd[p].fa) nd[p].ch[c] = nv;
        }
    }
}
struct Edge {
    int v, nex;
    Edge(int v = 0, int nex = 0) : v(v), nex(nex) {}
} E[maxn << 1];
int hd[maxn], tote;
void G_addedge(int u, int v) {
    E[++tote] = Edge(v, hd[u]), hd[u] = tote;
    E[++tote] = Edge(u, hd[v]), hd[v] = tote;
}
void G_build() {
    tote = 0, memset(hd, 0, sizeof(hd));
    for (int i = 2; i <= nd_cnt; i++) G_addedge(nd[i].fa, i);
}
LL ans;
void G_dfs(int u, int fa) {
    for (int i = hd[u]; i; i = E[i].nex) {
        int v = E[i].v;
        if (v == fa) continue;
        G_dfs(v, u), cnt[u] += cnt[v];
    }
    ans += 1ll * (nd[u].len - nd[fa].len) * cnt[u] * cnt[u];
}

string str;
void solve() {
    ans = 0, SAM_init();
    cin >> str;
    for (int i = 0; i < str.size(); i++) SAM_insert(str[i] - 'a');
    G_build(), G_dfs(1, 0);
    printf("%lld\n", ans);
}

int main() {
    // freopen("test.in", "r", stdin);
    // freopen("test.out", "w", stdout);
    int T; scanf("%d", &T);
    while (T--) solve();
    return 0;
}