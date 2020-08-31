#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>

using namespace std;

const int maxn = 255;
struct Vector2 {
    int x, y, a, b;
    Vector2(int x = 0, int y = 0) : x(x), y(y) {}
    friend Vector2 operator - (Vector2 a, Vector2 b) {
        return Vector2(a.x - b.x, a.y - b.y);
    }
    friend int operator * (Vector2 a, Vector2 b) {
        return a.x * b.y - a.y * b.x;
    }
    friend bool operator < (Vector2 a, Vector2 b) {
        return a * b > 0;
    }
} p[maxn], l[maxn * maxn];

int n, l_cnt, ans, f[maxn];
int main() {
    // freopen("test.in", "r", stdin);
    // freopen("test.out", "w", stdout);
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d%d", &p[i].x, &p[i].y);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) {
            if (i == j) continue;
            l[++l_cnt] = p[j] - p[i];
            l[l_cnt].a = i, l[l_cnt].b = j;
        }
    sort(l + 1, l + 1 + l_cnt);
    
    for (int st = 1; st <= n; st++) {
        for (int i = 1; i <= n; i++) f[i] = -(n + 2);
        f[st] = 0;
        for (int i = 1; i <= l_cnt; i++) f[l[i].b] = max(f[l[i].b], f[l[i].a] + 1);
        ans = max(ans, f[st]);
    }
    printf("%d\n", ans);
    return 0;
}