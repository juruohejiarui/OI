#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
#define LL long long

using namespace std;

const int maxn = 5e4 + 5;
struct Query {
    int l, r, id, arg;
    Query(int _l, int _r, int _id, int _arg) {
        if (_l > _r) swap(_l, _r);
        l = _l, r = _r, id = _id, arg = _arg;
    }
    Query() {}
} q[maxn << 2];

int n, m, qsz, blg[maxn];
LL ans_ls[maxn], a[maxn], cntl[maxn], cntr[maxn], sum;

bool cmp(Query a, Query b) {
    if (blg[a.l] != blg[b.l]) return a.l < b.l;
    return a.r < b.r;
}
int change_l(int fl, int i) {
    if (fl == 1) return cntl[a[i+1]]++, sum += cntr[a[i+1]], i + 1;
    else return cntl[a[i]]--, sum -= cntr[a[i]], i - 1;
}
int change_r(int fl, int i) {
    if (fl == 1) return cntr[a[i+1]]++, sum += cntl[a[i+1]], i + 1;
    else return cntr[a[i]]--, sum -= cntl[a[i]], i - 1;
}

int main() {
    // freopen("test.in", "r", stdin);
    // freopen("test.out", "w", stdout);
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%lld", &a[i]);
    scanf("%d", &m);
    for (int i = 1; i <= m; i++) {
        int l1, r1, l2, r2; scanf("%d%d%d%d", &l1, &r1, &l2, &r2);
        q[++qsz] = Query(r1, r2, i, 1);
        q[++qsz] = Query(l1-1, r2, i, -1);
        q[++qsz] = Query(r1, l2-1, i, -1);
        q[++qsz] = Query(l1-1, l2-1, i, 1);
    }
    
    int blk = sqrt(n);
    for (int i = 1; i <= n; i++) blg[i] = i / blk + 1;
    sort(q + 1, q + 1 + qsz, cmp);
    // for (int i = 1; i <= qsz; i++) 
        // printf("{%d,%d,%d,%d}\n", q[i].l, q[i].r, q[i].id, q[i].arg);
    int l = 0, r = 0;
    for (int i = 1; i <= qsz; i++) {
        while (q[i].l > l) l = change_l(1, l);
        while (q[i].l < l) l = change_l(-1, l);
        while (q[i].r > r) r = change_r(1, r);
        while (q[i].r < r) r = change_r(-1, r);

        ans_ls[q[i].id] += q[i].arg * sum;
    }
    for (int i = 1; i <= m; i++) printf("%lld\n", ans_ls[i]);
    return 0;
}