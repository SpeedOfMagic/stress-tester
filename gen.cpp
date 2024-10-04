#include "bits/stdc++.h"
#include <chrono>
#include <random>
using namespace std;
template<typename T> using v = vector<T>;
#define int long long
typedef double ld;
typedef string str;
typedef vector<int> vint;
#define rep(a, l, r) for(int a = (l); a < (r); a++)
#define pb push_back
#define fs first
#define sc second
#define sz(a) ((int) a.size())
const long long inf = 1000000000000000000;
const long double EPS = 1e-8;
#if 0  //FileIO
const string fileName = "";
ifstream fin((fileName == "" ? "input.txt" : fileName + ".in"));
ofstream fout((fileName == "" ? "output.txt" : fileName + ".out"));
#define get fin >>
#define put fout <<
#else
#define get cin >>
#define put cout <<
#endif
#define eol put endl
void read() {} template<typename Arg, typename... Args> void read(Arg& arg, Args& ... args) { get(arg);read(args...); }
void print() {} template<typename Arg, typename... Args> void print(Arg  arg, Args...  args) { put(arg) << " ";print(args...); }
int getInt() { int a; get a; return a; }

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int random(int l, int r) {
	return rng() % (r - l + 1) + l;
}


signed main() {
	cout << random(1, 3) << endl;
	return 0;
}