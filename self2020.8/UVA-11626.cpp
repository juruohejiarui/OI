#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
#define LL long long

using namespace std;

const int maxn = 1e5 + 5;
struct Vector2 {
    LL x, y;
    Vector2(LL x = 0, LL y = 0) : x(x), y(y) {}
    inline friend Vector2 operator - (Vector2 a, Vector2 b) {
        return Vector2(a.x - b.x, a.y - b.y);
    }
    inline friend LL operator * (Vector2 a, Vector2 b) {
        return a.x * b.y - a.y * b.x;
    }
    friend bool operator < (Vector2 a, Vector2 b) {
        if (a.x != b.x) return a.x < b.x;
        else return a.y < b.y;
    }
};
#define Point Vector2 
int n;
Point p[maxn];

inline LL squ(LL a) { return a * a; }
inline LL dist(Point a, Point b) { return squ(a.x - b.x) + squ(a.y - b.y); }

int stk[maxn], stk_tp, used[maxn];
void solve() {
    scanf("%d", &n);
    char ch;
    for (int i = 1; i <= n; i++) cin >> p[i].x >> p[i].y >> ch;
    sort(p + 1, p + 1 + n);
    stk[1] = stk_tp = 1; 
    for (int i = 2; i <= n; i++) {
        while (stk_tp > 1 && (p[stk[stk_tp]] - p[stk[stk_tp - 1]]) * (p[i] - p[stk[stk_tp]]) < 0)
            used[stk[stk_tp]] = 0, stk_tp--;
        stk[++stk_tp] = i, used[i] = 1;
    }
    int tmp = stk_tp;
    for (int i = n - 1; i >= 1; i--) if (!used[i]) {
        while (stk_tp > tmp && (p[stk[stk_tp]] - p[stk[stk_tp - 1]]) * (p[i] - p[stk[stk_tp]]) < 0)
            stk_tp--;
        stk[++stk_tp] = i;
    }

    printf("%d\n", stk_tp - 1);
    for (int i = 1; i < stk_tp; i++)
        printf("%lld %lld\n", p[stk[i]].x, p[stk[i]].y), used[stk[i]] = 0;
}

int main() {
    // freopen("test.in", "r", stdin);
    // freopen("test.out", "w", stdout);
    int T; scanf("%d", &T);
    while (T--) solve();
    return 0;
}