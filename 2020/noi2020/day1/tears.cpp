#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
#define LL long long

using namespace std;

const int maxn = 1e5 + 5, maxm = 2e5 + 5;

int read_int() {
    int t = 0, m = 1;
    char ch = getchar();
    while ('0' > ch || ch > '9') {
        if (ch == '-') m = -1;
        ch = getchar();
    }
    while ('0' <= ch && ch <= '9')
        t = (t << 3) + (t << 1) + ch - '0',
        ch = getchar();
    return t * m;
}

struct Rect {
    int c1, r1, c2, r2, id;
} rect[maxm];
int n, m, p[maxn];
int C[maxn];
#define lowbit(x) ((x) & -(x))
int ask(int x) {
    int ret = 0;
    for (; x; x -= lowbit(x)) ret = ret + C[x];
    return ret;
}
void add(int x, int val) {
    for (; x <= n; x += lowbit(x)) C[x] += val;
}

int blg[maxn]; LL ans[maxm];
bool cmp(Rect a, Rect b) {
    if (blg[a.r1] == blg[b.r1]) return a.r2 > b.r2;
    else return blg[a.r1] < blg[b.r1];
}

void solve_t1() {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j < i; j++) {
            if (p[j] > p[i]) continue;
            for (int k = 1; k <= m; k++) {
                if (rect[k].r1 <= j && i <= rect[k].r2
                 && rect[k].c1 <= min(p[i],p[j]) && max(p[i],p[j]) <= rect[k].c2)
                ans[k]++;
            }
        }
    }
    for (int i = 1; i <= m; i++) printf("%lld\n", ans[i]);
}

void solve_t2() {
    int blk = n / sqrt(m);
    for (int i = 1; i <= n; i++) blg[i] = (i-1) / blk + 1;
    sort(rect + 1, rect + 1 + m, cmp);
    int l = 1, r = 0; LL cnt = 0;
    for (int i = 1; i <= m; i++) {
        while (l < rect[i].r1) cnt -= ask(n) - ask(p[l]), add(p[l], -1), l++;
        while (l > rect[i].r1) l--, cnt += ask(n) - ask(p[l]), add(p[l], 1);
        while (r < rect[i].r2) r++, cnt += ask(p[r] - 1), add(p[r], 1);
        while (r > rect[i].r2) cnt -= ask(p[r] - 1), add(p[r], -1), r--;

        ans[rect[i].id] = cnt;
    }
    for (int i = 1; i <= m; i++) printf("%lld\n", ans[i]);
}
int main() {
    // freopen("test.in", "r", stdin);
    // freopen("test.out", "w", stdout);
    // freopen("tears.in", "r", stdin);
    // freopen("tears.out", "w", stdout);
    int t1 = 1, t2 = 1;
    n = read_int(), m = read_int();
    if (n > 10 || m > 10) t1 = 0;
    for (int i = 1; i <= n; i++)
        p[i] = read_int();
    for (int i = 1; i <= m; i++) {
        rect[i].r1 = read_int(), rect[i].r2 = read_int(), rect[i].c1 = read_int(), rect[i].c2 = read_int();
        rect[i].id = i;
        if (rect[i].c1 != 1 || rect[i].c2 != n) t2 = 0;
    }
    if (t2) solve_t2();
    else solve_t1();
    return 0;
}