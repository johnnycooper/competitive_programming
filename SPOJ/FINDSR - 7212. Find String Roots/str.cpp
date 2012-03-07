// Andrés Mejía
using namespace std;
#include <algorithm>
#include <iostream>
#include <iterator>
#include <numeric>
#include <sstream>
#include <fstream>
#include <cassert>
#include <climits>
#include <cstdlib>
#include <cstring>
#include <string>
#include <cstdio>
#include <vector>
#include <cmath>
#include <queue>
#include <deque>
#include <stack>
#include <list>
#include <map>
#include <set>

////////////// Prewritten code follows. Look down for solution. ////////////////
#define foreach(x, v) for (typeof (v).begin() x=(v).begin(); x !=(v).end(); ++x)
#define For(i, a, b) for (int i=(a); i<(b); ++i)
#define D(x) cout << #x " is " << (x) << endl

const double EPS = 1e-9;
int cmp(double x, double y = 0, double tol = EPS) {
    return (x <= y + tol) ? (x + tol < y) ? -1 : 0 : 1;
}
////////////////////////// Solution starts below. //////////////////////////////

const int MAXN = 100005;
int b[2 * MAXN];

int main(){
    string s;
    while (getline(cin, s) and s != "*") {
        int n = s.size();
        s += s;
        b[0] = 0;
        int ans = 0;
        for (int i = 1; i < 2*n; ++i) {
            b[i] = b[i - 1];
            while (b[i] > 0 and s[i] != s[b[i]]) b[i] = b[b[i] - 1];
            if (s[i] == s[b[i]]) b[i]++;
            if (b[i] >= n) {
                assert(n % (i - n + 1) == 0);
                printf("%d\n", n / (i - n + 1));
                break;
            }
        }
    }
    return 0;
}