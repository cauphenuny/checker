#include <string>
#include <iostream>
#include <cstdio>
#include <unistd.h>
#include "color.h"

using std::string;

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

//func.cpp
extern void clear_buffer();
extern int run(string s);
extern bool isdir(string filename);
extern void bash_fail();

//myreadline.cpp
extern string readline(string prompt);

//analysis.cpp
extern void analysis_cmd(string cmd);
extern void analysis_long_cmd(string s, int &pos);
extern string getword(string s, int &pos);
extern void check_version();
extern void usage(int id);

//quit.cpp
extern void quit(int signum);
extern void register_signal();

//judge.cpp
extern void normal_judge();

//data.cpp
extern void create_data();
