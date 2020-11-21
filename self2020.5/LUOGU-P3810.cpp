#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>

using namespace std;

const int maxn = 1e5 + 5, maxm = 2e5 + 5;

int n, k, ans_ls[maxn];
struct Data {
    int a, b, c, op, ans;
    friend bool operator == (Data a, Data b) {
        return a.a == b.a && a.b == b.b && a.c == b.c;
    }
} a[maxn];

bool cmp1(Data a, Data b) { return (a.a != b.a ? a.a<b.a : (a.b != b.b ? a.b<b.b : a.c<b.c)); }
bool cmp2(Data a, Data b) { return (a.b != b.b ? a.b<b.b : (a.a != b.a ? a.a<b.a : a.c<b.c)); }

int C[maxm];
#define lowbit(x) ((x) & -(x))
void trarr_add(int x, int val) {
    for (; x <= k; x += lowbit(x)) C[x] += val;
}
int trarr_ask(int x) {
    int ret = 0;
    for (; x; x ^= lowbit(x)) ret += C[x];
    return ret;
}
void trarr_clr(int x) {
    for (; x <= k; x += lowbit(x)) C[x] = 0; 
}

void solve(int l, int r) {
    if (l == r) return ;
    int mid = (l + r) >> 1;
    solve(l, mid), solve(mid + 1, r);
    for (int i = l; i <= mid; i++) a[i].op = 1;
    for (int i = mid+1; i <= r; i++) a[i].op = 2;

    stable_sort(a + l, a + r + 1, cmp2);
    for (int i = l; i <= r; i++) {
        if (a[i].op == 1) trarr_add(a[i].c, 1);
        else a[i].ans += trarr_ask(a[i].c);
    }

    for (int i = l; i <= r; i++)
        if (a[i].op == 1) trarr_clr(a[i].c);
}

int main() {
    // freopen("test.in", "r", stdin);
    // freopen("test.out", "w", stdout);
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++) 
        scanf("%d%d%d", &a[i].a, &a[i].b, &a[i].c);
    sort(a + 1, a + 1 + n, cmp1);
    for (int i = n - 1; i; i--)
        if (a[i+1] == a[i])
            a[i].ans = a[i+1].ans + 1;
    solve(1, n);
    for (int i = 1; i <= n; i++) ans_ls[a[i].ans]++;
    for (int i = 0; i < n; i++) printf("%d\n", ans_ls[i]);
    return 0;
}