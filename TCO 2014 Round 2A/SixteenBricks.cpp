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

const int dx[4] = { -1, 1, 0, 0 };
const int dy[4] = { 0, 0, -1, 1 };

class SixteenBricks {
public:
	int tmp[6][6];

	int surface(vector<int> v)
	{
		memset(tmp, 0, sizeof(tmp));
		int nv = 0;
		for (int i = 1; i <= 4; i++)
			for (int j = 1; j <= 4; j++)
				tmp[i][j] = v[nv++];
		int ret = 0;
		for (int i = 1; i <= 4; i++)
			for (int j = 1; j <= 4; j++)
			{
				for (int d = 0; d < 4; d++)
				{
					int ni = i + dx[d];
					int nj = j + dy[d];
					if (tmp[i][j] > tmp[ni][nj])
						ret += tmp[i][j] - tmp[ni][nj];
				}
			}
		ret += 16;
		return ret;
	}

	vector<int> construct(int small[], int big[], int vs[], int vb[])
	{
		vector<int> ret;
		ret.resize(16);
		fill(ret.begin(), ret.end(), 0);
		ret[5] = vb[1], ret[10] = vb[0];
		ret[6] = vs[0], ret[9] = vs[1];
		ret[0] = big[0], ret[2] = big[1], ret[7] = big[2], ret[8] = big[3], ret[13] = big[4], ret[15] = big[5];
		int ns = 0;
		for (int i = 0; i < 16; i++)
			if (ret[i] == 0)
				ret[i] = small[ns++];
		return ret;
	}

	int maximumSurface(vector<int> height)
	{
		sort(height.begin(), height.end());
		int small[7];
		int big[7];
		int vs[2] = { height[0], height[1] };
		int vb[2] = { height[14], height[15] };
		for (int i = 2; i < 8; i++)
			small[i - 2] = height[i];
		for (int i = 8; i < 14; i++)
			big[i - 8] = height[i];
		int ans = 0;
		do
		{
			do
			{
				vector<int> tmp = construct(small, big, vs, vb);
				int ret = surface(tmp);
				if (ret > ans)
					ans = ret;
			} while (next_permutation(big, big + 6));
		} while (next_permutation(small, small + 6));
		return ans;
	}
};

// CUT begin
ifstream data("SixteenBricks.sample");

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

bool do_test(vector<int> height, int __expected) {
    time_t startClock = clock();
    SixteenBricks *instance = new SixteenBricks();
    int __result = instance->maximumSurface(height);
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
        vector<int> height;
        from_stream(height);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(height, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1400342410;
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
        cout << "SixteenBricks (250 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
