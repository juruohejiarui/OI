#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
#define LL long long

using namespace std;

const int maxn = 55, maxw = 5, maxm = 505, maxk = 205;
const LL INF = 1e18;

int N, M, K, T, logT;
LL c[maxn];

struct Matrix {
    int r, c;
    LL val[maxn * maxw][maxn * maxw];

    LL* operator[] (int index) { return val[index]; }
    void init(int R, int C) {
        r = R, c = C;
        for (int i = 1; i <= r; i++)
            for (int j = 1; j <= c; j++)
                val[i][j] = -INF;
    }
    friend Matrix operator * (Matrix& a, Matrix& b) {
        Matrix c; c.init(a.r, b.c);
        for (int k = 1; k <= a.c; k++)
            for (int i = 1; i <= c.r; i++)
                for (int j = 1; j <= c.c; j++)
                    c[i][j] = max(c[i][j], a[i][k] + b[k][j]);
        return c;
    }
} g[31], f, st;

struct Act {
    int t, x; LL y;
    friend bool operator < (Act a, Act b) {
        return a.t < b.t;
    }
} act[maxk];

void qpow(Matrix& matrix, int b) {
    for (int i = logT; i >= 0; i--) if (b & (1 << i))
        matrix = matrix * g[i];
}

int main() {
    // freopen("test.in", "r", stdin);
    // freopen("test.out", "w", stdout);
    scanf("%d%d%d%d", &N, &M, &T, &K);
    st.init(N * 5, N * 5);
    logT = log2(T);
    for (int i = 1; i <= N; i++) scanf("%lld", &c[i]);
    for (int i = 1; i <= N; i++)
        for (int w = 1; w < maxw; w++)
            st[i + N * (w - 1)][i + N * w] = 0;
    for (int i = 1; i <= M; i++) {
        int u, v, w; scanf("%d%d%d", &u, &v, &w);
        st[u + N * (w - 1)][v] = c[u];
    }
    for (int i = 1; i <= K; i++) scanf("%d%d%lld", &act[i].t, &act[i].x, &act[i].y);
    act[0].t = 0, act[0].x = 1, act[0].y = 0;
    act[K + 1].t = T, act[K + 1].x = 1, act[K + 1].y = 0;
    sort(act + 1, act + 1 + K);

    g[0] = st;
    for (int i = 1; i <= logT; i++) g[i] = g[i - 1] * g[i - 1];
    
    f.init(1, 5 * N), f[1][1] = 0;
    for (int i = 1; i <= K + 1; i++) {
        qpow(f, act[i].t - act[i - 1].t);
        f[1][act[i].x] += act[i].y;
    }
    LL ans = f[1][1] + c[1];
    printf("%lld\n", (ans < 0 ? -1 : ans));
    return 0;
}