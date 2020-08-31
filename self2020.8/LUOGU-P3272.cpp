#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
#define LL long long

using namespace std;

const int maxn = 105, maxm = 15, maxk = 180005, HASH_MOD = 1e5;
const LL MOD = 20110520;
int n, m, ip_a[maxn][maxn], a[maxn][maxn];
LL pow3[maxn], maxS;

char read_ch() {
    char ch = getchar();
    while (ch != '_' && ch != '*') ch = getchar();
    return ch;
}

inline int val(int S, int x) { return S / pow3[x - 1] % 3; }
inline int chg(int S, int x, int v) { return S - val(S, x) * pow3[x - 1] + v * pow3[x - 1]; }

struct DP_INFO {
    int hd[HASH_MOD + 5], t[HASH_MOD + 5], ti;
    int S[maxk], nex[maxk], stot; LL f[maxk];
    void init() { stot = 0, ti++; }
    void update(int s, LL val) {
        int hs = s % HASH_MOD;
        if (t[hs] != ti) hd[hs] = 0, t[hs] = ti;
        bool succ = false;
        for (int i = hd[hs]; i; i = nex[i]) if (S[i] == s) {
            f[i] = (f[i] + val) % MOD, succ = true;
            break;
        }
        if (succ) return ;
        stot++;
        nex[stot] = hd[hs], f[stot] = val, S[stot] = s;
        hd[hs] = stot;
    }
} f[2];

void input_data() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            ip_a[i][j] = (read_ch() == '_');
    if (n < m) {
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++) a[j][i] = ip_a[i][j];
        swap(n, m);
    } else for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) a[i][j] = ip_a[i][j];
}

void init() {
    pow3[0] = 1;
    for (int i = 1; i <= m + 1; i++) pow3[i] = pow3[i - 1] * 3;
    maxS = pow3[m + 1] - 1;
}


int dp() {
    int cur = 0, ls = 1;
    f[cur].init(), f[cur].update(0, 1);
    // f[cur].debug();
    for (int i = 1; i <= n; i++) {
        ls = cur, cur ^= 1;
        f[cur].init();
        for (int sid = 1; sid <= f[ls].stot; sid++)
            f[cur].update(f[ls].S[sid] * 3, f[ls].f[sid]);
        // f[cur].debug();
        for (int j = 1; j <= m; j++) {
            ls = cur, cur ^= 1, f[cur].init();
            for (int sid = 1; sid <= f[ls].stot; sid++) {
                int S = f[ls].S[sid], l = val(S, j), u = val(S, j+1);
                LL v = f[ls].f[sid];
                if (!a[i][j]) {
                    if (!l && !u) f[cur].update(S, v);
                    continue;
                }
                if (!l && !u) {
                    if (a[i+1][j]) f[cur].update(chg(S,j,1), v);
                    if (a[i][j+1]) f[cur].update(chg(S,j+1,1), v);
                    if (a[i+1][j] && a[i][j+1]) f[cur].update(chg(chg(S,j,2),j+1,2), v);
                } else if (!l && u == 1) {
                    if (a[i+1][j]) f[cur].update(chg(chg(S,j,1),j+1,0), v);
                    if (a[i][j+1]) f[cur].update(chg(S,j+1,2), v);
                } else if (!l && u == 2) {
                    if (a[i+1][j]) f[cur].update(chg(chg(S,j,2),j+1,0), v);
                    f[cur].update(chg(S,j+1,0), v);
                } else if (l == 1 && !u) {
                    if (a[i][j+1]) f[cur].update(chg(chg(S,j,0),j+1,1), v);
                    if (a[i+1][j]) f[cur].update(chg(S,j,2), v);
                } else if (l == 1 && u == 1) {
                    f[cur].update(chg(chg(S,j,0),j+1,0), v);
                } else if (l == 2 && !u) {
                    if (a[i][j+1]) f[cur].update(chg(chg(S,j,0),j+1,2), v);
                    f[cur].update(chg(S,j,0), v);
                }
            }
            // f[cur].debug();
        }
    }
    return cur;
}

int main() {
    // freopen("test.in", "r", stdin);
    // freopen("test.out", "w", stdout);
    input_data();
    init();
    int id = dp(), succ = false;
    for (int i = 1; i <= f[id].stot; i++) if (!f[id].S[i]) {
        printf("%lld\n", f[id].f[i]);
        succ = true;
        break;
    }
    if (!succ) printf("0\n");
    return 0;
}