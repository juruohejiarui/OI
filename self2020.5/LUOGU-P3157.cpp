#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
#define LL long long

using namespace std;

const int maxn = 1e5 + 5, maxm = 5e4 + 5;
struct Data {
    int a, b, c, op, t, ans, id;
    Data() {}
    Data(int a, int b, int c, int t, int id)
        : a(a), b(b), c(c), t(t), id(id) {}
    friend bool operator == (Data a, Data b) {
        return a.a == b.a && b.a == b.b && a.c == b.c;
    }
} a[maxn + maxm];

bool cmp1(Data a, Data b) {
    return a.a != b.a ? a.a < b.a : (a.b != b.b ? a.b < b.b : a.c > b.c);
}
bool cmp2(Data a, Data b) {
    return a.b != b.b ? a.b < b.b : (a.a != b.a ? a.a < b.a : a.c > b.c);
}
int a_sz, ls[maxn], pos[maxn], n, m;

LL ans_ls[maxn + maxm], C[maxn];
#define lowbit(x) ((x) & -(x))
void add(int x, LL val) {
    for (; x <= n; x += lowbit(x)) C[x] += val;
}
int ask(int x) {
    int ret = 0;
    for (; x; x ^= lowbit(x)) ret += C[x];
    return ret;
}

void solve(int l, int r) {
    if (l == r) return ;
    int mid = (l + r) >> 1;
    solve(l, mid), solve(mid + 1, r);
    for (int i = l; i <= mid; i++) a[i].op = 1;
    for (int i = mid+1; i <= r; i++) a[i].op = 2;
    stable_sort(a + l, a + r + 1, cmp2);
    
    for (int i = l; i <= r; i++) {
        if (a[i].op == 1) add(a[i].c, a[i].t);
        else ans_ls[a[i].id] += a[i].t * (ask(n) - ask(a[i].c));
    }
    for (int i = l; i <= r; i++)
        if (a[i].op == 1) add(a[i].c, -a[i].t);

    for (int i = r; i >= l; i--) {
        if (a[i].op == 1) add(a[i].c, a[i].t);
        else ans_ls[a[i].id] += a[i].t * ask(a[i].c - 1);
    }
    for (int i = r; i >= l; i--)
        if (a[i].op == 1) add(a[i].c, -a[i].t);

    // for (int i = 1; i <= a_sz; i++) printf("%d ", ans_ls[i]);
    // putchar('\n');
}

int main() {
    // freopen("test.in", "r", stdin);
    // freopen("test.out", "w", stdout);
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &ls[i]);
        pos[ls[i]] = i;
        a[++a_sz] = Data(i, i, ls[i], 1, i);
    }
    for (int i = 1; i <= m; i++) {
        int ele; scanf("%d", &ele);
        a[++a_sz] = Data(i + n, pos[ele], ele, -1, n + i);
    }
    sort(a + 1, a + 1 + a_sz, cmp1);
    solve(1, a_sz);
    for (int i = 2; i <= a_sz; i++) ans_ls[i] += ans_ls[i-1];
    for (int i = n; i < n+m; i++) printf("%lld\n", ans_ls[i]);
    return 0;
}