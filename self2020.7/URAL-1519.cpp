#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
#define LL long long

using namespace std;

const int maxn = 15;
int id_cnt, n, m, maxS, v[160000], k[43005], mt[60005][maxn], a[maxn][maxn];
LL f[14][14][60005], pow3[maxn], ans;

char read_ch() {
    char ch = getchar();
    while (ch != '*' && ch != '.') ch = getchar();
    return ch;
}

inline int val(int S, int x) { return (S / pow3[x - 1]) % 3; }
inline int chg(int S, int x, int v) { return S - val(S, x) * pow3[x - 1] + v * pow3[x - 1]; }

void init() {
    int stk[14];
    pow3[0] = 1;
    for (int i = 1; i <= m + 1; i++) pow3[i] = pow3[i - 1] * 3;
    maxS = pow3[m + 1] - 1;
    id_cnt = 0;
    for (int S = 0; S <= maxS; S++) {
        bool succ = true; int cnt = 0;
        for (int i = 1; i <= m + 1; i++) {
            int v = val(S, i);
            if (v == 1) stk[++cnt] = i;
            else if (v == 2) { 
                if (!cnt) { succ = false; break; }
                mt[id_cnt + 1][i] = stk[cnt], mt[id_cnt + 1][stk[cnt]] = i, cnt--;
            } else mt[id_cnt + 1][i] = 0;
        }
        if (cnt) succ = false;
        if (succ) v[S] = ++id_cnt, k[id_cnt] = S;
    }
}
int main() {
    freopen("test.in", "r", stdin);
    freopen("test.out", "w", stdout);
    printf("%.3lf\n", ((double)sizeof(f)) / 1024 / 1024);
    scanf("%d%d", &n, &m);
    int x, y;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) {
            a[i][j] = (read_ch() == '.');
            if (a[i][j]) x = i, y = j;
        }
    init();
    f[0][m][1] = 1;
    for (int i = 1; i <= n; i++) {
        for (int Sid = 1; Sid <= id_cnt; Sid++) f[i][0][v[k[Sid] * 3]] = f[i - 1][m][Sid];
        for (int j = 1; j <= m; j++) {
            for (int Sid = 1; Sid <= id_cnt; Sid++) {
                int S = k[Sid];
                int left = val(S, j), up = val(S, j + 1);
                if (!a[i][j]) {
                    if (!left && !up) f[i][j][Sid] += f[i][j - 1][Sid];
                    continue;
                } 
                if (left == 1 && up == 2) {
                    if (x == i && y == j) ans += f[i][j - 1][Sid];
                }else if (left == 1 && up == 1)
                    f[i][j][v[chg( chg( chg(S,j,0), j+1, 0), mt[Sid][j+1], 1)]] += f[i][j - 1][Sid];
                else if (left == 2 && up == 1)
                    f[i][j][v[chg( chg(S,j,0), j+1, 0)]] += f[i][j - 1][Sid];
                else if (left == 2 && up == 2)
                    f[i][j][v[chg( chg( chg(S,j,0), j+1, 0), mt[Sid][j], 2)]] += f[i][j - 1][Sid]; 
                else if (!left && up) {
                    if (a[i][j+1]) f[i][j][Sid] += f[i][j - 1][Sid];
                    if (a[i+1][j]) f[i][j][v[chg( chg(S,j, up), j + 1, 0)]] += f[i][j - 1][Sid];
                } else if (left && !up) {
                    if (a[i][j+1]) f[i][j][v[chg( chg(S, j+1, left), j, 0)]] += f[i][j - 1][Sid];
                    if (a[i+1][j]) f[i][j][Sid] += f[i][j - 1][Sid];
                } else if (!left && !up) {
                    if (a[i][j + 1] && a[i + 1][j]) 
                        f[i][j][v[chg( chg(S, j, 1), j+1, 2)]] += f[i][j - 1][Sid];
                }
            }
        } 
    }
    printf("%lld\n", ans);
    return 0;
}