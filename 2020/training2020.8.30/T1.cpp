#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
#define LL long long

using namespace std;

const int maxn = 1e6 + 5;
LL ls[maxn], ls_cnt;
void init() {
    for (LL i = 1; 3 * i * i - 3 * i + 1 <= (LL)1e11; i++)
        ls[i] = 3 * i * i - 3 * i + 1, ls_cnt++;
}

void solve() {
    LL N, ans = 0; bool flag = false;
    scanf("%lld", &N);
    ans = N % 6;
    if (ans == 1) {
        for (int i = 1; i <= ls_cnt; i++) if (ls[i] == N)
            flag = true;
        if (flag) printf("1\n");
        else printf("7\n");
    } else if (ans == 2) {
        int l = ls_cnt;
        for (int i = 1; i <= ls_cnt; i++) {
            while (ls[i] + ls[l] > N && l > 1) l--;
            if (ls[i] + ls[l] == N) { flag = true; break; } 
        }
        if (flag) printf("2\n");
        else printf("8\n");
    } else printf("%lld\n", (ans ? ans : 6));
}
int main() {
    // freopen("test.in", "r", stdin);
    // freopen("test.out", "w", stdout);

    init();

    int T; scanf("%d", &T);
    while (T--) solve();
    return 0;
}