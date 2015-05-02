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

class TheTips {
public:
	int gr[50][50];

	double solve(vector<string> clues, vector<int> probability)
	{
		int n = clues.size();
		memset(gr, 0, sizeof(gr));
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
				if (clues[i][j] == 'Y')
					gr[i][j] = 1;
			gr[i][i] = 1;
		}
		for (int k = 0; k < n; k++)
			for (int i = 0; i < n; i++)
				for (int j = 0; j < n; j++)
					if (gr[i][k] == 1 && gr[k][j] == 1)
						gr[i][j] = 1;
		double ans = 0;
		for (int i = 0; i < n; i++)
		{
			double prod = 1;
			for (int j = 0; j < n; j++)
				if (gr[j][i] == 1)
					prod *= (1 - 1.0 * probability[j] / 100);
			double p = 1 - prod;
			ans += p;
		}
		return ans;
	}
};

// CUT begin
ifstream data("TheTips.sample");

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

bool double_equal(const double &a, const double &b) { return b == b && a == a && fabs(b - a) <= 1e-9 * max(1.0, fabs(a)); }

bool do_test(vector<string> clues, vector<int> probability, double __expected) {
	time_t startClock = clock();
	TheTips *instance = new TheTips();
	double __result = instance->solve(clues, probability);
	double elapsed = (double)(clock() - startClock) / CLOCKS_PER_SEC;
	delete instance;

	if (double_equal(__expected, __result)) {
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
		vector<string> clues;
		from_stream(clues);
		vector<int> probability;
		from_stream(probability);
		next_line();
		double __answer;
		from_stream(__answer);

		cases++;
		if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
			continue;

		cout << "  Testcase #" << cases - 1 << " ... ";
		if (do_test(clues, probability, __answer)) {
			passed++;
		}
	}
	if (mainProcess) {
		cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
		int T = time(NULL) - 1429978126;
		double PT = T / 60.0, TT = 75.0;
		cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
		cout << "Score  : " << 500 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
		cout << "TheTips (500 Points)" << endl << endl;
	}
	return run_test(mainProcess, cases, argv[0]);
}
// CUT end
