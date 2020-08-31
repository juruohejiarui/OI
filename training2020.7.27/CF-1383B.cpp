#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>

using namespace std;

const int maxn = 1e5 + 5;
int a[maxn], n, cnt[32], cnt0[32];

inline int val(int S, int x) { return (S >> (x - 1)) & 1; }
int main() {
    // freopen("test.in", "r", stdin);
    // freopen("test.out", "w", stdout);
    int T; scanf("%d", &T);
    while (T--) {
        memset(cnt, 0, sizeof(cnt)), memset(cnt0, 0, sizeof(cnt0));
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) {
            scanf("%d", &a[i]);
            for (int j = 1; j <= 31; j++) 
                cnt[j] += val(a[i], j),
                cnt0[j] += (!val(a[i], j));
        }
        // for (int i = 1; i <= 31; i++) printf("%d->{%d,%d} ", i, cnt[i], cnt0[i]);
        // putchar('\n');
        int tag = 0;
        for (int i = 31; i >= 1; i--) {
            if ((cnt[i] & 1) == 0) continue;
            int x = (cnt[i] + 1) >> 1;
            if (x & 1) { tag = 1; break; }
            else {
                if (cnt0[i] & 1) tag = 1;
                else tag = 2;
                break; 
            }
        }
        if (!tag) printf("DRAW\n");
        else if (tag == 1) printf("WIN\n");
        else printf("LOSE\n");
    }
    return 0;
}