#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
#define upd(a, b) ((a) = max((a), (b)))

using namespace std;

const int maxn = 105, maxm = 10, INF = 600000;
int n, m, a[maxn][maxm], f[maxn][maxm][330];
int maxS, pow3[maxm];

int v[6600], k[330], mt[330][13], id_cnt;

inline int val(int S, int x) { return S / pow3[x - 1] % 3; }
inline int chg(int S, int x, int v) {
    return S - val(S, x) * pow3[x - 1] + v * pow3[x - 1];
}

void init() {
    int stk[9], stksz;
    pow3[0] = 1;
    for (int i = 1; i <= m + 1; i++) pow3[i] = pow3[i - 1] * 3;
    maxS = pow3[m + 1] - 1;
    for (int S = 0; S <= maxS; S++) {
        bool succ = true;
        stksz = 0;
        for (int i = 1; i <= m + 1; i++) {
            int v = val(S, i);
            if (v == 1) stk[++stksz] = i;
            else if (v == 2) {
                if (!stksz) { succ = false; break; }
                int l = stk[stksz--];
                mt[id_cnt + 1][l] = i, mt[id_cnt + 1][i] = l;
            } else mt[id_cnt + 1][i] = 0;
        }
        if (stksz) succ = false;
        if (succ) v[S] = ++id_cnt, k[id_cnt] = S;
    }
}

int main() {
    // freopen("test.in", "r", stdin);
    // freopen("test.out", "w", stdout);
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            scanf("%d", &a[i][j]);
    init();
    int ans = -INF;
    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= m; j++)
            for (int Sid = 1; Sid <= id_cnt; Sid++)
                f[i][j][Sid] = -INF;
    f[0][m][1] = 0;
    for (int i = 1; i <= n; i++) {
        for (int Sid = 1; Sid <= id_cnt; Sid++)
            if (!val(k[Sid], m+1)) upd(f[i][0][v[k[Sid] * 3]], f[i-1][m][Sid]);
        for (int j = 1; j <= m; j++) {
            for (int Sid = 1; Sid <= id_cnt; Sid++) {
                int S = k[Sid], l = val(S, j), u = val(S, j + 1);
                if (l == 1 && u == 2) {
                    if (S == chg(0,j,1) + chg(0, j+1, 2)) upd(ans, f[i][j - 1][Sid] + a[i][j]);
                } else if (l == 1 && u == 1) {
                    upd(f[i][j][v[chg(chg(chg(S,j,0),j+1,0),mt[Sid][j+1],1)]], f[i][j-1][Sid]+a[i][j]);
                } else if (l && !u) {
                    upd(f[i][j][Sid], f[i][j-1][Sid] + a[i][j]);
                    upd(f[i][j][v[chg(chg(S,j,0),j+1,l)]], f[i][j-1][Sid] + a[i][j]);
                } else if (!l && u) {
                    upd(f[i][j][Sid], f[i][j-1][Sid] + a[i][j]);
                    upd(f[i][j][v[chg(chg(S,j,u),j+1,0)]], f[i][j-1][Sid] + a[i][j]);
                } else if (l == 2 && u == 1) {
                    upd(f[i][j][v[chg(chg(S,j,0),j+1,0)]], f[i][j-1][Sid] + a[i][j]);
                } else if (l == 2 && u == 2) {
                    upd(f[i][j][v[chg(chg(chg(S,j,0),j+1,0),mt[Sid][j],2)]], f[i][j-1][Sid]+a[i][j]);
                } else if (!l && !u) {
                    if (i != n && j != m) 
                        upd(f[i][j][v[chg(chg(S,j,1),j+1,2)]], f[i][j-1][Sid] + a[i][j]);
                    upd(f[i][j][Sid], f[i][j - 1][Sid]);
                }
            }
        }
    }
    printf("%d\n", ans);
    return 0;
}