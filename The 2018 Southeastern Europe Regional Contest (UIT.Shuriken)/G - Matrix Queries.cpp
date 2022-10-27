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
 
struct Data_update {
    int id, x, y, u, v;
} D[100006];
 
int n, q, seg[2][(1 << 22) + 6], len[26], cnt[2][26];
bool black[2][(1 << 20) + 6];
 
void modify(int is_column, int id, int l, int r, int depth, int p, int val) {
    if (l > p || r < p) return;
 
    if (l == r) {
        seg[is_column][id] += val;
        return;
    }
 
    if (seg[is_column][id] == 0 || seg[is_column][id] == len[n - depth]) --cnt[is_column][n - depth];
 
    int mid = (l + r) >> 1;
    modify(is_column, id * 2 + 1, l, mid, depth + 1, p, val);
    modify(is_column, id * 2 + 2, mid + 1, r, depth + 1, p, val);
 
    seg[is_column][id] = seg[is_column][id * 2 + 1] + seg[is_column][id * 2 + 2];
 
    if (seg[is_column][id] == 0 || seg[is_column][id] == len[n - depth]) ++cnt[is_column][n - depth];
}
 
void UITShuriken() {
    cin >> n >> q;
 
    /// Goi T la so o kich thuoc (2^i x 2^i) khong dong nhat mau
    /// Ket qua la 4 * T + 1
 
    llong tot = 0, num = 1; len[0] = 1;
    for(int i = 1; i <= n; ++i) {
        len[i] = (len[i - 1] << 1);
        tot += num;
        num <<= 2;
    }
 
    for(int i = 1; i <= n; ++i) cnt[0][i] = cnt[1][i] = len[n - i];
 
    while (q--) {
        int is_column, p; cin >> is_column >> p;
 
        int val = 1;
        if (black[is_column][p]) val = -1;
        black[is_column][p] = !black[is_column][p];
 
        modify(is_column, 0, 1, (1 << n), 0, p, val);
 
        llong ok = 0;
        for(int i = 1; i <= n; ++i) ok += 1LL * cnt[is_column][i] * cnt[is_column ^ 1][i];
 
        cout << 4LL * (tot - ok) + 1 << '\n';
    }
}
 
int main() {
    ios_base::sync_with_stdio(0); cin.tie(NULL);
 
    init();
 
    int tests = 1; /// cin >> tests;
    while (tests--) UITShuriken();
 
    return 0;
}
