#include <cstdio>
#include <iostream>
#include <ctime>
#include <cstring>
#include <fstream>
#include <cstdlib>
#include <csignal>
#include <unistd.h>
#include <map>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include "color.h"

using std::string;

//func.cpp
extern void clear_buffer();
extern long long myclock();
extern std::string tostring(int a);
extern int run(std::string s);
extern bool isdir(std::string filename);
extern void delline();
extern void bash_fail();

//myreadline.cpp
extern std::string readline(std::string prompt);

//update.cpp
extern void start_update();
extern void start_forced_update();
extern void forced_update();
extern void auto_update();
extern void normal_exit(int signum);

//constants
extern std::string version;
extern std::string branch;
extern const std::string config_dir;
extern const std::string data_dir;

//command.cpp
extern bool analysis_key_value(string, string &key, string &value, int = 0);
