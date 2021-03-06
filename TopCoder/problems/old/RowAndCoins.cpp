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

#define foreach(x, v) for (typeof (v).begin() x=(v).begin(); x !=(v).end(); ++x)
#define For(i, a, b) for (int i=(a); i<(b); ++i)
#define D(x) cout << #x " is " << x << endl

class RowAndCoins {
  public:
  string getWinner(string cells);

  
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const string &Expected, const string &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = "ABBB"; string Arg1 = "Alice"; verify_case(0, Arg1, getWinner(Arg0)); }
	void test_case_1() { string Arg0 = "BBBB"; string Arg1 = "Bob"; verify_case(1, Arg1, getWinner(Arg0)); }
	void test_case_2() { string Arg0 = "BA"; string Arg1 = "Alice"; verify_case(2, Arg1, getWinner(Arg0)); }
	void test_case_3() { string Arg0 = "BABBABBB"; string Arg1 = "Bob"; verify_case(3, Arg1, getWinner(Arg0)); }
	void test_case_4() { string Arg0 = "ABABBBABAABBAA"; string Arg1 = "Alice"; verify_case(4, Arg1, getWinner(Arg0)); }
	void test_case_5() { string Arg0 = "BBBAAABBAAABBB"; string Arg1 = "Bob"; verify_case(5, Arg1, getWinner(Arg0)); }

// END CUT HERE

};

vector<int> board;
int n;

int memo[1 << 14][2];

int f(int mask, int turn) {
    if (__builtin_popcount(mask) == n - 1) {
        for (int j = 0; j < n; ++j) {
            if (mask & (1 << j)) continue;
            return board[j];
        }
        assert(false);
    }
    
    if (memo[mask][turn] != -1) return memo[mask][turn];
    
    // It's my turn
    for (int i = 0; i < n; ++i) {
        if (mask & (1 << i)) continue;
        int new_mask = mask;
        for (int j = i; j < n; ++j) {
            if (mask & (1 << j)) continue;
            new_mask |= (1 << j);
            if (__builtin_popcount(new_mask) == n) continue;
            if (f(new_mask, !turn) == turn) {
                return memo[mask][turn] = turn;
            }
        }
    }

    return memo[mask][turn] = !turn;
}

string RowAndCoins::getWinner(string cells) {
    n = cells.size();
    board.resize(n);
    For(i, 0, n) board[i] = (cells[i] == 'B');
    memset(memo, -1, sizeof memo);
    int ans = f(0, 0);
    return ans == 0 ? "Alice" : "Bob";
}

// BEGIN CUT HERE
int main(){
    RowAndCoins ___test;
    ___test.run_test(-1);
    return 0;
}
// END CUT HERE
