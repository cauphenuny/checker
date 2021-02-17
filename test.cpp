//author: ycp | https://ycpedef.github.io
//#pragma GCC diagnostic error "-std=c++11"
//#pragma GCC optimize(2)
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdarg>
#include <cstdio>
#include <iostream>
#include <ctime>
#include <cstring>
#include <fstream>
#include <cstdlib>
#include <csignal>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#define debug(x) cerr << #x << " = " << x << endl
#define debugf(...) fprintf(stderr, __VA_ARGS__)
#define debugs(x) fputs(x"\n", stderr)
using namespace std;
template <class T> bool cmax(T &a, T b) { return b > a ? (a = b, 1) : 0; }
template <class T> bool cmin(T &a, T b) { return b < a ? (a = b, 1) : 0; }
template <class T> void read(T &a) {
    a = 0; char c = getchar(); int f = 0;
    while (!isdigit(c)) { f ^= c == '-',  c = getchar(); }
    while (isdigit(c)) { a = a * 10 + (c ^ 48),  c = getchar(); }
    a *= f ? -1 : 1;
}
struct Fastin {
    template <class T> Fastin& operator >> (T &x) {read(x); return *this;}
} fastin;

int main() {
    cout << access(".git/", F_OK) << endl;
    return 0;
}

