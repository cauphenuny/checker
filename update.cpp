/* * * * * * * * * * * * * * * * * * * * * * * * *
 * author: ycpedef | https://ycpedef.github.io   *
 * email: ycpedef@foxmail.com                    *
 * Copyright ycpedef 2020-2021.                  *
 * * * * * * * * * * * * * * * * * * * * * * * * */
#include "update.h"
using namespace std;

void normal_exit(int signum) {
    exit(0);
}

void auto_update() {
    run("~/.ycpedef_checker_update/auto_update.sh " + branch);
}

void start_update() {
    signal(SIGTERM, normal_exit);
    atexit(auto_update);
    exit(0);
}

void forced_update() {
    run("~/.ycpedef_checker_update/forced_update.sh " + branch);
}

void start_forced_update() {
    signal(SIGTERM, normal_exit);
    atexit(forced_update);
    exit(0);
}

