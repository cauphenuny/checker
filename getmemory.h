#ifndef GETMEMORY_H
#define GETMEMORY_H
// getmemory.h
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
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
#endif
