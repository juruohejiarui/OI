#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>

using namespace std;

const int maxn = 3e5 + 5;
int n, a[maxn << 1], rk[maxn << 1], p[maxn << 1], ls[maxn << 1], ls_cnt, nrk[maxn << 1];

int cnt[maxn << 1];
int tmp[maxn], tmp_cnt;
void init_rk() {
    for (int i = 1; i <= n; i++) tmp[++tmp_cnt] = a[i];
    sort(tmp + 1, tmp + 1 + tmp_cnt);
    tmp_cnt = unique(tmp + 1, tmp + 1 + tmp_cnt) - tmp - 1;
    for (int i = 1; i <= (n << 1); i++) {
        int l = 1, r = tmp_cnt, pos = -1;
        while (l <= r) {
            int mid = (l + r) >> 1;
            if (tmp[mid] == a[i]) { pos = mid; break; }
            if (tmp[mid] < a[i]) l = mid + 1;
            else r = mid - 1;
        }
        rk[i] = pos;
    }
}

inline bool equal(int p1, int p2, int len) {
    if (rk[p1] != rk[p2]) return false;
    if ((p1+len <= (n<<1) && p1+len > (n<<1)) || (p1+len > (n<<1) && p2+len <= (n+1)))
        return false;
    if (p1+len > (n+1) && p2+len > (n+1)) return true;
    return rk[p1+len] == rk[p2+len];
}

int main() {
    // freopen("test.in", "r", stdin);
    // freopen("test.out", "w", stdout);
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    for (int i = 1; i <= n; i++) a[i + n] = a[i];
    init_rk();
    int m = (n << 1), max_rk = 0, len;
    //init p[]
    for (int i = 1; i <= m; i++) cnt[rk[i]]++, max_rk = max(max_rk, rk[i]);
    for (int i = 1; i <= max_rk; i++) cnt[i] += cnt[i - 1];
    for (int i = m; i >= 1; i--) p[cnt[rk[i]]--] = i;
    for (len = 1; len < m; len <<= 1) {
        ls_cnt = 0;
        //完成第二关键字排序 (rk[i + len])
        for (int i = m-len+1; i <= m; i++) ls[++ls_cnt] = i;
        for (int i = 1; i <= m; i++) if (p[i] > len) ls[++ls_cnt] = p[i] - len;

        //完成第二关键字排序 (rk[i])
        for (int i = 1; i <= max_rk; i++) cnt[i] = 0;
        max_rk = 0;
        for (int i = 1; i <= m; i++) cnt[rk[i]]++, max_rk = max(max_rk, rk[i]);
        for (int i = 1; i <= max_rk; i++) cnt[i] += cnt[i - 1];
        for (int i = m; i >= 1; i--) p[cnt[rk[ls[i]]]--] = ls[i];

        int rk_cnt = 1;
        nrk[p[1]] = 1;
        for (int i = 2; i <= m; i++) {
            if (!equal(p[i - 1], p[i], len)) rk_cnt++;
            nrk[p[i]] = rk_cnt;
        }
        for (int i = 1; i <= m; i++) rk[i] = nrk[i];
    }
    int pos = 1;
    while (p[pos] > n) pos++; 
    for (int i = 0; i < n; i++) printf("%d ", a[p[pos] + i]);
    return 0;
}