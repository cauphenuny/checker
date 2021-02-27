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

using std::string;

//update.cpp
void start_update();
void start_forced_update();
void forced_update();
void auto_update();
void normal_exit(int signum);

//func.cpp
int run(std::string s);

//constants
extern string version;
extern string branch;
extern const string config_dir;
extern const string data_dir;
