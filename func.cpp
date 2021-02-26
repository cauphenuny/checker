/* * * * * * * * * * * * * * * * * * * * * * * * *
 * author: ycpedef | https://ycpedef.github.io   *
 * email: ycpedef@foxmail.com                    *
 * Copyright ycpedef 2020-2021.                  *
 * * * * * * * * * * * * * * * * * * * * * * * * */
#include "func.h"
using namespace std;

#define COMPATIBLE

#ifndef COMPATIBLE
#   include <readline/history.h>
#   include <readline/readline.h>
#else
    std::string readline(std::string prompt) {
        printf("%s", prompt.c_str());
        std::string res;
        std::cin >> res;
        return res;
    }
#endif

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

#define VMRSS_LINE 21  // VMRSS所在行, 注:根据不同的系统,位置可能有所区别.
#define pid_t int
int get_memory_by_pid(pid_t p) {
    FILE* fd;
    char name[32], line_buff[256] = {0}, file[64] = {0};
    int i, vmrss = 0;
    sprintf(file, "/proc/%d/status", p);
    // 以R读的方式打开文件再赋给指针fd
    fd = fopen(file, "r");
    if (fd == NULL) {
        return -1;
    }
    // 读取VmRSS这一行的数据
    for (i = 0; i < 40; i++) {
        if (fgets(line_buff, sizeof(line_buff), fd) == NULL) {
            break;
        }
        if (strstr(line_buff, "VmRSS:") != NULL) {
            sscanf(line_buff, "%s %d", name, &vmrss);
            break;
        }
    }
    fclose(fd);
    return vmrss;
}

int get_total_mem() {
    const char* file = "/proc/meminfo";  // 文件名
    FILE* fd;
    // 定义文件指针fd
    char line_buff[256] = {0};  // 读取行的缓冲区
    fd = fopen(file, "r");  // 以R读的方式打开文件再赋给指针fd
    // 获取memtotal:总内存占用大小
    int i;
    char name[32];  // 存放项目名称
    int memtotal;  // 存放内存峰值大小
    char* ret = fgets(line_buff, sizeof(line_buff), fd);  // 读取memtotal这一行的数据,memtotal在第1行
    sscanf(line_buff, "%s %d", name, &memtotal);
    fprintf(stderr, "====%s：%d====\n", name, memtotal);
    fclose(fd);
    // 关闭文件fd
    return memtotal;
}
