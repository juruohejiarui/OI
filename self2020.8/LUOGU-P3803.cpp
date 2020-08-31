#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
#define NUM double

using namespace std;

const int maxn = 1.35e6 + 5;
struct Complex {
    NUM x, y;
    Complex(NUM x = 0, NUM y = 0) : x(x), y(y) {}
    friend Complex operator + (Complex a, Complex b) {
        return Complex(a.x + b.x, a.y + b.y);
    }
    friend Complex operator - (Complex a, Complex b) {
        return Complex(a.x - b.x, a.y - b.y);
    }
    friend Complex operator * (Complex a, Complex b) {
        return Complex(a.x * b.x - a.y * b.y, a.y * b.x + a.x * b.y);
    }
} f[maxn << 1], p[maxn << 1];

NUM self_pi;
int n, m, lsp[maxn << 1];

void init() {
    m += n;
    for (n = 1; n <= m; n <<= 1);
    self_pi = acos(-1);
    for (int i = 0; i < n; i++) lsp[i] = (lsp[i>>1]>>1) | ((i&1)?(n>>1):0);
    // for (int i = 0; i < n; i++) printf("%d ", lsp[i]);
    // putchar('\n');
}

void fft(Complex *f, int flag) {
    for (int i = 0; i < n; i++) if (i < lsp[i]) swap(f[i], f[lsp[i]]);
    for (int i = 2; i <= n; i <<= 1) {
        int lsl = i >> 1;
        Complex w1(cos(2 * self_pi / i), sin(2 * self_pi / i));
        if (!flag) w1.y *= -1;
        for (int st = 0; st < n; st += i) {
            Complex buf(1, 0);
            for (int k = st; k < st + lsl; k++) {
                Complex tmp = buf * f[k + lsl];
                f[k + lsl] = f[k] - tmp;
                f[k] = f[k] + tmp;
                buf = buf * w1;
            }
        }
    }
    // for (int i = 1; i < n; i++) printf("{%lf,%lf}", f[i].x, f[i].y);
    // printf("\n");
}
int main() {
    // freopen("test.in" , "r", stdin);
    // freopen("test.out", "w", stdout);
    scanf("%d%d", &n, &m);
    for (int i = 0; i <= n; i++) scanf("%lf", &f[i].x);
    for (int i = 0; i <= m; i++) scanf("%lf", &p[i].x);
    init();
    fft(f, 1), fft(p, 1);
    for (int i = 0; i < n; i++) f[i] = f[i] * p[i];
    fft(f, 0);
    for (int i = 0; i <= m; i++) printf("%d ", (int)(f[i].x / n + 0.49));
    return 0;
}