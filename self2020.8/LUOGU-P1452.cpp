#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
#define D double

using namespace std;

const int maxn = 5e4 + 5;
struct Vector2 {
    D x, y;
    Vector2(D x = 0, D y = 0) : x(x), y(y) {}
    friend Vector2 operator + (Vector2 a, Vector2 b) {
        return Vector2(a.x + b.x, a.y + b.y);
    }
    friend Vector2 operator - (Vector2 a, Vector2 b) {
        return Vector2(a.x - b.x, a.y - b.y);
    }
    friend Vector2 operator / (Vector2 a, D b) {
        return Vector2(a.x / b, a.y / b);
    }
    friend int operator * (Vector2 a, Vector2 b) {
        return a.x * b.y - a.y * b.x;
    }
    friend bool operator < (Vector2 a, Vector2 b) {
        return (a.x == b.x ? a.y < b.y : a.x < b.x);
    }
} a[maxn], stk[maxn];

D dist(Vector2 a, Vector2 b) {
    Vector2 c = a - b;
    return c.x * c.x + c.y * c.y;
}

int n, p_sz, tp;

void find_hull() {
    sort(a + 1, a + 1 + n);
    stk[tp = 1] = a[1];
    for (int i = 2; i <= n; i++) {
        while (tp > 1 && (stk[tp] - stk[tp - 1]) * (a[i] - stk[tp - 1]) <= 0) 
            tp--;
        stk[++tp] = a[i];
    }
    int tmp = tp;
    for (int i = n - 1; i >= 1; i--) {
        while (tp > tmp && (stk[tp] - stk[tp - 1]) * (a[i] - stk[tp - 1]) <= 0)
            tp--;
        stk[++tp] = a[i];
    }
    p_sz = tp - 1;
}

Vector2 cc;
D diame;
void calc_circle() {
    diame = 0;
    if (p_sz == 2) {
        cc = (stk[1] + stk[2]) / 2;
        diame = dist(stk[1], stk[2]);
        return ;
    } 
    int to = 2;
    for (int i = 1; i <= p_sz; i++) {
        while ((stk[i+1]-stk[i])*(stk[to]-stk[i]) < (stk[i+1]-stk[i])*(stk[to+1]-stk[i]))
            to = to % p_sz + 1;
        if (diame < dist(stk[to], stk[i])) {
            diame = dist(stk[to], stk[i]);
            cc = (stk[to] + stk[i]) / 2;
        } 
        if (diame < dist(stk[to], stk[i+1])) {
            diame = dist(stk[to], stk[i+1]);
            cc = (stk[to] + stk[i+1]) / 2;
        }
    }
}
int main() {
    // freopen("test.in", "r", stdin);
    // freopen("test.out", "w", stdout);
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%lf%lf", &a[i].x, &a[i].y);
    find_hull();
    calc_circle();
    printf("%.0lf\n", diame);
    return 0;
}