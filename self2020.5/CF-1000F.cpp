#pragma GCC optimize(3,"Ofast","inline")
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>

int read() {
    int m = 0;
    char ch = getchar();
    while ('0' > ch || '9' < ch) ch = getchar();
    while ('0' <= ch && ch <= '9') 
        m = (m << 3) + (m << 1) + ch - '0', ch = getchar();
    return m;
}

using namespace std;

const int maxn = 5e5 + 5;
int n, m, max_a, ans_ls[maxn], a[maxn], blg[maxn], blk_sz;
struct Query { int l, r, id; } q[maxn];
int stk[maxn], top, pos[maxn];
bool cmp(Query a, Query b) {
    if (blg[a.l] != blg[b.l]) return a.l < b.l;
    if ((blg[a.l] & 1) == 1) return a.r < b.r;
    else return a.r > b.r;
} 
int cnt[maxn];

void addv(int i) {
    int x = a[i];
    if (!cnt[x]) stk[++top] = x, pos[x] = top;
    else if (cnt[x] == 1) {
        if (stk[top] != x) pos[stk[top]] = pos[x], swap(stk[top], stk[pos[x]]);
        top--;
    }
    cnt[x]++;
}
void delv(int i) {
    int x = a[i];
    if (cnt[x] == 1) {
        if (stk[top] != x) pos[stk[top]] = pos[x], swap(stk[top], stk[pos[x]]);
        top--;
    } else if (cnt[x] == 2) stk[++top] = x, pos[x] = top;
    cnt[x]--;
}
int main() {
    // freopen("test.in", "r", stdin);
    // freopen("test.out", "w", stdout);
    n = read();
    for (int i = 1; i <= n; i++) a[i] = read();
    m = read();
    int block = sqrt(n);
    for (int i = 1; i <= n; i++) blg[i] = (i-1) / block + 1;
    for (int i = 1; i <= m; i++) q[i].l = read(), q[i].r = read(), q[i].id = i;
    sort(q + 1, q + 1 + m, cmp);
    int l = 1, r = 0;
    for (int i = 1; i <= m; i++) {
        while (l < q[i].l) delv(l), l++;
        while (l > q[i].l) l--, addv(l);
        while (r < q[i].r) r++, addv(r);
        while (r > q[i].r) delv(r), r--;
        ans_ls[q[i].id] = stk[top];
    }
    for (int i = 1; i <= m; i++) printf("%d\n", ans_ls[i]);
    return 0;
}