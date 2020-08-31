#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>

using namespace std;

const int maxn = 1e5 + 5;
int blk_sz, n, m, k, blkid[maxn], a[maxn], S[maxn], cnt[maxn];
long long sum, ans[maxn];
struct Query { int l, r, id; } q[maxn];

bool cmp(Query a, Query b) {
    if (blkid[a.l] != blkid[b.l]) return a.l < b.l;
    return a.r > b.r;
}

void addv(int pos) { sum += cnt[S[pos] ^ k]; cnt[S[pos]]++; }
void delv(int pos) { cnt[S[pos]]--; sum -= cnt[S[pos] ^ k]; }

int main() {
    // freopen("test.in", "r", stdin);
    // freopen("test.out", "w", stdout);
    int l = 1, r = 0;
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]), S[i] = S[i-1] ^ a[i];
    for (int i = 1; i <= m; i++)
        scanf("%d%d", &q[i].l, &q[i].r), q[i].id = i, q[i].l--;
    blk_sz = n / sqrt(m);
    for (int i = 1; i <= n; i++) blkid[i] = (i-1) / blk_sz + 1;
    sort(q+1, q+1+m, cmp);
    for (int i = 1; i <= m; i++) {
        while (l < q[i].l) delv(l), l++; 
        while (l > q[i].l) l--, addv(l);
        while (r < q[i].r) r++, addv(r);
        while (r > q[i].r) delv(r), r--;
        ans[q[i].id] = sum;
    }
    for (int i = 1; i <= m; i++) printf("%lld\n", ans[i]);
    return 0;
}