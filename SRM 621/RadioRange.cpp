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

const double PI = acos(-1);
const double EPS = 1e-8;

#define eq(x,y) (fabs((x)-(y))<EPS)

struct Point
{
	double x, y;
	Point(double x0 = 0, double y0 = 0) :x(x0), y(y0){}
};

struct Circle
{
	Point c;
	double r;
};

double Dis(Point p1, Point p2)
{
	return sqrt((p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y));
}

class RadioRange {
public:
	double RadiusProbability(vector<int> X, vector<int> Y, vector<int> R, int Z)
	{
		int num = (int)X.size();
		double r1[100], r2[100];
		for (int i = 0; i < num; i++)
		{
			Point p1 = Point(X[i], Y[i]);
			Point p2 = Point(0, 0);
			double dist = Dis(p1, p2);

			r1[i] = dist - R[i];
			r2[i] = dist + R[i];
		}

		vector<double> v;
		v.clear();
		v.push_back(0);
		v.push_back(Z);

		for (int i = 0; i < num; i++)
		{
			if (r1[i] > 0)
				v.push_back(r1[i]);

			if (r2[i] > 0 && r2[i] <= Z)
				v.push_back(r2[i]);
		}

		sort(v.begin(), v.end());
		double ret = 0;

		for (int i = 0; i < (int)v.size() - 1; i++)
		{
			double mid = (v[i] + v[i + 1]) / 2;
			bool flag = true;
			for (int j = 0; j < num; j++)
			{
				bool valid = false;
				if (r1[j] > 0 && mid <= r1[j]) valid = true;
				if (r2[j] > 0 && r2[j] <= Z && mid >= r2[j]) valid = true;
				if (!valid)
				{
					flag = false;
					break;
				}
			}
			if (flag && mid <= Z)
				ret += (v[i + 1] - v[i]) / Z;
		}
		return ret;
	}
};

// CUT begin
ifstream data("RadioRange.sample");

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

bool do_test(vector<int> X, vector<int> Y, vector<int> R, int Z, double __expected) {
	time_t startClock = clock();
	RadioRange *instance = new RadioRange();
	double __result = instance->RadiusProbability(X, Y, R, Z);
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
		vector<int> X;
		from_stream(X);
		vector<int> Y;
		from_stream(Y);
		vector<int> R;
		from_stream(R);
		int Z;
		from_stream(Z);
		next_line();
		double __answer;
		from_stream(__answer);

		cases++;
		if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
			continue;

		cout << "  Testcase #" << cases - 1 << " ... ";
		if (do_test(X, Y, R, Z, __answer)) {
			passed++;
		}
	}
	if (mainProcess) {
		cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
		int T = time(NULL) - 1400598012;
		double PT = T / 60.0, TT = 75.0;
		cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
		cout << "Score  : " << 275 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
		cout << "RadioRange (275 Points)" << endl << endl;
	}
	return run_test(mainProcess, cases, argv[0]);
}
// CUT end
