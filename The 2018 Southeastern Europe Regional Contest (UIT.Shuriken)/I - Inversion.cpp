/// hhoangcpascal
 
#pragma GCC target("avx,avx2,fma,popcnt")
#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <set>
#include <map>
#include <stack>
#include <deque>
#include <tuple>
#include <queue>
#include <bitset>
#include <unordered_map>
#include <unordered_set>
#include <iomanip>
#include <assert.h>
#include <complex>
#include <random>
#include <chrono>
#include <functional>
#define sint short int
#define usint unsigned short int
#define uint unsigned int
#define llong long long
#define ullong unsigned long long
#define ldouble long double
 
using namespace std;
using namespace chrono;
 
void init() {
    ///
}
 
llong dp[106]; /// dp[i]: So day con tang xet tu 1 den i thoa man de bai
bool E[106][106];
 
void UITShuriken() {
    int n, m; cin >> n >> m;
    for(int i = 1; i <= m; ++i) {
        int u, v; cin >> u >> v;
        E[u][v] = E[v][u] = true;
    }
 
    dp[0] = 1;
    for(int i = 1; i <= n; ++i)
    for(int j = 0; j < i; ++j) { /// Xet cac vi tri j truoc do de them i vao tap chua j
        if (E[i][j]) continue; /// Neu ton tai canh (i, j) thi khong the tao tap doc lap chua i va j
 
        /// Xet den "dominant"
        bool ok = true;
 
        /* Neu khi dua i vao tap dp[j], nhung khong ton tai j < k < i thoa man co canh (k, j) hoac (k, i)
            tuc co a[k] ma a[j] < a[k] < a[i] thi khong the de i chung tap j. */
        for(int k = j + 1; k < i && ok; ++k)
        if (!E[k][i] && !E[k][j]) ok = false;
 
        if (ok) dp[i] += dp[j];
    }
 
    llong ans = 0;
    for(int i = 1; i <= n; ++i) {
        bool ok = true;
 
        for(int j = i + 1; j <= n && ok; ++j)
        if (!E[i][j]) ok = false;
 
        if (ok) ans += dp[i];
    }
 
    cout << ans;
}
 
int main() {
    ios_base::sync_with_stdio(0); cin.tie(NULL);
 
    init();
 
    int tests = 1; /// cin >> tests;
    while (tests--) UITShuriken();
 
    return 0;
}
