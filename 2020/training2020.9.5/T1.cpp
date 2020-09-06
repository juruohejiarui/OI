#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
#define LL long long

using namespace std;

const int maxn = 2e5 + 5;
struct Plan {
    LL a, b;
    friend bool operator < (Plan a, Plan b) {
        return a.a < b.a;
    }
} p[maxn];
int n, m;
LL s1[maxn], s2[maxn], c[maxn];

struct STNode {
    LL sum1, sum2, tag1 /*增长*/, tag0 /*清空*/;
    #define LS(o) o << 1
    #define RS(o) o << 1 | 1
} nd[maxn << 1];

void pushdown(int o, int l, int r) {
    if (nd[o].tag0) {
        nd[LS(o)].tag0 = nd[RS(o)].tag0 = 1;
        nd[LS(o)].sum1 = nd[RS(o)].sum1 = nd[LS(o)].sum2 = nd[RS(o)].sum2 = 0;
        nd[LS(o)].tag1 = nd[RS(o)].tag1 = 0;
        nd[o].tag0 = 0;
    } 
    int mid = (l + r) >> 1;
    nd[LS(o)].tag1 += nd[o].tag1, nd[RS(o)].tag1 += nd[o].tag1;
    nd[LS(o)].sum1 += nd[o].tag1 * (s1[mid] - s1[l - 1]);
    nd[RS(o)].sum1 += nd[o].tag1 * (s1[r] - s1[mid]);
    nd[LS(o)].sum2 += nd[o].tag1 * (s2[mid] - s2[l - 1]);
    nd[RS(o)].sum2 += nd[o].tag1 * (s2[r] - s2[mid]);
    nd[o].tag1 = 0;
}

inline void pushup(int o) {
    nd[o].sum1 = nd[LS(o)].sum1 + nd[RS(o)].sum1;
    nd[o].sum2 = nd[LS(o)].sum2 + nd[RS(o)].sum2;
}

void change_setzero(int o, int l, int r, int ql, int qr) {
    if (ql > r || qr < l) return ;
    if (ql <= l && r <= qr) {
        nd[o].sum1 = nd[o].sum2 = nd[o].tag1 = 0, nd[o].tag0 = 1;
        return ;
    }
    pushdown(o, l, r);
    int mid = (l + r) >> 1;
    change_setzero(LS(o), l, mid, ql, qr);
    change_setzero(RS(o), mid + 1, r, ql, qr);
    pushup(o);
}

void change_add(int o, int l, int r, int ql, int qr) {
    if (ql > r || qr < l) return ;
    if (ql <= l && r <= qr) {
        nd[o].sum1 += s1[r] - s1[l - 1], nd[o].sum2 += s2[r] - s2[l - 1];
        nd[o].tag1++;
        return ;
    }
    pushdown(o, l, r);
    int mid = (l + r) >> 1;
    change_add(LS(o), l, mid, ql, qr);
    change_add(RS(o), mid + 1, r, ql, qr);
    pushup(o);
}

void change_single(int o, int l, int r, int pl, int val) {
    if (l == r) {
        nd[o].sum1 -= val, nd[o].sum2 -= val * p[l].a;
        return ;
    }
    pushdown(o, l, r);
    int mid = (l + r) >> 1;
    if (pl <= mid) change_single(LS(o), l, mid, pl, val);
    else change_single(RS(o), mid + 1, r, pl, val);
    pushup(o);
}

LL query_sum(int o, int l, int r, int ql, int qr, int id) {
    if (ql > r || qr < l) return 0;
    if (ql <= l && r <= qr) return (id == 1 ? nd[o].sum1 : nd[o].sum2);
    pushdown(o, l, r);
    int mid = (l + r) >> 1;
    return query_sum(LS(o), l, mid, ql, qr, id) + query_sum(RS(o), mid + 1, r, ql, qr, id);
}

int find_pos(int o, int l, int r, LL val) {
    if (l == r) return l;
    pushdown(o, l, r);
    int mid = (l + r) >> 1;
    if (nd[LS(o)].sum1 >= val) return find_pos(LS(o), l, mid, val);
    else return find_pos(RS(o), mid + 1, r, val - nd[LS(o)].sum1);
}

int main() {
    // freopen("test.in", "r", stdin);
    // freopen("test.out", "w", stdout);
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%lld", &c[i]);
    for (int i = 1; i <= m; i++)
        scanf("%lld%lld", &p[i].a, &p[i].b);
    sort(p + 1, p + 1 + m);
    int new_m = 1; LL ans = 0;
    while (p[new_m].b != -1) new_m++;
    m = new_m - 1;
    if (!m) {
        for (int i = 1; i <= n; i++) ans += p[1].a * c[i];
        printf("%lld\n", ans);
        return 0;
    }
    for (int i = 1; i <= m; i++) 
        s1[i] = s1[i - 1] + p[i].b, s2[i] = s2[i - 1] + p[i].b * p[i].a;
    for (int i = 1; i <= n; i++) {
        change_add(1, 1, m, 1, m);
        LL ls = c[i], pos;
        if (query_sum(1, 1, m, 1, m, 1) < c[i]) {
            ls -= query_sum(1, 1, m, 1, m, 1);
            ans += query_sum(1, 1, m, 1, m, 2);
            change_setzero(1, 1, m, 1, m);
            ans += p[m + 1].a * ls;
        } else {
            pos = find_pos(1, 1, m, c[i]);
            // cout << pos << endl;
            if (pos > 1) {
                ls -= query_sum(1, 1, m, 1, pos - 1, 1);
                ans += query_sum(1, 1, m, 1, pos - 1, 2);
                change_setzero(1, 1, m, 1, pos - 1);
            }
            ans += p[pos].a * ls;
            change_single(1, 1, m, pos, ls);
        }
        // for (int j = 1; j <= m; j++) 
        //     printf("{%lld,%lld} ", query_sum(1, 1, m, j, j, 1), query_sum(1, 1, m, j, j, 2));
        // cout << endl;
    }
    printf("%lld\n", ans);
    return 0;
}