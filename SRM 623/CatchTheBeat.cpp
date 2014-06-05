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

int x[500000], y[500000];

class CatchTheBeat {
    public:
    int maxCatched(int n, int x0, int y0, int a, int b, int c, int d, int mod1, int mod2, int offset) 
	{
		x[0] = x0;
		for (int i = 1; i < n; i++)
			x[i] = ((long long)x[i - 1] * a + b) % mod1;
		for (int i = 0; i < n; i++)
			x[i] -= offset;
		y[0] = y0;
		for (int i = 1; i < n; i++)
			y[i] = ((long long)y[i - 1] * c + d) % mod2;

		vector<pair<int, int> > A;
		for (int i = 0; i < n; i++)
			if (abs(x[i]) <= y[i])
				A.push_back(make_pair(x[i] + y[i], y[i] - x[i]));
		sort(A.begin(), A.end());
		int N = (int)A.size();

		vector<int> V;
		for (int i = 0; i < N; i++)
		{
			int pos = upper_bound(V.begin(), V.end(), A[i].second) - V.begin();
			if (pos == V.size())
				V.push_back(A[i].second);
			else
				V[pos] = A[i].second;
		}
		return V.size();
    }
};

// CUT begin
ifstream data("CatchTheBeat.sample");

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

template <typename T>
string to_string(T t) {
    stringstream s;
    s << t;
    return s.str();
}

string to_string(string t) {
    return "\"" + t + "\"";
}

bool do_test(int n, int x0, int y0, int a, int b, int c, int d, int mod1, int mod2, int offset, int __expected) {
    time_t startClock = clock();
    CatchTheBeat *instance = new CatchTheBeat();
    int __result = instance->maxCatched(n, x0, y0, a, b, c, d, mod1, mod2, offset);
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
        int n;
        from_stream(n);
        int x0;
        from_stream(x0);
        int y0;
        from_stream(y0);
        int a;
        from_stream(a);
        int b;
        from_stream(b);
        int c;
        from_stream(c);
        int d;
        from_stream(d);
        int mod1;
        from_stream(mod1);
        int mod2;
        from_stream(mod2);
        int offset;
        from_stream(offset);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(n, x0, y0, a, b, c, d, mod1, mod2, offset, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1401950210;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 450 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "CatchTheBeat (450 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
