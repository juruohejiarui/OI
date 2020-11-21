#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
#define LL long long

using namespace std;

const int maxm = 164005;
const LL MOD = 1004535809;
LL f[32][maxm], g[maxm];
int n, logn, m, mp[maxm];

LL qpow(LL a, LL b, LL M = MOD) {
    LL ret = 1;
    while (b) {
        if (b & 1) ret = ret * a % M;
        a = a * a % M, b >>= 1;
    } 
    return ret;
}

LL f1[maxm << 1], f2[maxm << 1], NTT_g, NTT_invg, invf1_len;
int f1_len, f2_len, lsp[maxm << 1];
void NTT_init() {
    f2_len += f1_len, NTT_g = 3, NTT_invg = qpow(NTT_g, MOD - 2);
    for (f1_len = 1; f1_len <= f2_len; f1_len <<= 1) ;
    invf1_len = qpow(f1_len, MOD - 2);
    for (int i = 0; i < f1_len; i++) lsp[i] = (lsp[7i>>1]>>1) | ((i&1)?(f1_len>>1):0);
}
void NTT_calc(LL* f, int len, int flag) {
    for (int i = 0; i < len; i++) if (i < lsp[i]) swap(f[i], f[lsp[i]]);
    for (int i = 2; i <= len; i <<= 1) {
        LL w1 = qpow((flag ? NTT_g : NTT_invg), (MOD - 1) / i);
        int lsl = (i >> 1);
        for (int st = 0; st < len; st += i) {
            LL buf = 1;
            for (int k = st; k < st + lsl; k++) {
                LL tmp = buf * f[k + lsl] % MOD;
                f[k + lsl] = (f[k] - tmp + MOD) % MOD;
                f[k] = (f[k] + tmp) % MOD;
                buf = buf * w1 % MOD;
            }
        }
    }
    if (!flag) for (int i = 0; i < len; i++) f[i] = f[i] * invf1_len % MOD;
}

int pri[maxm], pri_cnt;
int find_root(int m) {
    int phi = m - 1;
    pri_cnt = 0;
    for (int i = 2; i * i <= phi; i++) if (phi % i == 0) {
        pri[++pri_cnt] = i;
        while (phi % i == 0) phi /= i;
    }
    if (phi != 1) pri[++pri_cnt] = phi;
    phi = m - 1;
    for (int i = 2; i <= phi; i++) {
        bool succ = true;
        for (int j = 1; j <= pri_cnt; j++) 
            if (qpow(i, phi / pri[j], m) == 1) {
                succ = false;
                break;
            }
        if (succ) return i;
    }
    return -1;
}

int main() {
    // freopen("test.in", "r", stdin);
    // freopen("test.out", "w", stdout);
    int n, m, x, _S_;
    scanf("%d%d%d%d", &n, &m, &x, &_S_);
    f1_len = f2_len = m, logn = log2(n);
    NTT_init();
    int m_g = find_root(m);
    for (int i = 0; i < m - 1; i++) mp[qpow(m_g, i, m)] = i;
    for (int i = 1; i <= _S_; i++) {
        int ele; scanf("%d", &ele);
        if (!ele) continue;
        f[0][mp[ele]] = 1;
    }
    for (int k = 1; k <= logn; k++) {
        for (int i = 0; i < m - 1; i++) f1[i] = f[k - 1][i];
        for (int i = m - 1; i < f1_len; i++) f1[i] = 0;
        NTT_calc(f1, f1_len, 1);
        for (int i = 0; i < f1_len; i++) f1[i] = f1[i] * f1[i] % MOD;
        NTT_calc(f1, f1_len, 0);
        for (int i = 0; i < m - 1; i++) f[k][i] = (f1[i] + f1[i + m - 1]) % MOD;
    }
    int len = 0;
    g[0] = 1;
    for (int k = logn; k >= 0; k--) {
        if ((1 << k) + len > n) continue;
        len += (1 << k);
        for (int i = 0; i < m - 1; i++) f1[i] = g[i], f2[i] = f[k][i];
        for (int i = m - 1; i < f1_len; i++) f1[i] = f2[i] = 0;
        NTT_calc(f1, f1_len, 1), NTT_calc(f2, f1_len, 1);
        for (int i = 0; i < f1_len; i++) f1[i] = f1[i] * f2[i] % MOD;
        NTT_calc(f1, f1_len, 0);
        for (int i = 0; i < m - 1; i++) g[i] = (f1[i] + f1[i + m - 1]) % MOD;
    }
    printf("%lld\n", g[mp[x]]);
    return 0;
}