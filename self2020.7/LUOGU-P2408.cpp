#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
#define LL long long

using namespace std;

const int maxn = 2e5 + 5;

struct SAMNode { int ch[27], len, fa; } nd[maxn];
int nd_cnt, lst;
void SAM_init() {
    lst = nd_cnt = 1, nd[1].len = 0;
}
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
            nd[nv] = nd[v], nd[nv].len = nd[p].len + 1;
            nd[v].fa = nd[np].fa = nv;
            for (; p && nd[p].ch[c] == v; p = nd[p].fa) nd[p].ch[c] = nv;
        }
    }
}
LL f[maxn];
void dfs(int u) {
    if (f[u]) return ;
    for (int i = 0; i < 26; i++) {
        int v = nd[u].ch[i];
        if (!v) continue;
        dfs(v), f[u] += f[v];
    }
    f[u]++;
}

string str;
int main() {
    // freopen("test.in", "r", stdin);
    // freopen("test.out", "w", stdout);
    int n; scanf("%d", &n);
    cin >> str;
    SAM_init();
    for (int i = 0; i < n; i++) SAM_insert(str[i] - 'a');
    dfs(1);
    printf("%lld\n", f[1] - 1);
    return 0;
}