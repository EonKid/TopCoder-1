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
#include <climits>
using namespace std;

int gr[51][51];
int prevNode[51][51];
int firstNode[51][51];

class Egalitarianism3
{
public:
	int maxCities(int n, vector<int> a, vector<int> b, vector<int> len)
	{
		if (n <= 2) return n;
		int best = 2;

		for (int i = 1; i <= 50; i++)
		{
			for (int j = 1; j <= 50; j++)
			{
				gr[i][j] = INT_MAX;
				prevNode[i][j] = i;
			}
			gr[i][i] = 0;
		}
		for (int i = 0; i < n - 1; i++)
			gr[a[i]][b[i]] = gr[b[i]][a[i]] = len[i];
		for (int k = 1; k <= n; k++)
		{
			for (int i = 1; i <= n; i++)
			{
				for (int j = 1; j <= n; j++)
				{
					if (gr[i][k] < INT_MAX && gr[k][j] < INT_MAX && gr[i][k] + gr[k][j] < gr[i][j])
					{
						gr[i][j] = gr[i][k] + gr[k][j];
						prevNode[i][j] = k;
					}
				}
			}
		}

		for (int i = 1; i <= n; i++)
		{
			for (int j = 1; j <= n; j++)
			{
				int curr = j;
				while (prevNode[i][curr] != i)
					curr = prevNode[i][curr];
				firstNode[i][j] = curr;
			}
		}

		for (int root = 1; root <= n; root++)
		{
			for (int i = 1; i <= n; i++)
			{
				set<int> s;
				s.clear();

				int cnt = 0;
				for (int j = 1; j <= n; j++)
				{
					if (gr[root][j] == gr[root][i] && s.find(firstNode[root][j]) == s.end())
					{
						s.insert(firstNode[root][j]);
						cnt++;
					}
				}
				if (cnt > best)
					best = cnt;
			}
		}
		return best;
	}
};

// CUT begin
ifstream data("Egalitarianism3.sample");

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

bool do_test(int n, vector<int> a, vector<int> b, vector<int> len, int __expected) {
	time_t startClock = clock();
	Egalitarianism3 *instance = new Egalitarianism3();
	int __result = instance->maxCities(n, a, b, len);
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
		vector<int> a;
		from_stream(a);
		vector<int> b;
		from_stream(b);
		vector<int> len;
		from_stream(len);
		next_line();
		int __answer;
		from_stream(__answer);

		cases++;
		if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
			continue;

		cout << "  Testcase #" << cases - 1 << " ... ";
		if (do_test(n, a, b, len, __answer)) {
			passed++;
		}
	}
	if (mainProcess) {
		cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
		int T = time(NULL) - 1408669286;
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
		cout << "Egalitarianism3 (250 Points)" << endl << endl;
	}
	return run_test(mainProcess, cases, argv[0]);
}
// CUT end
