#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
#define LL long long
#define add_m(a, b) ((a) = ((a) + (b)) % MOD)

using namespace std;

const int maxn = 19;
const LL MOD = 1e9 + 7;
int maxS, n, m, a[20][20];
int f1[maxn][maxn][1 << 18], f2[maxn][maxn][1 << 18];

inline int val(int S, int x) { return (S >> (x - 1)) & 1; }
inline int chg(int S, int x) { return S ^ (1 << (x - 1)); }
void init() {
    maxS = (1 << (m + 1)) - 1;
}
void calc_f1() {
    f1[0][m][0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int S = 0; S <= maxS; S++)
            add_m(f1[i][0][S << 1], f1[i-1][m][S]);
        for (int j = 1; j <= m; j++)
            for (int S = 0; S <= maxS; S++) {
                int left = val(S, j), up = val(S, j + 1);
                if (!a[i][j]) {
                    if (!left && !up) add_m(f1[i][j][S], f1[i][j-1][S]);
                    continue;
                }
                if (!left && !up) {
                    if (a[i][j+1]) add_m(f1[i][j][chg(S, j+1)], f1[i][j-1][S]);
                    if (a[i+1][j]) add_m(f1[i][j][chg(S, j)], f1[i][j-1][S]);
                    add_m(f1[i][j][S], f1[i][j-1][S]);
                } else if (!left && up) {
                    add_m(f1[i][j][chg(S, j+1)], f1[i][j-1][S]);
                } else if (left && !up) {
                    add_m(f1[i][j][chg(S, j)], f1[i][j-1][S]);
                }
            } 
    }
}
void calc_f2() {
    f2[n+1][1][0] = 1;
    for (int i = n; i >= 1; i--) {
        for (int S = 0; S <= maxS; S++)  
            add_m(f2[i][m + 1][S >> 1], f2[i+1][1][S]);
        for (int j = m; j >= 1; j--) for (int S = 0; S <= maxS; S++) {
            int right = val(S, j + 1), down = val(S, j);
            if (!a[i][j]) {
                if (!right && !down) add_m(f2[i][j][S], f2[i][j+1][S]);
                continue; 
            }
            if (!right && !down) {
                if (a[i][j-1]) add_m(f2[i][j][chg(S, j)], f2[i][j+1][S]);
                if (a[i-1][j]) add_m(f2[i][j][chg(S, j+1)], f2[i][j+1][S]);
                add_m(f2[i][j][S], f2[i][j+1][S]); 
            } else if (!right && down) {
                add_m(f2[i][j][chg(S, j)], f2[i][j+1][S]);
            } else if (right && !down) {
                add_m(f2[i][j][chg(S, j+1)], f2[i][j+1][S]);
            }
        }
    }
}

int main() {
    // freopen("test.in", "r", stdin);
    // freopen("test.out", "w", stdout);
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) {
            scanf("%d", &a[i][j]), a[i][j] ^= 1;
        }
    init(), calc_f1(), calc_f2();
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (!a[i][j]) { printf("0 "); continue; }
            LL ans = 0;
            for (int S = 0; S <= maxS; S++) {
                if (val(S, j) || val(S, j+1)) continue;
                add_m(ans, 1ll * f1[i][j - 1][S] * f2[i][j + 1][S] % MOD);
            }
            printf("%lld ", ans);
        }
        putchar('\n');
    }
    return 0;
}