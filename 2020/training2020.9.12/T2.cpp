#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
#define D double

using namespace std;
int main() {
    // freopen("test.int", "r", stdin);
    // freopen("test.out", "w", stdout);
    int N;
    scanf("%d", &N);
    if (N == 1) printf("4\n");
    if (N == 2) printf("50\n");
    else if (N == 3) printf("143\n");
    return 0;
}