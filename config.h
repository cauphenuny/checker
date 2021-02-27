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

//config.cpp
extern void store_data(int, std::string, std::string, std::string, std::string, int);
extern void load_data(int &T, std::string &data, std::string &sc1, std::string &sc2, std::string prob, int &time);
extern bool check_file(std::string prob);
extern int limited_run(std::string name, int time_limit, int memory_limit);

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
