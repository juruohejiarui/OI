#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>

using namespace std;

const int maxn = 5e5 + 5;
struct PAM {
    struct Node {
        int ch[27], len, fail, sz;
        void init() { 
            for (int i = 0; i < 26; i++) ch[i] = 0;
            len = fail = sz = 0;
        }
    } nd[maxn];
    int nd_cnt, lst;
    char str[maxn];
    void init() {
        str[0] = -1, nd_cnt = 1, lst = 0; 
        nd[0].init(), nd[1].init();
        nd[0].fail = 1, nd[1].len = -1;
    }
    int create(int len) {
        nd_cnt++, nd[nd_cnt].init(), nd[nd_cnt].len = len;
        return nd_cnt;
    }
    int getfail(int x, int pos) {
        while (pos - nd[x].len - 1 < 0 || str[pos - nd[x].len - 1] != str[pos])
            x = nd[x].fail;
        return x;
    }
    void insert(int c, int n) {
        int u = getfail(lst, n);
        if (!nd[u].ch[c]) {
            int np = create(nd[u].len + 2);
            nd[np].fail = nd[getfail(nd[u].fail, n)].ch[c];
            nd[u].ch[c] = np;
            nd[np].sz = nd[nd[np].fail].sz + 1;
        }
        lst = nd[u].ch[c];
    }
} pam;

int main() {
    // freopen("test.in", "r", stdin);
    // freopen("test.out", "w", stdout);
    pam.init();
    scanf("%s", pam.str + 1);
    int str_len = strlen(pam.str + 1);
    for (int i = 1; i <= str_len; i++) {
        pam.insert(pam.str[i] - 'a', i);
        pam.str[i + 1] = (pam.str[i + 1] - 97 + pam.nd[pam.lst].sz) % 26 + 97;
        printf("%d ", pam.nd[pam.lst].sz);
    }
    return 0;
}