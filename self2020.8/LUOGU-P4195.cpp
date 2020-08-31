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
void exgcd(LL a,LL b,LL &x,LL &y)  //扩欧
{
	if (!b)x=1,y=0;
	else
	{
		exgcd(b,a%b,x,y);
		LL t=x;
		x=y;
		y=t-a/b*y;
	}
}
LL inv(LL a,LL b)    //逆元
{
	LL x,y;
	exgcd(a,b,x,y);
	return (x%b+b)%b;
}
namespace BSGS {
    map<LL, LL> val_map;
    LL log(LL a, LL b, LL M) { // a^x = b (mod M) 
        val_map.clear();
        LL sqrt_m = ceil(sqrt(M));
        b %= M;
        for (int i = 1; i <= sqrt_m; i++) {
            b = b * a % M;
            val_map[b] = i;
        }
        LL vec = qpow(a, sqrt_m, M); b = 1;
        for (int i = 1; i <= sqrt_m; i++) {
            b = b * vec % M;
            if (val_map.count(b)) return (i * sqrt_m - val_map[b] + M) % M;
        }
        return -1;
    }
}

namespace EX_BSGS {
    LL log(LL a, LL b, LL M) {
        if (b == 1 || M == 1) return 0;
        LL g = gcd(a, M), cnt = 0, k = 1;
        while (g > 1) {
            if (b % g) return -1;
            cnt++, b /= g, M /= g, k = k * (a / g) % M;
            if (k == b) return cnt;
            g = gcd(a, M);
        }
        LL ans2 = BSGS::log(a, b * inv(k, M) % M, M);
        if (ans2 == -1) return -1;
        else return ans2 + cnt;
    }
}

int main() {
    // freopen("test.in", "r", stdin);
    // freopen("test.out", "w", stdout);
    LL a, p, q;
    while (true) {
        scanf("%lld%lld%lld", &a, &p, &q);
        if (!a && !p && !q) break;
        LL ans = EX_BSGS::log(a % p, q % p, p);
        if (ans == -1) printf("No Solution\n");
        else printf("%lld\n", ans);
    }
    return 0;
}