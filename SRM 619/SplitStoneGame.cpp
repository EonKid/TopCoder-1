#include <cstdio>
#include <cmath>
#include <cstring>
#include <ctime>
#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
#include <sstream>
#include <typeinfo>
#include <fstream>

using namespace std;

class SplitStoneGame {
public:
	int dp[51][51];

	int foo(int n, int m)
	{
		if (dp[n][m] != -1) return dp[n][m];
		if (n == m) return dp[n][m] = 0;
		if (n < 3) return dp[n][m] = 0;
		else
		{
			if (n - m >= 3 && foo(n - 1, m) == 0) return dp[n][m] = 1;
			if (n - m >= 2 && m >= 1 && foo(n - 1, m - 1) == 0) return dp[n][m] = 1;
			if (n - m >= 1 && m >= 2 && foo(n - 1, m - 2) == 0) return dp[n][m] = 1;
			return dp[n][m] = 0;
		}
	}

	int foo2(int n, int m)
	{
		if (n < 3) return 0;
		if (n == m) return 0;
		if (n % 2 == 1) return 1;
		return 0;
	}

	string winOrLose(vector<int> number) {
		srand((unsigned int)time(0));

		memset(dp, -1, sizeof(dp));
		int cnt = 0;
		int n = (int)number.size();
		for (int i = 0; i < n; i++)
			if (number[i] == 1)
				cnt++;
		int ret = foo2(n, cnt);
		if (ret == 1) return "WIN";
		return "LOSE";
	}
};

// CUT begin
ifstream data("SplitStoneGame.sample");

string next_line() {
    string s;
    getline(data, s);
    return s;
}

template <typename T> void from_stream(T &t) {
    stringstream ss(next_line());
    ss >> t;
}

void from_stream(string &s) {
    s = next_line();
}

template <typename T> void from_stream(vector<T> &ts) {
    int len;
    from_stream(len);
    ts.clear();
    for (int i = 0; i < len; ++i) {
        T t;
        from_stream(t);
        ts.push_back(t);
    }
}

template <typename T>
string to_string(T t) {
    stringstream s;
    s << t;
    return s.str();
}

string to_string(string t) {
    return "\"" + t + "\"";
}

bool do_test(vector<int> number, string __expected) {
    time_t startClock = clock();
    SplitStoneGame *instance = new SplitStoneGame();
    string __result = instance->winOrLose(number);
    double elapsed = (double)(clock() - startClock) / CLOCKS_PER_SEC;
    delete instance;

    if (__result == __expected) {
        cout << "PASSED!" << " (" << elapsed << " seconds)" << endl;
        return true;
    }
    else {
        cout << "FAILED!" << " (" << elapsed << " seconds)" << endl;
        cout << "           Expected: " << to_string(__expected) << endl;
        cout << "           Received: " << to_string(__result) << endl;
        return false;
    }
}

int run_test(bool mainProcess, const set<int> &case_set, const string command) {
    int cases = 0, passed = 0;
    while (true) {
        if (next_line().find("--") != 0)
            break;
        vector<int> number;
        from_stream(number);
        next_line();
        string __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(number, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1399287604;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 250 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
    }
    return 0;
}

int main(int argc, char *argv[]) {
    cout.setf(ios::fixed, ios::floatfield);
    cout.precision(2);
    set<int> cases;
    bool mainProcess = true;
    for (int i = 1; i < argc; ++i) {
        if ( string(argv[i]) == "-") {
            mainProcess = false;
        } else {
            cases.insert(atoi(argv[i]));
        }
    }
    if (mainProcess) {
        cout << "SplitStoneGame (250 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
