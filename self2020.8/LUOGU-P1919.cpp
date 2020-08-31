#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
#define D double

using namespace std;

const int maxn = 1.35e6 + 5;
const D self_pi = acos(-1);

struct Complex {
    D x, y;
    Complex(D x = 0, D y = 0) : x(x), y(y) {}
    friend Complex operator + (Complex a, Complex b) {
        return Complex(a.x+b.x, a.y+b.y);
    }
    friend Complex operator - (Complex a, Complex b) {
        return Complex(a.x-b.x, a.y-b.y);
    }
    friend Complex operator * (Complex a, Complex b) {
        return Complex(a.x*b.x-a.y*b.y, a.x*b.y+a.y*b.x);
    }
} f[maxn << 1], p[maxn << 1];

int n, m, lsp[maxn << 1], ans[maxn << 1];

void init() {
    m += n;
    for (n = 1; n <= m; n <<= 1);
    for (int i = 0; i < n; i++) lsp[i] = (lsp[i>>1]>>1) | ((i&1) ? (n>>1) : 0);
}

int num[maxn << 1];
void read_number(Complex* f, int& len) {
    len = 0;
    char ch = getchar();
    while ('0' > ch || ch > '9') ch = getchar();
    while ('0' <= ch && ch <= '9') num[++len] = ch - '0', ch = getchar();
    for (int i = 1; i <= len; i++) f[i - 1].x = num[len - i + 1];
    len--;
}

void fft(Complex* f, int flag) {
    for (int i = 0; i < n; i++) if (i < lsp[i]) swap(f[i], f[lsp[i]]);

    for (int i = 2; i <= n; i <<= 1) {
        int lsl = (i >> 1);
        Complex w1(cos(2 * self_pi / i), sin(2 * self_pi / i));
        if (!flag) w1.y *= -1;
        for (int st = 0; st < n; st += i) {
            Complex buf(1, 0);
            for (int k = st; k < st + lsl; k++) {
                Complex tmp = f[k + lsl] * buf;
                f[k + lsl] = f[k] - tmp;
                f[k] = f[k] + tmp;
                buf = buf * w1;
            }
        }
    }
}

int main() {
    // freopen("test.in", "r", stdin);
    // freopen("test.out", "w", stdout);
    read_number(f, n), read_number(p, m);
    init();
    fft(f, 1), fft(p, 1);
    for (int i = 0; i < n; i++) f[i] = f[i] * p[i];
    fft(f, 0);
    int shift = 0, ans_len = 0;
    for (int i = 0; i <= m; i++) {
        int tmp = ((int)(f[i].x/n + 0.49) + shift);
        ans[++ans_len] = tmp % 10, shift = tmp / 10;
    }
    while (shift) ans[++ans_len] = shift % 10, shift /= 10;
    for (int i = ans_len; i >= 1; i--) printf("%d", ans[i]);
    return 0;
}