#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>

using namespace std;

const int maxn = 5005, maxm = 2e4 + 5;
int n, ans, mxpri, a[maxn], fl[maxm];

void find_pri() {
    for (int i = 2; i < maxm; i++) fl[i] = 1;
    for (int i = 2; i < maxm; i++) if (fl[i]) {
        for (int j = 2; j * i < maxm; j++)
            fl[i * j] = 0;
    }
}
int main() {
    freopen("test.in", "r", stdin);
    freopen("test.out", "w", stdout);
    find_pri();
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        for (int j = 1; j * j <= a[i]; j++) {
            if (a[i] % j) continue;
            if (fl[a[i]/j] && a[i] / j >= mxpri) 
                mxpri = a[i] / j, ans = max(ans, a[i]);
            if (fl[j] && j >= mxpri)
                mxpri = j, ans = max(ans, a[i]);
        }
    }
    printf("%d\n", ans);
    return 0;
}