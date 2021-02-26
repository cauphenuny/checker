#include "tools.h"
using namespace std;

bool isdir(string filename) {
    struct stat s_buf;
    stat(filename.c_str(), &s_buf);
    return S_ISDIR(s_buf.st_mode);
}

void clear_buffer() {
    setbuf(stdin, nullptr);
}

long long myclock() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

std::string tostring(int a) {
    char s[256];
    memset(s, 0, sizeof(s));
    int tot = 0;
    while (a > 0) {
        s[tot] = (a % 10) + '0';
        tot++;
        a /= 10;
    }
    for (int i = 0; i < (tot / 2); i++) {
        std::swap(s[i], s[tot - 1 - i]);
    }
    return s;
}

int run(std::string s) {
    return system(s.c_str());
}

void delline() {
    printf("\e[2A");
    printf("\e[K");
}

void bash_fail() {
    puts(L_RED"\nFailed");
    exit(0);
}

