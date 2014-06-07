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

class SwitchingGame {
public:
	int timeToWin(vector<string> states)
	{
		int nr = (int)states.size();
		int nc = (int)states[0].size();

		char curr[50];
		for (int i = 0; i < nc; i++)
			curr[i] = '-';

		int ret = 0;
		for (int r = 0; r < nr; r++)
		{
			bool f1 = false, f2 = false;

			for (int c = 0; c < nc; c++)
			{
				if (states[r][c] == '+' && curr[c] == '-') f1 = true;
				if (states[r][c] == '-' && curr[c] == '+') f2 = true;
			}
			if (f1)
			{
				for (int c = 0; c < nc; c++)
				{
					if (states[r][c] == '+' && curr[c] == '-') curr[c] = '+';
					if (states[r][c] == '-') continue;
					int tmp = r;
					while (tmp < nr && states[tmp][c] == '?') tmp++;
					if (tmp < nr && states[tmp][c] == '+') curr[c] = '+';
				}
				ret++;
			}
			if (f2)
			{
				for (int c = 0; c < nc; c++)
				{
					if (states[r][c] == '-' && curr[c] == '+') curr[c] = '-';
					if (states[r][c] == '+') continue;
					int tmp = r;
					while (tmp < nr && states[tmp][c] == '?') tmp++;
					if (tmp < nr && states[tmp][c] == '-') curr[c] = '-';
				}
				ret++;
			}
		}

		return ret + nr;
	}
};

// CUT begin
ifstream data("SwitchingGame.sample");

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

bool do_test(vector<string> states, int __expected) {
    time_t startClock = clock();
    SwitchingGame *instance = new SwitchingGame();
    int __result = instance->timeToWin(states);
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
        vector<string> states;
        from_stream(states);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(states, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1402164426;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 350 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "SwitchingGame (350 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
