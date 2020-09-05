#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
#define LL long long

using namespace std;

const int maxn = 3e5 + 5;
struct PAMNode {
    int ch[27], cnt, fail;
    LL len;
} nd[maxn];

char str[maxn];
int nd_tot, lst;

void PAM_init() {
    str[0] = -1;
    nd_tot = 1, lst = 0;
    nd[0].fail = 1, nd[1].len = -1;
}

int PAM_getfail(int x, int pos) {
    while (pos - nd[x].len - 1 < 0 || str[pos - nd[x].len - 1] != str[pos])
        x = nd[x].fail;
    return x;
}

int PAM_create(int len) {
    nd_tot++, nd[nd_tot].len = len;
    return nd_tot;
}

void PAM_insert(char c, int pos) {
    int u = PAM_getfail(lst, pos);
    if (!nd[u].ch[c]) {
        int np = PAM_create(nd[u].len + 2);
        nd[np].fail = nd[PAM_getfail(nd[u].fail, pos)].ch[c];
        nd[u].ch[c] = np;
    }
    nd[lst = nd[u].ch[c]].cnt++;
}
int main() {
    // freopen("test.in", "r", stdin);
    // freopen("test.out", "w", stdout);
    int str_len;
    scanf("%s", str + 1), str_len = strlen(str + 1);
    PAM_init();
    for (int i = 1; i <= str_len; i++)
        PAM_insert(str[i] - 'a', i);
    LL ans = 0;
    for (int i = nd_tot; i >= 0; i--)
        nd[nd[i].fail].cnt += nd[i].cnt;
    for (int i = 0; i <= nd_tot; i++) ans = max(ans, nd[i].len * nd[i].cnt);
    printf("%lld\n", ans);
    return 0;
}