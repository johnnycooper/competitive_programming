// Andrés Mejía

// Accepted.

// Complexity: O(n log n) when building the suffix array
//             O(n) with a stack after building the LCP array (this part is very similar to finding the maximum area under histogram problem).

// Some micro-optimizations and clean up, compared to file.6.cpp.

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

const int MAXN = 60 * 10005;

char text[MAXN];
namespace SuffixArray {
    int t, rank[MAXN], sa[MAXN], lcp[MAXN];

    bool compare(int i, int j){
        return rank[i + t] < rank[j + t];
    }
    
    void build(int n){
        const char * s = text;
        int bc[256];
        for (int i = 0; i < 256; ++i) bc[i] = 0;
        for (int i = 0; i < n; ++i) ++bc[s[i]];
        for (int i = 1; i < 256; ++i) bc[i] += bc[i-1];
        for (int i = 0; i < n; ++i) sa[--bc[s[i]]] = i;
        for (int i = 0; i < n; ++i) rank[i] = bc[s[i]];
        for (t = 1; t < n; t <<= 1){
            for (int i = 0, j = 1; j < n; i = j++){
                while (j < n && rank[sa[j]] == rank[sa[i]]) j++;
                if (j - i == 1) continue;
                int *start = sa + i, *end = sa + j;
                sort(start, end, compare);
                int first = rank[*start + t], num = i, k;
                for(; start < end; rank[*start++] = num){
                    k = rank[*start + t];
                    if (k != first and (i > first or k >= j))
                        first = k, num = start - sa;
                }
            }
        }

        // Remove this part if you don't need the LCP
        int size = 0, i, j;
        for(i = 0; i < n; i++) if (rank[i] > 0) {
            j = sa[rank[i] - 1];
            while(s[i + size] == s[j + size]) ++size;
            lcp[rank[i]] = size;
            if (size > 0) --size;
        }
        lcp[0] = 0;
    }
};


using namespace SuffixArray;
set< long long > seen;

int cnt[MAXN][60], F;
int who[MAXN], L[MAXN];

void add(int i, int j) {
    long long mask = 0;
    assert(i > 0);
    assert(i <= j);
    for (int k = 0; k < F; ++k) {
        if (cnt[j][k] - cnt[i - 1][k] > 0){
            mask |= (1LL << k);
        }
    }
    seen.insert(mask);
}

int main(){
    while (scanf("%d ", &F) == 1) {
        if (F == 0) break;
        //vector<string> files;
        int N = 0;
        text[N] = '\0';
        for (int i = 0; i < F; ++i) {
            scanf(" %s ", text + N);
            //files.push_back(string(buffer));
            int add = strlen(text + N);
            N += add;
            text[N++] = 'a' - i - 1;
            text[N] = '\0';
        }
        
        if (F == 1) {
            puts("1");
            continue;
        }

        SuffixArray::build(N);
        for (int i = 0; i + 1 < N; ++i) {
            lcp[i] = lcp[i + 1];
        }
        lcp[N - 1] = 0;

        for (int i = N - 1, k, len; i >= 0; --i) {
            if (text[i] < 'a') {
                len = 0;
                k = 'a' - text[i] - 1;
            } else {
                len++;
                L[rank[i]] = len;
                who[rank[i]] = k;
            }
        }
        
        for (int i = 0; i < F; ++i) cnt[0][i] = 0;
        cnt[0][who[0]]++;
        for (int i = 1; i < N; ++i){
            for (int j = 0; j < F; ++j) {
                cnt[i][j] = cnt[i - 1][j];
            }
            cnt[i][who[i]]++;
        }
        
     
        seen.clear();
        for (int i = F; i < N; ++i){
            if (lcp[i - 1] < L[i] and lcp[i] < L[i]) add(i, i);
        }
        stack< pair<int, int> > stk;
        for (int i = F; i < N; ++i) {
            int from = i;
            while (stk.size() > 0 and stk.top().second > lcp[i]) {
                add(stk.top().first, i);
                from = stk.top().first;
                stk.pop();
            }
            if (stk.empty() or lcp[i] > stk.top().second) {
                stk.push(make_pair(from, lcp[i]));
            }
        }
        assert(stk.size() > 0 and stk.top().second == 0);
        
        printf("%d\n", seen.size());
    }
    return 0;
}