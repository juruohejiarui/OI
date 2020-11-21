#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
#define D double

using namespace std;

const int maxn = 25;
const D eps = 1e-10;

int dcmp(D a, D b) {
    if (fabs(a - b) < eps) return 0;
    else if (a < b) return -1;
    else return 1;
}

struct Vector2 {
    D x, y, v, l;
    Vector2(D x = 0, D y = 0) : x(x), y(y) {}
    inline friend Vector2 operator - (Vector2 a, Vector2 b) {
        return Vector2(a.x - b.x, a.y - b.y);
    }
    inline friend D operator * (Vector2 a, Vector2 b) {
        return a.x * b.y - a.y * b.x; 
    }
    friend bool operator < (Vector2 a, Vector2 b) {
        return (a.x == b.x ? a.y < b.y : a.x < b.x);
    }
} p[maxn], a[maxn];

int p_sz, n, stk[maxn], tp;

D dist(Vector2 a, Vector2 b) {
    Vector2 c = a - b;
    return sqrt(c.x * c.x + c.y * c.y);
}
void find_hull(int n) {
    sort(p + 1, p + 1 + n);
    stk[1] = tp = 1;
    for (int i = 2; i <= n; i++) {
        while (tp > 1 && (p[stk[tp]]-p[stk[tp-1]]) * (p[i]-p[stk[tp-1]]) <= 0)
            tp--;
        stk[++tp] = i;
    }
    int tmp = tp;
    for (int i = n - 1; i >= 1; i--) {
        while (tp > tmp && (p[stk[tp]]-p[stk[tp-1]]) * (p[i]-p[stk[tp-1]]) <= 0)
            tp--;
        stk[++tp] = i;
    }
}

int T, S_ans, c_ans; 
D l_ans, v_ans;

void solve() {
    if (T) putchar('\n');
    T++, v_ans = 1e8, c_ans = 0;
    for (int i = 1; i <= n; i++)
        scanf("%lf%lf%lf%lf", &a[i].x, &a[i].y, &a[i].v, &a[i].l);
    for (int S = 1; S < (1 << n); S++) {
        p_sz = 0;
        D l_sum = 0, v_sum = 0;
        for (int i = 1; i <= n; i++) 
            if ((S >> (i - 1)) & 1) {
                l_sum += a[i].l, v_sum += a[i].v;
            } else p[++p_sz] = a[i];
        find_hull(p_sz);
        D used_l = 0;
        for (int i = 1; i < tp; i++) used_l += dist(p[stk[i]], p[stk[i + 1]]);
        if (dcmp(used_l, l_sum) > 0) continue;

        if (v_sum < v_ans || (v_sum == v_ans && p_sz > c_ans))
            l_ans = l_sum - used_l, v_ans = v_sum, c_ans = p_sz, S_ans = S;
    }
    printf("Forest %d\nCut these trees:", T);
    for (int i = 0; i < n; i++) if ((S_ans >> i) & 1) printf(" %d", i + 1);
    printf("\nExtra wood: %.2f\n", l_ans);
}

int main() {
    // freopen("test.in", "r", stdin);
    // freopen("test.out", "w", stdout);
    while (scanf("%d", &n) == 1 && n) solve();
    return 0;
}