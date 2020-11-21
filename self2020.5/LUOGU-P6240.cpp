#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
#define LL long long

using namespace std;

const int maxn = 4e4 + 5, maxm = 2e5 + 5, maxh = 205;

struct Query {
    int l, r, t;
} q[maxm];
int n, m, h[maxn], ls1[maxm], ls2[maxm];
LL ans_ls[maxm], w[maxn], f[maxn][maxh];

void solve(int l, int r, int tl, int tr) {
    if (tl > tr || l > r) return ;
    int mid = (l + r) >> 1, ls1_p = tl - 1;
    for (int i = 0; i <= 200; i++) f[mid][i] = 0;
    for (int i = mid + 1; i <= r; i++) {
        for (int j = 0; j < h[i]; j++) f[i][j] = f[i-1][j];
        for (int j = h[i]; j <= 200; j++)
            f[i][j] = max(f[i-1][j], f[i-1][j-h[i]] + w[i]);
    }
    f[mid][h[mid]] = w[mid];
    for (int i = mid - 1; i >= l; i--) {
        for (int j = 0; j < h[i]; j++) f[i][j] = f[i+1][j];
        for (int j = h[i]; j <= 200; j++)
            f[i][j] = max(f[i+1][j], f[i+1][j-h[i]] + w[i]);
    }
    int ls2_sz = 0;
    for (int i = tl; i <= tr; i++) {
        int id = ls1[i];
        if (q[id].l > mid) ls2[++ls2_sz] = id;
        else if (q[id].r <= mid) ls1[++ls1_p] = id;
        else {
            ans_ls[id] = 0;
            for (int j = 0; j <= q[id].t; j++)
                ans_ls[id] = max(ans_ls[id], f[q[id].l][j] + f[q[id].r][q[id].t - j]);
        }
    }
    for (int i = 1; i <= ls2_sz; i++) ls1[ls1_p + i] = ls2[i];
    tr = ls1_p + ls2_sz;
    solve(l, mid, tl, ls1_p), solve(mid + 1, r, ls1_p + 1, tr);
}

int main() {
    // freopen("test.in", "r", stdin);
    // freopen("test.out", "w", stdout);
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%d", &h[i]);
    for (int i = 1; i <= n; i++) scanf("%lld", &w[i]);

    int ls1_sz = 0;
    for (int i = 1; i <= m; i++) {
        scanf("%d%d%d", &q[i].l, &q[i].r, &q[i].t);
        if (q[i].l == q[i].r) {
            ans_ls[i] = (q[i].t >= h[q[i].l] ? w[q[i].l] : 0);
        } else ls1[++ls1_sz] = i;
    }
    solve(1, n, 1, ls1_sz);
    for (int i = 1; i <= m; i++) printf("%lld\n", ans_ls[i]);
    return 0;
}