#include <cstdio>
#include <iostream>
#include <ctime>
#include <cstring>
#include <fstream>
#include <cstdlib>
#include <csignal>
#include <unistd.h>
#include "color.h"

using std::string;

#ifndef COMPATIBLE
#   include <readline/history.h>
#   include <readline/readline.h>
#else
    extern string readline(string prompt);
#endif


//constants
extern string version;
extern string branch;
extern const string config_dir;
extern const string data_dir;

//variable
extern string global_result;
extern int global_time1, global_time2;
extern int T, timelimit;
extern string dtm, sc1, sc2, prob, file, dtm_exc, sc1_exc, sc2_exc;
extern bool always_load, always_continue, always_quit, fast_mode, loaded;
extern int save_mode;
extern int general_mode;

//config.cpp
extern void store_data(int, string, string, string, string, int);
extern void load_data(int &T, string &data, string &sc1, string &sc2, string prob, int &time);
extern bool check_file(string prob);
extern int limited_run(string name, int time_limit, int memory_limit);

//tools.cpp
extern void clear_buffer();
extern long long myclock();
extern string tostring(int a);
extern int run(string s);
extern bool isdir(string filename);
extern void delline();
extern void bash_fail();

//myreadline.cpp
extern string readline(string prompt);

//quit.cpp
extern void quit(int signum);
extern void register_signal();
