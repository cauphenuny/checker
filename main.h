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
void store_data(int, string, string, string, string, int);
void load_data(int &T, string &data, string &sc1, string &sc2, string prob, int &time);
bool check_file(string prob);
int limited_run(string name, int time_limit, int memory_limit);

//func.cpp
void clear_buffer();
int run(string s);
bool isdir(string filename);
void bash_fail();

//myreadline.cpp
string readline(string prompt);

//analysis.cpp
void analysis_cmd(string cmd);
void analysis_long_cmd(string s, int &pos);
string getword(string s, int &pos);
void check_version();
void usage(int id);

//quit.cpp
void quit(int signum);
void register_signal();

//judge.cpp
void normal_judge();

//data.cpp
void create_data();
