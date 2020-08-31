#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <ctime>
#include <queue>

using namespace std;

const int maxn = 55, INF = 1e8;
const double delta = 0.99;

int n, m, k, is_alr[maxn], alr[maxn], cho[maxn], cho_sz, ans;
struct Edge {
    int v, w, nex;
    Edge() {}
    Edge(int v, int w, int nex) : v(v), w(w), nex(nex) {}
} E[maxn << 1];
int hd[maxn], tote;

void addedge(int u, int v, int w) {
    E[++tote] = Edge(v, w, hd[u]), hd[u] = tote;
    E[++tote] = Edge(u, w, hd[v]), hd[v] = tote;
}

int dist[maxn], vis[maxn];
priority_queue< pair<int, int> > q;

void dij() {
    for (int i = 1; i <= n; i++) vis[i] = 0, dist[i] = INF;
    while (!q.empty()) q.pop();
    for (int i = 1; i <= m; i++) q.push(make_pair(0, alr[i])), dist[alr[i]] = 0;
    for (int i = 1; i <= k; i++) q.push(make_pair(0, cho[i])), dist[cho[i]] = 0;

    while (!q.empty()) {
        int u = q.top().second;
        q.pop();
        if (vis[u]) continue;
        vis[u] = 1;
        for (int i = hd[u]; i; i = E[i].nex) {
            int v = E[i].v;
            if (dist[v] > dist[u] + E[i].w) {
                dist[v] = dist[u] + E[i].w;
                q.push(make_pair(-dist[v], v));
            }
        }
    }
}

int calc() {
    int ret = 0;
    dij();
    for (int i = 1; i <= n; i++) ret = max(ret, dist[i]);
    return ret;
}

void SA() {
    for (double T = 1e4; T > 1e-14; T *= delta) {
        int a = rand() % k + 1, b = rand() % (cho_sz - k) + 1;
        swap(cho[a], cho[k + b]);
        int t = calc(), del = t - ans;
        if (del < 0) ans = t;
        else if (exp(-del / T) * RAND_MAX <= rand()) swap(cho[a], cho[k + b]);
    }
}

int to[maxn];

int main() {
    srand(time(NULL)), srand(rand()), srand(rand());
    // freopen("test.in", "r", stdin);
    // freopen("test.out", "w", stdout);
    
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 1; i <= n; i++) scanf("%d", &to[i]), to[i]++;
    for (int i = 1; i <= n; i++) {
        int l; scanf("%d", &l);
        addedge(i, to[i], l);
    }
    for (int i = 1; i <= m; i++) {
        scanf("%d", &alr[i]), alr[i] += 1;
        is_alr[alr[i]] = 1;
    }
    dij(), ans = 0;
    for (int i = 1; i <= n; i++) ans = max(ans, dist[i]);
    if (!k) { printf("%d\n", ans); return 0; }
    for (int i = 1; i <= n; i++)
        if (!is_alr[i]) cho[++cho_sz] = i;
    if (m + k == n) {
        printf("%d\n", calc());
        return 0;
    }
    while ((double)clock() / 1000000 <= 0.6)  SA();
    printf("%d\n", ans);
    return 0;
}