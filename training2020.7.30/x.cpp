#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
#define LL long long

using namespace std;

const int maxn = 4e6 + 5;
struct Edge {
    int v, nex;
    Edge(int v = 0, int nex = 0) : v(v), nex(nex) {}
} E[maxn << 1];

int hd[maxn], tote;
void addedge(int u, int v) { 
    E[++tote] = Edge(v, hd[u]), hd[u] = tote;
    E[++tote] = Edge(u, hd[v]), hd[v] = tote;
}
int ls_sz;
LL val[maxn], f[maxn], ls[maxn];

void dfs(int u, int fa) {
    int from = 0;
    for (int i = hd[u]; i; i = E[i].nex) {
        int v = E[i].v;
        if (v == fa) continue;
        dfs(v, u);
        if (f[v] < f[from]) ls[++ls_sz] = f[v];
        else {
            if (from) ls[++ls_sz] = f[from];
            from = v;
        }
    }
    f[u] = f[from] + val[u];
}

int main() {
    freopen("x.in", "r", stdin);
    freopen("x.out", "w", stdout);
    int n, K;
    scanf("%d%d%lld", &n, &K, &val[1]);
    for (LL i = 2; i <= n; i++) {
        val[i] = (val[i-1]*(LL)23333333+6666666ll)%1000000007ll;
        addedge((val[i] ^ (LL)23333333)%(LL)(i - 1) + 1ll, i);
    }
    dfs(1, 0), ls[++ls_sz] = f[1];
    sort(ls + 1, ls + 1 + ls_sz);
    LL ans = 0;
    for (int i = ls_sz; i >= max(1, ls_sz - K + 1); i--)
        ans += ls[i];
    printf("%lld\n", ans);
    return 0;
}