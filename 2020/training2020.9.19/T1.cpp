#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
#define F(i,j) (f[(i)][(j) + 55])

using namespace std;

const int maxn = 1e5 + 6, INF = 1e8;

char s1[maxn], s2[maxn];
int f[maxn][125], n, m;

int main() {
    // freopen("test.in", "r", stdin);
    // freopen("test.out", "w", stdout);
    scanf("%s\n%s", s1 + 1, s2 + 1);
    n = strlen(s1 + 1), m = strlen(s2 + 1);
    if (abs(n - m) > 50) {
        printf("-1\n");
        return 0;
    }
    memset(f, 0x3f, sizeof(f));
    F(0,0) = 0;
    for (int i = 1; i <= n; i++) {
        for (int x = -51; x <= 51; x++) {
            int j = i + x; 
            if (j <= 0 || j > m) continue;
            F(i, x) = F(i-1, x) + (s1[i] != s2[j]);
            F(i, x) = min(F(i, x), F(i, x-1) + 1);
            F(i, x) = min(F(i, x), F(i-1, x+1) + 1);
            // printf("F(%d,%d)=%d (x=%d)\n", i, j, F(i, x), x);
        }
    }
    int ans = F(n, m - n);
    if (ans > 50) printf("-1\n");
    else printf("%d\n", ans);
    return 0;
}