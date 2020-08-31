#include <iostream>
#include <cstring>
#include <cstdio>
#include <string>
#include <cmath>
#define LL long long

using namespace std;

const int maxn = 2e6 + 6;
inline int id(char ch) { return ch - 'a'; }
LL cnt[maxn];
struct SAMNode { int len, fa, ch[27]; } nd[maxn];
struct Edge {
    int v, nex;
    Edge(int v = 0, int nex = 0) : v(v), nex(nex) {}
} E[maxn << 1];

string str;
int hd[maxn], tote;
void addedge(int u, int v) {
    E[++tote] = Edge(v, hd[u]), hd[u] = tote;
    E[++tote] = Edge(u, hd[v]), hd[v] = tote;
}

int nd_cnt, lst;
void SAM_init() {
    lst = ++nd_cnt, nd[nd_cnt].len = 0;
}
void SAM_update(int c) {
    int p = lst, np = lst = ++nd_cnt;
    cnt[np] = 1;
    nd[np].len = nd[p].len + 1;
    for (; p && !nd[p].ch[c]; p = nd[p].fa) nd[p].ch[c] = np;
    if (!p) nd[np].fa = 1;
    else {
        int v = nd[p].ch[c];
        if (nd[v].len == nd[p].len + 1) nd[np].fa = v;
        else {
            int nv = ++nd_cnt;
            nd[nv] = nd[v]; nd[nv].len = nd[p].len + 1;
            nd[v].fa = nd[np].fa = nv;
            for (; p && nd[p].ch[c] == v; p = nd[p].fa) nd[p].ch[c] = nv;
        }
    }
}

LL ans;
void build_graph() {
    for (int i = 2; i <= nd_cnt; i++)
        addedge(nd[i].fa, i);
}

void dfs(int u, int fa) {
    for (int i = hd[u]; i; i = E[i].nex) {
        int v = E[i].v;
        if (v == fa) continue;
        dfs(v, u);
        cnt[u] += cnt[v];
    }
    if (cnt[u] > 1) ans = max(ans, cnt[u] * (LL)nd[u].len);
}

int main() {
    // freopen("test.in", "r", stdin);
    // freopen("test.out", "w", stdout);
    cin >> str;
    SAM_init();
    for (int i = 0; i < str.size(); i++) SAM_update(id(str[i]));
    build_graph();
    dfs(1, 0);
    printf("%lld\n", ans);
    return 0;
}