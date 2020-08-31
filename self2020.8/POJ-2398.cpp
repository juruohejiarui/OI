#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
#define LL long long

using namespace std;

const int maxn = 1e3 + 5;
struct Point {
    LL x, y;
    Point(LL x = 0, LL y = 0) : x(x), y(y) {}
} p[maxn];
struct Line {
    LL U, L;
    friend bool operator < (Line a, Line b) { return a.U < b.U; }
} line[maxn];

inline Point operator - (Point a, Point b) { return Point(a.x - b.x, a.y - b.y); }
inline LL cross(Point a, Point b) { return a.x * b.y - a.y * b.x; }

int n, m, T;
LL X1, Y1, X2, Y2, cnt[maxn];


bool check(int lid, int pid) {
    Point a(line[lid].U, Y1), b(line[lid].L, Y2);
    return cross(p[pid] - b, a - b) > 0;
}

void solve() {
    memset(cnt, 0, sizeof(cnt));
    scanf("%d%lld%lld%lld%lld", &m, &X1, &Y1, &X2, &Y2);
    for (int i = 2; i <= n + 1; i++) scanf("%lld%lld", &line[i].U, &line[i].L);
    line[1].U = X1, line[1].L = X1;
    sort(line + 1, line + 2 + n);
    for (int i = 1; i <= m; i++) {
        scanf("%lld%lld", &p[i].x, &p[i].y);
        if (p[i].x > X2 || p[i].x < X1 || p[i].y > Y1 || p[i].y < Y2) continue;
        int l = 1, r = n + 1, ans = 0;
        while (l <= r) {
            int mid = (l + r) >> 1;
            if (check(mid, i)) ans = mid, l = mid + 1;
            else r = mid - 1;
        }
        cnt[ans]++;
    }
    printf("Box\n");
    for (int i = 1; i <= m; i++) {
        int ans = 0;
        for (int j = 1; j <= n + 1; j++) ans += (cnt[j] == i);
        if (ans) printf("%d: %d\n", i, ans);
    }
}
int main() {
    // freopen("test.in", "r", stdin);
    // freopen("test.out", "w", stdout);
    while (scanf("%d", &n), n) solve();
    return 0;
}