#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
#include <cmath>
#include <queue>
#define LL long long

using namespace std;

const int maxn = 1e3 + 5, maxm = 3e3 + 5;
const LL MOD = 998244353;

int n, m, k;
struct Team {
    int id, x, y;
    Team(int id, int x, int y) : id(id), x(x), y(y) {}
};
vector<Team> py[maxn];
struct Edge {
    int v, nex;
    Edge(int v = 0, int nex = 0) : v(v), nex(nex) {}
} E[maxm << 1];

int hd[maxn], tote;
void addedge(int u, int v) {
    E[++tote] = Edge(v, hd[u]), hd[u] = tote;
    E[++tote] = Edge(u, hd[v]), hd[v] = tote;
}

LL qpow(LL a, LL b) {
    LL ret = 1;
    while (b) {
        if (b & 1) ret = ret * a % MOD;
        b >>= 1, a = a * a % MOD;
    }
    return ret;
}

inline LL inv(LL a) { return qpow(a, MOD - 2); }

LL f[maxn][maxn], g[maxn][maxn], p1[maxn], p2[maxn];
int dis[maxn][maxn], vis[maxn];
queue<int> q;

void calc_dis(int st) {
    for (int i = 1; i <= n; i++) 
        dis[st][i] = vis[i] = 0;
    q.push(st), vis[st] = 1, dis[st][st] = 0;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int i = hd[u]; i; i = E[i].nex) {
            int v = E[i].v;
            if (vis[v]) continue;
            vis[v] = 1, q.push(v), dis[st][v] = dis[st][u] + 1;
        }
    }
}

void calc_f(Team t) {
    for (int i = 1; i <= n; i++) f[t.id][i] = vis[i] = 0;
    q.push(t.x), f[t.id][t.x] = 1, vis[t.x] = 1;
    while (!q.empty()) {
        int u = q.front(), deg = 0; q.pop();
        for (int i = hd[u]; i; i = E[i].nex) {
            int v = E[i].v;
            if (dis[t.x][v] == dis[t.x][u] + 1 && dis[t.x][v] + dis[v][t.y] == dis[t.x][t.y]) {
                deg++;
                if (!vis[v]) vis[v] = 1, q.push(v);
            }
        }
        for (int i = hd[u]; i; i = E[i].nex) {
            int v = E[i].v;
            if (dis[t.x][v] == dis[t.x][u] + 1 && dis[t.x][v] + dis[v][t.y] == dis[t.x][t.y]) {
                f[t.id][v] = (f[t.id][v] + f[t.id][u] * inv(deg) % MOD) % MOD;
            }
        }
    }
    // printf("calc_f(%d, %d, %d) : ", t.id, t.x, t.y);
    // for (int i = 1; i <= n; i++) printf("%lld ", f[t.id][i]);
    // putchar('\n');
}

void solve() {
    memset(hd, 0, sizeof(hd)), tote = 0;
    for (int i = 1; i <= k; i++) py[i].clear();
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 1; i <= m; i++) {
        int u, v, w; scanf("%d%d%d", &u, &v, &w);
        addedge(u, v);
    }
    for (int i = 1; i <= k; i++) {
        int c, x, y;
        scanf("%d%d%d", &c, &x, &y);
        py[c].push_back(Team(i, x, y));
    }
    for (int i = 1; i <= n; i++) calc_dis(i);
    for (int id = 1; id <= n; id++) {
        for (int i = 0; i < py[id].size(); i++) 
            calc_f(py[id][i]);
    }
    for (int u = 1; u <= n; u++) {
        for (int id = 1; id <= k; id++) {
            g[u][id] = 1;
            for (int i = 0; i < py[id].size(); i++) {
                Team& t = py[id][i];
                g[u][id] = g[u][id] * (1 - f[py[id][i].id][u] + MOD) % MOD;
            }
            // printf("g[%d,%d]=%lld ", u, id, g[u][id]);
        }
        // putchar('\n');
    }
    for (int u = 1; u <= n; u++) {
        p1[0] = p2[k + 1] = 1;
        LL p3 = 0;
        for (int i = 1; i <= k; i++) p1[i] = p1[i - 1] * g[u][i] % MOD;
        for (int i = k; i >= 1; i--) p2[i] = p2[i + 1] * g[u][i] % MOD;
        for (int i = 1; i <= k; i++) 
            p3 = (p3 + p1[i - 1] * p2[i + 1] % MOD * (1 - g[u][i] + MOD) % MOD) % MOD;
        printf("%lld\n", ((1 - p1[k] + MOD) % MOD - p3 + MOD) % MOD);
    }
}

int main() {
    // freopen("test.in", "r", stdin);
    // freopen("test.out", "w", stdout);
    int T; scanf("%d", &T);
    while (T--) solve();
    return 0;
}