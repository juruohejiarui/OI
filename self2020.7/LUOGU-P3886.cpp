#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>

using namespace std;

const int maxn = 11, INF = 2e9, HASH_MOD = 599999;
int n, a[maxn][maxn], ans;

//集合操作
inline int val(int S, int x) { return (S >> (3 * (x - 1))) % 8; }
inline int chg(int S, int x, int v) { 
    return S - val(S, x) * (1 << (3 * (x - 1))) + v * (1 << (3 * (x - 1))); 
}
int reord(int S) {
    int k[13] = {0}, k_cnt = 0;
    for (int i = 1; i <= n; i++) {
        int v = val(S, i);
        if (!v) continue;
        if (!k[v]) k[v] = ++k_cnt;
        S = chg(S, i, k[v]); 
    }
    return S;
}
int cnt(int S, int v) {
    int ret = 0;
    for (int i = 1; i <= n; i++)  ret += (val(S, i) == v);
    return ret;
}

struct DP_INFO {
    int f[600005], s[600005], nex[600005], S_cnt;
    int hd[HASH_MOD + 2], t[HASH_MOD + 2], ti;
    inline void init() { S_cnt = 0, ti++; }
    void upd(int S, int v) {
        S = reord(S);
        int tot1 = cnt(S, 1), tot0 = cnt(S, 0);
        if (tot1 + tot0 == n && tot1) ans = max(ans, v); 
        int hsv = S % HASH_MOD;
        if (t[hsv] != ti) hd[hsv] = 0, t[hsv] = ti;
        for (int i = hd[hsv]; i; i = nex[i])
            if (s[i] == S) { f[i] = max(f[i], v); return ; }
        f[++S_cnt] = v, s[S_cnt] = S, nex[S_cnt] = hd[hsv], hd[hsv] = S_cnt;
    }
} f[2];

int main() {
    // freopen("test.in", "r", stdin);
    // freopen("test.out", "w", stdout);
    scanf("%d", &n);
    ans = -INF;
    for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) scanf("%d", &a[i][j]);
    f[1].init(), f[1].upd(0, 0);
    int ls = 0, cur = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            ls = cur, cur ^= 1, f[cur].init();
            for (int sid = 1; sid <= f[ls].S_cnt; sid++) {
                int S = f[ls].s[sid], v = f[ls].f[sid];
                int l = (j > 1 ? val(S, j - 1) : 0), u = val(S, j);
                if (!u || cnt(S, u) > 1) {
                    f[cur].upd(chg(S, j, 0), v);
                } 
                if (!u && !l) 
                    f[cur].upd(chg(S, j, 7), v + a[i][j]);
                if (u || l) {
                    int new_id = max(u, l), _S = S;
                    _S = chg(_S, j, new_id);
                    for (int k = 1; k <= n; k++) {
                        int vk = val(_S, k);
                        if (!vk) continue;
                        if (vk == min(u, l)) _S = chg(_S, k, new_id);
                    }
                    f[cur].upd(_S, v + a[i][j]);
                }
            }
        }
    }
    printf("%d\n", ans);
    return 0;
}