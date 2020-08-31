#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>

using namespace std;

const int maxn = 1e3 + 5;

int n[maxn], m, l[maxn][maxn], r[maxn][maxn];

void solve() {
    scanf("%d", &m);
    int t1 = 1, L = 0, R = 0, B = 0;
    for (int i = 1; i <= m; i++) {
        scanf("%d", &n[i]);
        if (n[i] > 1) t1 = 0;
        for (int j = 1; j <= n[i]; j++) {
            scanf("%d%d", &l[i][j], &r[i][j]);
            if (l[i][j] && !r[i][j]) L = 1;
            else if (r[i][j] && !l[i][j]) R = 1;
            else if (l[i][j] && r[i][j]) B = 1;
        }
    }
    if (t1 == 1) printf("Almost Complete\n");
    else {
        if (L && R && B) printf("Almost Complete\n");
        else printf("No\n");
    }
}
int main() {
    // freopen("test.in", "r", stdin);
    // freopen("test.out", "w", stdout);
    freopen("surreal.in", "r", stdin);
    freopen("surreal.out", "w", stdout);
    int T; scanf("%d", &T);
    while (T--) solve();
    return 0;
}