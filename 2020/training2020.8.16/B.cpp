#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <map>
#define LL long long

using namespace std;

LL qpow(LL a, LL b, LL M) {
    LL ret = 1;
    while (b) {
        if (b & 1) ret = ret * a % M;
        a = a * a % M, b >>= 1;
    }
    return ret;
}
LL gcd(LL a, LL b) { return b ? gcd(b, a % b) : a; }

namespace BSGS {
    map<LL, LL> val_map;
    LL log(LL a, LL b, LL M) { //a^x=b(mod M)
        if (!a && !b) return 1;
        else if (!a && b) return -1;
        LL sqrt_m = sqrt(M), inv = qpow(a, M - 2, M), vec = qpow(a, sqrt_m, M);
        val_map.clear();
        for (LL i = 0; i <= sqrt_m; i++, b = b * inv % M) val_map[b] = i;
        for (LL i = 0, x = 1; i < M; i += sqrt_m, x = x * vec % M)
            if (val_map.count(x))
                return val_map[x] + i;
        return -1;
    }
};
int main() {
    // freopen("test.in", "r", stdin);
    // freopen("test.out", "w", stdout);
    int T, K;
    scanf("%d%d", &T, &K);
    while (T--) {
        LL y, z, p;
        scanf("%lld%lld%lld", &y, &z, &p);
        if (K == 1) printf("%lld\n", qpow(y, z, p));
        else if (K == 2) {
            y %= p, z %= p;
            if (!y && z) printf("Orz, I cannot find x!\n");
            else {
                printf("%lld\n", z * qpow(y, p - 2, p) % p);
            }
        } else {
            y %= p, z %= p;
            LL ans = BSGS::log(y, z, p);
            if (ans == -1) printf("Orz, I cannot find x!\n");
            else printf("%lld\n", ans);
        }
    }
    return 0;
}