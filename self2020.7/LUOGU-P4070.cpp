#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <map>

using namespace std;

const int maxn = 2e5 + 5;

struct SAMNode {
    int fa; long long len;
    map<int, int> ch;
} nd[maxn];
int nd_cnt, lst;
long long ans;
void SAM_init() { nd[nd_cnt = lst = 1].len = 0; }
void SAM_insert(int c) {
    int p = lst, np = lst = ++nd_cnt;
    nd[np].len = nd[p].len + 1;
    for (; p && !nd[p].ch.count(c); p = nd[p].fa) nd[p].ch[c] = np;
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
    ans += nd[np].len - nd[nd[np].fa].len;
}

int main() {
    // freopen("test.in", "r", stdin);
    // freopen("test.out", "w", stdout);
    int n; scanf("%d", &n);
    SAM_init();
    for (int i = 1; i <= n; i++) {
        int a; scanf("%d", &a);
        SAM_insert(a), printf("%lld\n", ans);
    }
    return 0;
}