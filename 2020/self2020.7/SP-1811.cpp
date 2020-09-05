#include <iostream>
#include <cstring>
#include <cstdio>
#include <string>
#include <cmath>

using namespace std;

const int maxn = 1e6 + 5;
struct SAMNode {
    int ch[27], fa, cnt[2], len;
} nd[maxn];
int nd_cnt, lst;

void SAM_copy(SAMNode& from, SAMNode& to) {
    for (int i = 0; i <= 26; i++) to.ch[i] = from.ch[i];
    to.fa = from.fa, to.len = from.len;
    to.cnt[0] = to.cnt[1] = 0;
}
void SAM_init() { nd_cnt = lst = 1; }
void SAM_insert(int c, int id) {
    int p = lst, np = lst = ++nd_cnt;
    nd[np].len = nd[p].len + 1;
    for (; p && !nd[p].ch[c]; p = nd[p].fa) nd[p].ch[c] = np;
    if (!p) nd[np].fa = 1;
    else {
        int v = nd[p].ch[c];
        if (nd[p].len + 1 == nd[v].len) nd[np].fa = v;
        else {
            int nv = ++nd_cnt;
            SAM_copy(nd[v], nd[nv]), nd[nv].len = nd[p].len + 1;
            nd[v].fa = nd[np].fa = nv;
            for (; p && nd[p].ch[c] == v; p = nd[p].fa) nd[p].ch[c] = nv;
        }
    }
    if (id < 2) nd[np].cnt[id] = 1;
}

struct Edge {
    int v, nex;
    Edge(int v = 0, int nex = 0) : v(v), nex(nex) {}
} E[maxn << 1];
int ans, hd[maxn], tote;
void G_addedge(int u, int v) {
    E[++tote] = Edge(v, hd[u]), hd[u] = tote;
    E[++tote] = Edge(u, hd[v]), hd[v] = tote;
} 
void G_build() {
    for (int i = 2; i <= nd_cnt; i++) G_addedge(nd[i].fa, i);
}
void G_dfs(int u, int fa) {
    for (int i = hd[u]; i; i = E[i].nex) {
        int v = E[i].v;
        if (v == fa) continue;
        G_dfs(v, u);
        nd[u].cnt[0] += nd[v].cnt[0];
        nd[u].cnt[1] += nd[v].cnt[1];
    }
    if (nd[u].cnt[0] && nd[u].cnt[1]) ans = max(ans, nd[u].len);
}
string str;
int main() {
    // freopen("test.in", "r", stdin);
    // freopen("test.out", "w", stdout);
    SAM_init();
    cin >> str;
    for (int i = 0; i < str.size(); i++) SAM_insert(str[i] - 'a', 0);
    SAM_insert(26, 2);
    cin >> str;
    for (int i = 0; i < str.size(); i++) SAM_insert(str[i] - 'a', 1);
    G_build(), G_dfs(1, 0);
    printf("%d\n", ans);
    return 0;
}