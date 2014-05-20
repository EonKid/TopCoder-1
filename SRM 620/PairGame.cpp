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

class PairGame {
public:
	int gcd(int a, int b)
	{
		if (b == 0) return a;
		return gcd(b, a%b);
	}

	int maxSum(int a, int b, int c, int d) {
		if (gcd(a, b) != gcd(c, d)) return -1;
		while (true)
		{
			if (a == c && b == d) return a + b;
			else
			{
				if (a >= b && a >= c && a >= d) a -= b;
				else if (b >= a && b >= c && b >= d) b -= a;
				else if (c >= a && c >= b &&c >= d) c -= d;
				else d -= c;
			}
		}
	}
};

// CUT begin
ifstream data("PairGame.sample");

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

bool do_test(int a, int b, int c, int d, int __expected) {
	time_t startClock = clock();
	PairGame *instance = new PairGame();
	int __result = instance->maxSum(a, b, c, d);
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
		int a;
		from_stream(a);
		int b;
		from_stream(b);
		int c;
		from_stream(c);
		int d;
		from_stream(d);
		next_line();
		int __answer;
		from_stream(__answer);

		cases++;
		if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
			continue;

		cout << "  Testcase #" << cases - 1 << " ... ";
		if (do_test(a, b, c, d, __answer)) {
			passed++;
		}
	}
	if (mainProcess) {
		cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
		int T = time(NULL) - 1399742018;
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
		if (string(argv[i]) == "-") {
			mainProcess = false;
		}
		else {
			cases.insert(atoi(argv[i]));
		}
	}
	if (mainProcess) {
		cout << "PairGame (250 Points)" << endl << endl;
	}
	return run_test(mainProcess, cases, argv[0]);
}
// CUT end