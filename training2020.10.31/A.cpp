#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <queue>
#define LL long long

using namespace std;

const int maxn = 3e3 + 5, maxk = 1e6 + 5;
const LL INF = 1e18;
int n, m, k;
LL v0, s1[maxn], s2[maxn], a[maxn][maxn];
struct ele {
    LL val, c; int id;
    ele(LL val, LL c, int id) : val(val), c(c), id(id) {}
    friend bool operator < (ele a, ele b) {
        return a.val < b.val;
    }
};

priority_queue<ele> q;

LL v1[maxk], v2[maxk];
int main() {
    // freopen("test.in", "r", stdin);
    // freopen("test.out", "w", stdout);
    scanf("%d%d%d%lld", &n, &m, &k, &v0);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            scanf("%lld", &a[i][j]), s1[i] += a[i][j], s2[j] += a[i][j];
    
    for (int i = 1; i <= n; i++) q.push(ele(s1[i], 1, i));
    for (int i = 1; i <= k; i++) {
        ele tp = q.top();
        v1[i] = v1[i - 1] + tp.val, q.pop();
        q.push(ele(tp.val - v0 * m, tp.c + 1, tp.id));
    }
    // for (int i = 0; i <= k; i++) printf("%lld ", v1[i]);
    // putchar('\n');
    while (!q.empty()) q.pop();
    for (int i = 1; i <= m; i++) q.push(ele(s2[i], 1, i));
    for (int i = 1; i <= k; i++) {
        ele tp = q.top();
        v2[i] = v2[i - 1] + tp.val, q.pop();
        q.push(ele(tp.val - v0 * n, tp.c + 1, tp.id));
    }
    // for (int i = 0; i <= k; i++) printf("%lld ", v2[i]);
    // putchar('\n');
    LL ans = -INF;
    for (int i = 0; i <= k; i++) ans = max(ans, v1[i] + v2[k - i] - v0 * i * (k - i));
    printf("%lld\n", ans);
    return 0;
}