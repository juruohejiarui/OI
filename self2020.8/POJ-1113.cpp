#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
#define D double

using namespace std;

const int maxn = 1e3 + 5;
const D eps = 1e-10, pi = 3.14159265358979323846;
D dcmp(D a, D b) {
    if (fabs(a - b) < eps) return 0;
    if (a < b) return -1;
    else return 1;
}
struct Vector2 {
    D x, y;
    Vector2(D x = 0, D y = 0) : x(x), y(y) {}
    friend Vector2 operator - (Vector2 a, Vector2 b) {
        return Vector2(a.x - b.x, a.y - b.y);
    }
    friend D operator * (Vector2 a, Vector2 b) {
        return a.x * b.y - a.y * b.x;
    }
    friend bool operator == (Vector2 a, Vector2 b) {
        return !dcmp(a.x, b.x) && !dcmp(a.y, b.y);
    }
    friend bool operator < (Vector2 a, Vector2 b) {
        return (dcmp(a.x, b.x) < 0 || (!dcmp(a.x, b.x) && dcmp(a.y, b.y) < 0));
    }
} a[maxn], stk[maxn];
int n, tp; 
D R;
typedef Vector2 Point;
D dist(Point a, Point b) {
    Point c = a - b;
    return sqrt(c.x * c.x + c.y * c.y);
}

void find_hull() {
    sort(a + 1, a + 1 + n);
    stk[tp = 1] = a[1];
    for (int i = 2; i <= n; i++) {
        while (tp > 1 && (stk[tp]-stk[tp-1]) * (a[i]-stk[tp-1]) <= 0) 
            tp--;
        stk[++tp] = a[i];
    }
    int tmp = tp;
    for (int i = n - 1; i >= 1; i--) {
        while (tp > tmp && (stk[tp]-stk[tp-1]) * (a[i]-stk[tp-1]) <= 0)
            tp--;
        stk[++tp] = a[i];
    }
}
int main() {
    // freopen("test.in", "r", stdin);
    // freopen("test.out", "w", stdout);
    scanf("%d%lf", &n, &R);
    for (int i = 1; i <= n; i++) scanf("%lf%lf", &a[i].x, &a[i].y);
    find_hull();
    D ans = 0;
    for (int i = 1; i < tp; i++) ans += dist(stk[i], stk[i + 1]);
    ans += 2 * pi * R;
    printf("%.0lf\n", ans);
    return 0;
}