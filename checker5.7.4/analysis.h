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
#include "color.h"

//update.cpp
void start_update();
void start_forced_update();
void forced_update();
void auto_update();
void normal_exit(int signum);

//main.cpp
extern bool always_load, always_continue, always_quit, fast_mode, loaded;
extern int save_mode;
extern int general_mode;
extern std::string branch;
extern std::string version;
