#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <map>

using namespace std;

const int maxn = 2e5 + 5;

int n, m, ans, a[maxn], k[maxn], ans_ls[maxn], blg[maxn], blksz, cnt[maxn], s[maxn], v_sz;
map<int, int> v_map;

struct Query { int l, r, id; } q[maxn];
bool cmp(Query a, Query b) {
    if (blg[a.l] != blg[b.l]) return a.l < b.l;
    return a.r > b.r;
}
int get_val(int key) {
    if (!v_map.count(key)) return v_map[key] = ++v_sz;
    return v_map[key]; 
}
void addv(int pos) {
    if (cnt[k[pos]] == ans) ans++;
    s[cnt[k[pos]]]--, cnt[k[pos]]++, s[cnt[k[pos]]]++;
}
void delv(int pos) {
    if (cnt[k[pos]] == ans && s[cnt[k[pos]]] == 1) ans--;
    s[cnt[k[pos]]]--, cnt[k[pos]]--, s[cnt[k[pos]]]++;
}

int main() {
    // freopen("test.in", "r", stdin);
    // freopen("test.out", "w", stdout);
    int l = 1, r = 0;
    scanf("%d%d", &n, &m), blksz = n / sqrt(m);;
    for (int i = 1; i <= n; i++) 
        scanf("%d", &a[i]), k[i] = get_val(a[i]),
        blg[i] = (i - 1) / blksz + 1;   
    for (int i = 1; i <= m; i++) 
        scanf("%d%d", &q[i].l, &q[i].r), q[i].id = i;
    sort(q + 1, q + 1 + m, cmp);
    for (int i = 1; i <= m; i++) {
        while (l < q[i].l) delv(l), l++;
        while (l > q[i].l) l--, addv(l);
        while (r < q[i].r) r++, addv(r);
        while (r > q[i].r) delv(r), r--;
        ans_ls[q[i].id] = ans;
    }
    for (int i = 1; i <= m; i++) printf("%d\n", -ans_ls[i]);
    return 0;
}