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

class Family {
	int gr[110][110];
	int color[110];
	int n;
	bool valid;

	void dfs(int now, int c)
	{
		color[now] = c;
		for (int i = 0; i < n; i++)
			if (gr[now][i] == 1)
			{
				if (color[i] == -1)
					dfs(i, 1 - c);
				else if (color[i] == c)
					valid = false;
			}
	}

public:
	string isFamily(vector <int> parent1, vector <int> parent2)
	{
		memset(gr, 0, sizeof(gr));
		memset(color, -1, sizeof(color));
		int len = parent1.size();
		n = 0;
		valid = true;
		for (int i = 0; i < len; i++)
			if (parent1[i] != -1 && parent2[i] != -1)
			{
				if (parent1[i] + 1 > n) n = parent1[i] + 1;
				if (parent2[i] + 1 > n) n = parent2[i] + 1;
				gr[parent1[i]][parent2[i]] = 1;
				gr[parent2[i]][parent1[i]] = 1;
			}
		for (int i = 0; i < n; i++)
			if (color[i] == -1)
				dfs(i, 0);

		return valid ? "Possible" : "Impossible";
	}
};

// CUT begin
ifstream data("Family.sample");

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

bool do_test(vector<int> parent1, vector<int> parent2, string __expected) {
    time_t startClock = clock();
    Family *instance = new Family();
    string __result = instance->isFamily(parent1, parent2);
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
        vector<int> parent1;
        from_stream(parent1);
        vector<int> parent2;
        from_stream(parent2);
        next_line();
        string __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(parent1, parent2, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1398399481;
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
        cout << "Family (250 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
