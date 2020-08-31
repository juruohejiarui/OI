#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <stack>
#define LL long long

using namespace std;

const int maxn = 5e5 + 5;
struct Edge {
    int v, nex;
    Edge(int v = 0, int nex = 0) : v(v), nex(nex) {}
} E[maxn << 1];

int hd[maxn], tote;
void addedge(int u, int v) { 
    E[++tote] = Edge(v, hd[u]), hd[u] = tote;
    E[++tote] = Edge(u, hd[v]), hd[v] = tote;
}
char str[maxn];
int n, grd[maxn], mt[maxn];
LL cnt[maxn], f[maxn];
stack<int> stk;

void dfs(int u, int fa) {
    if (str[u] == '(')
        stk.push(u);
    else {
        if (!stk.empty()) {
            int l = stk.top(); stk.pop();
            cnt[u] = 1 + cnt[grd[l]];
            mt[u] = l;
        } else cnt[u] = 0;
    }
    f[u] = f[grd[u]] + cnt[u];
    for (int i = hd[u]; i; i = E[i].nex) {
        int v = E[i].v;
        if (v == fa) continue;
        dfs(v, u);
    }
    if (mt[u]) stk.push(mt[u]);
    if (str[u] == '(') stk.pop();
}

int main() {
    // freopen("test.in", "r", stdin);
    // freopen("test.out", "w", stdout);
    scanf("%d\n%s\n", &n, str + 1);
    for (int i = 2; i <= n; i++) 
        scanf("%d", &grd[i]), addedge(i, grd[i]);
    dfs(1, 0);
    LL ans = f[1];
    for (int i = 2; i <= n; i++) ans ^= i * f[i];
    printf("%lld\n", ans);
    return 0;
}