#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
#define LL long long

using namespace std;

const int maxn = 2e5 + 5;

struct Node {
    LL val;
    int id;
    friend bool operator < (Node a, Node b) {
        return a.val > b.val;
    }
} nd[maxn];
struct Edge {
    int v, nex;
    Edge() {}
    Edge(int v, int nex) : v(v), nex(nex) {}
} E[maxn << 1];
int n, k, nd_cnt;
LL dep[maxn], sz[maxn], ans;
bool chosen[maxn];

int hd[maxn], tote;
void addedge(int u, int v) {
    E[++tote] = Edge(v, hd[u]), hd[u] = tote;
    E[++tote] = Edge(u, hd[v]), hd[v] = tote;
}

void dfs(int u, int fa) {
    sz[u] = 1;
    for (int i = hd[u]; i; i = E[i].nex) {
        int v = E[i].v;
        if (v == fa) continue;
        dep[v] = dep[u] + 1;
        dfs(v, u), sz[u] += sz[v];
    }
    nd[u].val = dep[u] - sz[u], nd[u].id = u;
}

void calc(int u, int fa) {
    if (chosen[u]) {
        ans += (dep[u] - 1) * sz[u];
        return ;
    }
    for (int i = hd[u]; i; i = E[i].nex) {
        int v = E[i].v;
        if (v == fa) continue;
        calc(v, u);
    }
}
int main() {
    // freopen("test.in", "r", stdin);
    // freopen("test.out", "w", stdout);
    scanf("%d%d", &n, &k);
    for (int i = 1; i < n; i++) {
        int u, v; scanf("%d%d", &u, &v);
        addedge(u, v);
    }
    dep[1] = 1;
    dfs(1, -1);
    sort(nd + 1, nd + 1 + n);
    for (int i = 1; i <= k; i++) chosen[nd[i].id] = true;
    calc(1, -1);
    printf("%lld\n", ans);
    return 0;
}