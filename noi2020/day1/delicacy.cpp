#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
#include <cmath>
#define LL long long

using namespace std;

LL read_LL() {
    LL t = 0, m = 1; char ch = getchar();
    while ('0' > ch || ch > '9') {
        if (ch == '-') m = -1;
        ch = getchar();
    }
    while ('0' <= ch && ch <= '9') t = (t << 3) + (t << 1) + ch - '0', ch = getchar();
    return t * m;
}

const int maxn = 255, maxm = 505;
const LL INF = 1e17;

struct Edge {
    int v, w, nex;
    Edge(int v = 0, int w = 0, int nex = 0) : v(v), w(w), nex(nex) {}
} E[maxm << 1];
int hd[maxn], tote;

void addedge(int u, int v, int w) {
    E[++tote] = Edge(v, w, hd[u]), hd[u] = tote;
}
struct Act {
    int t, x; LL y;
    Act(int t = 0, int x = 0, LL y = 0) : t(t), x(x), y(y) {}
    friend bool operator < (Act a, Act b) {
        return a.t < b.t;
    }
}  act[205];
vector<Act> nd[maxn];
int N, M, K, a_sz;
LL c[3005], f[205], T;

struct Matrix {
    LL a[255][255];
    Matrix() {
        for (int i = 1; i <= a_sz; i++)
            for (int j = 1; j <= a_sz; j++)
                a[i][j] = -INF;
    }
    Matrix operator * (const Matrix& b) {
        Matrix c;
        for (int i = 1; i <= a_sz; i++)
            for (int j = 1; j <= a_sz; j++)
                for (int k = 1; k <= a_sz; k++) {
                    if (a[i][k] == -INF || b.a[k][j] == -INF) continue;
                    c.a[i][j] = max(c.a[i][j], a[i][k] + b.a[k][j]);
                }
        return c;
    }
} g;

Matrix matrix_qpow(int st, int b) {
    Matrix a = g, res; res.a[st][st] = 0;
    while (b) {
        if (b & 1) res = res * a;
        a = a * a, b >>= 1;
    }
    return res;
}

LL len[maxn], W[maxn];
void solve_t1() {
    LL sum_c = 0;
    for (int i = 1; i <= N; i++) 
        len[i % N + 1] = len[i] + W[i], sum_c += c[i];
    if (T % len[1]) { printf("-1\n"); return ; } 
    LL ans = sum_c * (T / len[1]) + c[1];

    for (int i = 0; i < nd[1].size(); i++) if (nd[1][i].t % len[1] == 0)
        ans += nd[1][i].y;
    for (int i = 2; i <= N; i++) {
        for (int j = 0; j < nd[i].size(); j++)
            if (nd[i][j].t % len[1] == len[i]) ans += nd[i][j].y;
    }
    printf("%lld\n", ans);
}

namespace SubTask1 {
    int tchk[maxn]; LL f[52505][maxn];
    void solve() {
        for (int i = 1; i <= N; i++) sort(nd[i].begin(), nd[i].end());
        for (int t = 0; t <= T; t++)
            for (int u = 1; u <= N; u++) f[t][u] = -INF;
        f[0][1] = c[1];
        if (nd[1].size() && nd[1][0].t == 0) f[0][1] += nd[1][0].t;
        for (int t = 1; t <= T; t++) {
            for (int i = 1; i <= N; i++) {
                while (tchk[i] < nd[i].size() && nd[i][tchk[i]].t < t)
                    tchk[i]++;
            }
            for (int u = 1; u <= N; u++) {
                LL w = c[u];
                if (tchk[u] < nd[u].size() && nd[u][tchk[u]].t == t)
                    w += nd[u][tchk[u]].y;
                for (int i = hd[u]; i; i = E[i].nex) {
                    if (t < E[i].w) continue;
                    int v = E[i].v;
                    if (f[t - E[i].w][v] == -INF) continue;
                    f[t][u] = max(f[t][u], f[t - E[i].w][v] + w);
                }
            }
        }
        if (f[T][1] < 0) printf("-1\n");
        else printf("%lld\n", f[T][1]);
    }
}

int main() {
    // freopen("test.in", "r", stdin);
    // freopen("test.out", "w", stdout);
    // freopen("delicacy.in", "r", stdin);
    // freopen("delicacy.out", "w", stdout);
    N = read_LL(), M = read_LL(), T = read_LL(), K = read_LL();
    int t1 = 1;
    a_sz = N;
    for (int i = 1; i <= N + 4 * M; i++)
        for (int j = 1; j <= N + 4 * M; j++)
            g.a[i][j] = -INF;
    for (int i = 1; i <= N; i++) c[i] = read_LL();
    for (int i = 1; i <= M; i++) {
        int u, v, w;
        u = read_LL(), v = read_LL(), w = read_LL();
        int lst = u;
        W[u] = w, addedge(v, u, w);
        if (u != i || v != i % N + 1) t1 = 0;
        for (int j = 1; j < w; j++) {
            a_sz++;
            g.a[lst][a_sz] = c[lst], lst = a_sz;
        }
        g.a[lst][v] = c[lst];
    }
    
    for (int i = 1; i <= K; i++)
        act[i].t = read_LL(), act[i].x = read_LL(), act[i].y = read_LL(),
        nd[act[i].x].push_back(Act(act[i].t, 0, act[i].y));
    if (t1) {
        solve_t1(); return 0;
    }
    if (T <= 52501) {
        SubTask1::solve();
        return 0;
    }
    sort(act + 1, act + 1 + K);
    act[0].t = 0, act[0].x = 1, act[0].y = 0;
    act[K + 1].t = T, act[K + 1].x = 1, act[K + 1].y = 0;
    for (int i = 1; i <= K + 1; i++) {
        f[i] = -INF;
        for (int j = 0; j < i; j++) {
            if (f[j] == -INF) continue;
            Matrix res = matrix_qpow(act[j].x, act[i].t - act[j].t);
            if (res.a[act[j].x][act[i].x] == -INF) continue;
            f[i] = max(f[i], f[j] + act[j].y + res.a[act[j].x][act[i].x]);
        }
    }
    if (f[K + 1] == -INF) printf("-1\n");
    else printf("%lld\n", f[K + 1] + c[1]);
    return 0;
}