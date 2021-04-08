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
}

void start_update() {
    exit(0);
}

void forced_update() {
    run("/tmp/checker/update/update.sh " + branch);
}

void start_forced_update() {
    //signal(SIGTERM, normal_exit);
    atexit(forced_update);
    exit(0);
}

