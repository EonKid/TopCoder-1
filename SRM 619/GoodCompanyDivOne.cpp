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

const int MAXN = 50;
const int MAXM = 50;

class GoodCompanyDivOne {
public:
	int nCourse;

	int C[MAXN][MAXM], mx[MAXN], my[MAXM], lx[MAXN], ly[MAXM];
	int ar[MAXN][MAXN][MAXN];

	int cx[MAXN], cy[MAXM];

	bool Path(int nGraph, int u)
	{
		mx[u] = 1;
		for (int i = 0; i < nGraph; i++)
			if (!my[i] && lx[u] + ly[i] == C[u][i])
			{
				my[i] = 1;
				if (cy[i] < 0 || Path(nGraph, cy[i]))
				{
					cx[u] = i;
					cy[i] = u;
					return 1;
				}
			}
		return 0;
	}

	void Modify(int nGraph)
	{
		int i, j, alpha = 2147483647;
		for (i = 0; i < nGraph; i++)
			for (j = 0; j < nGraph; j++)
				if (mx[i] && !my[j] && lx[i] + ly[j] - C[i][j] < alpha)
					alpha = lx[i] + ly[j] - C[i][j];
		for (i = 0; i < nGraph; i++)
			if (mx[i]) lx[i] -= alpha;
		for (i = 0; i < nGraph; i++)
			if (my[i]) ly[i] += alpha;
	}

	void Solve(int nGraph)
	{
		int i, j;
		memset(lx, 0, sizeof(lx));
		memset(ly, 0, sizeof(ly));
		for (i = 0; i < nGraph; i++)
			for (j = 0; j<nGraph; j++)
				if (C[i][j]>lx[i])
					lx[i] = C[i][j];
		memset(cx, -1, sizeof(cx));
		memset(cy, -1, sizeof(cy));
		for (i = 0; i < nGraph; i++)
		{
			if (cx[i] < 0)
			{
				memset(mx, 0, sizeof(mx));
				memset(my, 0, sizeof(my));
				while (!Path(nGraph, i))
				{
					Modify(nGraph);
					memset(mx, 0, sizeof(mx));
					memset(my, 0, sizeof(my));
				}
			}
		}
	}

	vector<int> superior;
	vector<int> training;
	vector<vector<int> > child;
	int nEmployee;

	int dp[50][50];

	int foo(int root, int course)
	{
		if (dp[root][course] != -1) return dp[root][course];

		for (int i = 0; i < max(nEmployee, nCourse); i++)
			for (int j = 0; j < max(nEmployee, nCourse); j++)
				ar[root][i][j] = -10000;

		ar[root][root][course] = training[course];
		int nChild = (int)child[root].size();
		for (int i = 0; i < nChild; i++)
			for (int j = 0; j < nCourse; j++)
			{
				if (j == course) continue;

				int maxval = 0;
				for (int k = 0; k < nCourse; k++)
				{
					if (k == j) continue;
					if (training[k] > maxval)
						maxval = training[k];
				}

				int val = foo(child[root][i], j);
				if (val != 0)
					ar[root][child[root][i]][j] = foo(child[root][i], j) + maxval;
			}

		memcpy(C, ar[root], sizeof(ar[root]));
		Solve(max(nEmployee, nCourse));

		int ret = training[course];
		bool unmatched = false;
		
		for (int i = 0; i < nChild; i++)
		{
			int node = child[root][i];
			if (C[node][cx[node]] == -10000)
			{
				//printf("%d %d %d %d\n", node, cx[node], C[node][cx[node]], root);
				unmatched = true;
			}
			ret += C[node][cx[node]];
		}

		if (!unmatched)
		{
			//printf("root = %d, course = %d, ret = %d\n", root, course, ret);
			return dp[root][course] = ret;
		}
		else
		{
			//printf("root = %d, course = %d, unmatched\n", root, course);
			return dp[root][course] = 0;
		}
	}

	int minimumCost(vector<int> _superior, vector<int> _training)
	{
		memset(dp, -1, sizeof(dp));
		superior = _superior;
		nEmployee = (int)superior.size();
		nCourse = (int)_training.size();
		training.clear(); 
		for (int i = 0; i < nCourse; i++)
			training.push_back(101 - _training[i]);

		child.clear();
		child.resize(nEmployee);
		for (int i = 1; i < (int)superior.size(); i++)
			child[superior[i]].push_back(i);

		int ret = 0;
		for (int i = 0; i < nCourse; i++)
		{
			int maxval = 0;
			for (int j = 0; j < nCourse; j++)
				if (training[j] > maxval && j != i)
					maxval = training[j];
			if (foo(0, i) + maxval > ret && foo(0, i) != 0)
				ret = foo(0, i) + maxval;
		}
		if (ret != 0)
			return 2 * nEmployee * 101 - ret;
		return -1;
	}
};

// CUT begin
ifstream data("GoodCompanyDivOne.sample");

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

bool do_test(vector<int> superior, vector<int> training, int __expected) {
    time_t startClock = clock();
    GoodCompanyDivOne *instance = new GoodCompanyDivOne();
    int __result = instance->minimumCost(superior, training);
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
        vector<int> superior;
        from_stream(superior);
        vector<int> training;
        from_stream(training);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(superior, training, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1399288718;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 600 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "GoodCompanyDivOne (600 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
