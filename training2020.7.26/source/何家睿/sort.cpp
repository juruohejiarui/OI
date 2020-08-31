#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>

using namespace std;

const int maxn = 3e3 + 5;
int n, a[maxn], p[maxn], id[maxn], id_cnt, lst;
int l[maxn], lsz, r[maxn], rsz;

int main() {
    freopen("sort.in", "r", stdin);
    freopen("sort.out", "w", stdout);
    // freopen("test.in", "r", stdin);
    // freopen("test.out", "w", stdout);
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]), p[a[i]] = i;
    id_cnt = lst = 0;
    for (int i = 1; i <= n; i++) {
        id[i] = (p[i] > lst ? id_cnt : ++id_cnt), lst = p[i];
    }
    int ans;
    for (ans = 0; (1 << ans) <= id_cnt; ans++);
    printf("%d\n", ans);
    for (int i = 1; i <= n; i++) printf("%d ", a[i]);
    putchar('\n');
    for (int i = 1; i <= ans; i++) {
        lsz = rsz = 0;
        for (int j = 1; j <= n; j++) {
            if ((id[a[j]] >> (i - 1)) & 1) r[++rsz] = a[j];
            else l[++lsz] = a[j];
        }
        int asz = 0;
        for (int j = 1; j <= lsz; j++) a[++asz] = l[j];
        for (int j = 1; j <= rsz; j++) a[++asz] = r[j];
        
        for (int j = 1; j <= n; j++) printf("%d ", a[j]);
        putchar('\n');
    }
    return 0;
}