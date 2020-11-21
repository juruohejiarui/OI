#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
#define LL long long

using namespace std;

const int maxn = 15;
int Tid, n, m, a[maxn][maxn], maxS;
LL f[maxn][maxn][1 << 13];

inline int chg(int S, int x) { return S ^ (1 << (x - 1)); }
inline int val(int S, int x) { return (S >> (x - 1)) & 1; }

void init() {
    memset(f, 0, sizeof(f));
}
void input() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            scanf("%d", &a[i][j]);
}
void solve() {
    maxS = (1 << (m + 1)) - 1;
    f[0][m][0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int S = 0; S <= maxS; S++) f[i][0][S << 1] = f[i-1][m][S];
        for (int j = 1; j <= m; j++) {
            for (int S = 0; S <= maxS; S++) {
                int left = val(S, j), up = val(S, j + 1);
                if (!a[i][j]) {
                    if (!left && !up) f[i][j][S] = f[i][j - 1][S];
                    continue;
                }
                if (left && up) f[i][j][chg(chg(S, j), j + 1)] += f[i][j - 1][S];
                else if (left && !up) {
                    if (a[i + 1][j]) f[i][j][S] += f[i][j - 1][S];
                    if (a[i][j + 1]) f[i][j][chg(chg(S, j), j + 1)] += f[i][j - 1][S];
                } else if (!left && up) {
                    if (a[i][j + 1]) f[i][j][S] += f[i][j - 1][S];
                    if (a[i + 1][j]) f[i][j][chg(chg(S, j + 1), j)] += f[i][j - 1][S];
                } else if (!left && !up) {
                    if (a[i][j + 1] && a[i + 1][j]) f[i][j][chg(chg(S, j), j + 1)] += f[i][j - 1][S];
                }
            }
        }
    }
}

void output() {
    printf("Case %d: There are %lld ways to eat the trees.\n", Tid, f[n][m][0]);
}

int main() {
    // freopen("test.in", "r", stdin);
    // freopen("test.out", "w", stdout);
    // printf("%.3lf\n", ((double)sizeof(f)) / 1024 / 1024);

    int T; scanf("%d", &T);
    while (T--) Tid++, init(), input(), solve(), output();
    return 0;
}