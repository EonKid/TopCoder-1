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

const int MAXN = 5000000;
bool isprime[MAXN + 1];
bool valid[MAXN + 1];

void sieve()
{
	memset(isprime, true, sizeof(isprime));
	isprime[0] = isprime[1] = false;
	for (int i = 2; i <= 5000000; i++)
	{
		if (isprime[i])
		{
			for (int j = i + i; j <= 5000000; j += i)
				isprime[j] = false;
		}
	}
}

class SumAndProductPuzzle {
public:
	long long getSum(int A, int B)
	{
		sieve();
		memset(valid, true, sizeof(valid));

		valid[1] = valid[2] = false;

		for (int i = 1; i <= 5000000; i++)
			if (isprime[i - 1])
				valid[i] = false;

		for (int i = 2; i * i <= MAXN; i++)
			for (int j = i; i*j <= MAXN; j++)
				if (!isprime[i + j - 1] && i * j + 1 <= MAXN)
					valid[i*j + 1] = false;
		
		long long ret = 0;
		for (int i = A; i <= B; i++)
			if (valid[i])
				ret += i;
		return ret;
	}
};

// CUT begin
ifstream data("SumAndProductPuzzle.sample");

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

bool do_test(int A, int B, long long __expected) {
    time_t startClock = clock();
    SumAndProductPuzzle *instance = new SumAndProductPuzzle();
    long long __result = instance->getSum(A, B);
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
        int A;
        from_stream(A);
        int B;
        from_stream(B);
        next_line();
        long long __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(A, B, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1402166173;
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
        if ( string(argv[i]) == "-") {
            mainProcess = false;
        } else {
            cases.insert(atoi(argv[i]));
        }
    }
    if (mainProcess) {
        cout << "SumAndProductPuzzle (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
